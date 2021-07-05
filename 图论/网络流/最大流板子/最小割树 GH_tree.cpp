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
const LL maxn=5000+7;
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
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

namespace maxflow {
    typedef int type;
    const type INF=0x3f3f3f3f;
    struct node {
        int to; type cap; int next;
        node(int t=0,type c=0,int n=0):to(t),cap(c),next(n) {};
    } edge[maxn*50];
    int head[maxn],tot;
    void addedge(int from,int to,type cap,type rcap=0) {
        edge[tot]=node(to,cap,head[from]); head[from]=tot++;
        edge[tot]=node(from,rcap,head[to]); head[to]=tot++;
    }
    int dep[maxn],cur[maxn];//当前弧优化
    bool bfs(int s,int t,int n) {
        static int Q[maxn],ST,ED;
        memset(dep+1,0,n*sizeof(int));
        ST=0; ED=-1;
        Q[++ED]=s; dep[s]=1;
        while (ST<=ED) {
            int u=Q[ST++];
            for (int i=head[u]; i!=-1; i=edge[i].next) {
                int v=edge[i].to;
                if (!dep[v]&&edge[i].cap) {
                    Q[++ED]=v; dep[v]=dep[u]+1;
                }
            }
        } return (dep[t]!=0);
    }
    type dfs(int x,const int &t,type flow=INF) {
        if (x==t||flow==0) return flow;
        type ret=0;
        for (int i=cur[x]; i!=-1; i=edge[i].next) {
            if (dep[x]+1==dep[edge[i].to]&&edge[i].cap){
                int f=dfs(edge[i].to,t,min(flow,edge[i].cap));
                edge[i].cap-=f; edge[i^1].cap+=f;
                ret+=f; flow-=f; cur[x]=i;
                if (flow==0) break;
            }
        } if (!ret) dep[x]=0;
        return ret;
    }
    type maxflow(int s,int t,int n) {
        int ret=0;
        while (bfs(s,t,n)) {
            int f;
            memcpy(cur+1,head+1,n*sizeof(int));
            while ((f=dfs(s,t))>0) ret+=f;
        } return ret;
    }
    void init(int n) {
        memset(head+1,0xff,n*sizeof(int)); tot=0;
    }
}
//两点的LCA_MAX是最小割
namespace gomoryhu_tree {
    typedef int type;
    struct node { //只能是双向的
        int u,v; type len;
        node(int u=0,int v=0,type len=0):u(u),v(v),len(len) {};
    } edge[maxn],e[maxn];
    int tot,etot;
    void addedge(int u,int v,int len) {
        edge[++tot]=node(u,v,len);
    } int n;
    void solve(int l,int r,int id[]) {//id,id+n
        // CNT++;
        static int tmp[maxn];
        if (l==r) return;
        random_shuffle(id+l,id+r+1);
        maxflow::init(n); int i,L=l,R=r;
        FOR(i,1,tot) maxflow::addedge(edge[i].u,edge[i].v,edge[i].len,edge[i].len);
        e[++etot]=node(id[l],id[r],maxflow::maxflow(id[l],id[r],n));
        FOR(i,l,r) if (maxflow::dep[id[i]])
            tmp[L++]=id[i]; else tmp[R--]=id[i];
        FOR(i,l,r) id[i]=tmp[i];
        solve(l,R,id); solve(L,r,id);
    }
    void init(int _n) {
        n=_n; tot=etot=0;
        srand(time(0));
    }
}
int fa[maxn],cnt[maxn];
inline int getfa(int x) {
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa[x]);
} int id[maxn];
int main() {
    int i;
    scanf("%d%d",&n,&m);
    // startTimer();
    // n=1000;
    gomoryhu_tree::init(n);
    // FOR(i,1,1000) gomoryhu_tree::addedge(i,i%n+1,1); 
    FOR(i,1,m) {
        int u,v;
        scanf("%d%d",&u,&v);
        gomoryhu_tree::addedge(u,v,1);
    }
    FOR(i,1,n) id[i]=i;
    gomoryhu_tree::solve(1,n,id);
    sort(gomoryhu_tree::e+1,gomoryhu_tree::e+gomoryhu_tree::etot+1,[](gomoryhu_tree::node &A,gomoryhu_tree::node &B){
        return A.len>B.len;
    }); int ans=0;
    FOR(i,1,n) fa[i]=i,cnt[i]=1;
    FOR(i,1,gomoryhu_tree::etot) {
        auto now=gomoryhu_tree::e[i];
        int x=getfa(now.u),y=getfa(now.v);
        if (x==y) continue;
        ans+=cnt[x]*cnt[y]*now.len;
        fa[x]=y; cnt[y]+=cnt[x];
    } printf("%d\n",ans);
    // printTimer();
    // printf("maxflow:%d\n",CNT);
}
/*
*/
