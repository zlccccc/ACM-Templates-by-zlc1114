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

#define DEBUG
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

namespace O {
    const int maxn=1e5+7;
    const int maxm=1e5+7;
    struct Edge {//id,pre!=0;uid:替换
        int u,v,len;//id->usedID(new),用于新建边
        Edge(int _u=0,int _v=0,int _len=0):
            u(_u),v(_v),len(_len) {}
    } edge[maxm]; int etot;
    void init() {etot=0;}
    void addedge(int u,int v,int len) {
        edge[++etot]=Edge(u,v,len);
    }
    struct _info {//pre为preuid
        int pre,len,eid;//position(id) and length
        void init(int _pre,int _len,int _eid){
            pre=_pre; len=_len; eid=_eid;
        }
    } Info[maxn*2];
    //id:circle_id(father);top:tree_anc
    inline int getfa(int fa[],int x) {
        if (fa[x]==x) return x;
        return fa[x]=getfa(fa,fa[x]);
    } int id[maxn*2],top[maxn*2];//并查集;
    int idfa[maxn*2],useid[maxn*2];//changes_fa
    int used[maxm];//output; 记录edge
    int solve(int root,int n) {
        int ret=0,i,lastnid=n;
        FOR(i,1,n) id[i]=top[i]=i,Info[i].len=INF;
        FOR(i,1,etot) { //initialize
            Edge &e=edge[i];
            if (e.u!=e.v&&e.len<Info[e.v].len)
                Info[e.v].init(e.u,e.len,i);
        }
        FOR(i,1,lastnid) {
            if (i==root) continue;
            if (Info[i].len==INF) return -1;
            _info &info=Info[i];
            int f=getfa(top,info.pre);
            //choose; 之后再更新
            useid[i]++; ret+=info.len; idfa[i]=i;
            if (f==i) {//circle
                int k; ++lastnid; Info[lastnid].len=INF;
                top[lastnid]=id[lastnid]=lastnid;
                for (int x=getfa(id,info.pre); ;x=getfa(id,Info[x].pre)) {
                    FOR(k,1,etot) {
                        Edge &e=edge[k];
                        if (k==info.eid) e.len=INF;
                        if (e.len==INF) continue;//removed
                        if (getfa(id,e.v)==x) //must_ok
                            e.len-=Info[x].len;
                    }
                    //use and delete
                    id[x]=top[x]=idfa[x]=lastnid;//缩环
                    if (x==i) break;
                } //update edges
                FOR(k,1,etot) {
                    Edge &e=edge[k];
                    if (e.len==INF) continue;//removed
                    if (getfa(id,e.v)==lastnid) {//must_ok
                        if (getfa(id,e.u)!=lastnid&&e.len<Info[lastnid].len)
                            Info[lastnid].init(e.u,e.len,k);//直接这样应该ok?
                    }
                }
            } else top[getfa(id,i)]=info.pre;//getfa=getid
        }
        rFOR(i,1,lastnid) if (useid[i]) {//remove_to_top
            static int ids[maxn];
            int x=0,k;
            for (int k=edge[Info[i].eid].v;k!=i;k=idfa[k]) ids[x++]=k;
            REP(k,x) idfa[ids[k]]=i,useid[ids[k]]=0;
            used[Info[i].eid]=1;
        }
        return ret;
    }
}
int ini[maxn];
int n,m,i;
int u,v,w;
int main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    scanf("%d%d",&n,&m);
    O::init();
    FOR(i,1,m) {
        if (scanf("%d%d%d",&u,&v,&w)!=3) {
            puts("input not right"); 
            return 0;
        };
        ini[i]=w;
        O::addedge(u,v,w);
        O::addcheck_edge_check(u,v,i);
    }
    int ans=O::solve(1,n);
    printf("%d\n",ans);
    if (ans!=-1) {
        O::bfs(1,n);
        FOR(i,1,m) if (ini[i]&&O::used[i])
            printf("%d ",i),ans--;
        if (ans) printf("\n%d\n",ans);
    }
}
/*
*/
