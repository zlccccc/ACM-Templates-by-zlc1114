#include <bits/stdc++.h>
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
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
inline void add(int &A,int B) {A+=B; (A>=M) &&(A-=M);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int n,m;
char S[maxn];

// 2-sat很简单, 拆点连边就可以了, choose x->y; choose !y->!x
// 题意: 给颗树, 每次给俩路径
// 问你m组询问, 从每个里选个路径, 是否可以不相交
// 做法: 可持久化建线段树然后 2-sat
// A和B不能同时选/必须同时选;
// 输出方案由于tarjan就是拓扑序直接做就行了..
namespace T_SAT {
    const static int maxn=5e6+7;
    struct enode {
        int to,next;
        enode(int _to=0,int _next=-1):to(_to),next(_next) {};
    } edge[maxn*6];
    int head[maxn],etot;
    void addedge(int u,int v) {
        edge[++etot]=enode(v,head[u]); head[u]=etot;
    }
    int dfn[maxn],low[maxn],belong[maxn];
    bool vis[maxn];
    int tot,cnt;
    int S[maxn],top;
    void dfs(int x) {
        dfn[x]=low[x]=++tot;
        S[++top]=x; vis[x]=1;
        for (int i=head[x]; ~i; i=edge[i].next) {
            int v=edge[i].to;
            if (!dfn[v]) {
                dfs(v);
                low[x]=min(low[x],low[v]);
            } else if (vis[v])
                low[x]=min(low[x],dfn[v]);
        }
        if (dfn[x]==low[x]) {
            cnt++;
            while (1) {
                int now=S[top--];
                vis[now]=0; belong[now]=cnt;
                if (now==x) break;
            }
        }
    }
    void init() {
        memset(head,-1,sizeof(head)); etot=0;
    }
    void solve(int n) {
        int i; tot=cnt=0;
        FOR(i,1,n) dfn[i]=vis[i]=0;
        FOR(i,1,n) if (!dfn[i]) dfs(i);
    }
}
int choose,remain;
int upid[maxn*8],downid[maxn*8],tot;
void build(int x,int L,int R) {
    upid[x]=++tot; downid[x]=++tot;
    if (downid[x>>1]) {
        T_SAT::addedge(downid[x>>1],downid[x]);
    } if (L==R) return;
    int mid=(L+R)/2;
    build(x<<1,L,mid);
    build(x<<1|1,mid+1,R);
}
bool update;
void query(int x,int l,int r,int L,int R) {
    if (l>r) return;
//    assert(l<=r);
    if (l<=L&&R<=r) {
        if (!update) {
            T_SAT::addedge(choose,downid[x]);
        } else {
            T_SAT::addedge(++tot,downid[x]); downid[x]=tot;
            T_SAT::addedge(upid[x],remain);
            T_SAT::addedge(downid[x],remain);
            int fa=downid[x>>1],ls=downid[x<<1],rs=downid[x<<1|1];
            if (fa) T_SAT::addedge(fa,downid[x]);
            if (ls) T_SAT::addedge(downid[x],ls);
            if (rs) T_SAT::addedge(downid[x],rs);
        }
        return;
    } else if (!update) T_SAT::addedge(choose,upid[x]);
    int mid=(L+R)/2;
    if (l<=mid) query(x<<1,l,r,L,mid);
    if (mid<r) query(x<<1|1,l,r,mid+1,R);
}
namespace PRE_CAL {
    vector<int> edge[maxn];
    int fa[maxn],son[maxn],id[maxn],tot;
    int sz[maxn],top[maxn],dep[maxn];
    void dfs_1(int u,int father,int depth) {
        fa[u]=father; dep[u]=depth;
        int mx=-1; sz[u]=1; son[u]=0;
        for (int v:edge[u]) {
            if (father==v) continue;
            dfs_1(v,u,depth+1);
            sz[u]+=sz[v];
            if (sz[v]>mx) mx=sz[v],son[u]=v;
        }
    }
    void dfs_2(int u,int x) {
        id[u]=++tot; top[u]=x;
        if (son[u]) dfs_2(son[u],x);
        for (int v:edge[u]) {
            if (v==fa[u]||v==son[u]) continue;;
            dfs_2(v,v);
        }
    }
    void solve(int x,int y) {
        debug("solve: %d, %d\n",x,y);
        while (top[x]!=top[y]) {
            if (dep[top[x]]<dep[top[y]]) swap(x,y);
            debug("  QUERY: %d, %d\n",id[top[x]],id[x]);
            query(1,id[top[x]],id[x],1,n); x=fa[top[x]];
        } if (dep[x]>dep[y]) swap(x,y);
        debug("  FINAL-QUERY: %d, %d\n",id[son[x]],id[y]);
        if (son[x]) query(1,id[son[x]],id[y],1,n);
    }
}
int chosen[maxn];
int A[maxn],B[maxn],C[maxn],D[maxn];
int TaskA() {
    int i,j,m;
    FOR(i,1,n-1) {
        int u,v;
        scanf("%d%d",&u,&v);
        PRE_CAL::edge[u].push_back(v);
        PRE_CAL::edge[v].push_back(u);
    } scanf("%d",&m);
    T_SAT::init();
    PRE_CAL::dfs_1(1,0,0);
    PRE_CAL::dfs_2(1,1);
    FOR(i,1,m) chosen[i]=++tot,++tot;
    build(1,1,n);
    deputs("dfs-2: OK");
    FOR(i,1,n) debug("%-2d ",PRE_CAL::id[i]); deputs(" <- id");
    FOR(i,1,n) debug("%-2d ",PRE_CAL::fa[i]); deputs(" <- fa");
    FOR(i,1,n) debug("%-2d ",PRE_CAL::son[i]); deputs(" <- son");
    FOR(i,1,n) debug("%-2d ",PRE_CAL::top[i]); deputs(" <- top");
    FOR(i,1,m) scanf("%d%d%d%d",&A[i],&B[i],&C[i],&D[i]);
    FOR(i,1,m) {
        choose=chosen[i]; remain=chosen[i]+1;
        update=0;
        PRE_CAL::solve(A[i],B[i]);
        swap(choose,remain);
        PRE_CAL::solve(C[i],D[i]);
        update=1; swap(choose,remain);
        PRE_CAL::solve(A[i],B[i]);
        swap(choose,remain);
        PRE_CAL::solve(C[i],D[i]);
    } build(1,1,n);
    rFOR(i,1,m) {
        choose=chosen[i]; remain=chosen[i]+1;
        update=0;
        PRE_CAL::solve(A[i],B[i]);
        swap(choose,remain);
        PRE_CAL::solve(C[i],D[i]);
        update=1; swap(choose,remain);
        PRE_CAL::solve(A[i],B[i]);
        swap(choose,remain);
        PRE_CAL::solve(C[i],D[i]);
    }
    T_SAT::solve(tot);
    FOR(i,1,m) if (T_SAT::belong[chosen[i]]==T_SAT::belong[chosen[i]+1]) return 0*puts("NO");
    puts("YES");
    FOR(i,1,m) printf("%d\n",((T_SAT::belong[chosen[i]]<T_SAT::belong[chosen[i]+1])^1)+1);
    return 0;
}
void initialize() {}
void Task_one() {TaskA();}
void Task_T() {int T; scanf("%d",&T); while (T--) TaskA();}
void Task_more_n() {while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m() {while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_string() {while (~scanf("%s",S)) TaskA();}
int main() {
    //initialize
    initialize();
    debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
    Task_more_n();
}
/*

*/
