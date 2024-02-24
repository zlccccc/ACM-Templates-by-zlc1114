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
const LL M=998244353;
const LL maxn=1e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,ull k=64) {ull i; REP(i,k) debug("%d",(int)((x>>i)&1)); putchar(' ');}
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

const int K_K=16+1;
namespace ST {
    const int maxn=1<<K_K;
    int ST[maxn][K_K],t_t[maxn];//only L
    inline void initST(int n,const int id[],const int A[]) { //0 to n-1
        int i,j; assert(n<=maxn);
        rep(i,1,n) t_t[i]=t_t[i>>1]+1;
        REP(i,n) {
            ST[i][0]=id[i];
            rep(j,1,t_t[i+1]) {
                int u=ST[i-(1<<(j-1))][j-1],v=ST[i][j-1];
                ST[i][j]=A[u]>=A[v]?u:v;
            }
        }
    }
    inline int RMQ(int x,int y,const int A[]) {
        int t=t_t[y-x+1]-1;
        x=ST[x+(1<<t)-1][t]; y=ST[y][t];
        return A[x]>=A[y]?x:y;
    }
}
namespace RMQ01 { //start from 0; return the First Maximize Value Position
    const int maxn=1<<K_K;
    inline int B(int x) {return x>>4;}
    int BLOCK[maxn],MAXP[1<<16|1],BMAX[maxn];
    inline int value(int l,int r) {//0000xxxx1111  // & mid | right
        int mid=((1<<((r&15)+1))-1)^((1<<((l&15)+1))-1);
        int right=((1<<16)-1)^((1<<((r&15)+1))-1);
        return MAXP[(BLOCK[B(l)]&mid)|right]+(l&~15);
    }
    void dfs_value(int x=0,int depth=15,int maxval=0,int maxpos=0) {
        if (maxval<=0) maxpos=0,maxval=0;
        if (depth==0) {MAXP[x<<1]=MAXP[x<<1|1]=maxpos; return;}
        dfs_value(x<<1,depth-1,maxval+1,maxpos+1);
        dfs_value(x<<1|1,depth-1,maxval-1,maxpos+1);
    }
    void build(int n, int A[]) {//0:+1; 1:-1 //start from (1-15); g[i]=A[i]-A[i-1]
        int i; dfs_value(); while (n&15) A[n]=A[n-1]-1,n++; assert(B(n-1)<maxn);
        memset(BLOCK,0,sizeof(BLOCK));
        rrep(i,1,n) BLOCK[B(i)]=BLOCK[B(i)]<<1|(1-((A[i]-A[i-1]+1)>>1));
        BLOCK[0]<<=1;
        REP(i,B(n-1)+1) BMAX[i]=MAXP[BLOCK[i]]+(i<<4);
        ST::initST(B(n-1)+1,BMAX,A);
    }
    int RMQ01(int x,int y,const int A[]) {
        if (x>y) swap(x,y);
        int rx=B(x)<<4|15,ly=B(y)<<4;
        if (y<=rx) return value(x,y);
        int u=value(x,rx),v;
        if (rx+1!=ly) v=ST::RMQ(B(x)+1,B(y)-1,A),u=A[u]>=A[v]?u:v;
        v=value(ly,y); u=A[u]>=A[v]?u:v;
        return u;
    }
}

