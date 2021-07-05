#include <sstream>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
#include <cassert>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG1
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=1e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

// 题意: 仙人掌, 从1号点开始选
// 如果存在u-v且u在某轮选了, v在下一轮选择概率w
// 求期望概率p. 做法是p=1-p1p2...-pipi+1...
// 然后仙人掌dp即可
// 注意一下方向
struct edges {
    int u,v,len;
} e[maxn];
// vector<edges> E;
namespace tarjan { // 边双连通分量, 这里是在做仙人掌
    struct Edge {
        int to,next,id;
        Edge(int _to=0,int _next=-1,int _id=0):to(_to),next(_next),id(_id) {};
    } edge[maxn*2];
    int head[maxn],etot;
    inline void addedge(int u,int v,int id) {
        edge[++etot]=Edge(v,head[u],id); head[u]=etot;
    }
    int dfn[maxn],low[maxn],tot;
    bool vis[maxn],used[maxn];
    int S[maxn],top;
    int value[maxn];//to_lower
    void tarjan(int x,int fa) {
        low[x]=dfn[x]=++tot; vis[x]=1;
        value[x]=1;
        for (int i=head[x]; ~i; i=edge[i].next) {
            int v=edge[i].to;
            if (used[edge[i].id]) continue;
            if (v==fa) continue;
            S[++top]=edge[i].id;
            used[edge[i].id]=1;
            if (!dfn[v]) {
                tarjan(v,x);
                low[x]=min(low[x],low[v]);
                if (dfn[x]<=low[v]) { //割边和边双联通
                    vector<int> eid,pid,basp;
                    int nowid=x;
                    while (1) {
                        int id=S[top--];
                        eid.push_back(id);
                        nowid^=e[id].u^e[id].v;
                        pid.push_back(nowid);//last
                        basp.push_back(1);//msut; 得正反分别一遍
                        debug("mapping: %d: (%d,%d)\n",nowid,e[id].u,e[id].v);
                        if (id==edge[i].id) break;
                    } if (low[v]==dfn[x]) { //双联通, 在这里dp
                        deputs(" circle :");//环, eid; pid
                        ll nowp=1;
                        for (int _=0; _<(int)eid.size()-1; _++) {//正
                            int noweid=eid[_];
                            edges nowe=e[noweid];
                            nowp=nowp*nowe.len%M;
                            basp[_]=nowp;
                            debug("e: (%d-%d) : %d\n",nowe.u,nowe.v,nowe.len);
                        } nowp=1;
                        for (int _=eid.size()-2; _>=0; _--) {//倒着
                            int noweid=eid[_+1];
                            edges nowe=e[noweid];
                            nowp=nowp*nowe.len%M;
                            ll base=M+1-(M+1-nowp)*(M+1-basp[_])%M;//*oth[i]
                            add_(value[x],value[pid[_]]*base%M);
                            debug("e(2): (%d-%d) %d : %d\n",nowe.u,nowe.v,pid[_],nowe.len);
                        }
                    } else {
                        deputs(" tree :");
                        for (int _=0; _<(int)eid.size(); _++) {
                            int noweid=eid[_];
                            edges nowe=e[noweid];
                            add_(value[x],value[pid[_]]*nowe.len%M);
                            debug("e: (%d-%d) %d : %d\n",nowe.u,nowe.v,pid[_],nowe.len);
                            // E.push_back(e[now]);//割边
                        }
                    }
                    debug("%d %d\n",low[v],dfn[x]);
                }
            } else if (vis[v])
                low[x]=min(low[x],dfn[v]);
        }
    }
    void init(int n,int m) {
        int i;
        FOR(i,1,m) used[i]=0;
        FOR(i,1,n) head[i]=-1,dfn[i]=0; etot=tot=0;
        FOR(i,1,m) addedge(e[i].u,e[i].v,i),addedge(e[i].v,e[i].u,i);
        // FOR(i,1,n) if (!dfn[i]) tarjan(i,0);
    }
}

int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) {
        int n,m,i;
        scanf("%d%d",&n,&m);
        FOR(i,1,m) {
            int a,b;
            scanf("%d%d%d%d",&e[i].u,&e[i].v,&a,&b);
            e[i].len=a*powMM(b,M-2)%M;
        } tarjan::init(n,m);
        tarjan::tarjan(1,0);
        ll Ans=tarjan::value[1];
        printf("Case #%d: %lld\n",_,Ans);
    }
}
/*
10
2 1
1 2 1 2
3 4
1 2 1 3
2 3 1 2
3 1 1 4
1 4 1 5
3 3
1 2 1 2
2 3 1 2
3 1 1 2
*/