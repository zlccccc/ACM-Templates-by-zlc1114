#include <sstream>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>
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
#define deputs(A) fprintf(stderr, "%s\n",A)
#else
#define debug(...)
#define deputs(A)
#endif // DEBUG
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=10000+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

//题意: 给两颗树, 树上有边
//问你: T1的1->i和T2的1->i的所有边加入计算后有多少联通块
//做法: 先把两棵树分成sqrt个块, 将query放到两个树的块上
//然后直接从上面转移+回滚, 最多sqrt的length
struct Changes {
    int x,y,ini;
    Changes(int _x=0,int _y=0,int _ini=0):x(_x),y(_y),ini(_ini) {};
} changes[maxn*50]; int top;
vector<int> E[maxn],V1,V2;
int fa1[maxn],fa2[maxn],SIZE;
int id1[maxn],id2[maxn];
int last[507][507];
vector<Changes> queries[507][507];
void dfs1(int x,int f,int dep) {
    fa1[x]=f; id1[x]=-1;
    if (!(dep%SIZE)) id1[x]=V1.size(),V1.push_back(x);
    for (int v:E[x]) if (v!=f) dfs1(v,x,dep+1);
} void dfs2(int x,int f,int dep) {
    fa2[x]=f; id2[x]=-1;
    if (!(dep%SIZE)) id2[x]=V2.size(),V2.push_back(x);
    for (int v:E[x]) if (v!=f) dfs2(v,x,dep+1);
}
int ux[maxn],uy[maxn],vx[maxn],vy[maxn];
int fa[maxn],sz[maxn],nowans;
void merge_(int x,int y) {
    while (x!=fa[x]) x=fa[x];
    while (y!=fa[y]) y=fa[y];
    if (x==y) return;
    if (sz[x]>sz[y]) swap(x,y);
    changes[++top]=Changes(x,y);
    fa[x]=y; nowans--; sz[y]+=sz[x];
    debug("merge_OK (%d %d)-%d ans=%d\n",x,y,top,nowans);
}
void revert(int x,int y) {
    debug("revert to %d %d\n",x,y);
    while (top>last[id1[x]][id2[y]]) {
        auto now=changes[top--]; nowans++;
        fa[now.x]=now.x; fa[now.y]=now.y;
        sz[now.y]-=sz[now.x];
        debug("revert_OK (%d %d)-%d+1 ans=%d\n",now.x,now.y,top,nowans);
    }
}
void commit(int x,int y) {
    int tx=x,ty=y;
    while (id1[tx]==-1) tx=fa1[tx];
    while (id2[ty]==-1) ty=fa2[ty];
//    if (tx!=lastx||ty!=lasty)
    revert(tx,ty);
    while (x!=tx) merge_(ux[x],vx[x]),x=fa1[x];
    while (y!=ty) merge_(uy[y],vy[y]),y=fa2[y];
}
int ans[maxn];
int main() {
    int T;
    int i,j,k;
    scanf("%d",&T);
    while (T--) {
        int n,m;
        scanf("%d%d",&n,&m);
        FOR(i,1,n) scanf("%d%d",&ux[i],&vx[i]);
        SIZE=sqrt(n)*1.1; if (SIZE==0) SIZE=1;
        FOR(i,1,n-1) {
            int u,v;
            scanf("%d%d",&u,&v);
            E[u].push_back(v);
            E[v].push_back(u);
        } V1.clear(); dfs1(1,0,0);
        FOR(i,1,n) E[i].clear();
        FOR(i,1,n) scanf("%d%d",&uy[i],&vy[i]);
        FOR(i,1,n-1) {
            int u,v;
            scanf("%d%d",&u,&v);
            E[u].push_back(v);
            E[v].push_back(u);
        } V2.clear(); dfs2(1,0,0);
        FOR(i,1,n) E[i].clear();
//        FOR(i,1,n) debug("%d %d\n",fa1[i],id1[i]);
//        FOR(i,1,n) debug("%d %d\n",fa2[i],id2[i]);
        FOR(i,1,n) {
            int u,v,x,y;
            u=v=i; x=u; y=v;
            while (id1[x]==-1) x=fa1[x];
            while (id2[y]==-1) y=fa2[y];
            queries[id1[x]][id2[y]].push_back(Changes(u,v,i));
        } deputs("okay");
        FOR(i,1,m) fa[i]=i,sz[i]=1;
        top=0; nowans=m;
        for (int x:V1) {
            for (int y:V2) {
                if (x==1&&y==1) {
                    merge_(ux[x],vx[x]);
                    merge_(uy[y],vy[y]);
                } else if (y==1) {
                    commit(fa1[x],y);
                    merge_(ux[x],vx[x]);
                } else {
                    commit(x,fa2[y]);
                    merge_(uy[y],vy[y]);
                } last[id1[x]][id2[y]]=top;
                for (auto now:queries[id1[x]][id2[y]]) {
                    debug("query %d %d\n",now.x,now.y);
                    commit(now.x,now.y);
                    ans[now.ini]=nowans;
                } queries[id1[x]][id2[y]].clear();
            }
        }
        FOR(i,1,n) printf("%d\n",ans[i]);
    }
    return 0;
}
/*
2
3 4
1 2
2 3
3 4
1 2
1 3

1 3
2 4
3 4
1 2
2 3

2 100
100 99
99 98
1 2
97 96
95 94
1 2
*/