namespace LCA {
    struct Edges {
        int to; ll len; int next;
        Edges(int _to=0,ll _len=0,int _next=0):to(_to),len(_len),next(_next) {}
    } edge[maxn*2]; int etot;
    int head[maxn];//for edges
    int fa[maxn],dep[maxn];
    ll uplen[maxn],len[maxn]; //uplen: single edge
    int id[maxn],dfn[maxn],tot;//down
    int id2[maxn*2],dfn2[maxn],tot2,value2[maxn*2];//down+up; dep2=-depth; just for 4-Russian Use
    inline void addedge(int u,int v,ll len) {
        edge[++etot]=Edges(v,len,head[u]); head[u]=etot;
    }
    void dfs(int x=1,int f=0,int d=0,ll l=0) {
        int i; dep[x]=d; len[x]=l;
        ++tot; id[tot]=x; dfn[x]=tot;
        id2[tot2]=x; dfn2[x]=tot2; value2[tot2]=-d; tot2++;
        for (i=head[x]; ~i; i=edge[i].next) if (edge[i].to!=f) {
                int v=edge[i].to;
                fa[v]=x; uplen[v]=edge[i].len;
                dfs(v,x,d+1,l+edge[i].len);
                value2[tot2]=-d; id2[tot2++]=x;
            }
    }
    void init_lca(int root=1) {
        dfs(root);
        RMQ01::build(tot2,value2);
    }
    inline int lca(int x,int y) {
        return id2[RMQ01::RMQ01(dfn2[x],dfn2[y],value2)];
    }
    inline ll dis(int x,int y) {
        return len[x]+len[y]-2*len[lca(x,y)];
    }
    void init(int n) {
        memset(head+1,0xff,n*sizeof(int));
        etot=tot=tot2=0;
    }
}

namespace vtree {
    int S[maxn],top;
    int pid[maxn],mark[maxn];
    int vid[maxn],vfa[maxn];
    LL vlen[maxn];
    int cmp(int x,int y) {
        return LCA::dfn[x]<LCA::dfn[y];
    }
    void addedge(int u,int v) {
        vfa[v]=u; vlen[v]=LCA::dis(u,v);
    }
    int m;
    void vbuild(int n) {
        int i; m=0;
        sort(pid+1,pid+1+n,cmp);
        S[top=1]=pid[1];
        mark[pid[1]]=1;
        FOR(i,2,n) {
            int f=LCA::lca(pid[i-1],pid[i]);
            while (top&&LCA::dep[S[top]]>LCA::dep[f]) {
                int v; vid[++m]=v=S[top--];
                if (top&&LCA::dep[S[top]]>LCA::dep[f]) addedge(S[top],v);
                else addedge(f,v);
            } if (!top||S[top]!=f) S[++top]=f;
            S[++top]=pid[i]; mark[pid[i]]=1;
        } while (top-1) addedge(S[top-1],S[top]),vid[++m]=S[top--];
        vid[++m]=S[1];
        reverse(vid+1,vid+m+1);
    }
    void vclear() {
        int i;
        FOR(i,1,m) mark[vfa[vid[i]]]=0;
        FOR(i,1,m) mark[vid[i]]=0;
    }
}

int ans;
int cnt[maxn];
void solve() {
    int i;
    FOR(i,1,vtree::m) cnt[vtree::vid[i]]=0;
    rFOR(i,1,vtree::m) {
        int x=vtree::vid[i];
        if (vtree::mark[x]) ans+=cnt[x],cnt[x]=1;
        else if (cnt[x]>1) ans++,cnt[x]=0;
        if (i>1) cnt[vtree::vfa[x]]+=cnt[x];
    }
}
int vis[maxn];
int main() {
    int i;
    int n,q;
    scanf("%d",&n);
    LCA::init(n);
    FOR(i,1,n-1) {
        int u,v;
        scanf("%d%d",&u,&v);
        LCA::addedge(u,v,1); LCA::addedge(v,u,1);
    } LCA::init_lca();
    scanf("%d",&q);
    while (q--) {
        int m,mark=0;
        scanf("%d",&m);
        FOR(i,1,m) scanf("%d",&vtree::pid[i]);
        FOR(i,1,m) vis[vtree::pid[i]]=1;
        FOR(i,1,m) if (vis[LCA::fa[vtree::pid[i]]]) mark=1;
        FOR(i,1,m) vis[vtree::pid[i]]=0;
        if (mark) {puts("-1"); continue;}
        vtree::vbuild(m);
        ans=0; solve();
        vtree::vclear();
        printf("%d\n",ans);
    }
}