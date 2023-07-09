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
const LL maxn=1e5+107;
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

// 题意:问最少去掉几个未标记点可以把所有的标记点全分开
// 做法:建虚树然后树上DP
// 虚树板子,注意:sort过程可以提到外边去
// 注意, 原先有的标记有的时候会到边上, 需要特判的, 千万不要if
namespace LCA {//内部和外部dfn不同...
    vector<pii> edge[maxn];
    int fa[maxn];
    int uplen[maxn];
    int id[maxn],dfn[maxn],idtot;
    void addedge(int u,int v,int l=1) {
        edge[u].push_back({v,l});
    }
    int dep[maxn]; ll len[maxn];
    int st_dfn[maxn],tot;
    int ST[maxn*2][22];//only L
    int t_t[maxn*2];
    void dfs(int x,int f,int depth=0,ll length=0) {
        dep[x]=depth; len[x]=length;
        st_dfn[x]=++tot; ST[tot][0]=x;
        id[++idtot]=x; dfn[x]=idtot;
        for (pii e:edge[x]) {
            int v=e.first,l=e.second;
            if (v==f) continue;
            fa[v]=x; uplen[v]=l;
            dfs(v,x,depth+1,length+l);
            ST[++tot][0]=x;
        }
    }
    inline void initST(int n) {
        int i,j;
        FOR(i,1,n*2) t_t[i]=t_t[i>>1]+1;
        FOR(i,1,n*2) {
            rep(j,1,t_t[i]) {
                int u=ST[i][j-1],v=ST[i-(1<<(j-1))][j-1];
                ST[i][j]=dep[u]<dep[v]?u:v;
            }
        }
    }
    inline int lca(int x,int y) {
        x=st_dfn[x]; y=st_dfn[y];
        if (x>y) swap(x,y);
        int t=t_t[y-x+1]-1;
        x=ST[x+(1<<t)-1][t]; y=ST[y][t];
        return dep[x]<dep[y]?x:y;
    }
    inline int dis(int x,int y) {
        return len[x]+len[y]-2*len[lca(x,y)];
    }
    void init(int n) {
        int i;
        FOR(i,1,n) edge[i].clear();
        idtot=tot=0;
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
        vfa[vid[1]]=0;
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
        LCA::addedge(u,v); LCA::addedge(v,u);
    } LCA::dfs(1,0,0,0);
    LCA::initST(n);
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
    return 0;
}
/*
*/
