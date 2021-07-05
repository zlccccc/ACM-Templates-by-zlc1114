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
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B) {A+=B; (A>=M) &&(A-=M);}
template<typename T>inline void mul_(T &A,ll B) {(A*=B)%=M;}
template<typename T>inline void mod_(T &A,ll B=M) {A%=M;}
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
int TaskA();
void Task_one() {TaskA();}
void Task_T() {int T; scanf("%d",&T); while (T--) TaskA();}
void Task_more_n() {while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m() {while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_n_m_q() {while (~scanf("%d%d%d",&n,&m,&q)) TaskA();}
void Task_more_string() {while (~scanf("%s",str)) TaskA();}

// 题意: 更改链上的边col
// 更改某个链相邻的边col
// 查询黑点数
// 做法: 轻重边分开维护
struct segment_tree {
    int val[maxn<<2],len[maxn<<2],lazy[maxn<<2];
    void build(int x,int L,int R) {
        len[x]=R-L+1; val[x]=0; lazy[x]=0;
        if (L==R) return;
        int mid=(L+R)/2;
        build(x<<1,L,mid);
        build(x<<1|1,mid+1,R);
    }
    void Inverse(int x) {
        lazy[x]^=1; val[x]=len[x]-val[x];
    }
    void pushdown(int x) {
        if (lazy[x]) {
            Inverse(x<<1);
            Inverse(x<<1|1);
            lazy[x]=0;
        }
    }
    void pushup(int x) {
        val[x]=val[x<<1]+val[x<<1|1];
    }
    void update(int x,int l,int r,int L,int R) {
        debug("update: %d %d %d\n",x,l,r);
        if (l<=L&&R<=r) {Inverse(x); return;}
        int mid=(L+R)/2;
        pushdown(x);
        if (l<=mid) update(x<<1,l,r,L,mid);
        if (mid<r) update(x<<1|1,l,r,mid+1,R);
        pushup(x);
    }
    int query(int x,int l,int r,int L,int R) {
        if (l<=L&&R<=r) return val[x];
        int mid=(L+R)/2,ret=0;
        pushdown(x);
        if (l<=mid) ret+=query(x<<1,l,r,L,mid);
        if (mid<r) ret+=query(x<<1|1,l,r,mid+1,R);
        pushup(x);
        return ret;
    }
} heavy,light;
vector<int> edge[maxn];
int fa[maxn],dep[maxn],sz[maxn],tot;
int top[maxn],id[maxn],son[maxn];
void dfs1(int u,int father,int depth) {
    int mx=-1; sz[u]=1;
    fa[u]=father; son[u]=0; dep[u]=depth;
    for (int v:edge[u]) {
        if (v==father) continue;
        dfs1(v,u,depth+1); sz[u]+=sz[v];
        if (sz[v]>mx) mx=sz[v],son[u]=v;
    }
}
void dfs2(int u,int x) {
    top[u]=x; id[u]=++tot;
    if (son[u]) dfs2(son[u],x);
    for (int v:edge[u]) {
        if (v==fa[u]||v==son[u]) continue;
        dfs2(v,v);
    }
}
inline void InverseEdge(int x,int y) {
    while (top[x]!=top[y]) {
        if (dep[top[x]]<dep[top[y]]) swap(x,y);
        heavy.update(1,id[top[x]],id[x],1,n);
        x=fa[top[x]];
    }
    if (dep[x]>dep[y]) swap(x,y);
    if (son[x]) heavy.update(1,id[son[x]],id[y],1,tot);
}
inline void InverseNode(int x,int y) {
    while (top[x]!=top[y]) {
        debug("Inverse   : %d %d\n",x,y);
        if (dep[top[x]]<dep[top[y]]) swap(x,y);
        light.update(1,id[top[x]],id[x],1,n);
        heavy.update(1,id[top[x]],id[top[x]],1,n);
        if (son[x]) heavy.update(1,id[son[x]],id[son[x]],1,n);
        x=fa[top[x]];
    }
    debug("Inverse   : %d %d\n",x,y);
    if (dep[x]>dep[y]) swap(x,y);
    light.update(1,id[x],id[y],1,tot);
    heavy.update(1,id[x],id[x],1,n);
    if (son[y]) heavy.update(1,id[son[y]],id[son[y]],1,n);
}
inline int Query(int x,int y) {
    int ret=0;
    while (top[x]!=top[y]) {
        if (dep[top[x]]<dep[top[y]]) swap(x,y);
        if (top[x]!=x) ret+=heavy.query(1,id[son[top[x]]],id[x],1,n);
        ret+=heavy.query(1,id[top[x]],id[top[x]],1,n)^light.query(1,id[fa[top[x]]],id[fa[top[x]]],1,n);
        x=fa[top[x]];
    }
    if (dep[x]>dep[y]) swap(x,y);
    if (son[x]) ret+=heavy.query(1,id[son[x]],id[y],1,n);
    return ret;
}
int TaskA() {
    int i;
    scanf("%d",&n); tot=0;
    FOR(i,1,n) edge[i].clear();
    FOR(i,1,n-1) {
        int u,v;
        scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    } dfs1(1,0,0); dfs2(1,1);
    FOR(i,1,n) debug("%d ",id[i]);
    heavy.build(1,1,n);
    light.build(1,1,n);
    scanf("%d",&q);
    REP(i,q) {
        int op,u,v;
        scanf("%d%d%d",&op,&u,&v);
        if (op==1) InverseEdge(u,v);
        if (op==2) InverseNode(u,v);
        if (op==3) printf("%d\n",Query(u,v));
    }
    return 0;
}
void initialize() {}
int main() {
    int startTime=clock();
    //initialize
    initialize();
    debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
    Task_T();
}
/*
*/
