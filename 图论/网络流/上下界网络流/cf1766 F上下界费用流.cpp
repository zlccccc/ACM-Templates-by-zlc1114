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
#include <functional>
#include <random>
#include <unordered_set>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

// #define DEBUG
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
// ll M=1;
const LL maxn=4e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T fastgcd(T a, T b) {
    int az=__builtin_ctz(a),bz=__builtin_ctz(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctz(diff);
        min_(b,a); a=abs(diff);
    }
    return b<<z;
}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

// limit: real_cap&1 == cap&1 (cap和real奇偶性相同)
// cap拆奇数连边,其他cap/2,cost*2,只有两个位置ind可以是奇数(1和n)
// 2->n-1的位置可以直接新建s和t连边ind/2,网络流就一致是偶数了
// 1->n可以随便走,那么添加一个n->1,0->inf的边即可
// 跑个上下界费用流即可;有负环
// 负环处理方式:
// 边u->v,l->r,cost等价于把r加上然后连负边v->u,r-l,-cost,跑上下界即可
namespace mincostflow {
    typedef ll type;
    const type INF=0x3f3f3f3f3f3f3f3f;
    struct node {
        int to; type cap,cost; int next;
        node(int t=0,type c=0,type _c=0,int n=0):
            to(t),cap(c),cost(_c),next(n) {};
    } edge[maxn*2]; int tot;
    int head[maxn];
    int addedge(int from,int to,type cap,type cost,type rcap=0) { //cost初始值不能有负环
        // printf("mincostflow addedge %d %d %d %d\n",from,to,cap,cost);
        if (!cap) return 0; // init了俩空的edge
        edge[tot]=node(to,cap,cost,head[from]); head[from]=tot++;
        edge[tot]=node(from,rcap,-cost,head[to]); head[to]=tot++;
        return tot-2;
    }
    type dis[maxn];
    bool mark[maxn];
    void spfa(int s,int t,int n) {
        memset(dis+1,0x3f,n*sizeof(type));
        memset(mark+1,0,n*sizeof(bool));
        static int Q[maxn],ST,ED;
        dis[s]=0; ST=ED=0; Q[ED++]=s;
        while (ST!=ED) {
            int v=Q[ST]; mark[v]=0;
            if ((++ST)==maxn) ST=0;
            for (int i=head[v]; ~i; i=edge[i].next) {
                node &e=edge[i];
                if (e.cap>0&&dis[e.to]>dis[v]+e.cost) {
                    dis[e.to]=dis[v]+e.cost;
                    if (!mark[e.to]) {
                        if (ST==ED||dis[Q[ST]]<=dis[e.to]) {
                            Q[ED]=e.to,mark[e.to]=1;
                            if ((++ED)==maxn) ED=0;
                        } else {
                            if ((--ST)<0) ST+=maxn;
                            Q[ST]=e.to,mark[e.to]=1;
                        }
                    }
                }
            }
        }
    } int cur[maxn];
    type dfs(int x,int t,type flow) {
        if (x==t||!flow) return flow;
        type ret=0; mark[x]=1;
        for (int i=cur[x]; ~i; i=edge[i].next) if (!mark[edge[i].to]) {
                if (dis[x]+edge[i].cost==dis[edge[i].to]&&edge[i].cap) {
                    int f=dfs(edge[i].to,t,min(flow,edge[i].cap));
                    edge[i].cap-=f; edge[i^1].cap+=f;
                    ret+=f; flow-=f; cur[x]=i;
                    if (flow==0) break;
                }
            }
        mark[x]=0;
        return ret;
    }
    pair<type,type> mincostflow(int s,int t,int n,type flow=INF) {
        type ret=0,ans=0;
        while (flow) {
            spfa(s,t,n); if (dis[t]==INF) break;
            // 这样加当前弧优化会快, 我也不知道为啥
            memcpy(cur+1,head+1,n*sizeof(int));
            type len=dis[t],f;
            if ((f=dfs(s,t,flow))>0)//while也行
                ret+=f,ans+=len*f,flow-=f;
        } return make_pair(ret,ans);
    }
    void init(int n) {
        memset(head+1,0xff,n*sizeof(int));
        tot=2;
    }
}
namespace pipeflow {
    typedef int type;
    int eid[maxn],sgn[maxn],etot;
    type in[maxn],out[maxn],flow[maxn];
    ll all=0;
    int s_s,t_t;//S,T
    int addedge(int u,int v,int low,int high,int cost) {
        // printf("addedge %d %d %d %d %d\n",u,v,low,high,cost);
        if (cost<0) {
            eid[etot]=mincostflow::addedge(v,u,high-low,-cost);
            out[u]+=high; in[v]+=high; sgn[etot]=-1; flow[etot++]=high;
            all+=(ll)-cost*high;
        } else  {
            eid[etot]=mincostflow::addedge(u,v,high-low,cost);
            out[u]+=low; in[v]+=low; sgn[etot]=1; flow[etot++]=low;
            all+=(ll)cost*low;
        }
        return etot-1;
    }
    void init(int n) {
        s_s=n+1,t_t=n+2; etot=0;
        memset(in+1,0,n*sizeof(type));
        memset(out+1,0,n*sizeof(type));
        mincostflow::init(n+2);
    }
    bool solve(int n) {
        int sum=0,i;
        FOR(i,1,n) {
            sum+=max(0,in[i]-out[i]);
            if (in[i]>out[i]) mincostflow::addedge(s_s,i,in[i]-out[i],0);
            if (in[i]<out[i]) mincostflow::addedge(i,t_t,out[i]-in[i],0);
        }
        // FOR(i,1,n) printf("%d(%d) ",in[i],out[i]); puts("<- solve");
        auto res=mincostflow::mincostflow(s_s,t_t,n+2); all+=res.second;
        if (res.first!=sum) return 0;
        REP(i,etot) flow[i]+=mincostflow::edge[eid[i]^1].cap*sgn[i];//more
        // REP(i,etot) printf("%d ",flow[i]); puts("<- flow");
        return 1;
    }
}
int E[maxn];
int ind[maxn];
int flow[maxn];
int main() {
    int n,m,i;
    scanf("%d%d",&n,&m);
    pipeflow::init(n+2);
    int s=n+1,t=n+2;
    REP(i,m) {
        int x,y,c,w;
        scanf("%d%d%d%d",&x,&y,&c,&w);
        E[i]=pipeflow::addedge(x,y,0,c/2,w*2);
        if (c&1) ind[x]++,ind[y]--,pipeflow::addedge(x,y,1,1,w),flow[i]++;
    }
    // FOR(i,1,n) printf("%d ",ind[i]); puts("<- ind");
    FOR(i,2,n-1) if (ind[i]&1) {puts("Impossible"); return 0;}
    FOR(i,2,n-1) {
        if (ind[i]>0) pipeflow::addedge(s,i,ind[i]/2,ind[i]/2,0);
        if (ind[i]<0) pipeflow::addedge(i,t,-ind[i]/2,-ind[i]/2,0);
    }
    pipeflow::addedge(t,s,0,INF,0);
    pipeflow::addedge(s,1,0,INF,0);
    pipeflow::addedge(n,t,0,INF,0);
    pipeflow::addedge(n,1,0,INF,0);
    if (!pipeflow::solve(n+2)) puts("Impossible");
    else {
        puts("Possible");
        REP(i,m) flow[i]+=pipeflow::flow[E[i]]*2;
        REP(i,m) printf("%d ",flow[i]);
    }
}
/*
*/