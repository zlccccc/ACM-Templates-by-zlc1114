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
const LL M=1e9+7;
const LL maxn=3e5+107;
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

int n,more;
vector<pii> ox_edge[maxn*2];
// https://codeforces.com/contest/1389/problem/G
// 原题题意略过, 知道这个板子是用来建树的即可
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
                    // int nowid=x;
                    while (1) {
                        int id=S[top--];
                        eid.push_back(id);
                        // nowid^=e[id].u^e[id].v; //only for 仙人掌
                        pid.push_back(e[id].u);//last
                        pid.push_back(e[id].v);//last
                        // debug("mapping: (%d,%d) (maybe not a circle)\n",e[id].u,e[id].v);
                        if (id==edge[i].id) break;
                    } sort(pid.begin(),pid.end());
                    pid.erase(unique(pid.begin(),pid.end()),pid.end());
                    if (low[v]==dfn[x]) { //双联通, 在这里dp
                        deputs(" circle :");//环, eid; pid
                        int nowid=n+(++more);
                        // for (int v:pid) debug("%d ",v); deputs(" <- link");
                        for (int v:pid) {
                            ox_edge[nowid].push_back(make_pair(0,v));
                            ox_edge[v].push_back(make_pair(0,nowid));
                        }
                    } else {
                        deputs(" tree :");
                        for (int _=0; _<(int)eid.size(); _++) {
                            int noweid=eid[_];
                            edges nowe=e[noweid];
                            debug("e: (%d-%d) %d : %d\n",nowe.u,nowe.v,pid[_],nowe.len);
                            ox_edge[nowe.u].push_back(make_pair(nowe.len,nowe.v));
                            ox_edge[nowe.v].push_back(make_pair(nowe.len,nowe.u));
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
        FOR(i,1,n) if (!dfn[i]) tarjan(i,0);
    }
}
inline int isRect(int x) {return x>n;}

int k;
int must[maxn*2];
ll downsum[maxn*2];
int c[maxn*2];
void dfs_up(int x,int fa) {
    for (auto &e:ox_edge[x]) {
        int l=e.first,v=e.second;
        if (v==fa) continue;//tree
        dfs_up(v,x);
        ll nowsum=downsum[v];
        if ((k-must[v])&&must[v]) nowsum-=l;//must use it; link it
        max_(nowsum,0ll);//must up
        downsum[x]+=nowsum;
        must[x]+=must[v];
    } downsum[x]+=c[x];
    // printf("%d : %lld\n",x,downsum[x]);
}
void dfs_down(int x,int fa) {
    for (auto &e:ox_edge[x]) {
        int l=e.first,v=e.second;
        if (v==fa) continue;//tree
        ll nowsum=downsum[v];
        if ((k-must[v])&&must[v]) nowsum-=l;
        max_(nowsum,0ll);
        ll noww=downsum[x]-nowsum;//from top
        if ((k-must[v])&&must[v]) noww-=l;//must use it; link it
        max_(noww,0ll);//must up
        downsum[v]+=noww;
        dfs_down(v,x);
    }
    // printf("%d : %lld\n",x,downsum[x]);
}
int main() {
    int i,m,t;
    scanf("%d%d%d",&n,&m,&k);
    FOR(i,1,k) scanf("%d",&t),must[t]=1;
    FOR(i,1,n) scanf("%d",&c[i]);
    FOR(i,1,m) scanf("%d",&e[i].len);
    FOR(i,1,m) scanf("%d%d",&e[i].u,&e[i].v);
    tarjan::init(n,m);
    dfs_up(1,0);
    dfs_down(1,0);
    FOR(i,1,n) printf("%lld%c",downsum[i]," \n"[i==n]);
    // printf("%d\n",ans);
}
/*
6 12 4
3 2 1 4
2 7 9 6 1 9
4 0 3 4 5 1 1 4 5 1 3 5
1 2
1 3
1 4
1 5
1 6
2 3
2 5
2 6
3 4
3 5
4 6
5 6

*/