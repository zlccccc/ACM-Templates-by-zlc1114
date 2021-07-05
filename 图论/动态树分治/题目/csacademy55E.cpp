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
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
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

struct enode {
    int to,next;
    enode(int _to=0,int _next=-1):to(_to),next(_next) {}
} edge[maxn*2];
int head[maxn],etot;
void addedge(int u,int v) {
    edge[++etot]=enode(v,head[u]); head[u]=etot;
} int sz[maxn],mark[maxn];
int root,minweight;
void dfs1(int x,int fa,int n) { //root
//    debug("dfs1: %d %d %d\n",x,fa,n);
    int weight=0; sz[x]=1;
    for (int i=head[x]; ~i; i=edge[i].next) {
        int v=edge[i].to;
        if (v==fa||mark[v]) continue;
        dfs1(v,x,n); sz[x]+=sz[v];
        weight=max(weight,sz[v]);
    } weight=max(weight,n-sz[x]);
    if (weight<minweight) root=x,minweight=weight;
}

struct pnode {
    int cnt[2]; LL len[2];
} pool[maxn*2],*st=pool,*rootpos[maxn],*sonpos[maxn];
struct cnode {
    int len,top,sub,next;
    cnode(int _top=0,int _sub=0,int _len=0,int _next=-1):top(_top),sub(_sub),len(_len),next(_next) {};
} calnode[maxn*40];
int calhead[maxn],caltot;
void addcal(int x,int top,int sub,int len) {
    calnode[++caltot]=cnode(top,sub,len,calhead[x]); calhead[x]=caltot;
}
void dfs2(int x,int fa,int top,int sub,int dep) {
    addcal(x,top,sub,dep);
    for (int i=head[x]; ~i; i=edge[i].next) {
        int v=edge[i].to;
        if (v==fa||mark[v]) continue;
        dfs2(v,x,top,sub,dep+1);
    }
}
void dfs3(int x) {
    debug("dfs3: %d\n",x);
    mark[x]=1; addcal(x,x,0,0);
    for (int i=head[x]; ~i; i=edge[i].next) {
        int v=edge[i].to;
        if (mark[v]) continue;
        minweight=sz[v]; dfs1(v,0,sz[v]);
        dfs2(v,0,x,root,1); sonpos[root]=st++;
        dfs3(root);
    } rootpos[x]=st++;
}
int color[maxn];
void add(int x) {
    for (int i=calhead[x]; ~i; i=calnode[i].next) {
        debug("add(%d) : %d %d %d\n",x,calnode[i].top,calnode[i].sub,calnode[i].len);
        int v=calnode[i].top,length=calnode[i].len;
        rootpos[v]->cnt[color[x]]++;
        rootpos[v]->len[color[x]]+=length;
        v=calnode[i].sub;
        if (v) {
            sonpos[v]->cnt[color[x]]++;
            sonpos[v]->len[color[x]]+=length;
        }
    }
} void update(int x) {
    for (int i=calhead[x]; ~i; i=calnode[i].next) {
        int v=calnode[i].top,length=calnode[i].len;
        rootpos[v]->cnt[color[x]]--;
        rootpos[v]->cnt[color[x]^1]++;
        rootpos[v]->len[color[x]]-=length;
        rootpos[v]->len[color[x]^1]+=length;
        v=calnode[i].sub;
        if (v) {
            sonpos[v]->cnt[color[x]]--;
            sonpos[v]->cnt[color[x]^1]++;
            sonpos[v]->len[color[x]]-=length;
            sonpos[v]->len[color[x]^1]+=length;
        }
    } color[x]^=1;
} LL query(int x) {
    LL ans=0;
    for (int i=calhead[x]; ~i; i=calnode[i].next) {
        int v=calnode[i].top,length=calnode[i].len;
        ans+=rootpos[v]->cnt[color[x]]*length + rootpos[v]->len[color[x]];
        debug("query_root: %d (%d) %d %d\n",length,v,rootpos[v]->cnt[color[x]],rootpos[v]->len[color[x]]);
        v=calnode[i].sub;
        if (v) {
            ans-=sonpos[v]->cnt[color[x]]*length + sonpos[v]->len[color[x]];
            debug("query_sub: %d (%d) %d %d\n",length,v,sonpos[v]->cnt[color[x]],sonpos[v]->len[color[x]]);
        }
    } return ans;
}
int main() {
    int n,m,i,j;
    memset(head,0xff,sizeof(head));
    memset(calhead,0xff,sizeof(calhead));
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",&color[i]);
    FOR(i,1,n-1) {
        int u,v;
        scanf("%d%d",&u,&v);
        addedge(u,v);
        addedge(v,u);
    }
    minweight=n; dfs1(1,0,n);
    dfs3(root);
    FOR(i,1,n) add(i);
    while (m--) {
        int op,x;
        scanf("%d%d",&op,&x);
        if (op==1) update(x);
        else printf("%lld\n",query(x));
    }
}
/*
*/
