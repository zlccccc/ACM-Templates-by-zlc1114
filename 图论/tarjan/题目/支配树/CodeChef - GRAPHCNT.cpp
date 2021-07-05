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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for(; b; b>>=1ll,a=1ll*a*a%M) if(b&1) ret=1ll*ret*a%M; return ret;}


//lowlink是说,遇到的min
//无向图:
//u割点:low[v]>=dfn[u];(表示能到的点都在之后)
//u-v割边(桥):low[v]>dfn[u];(要在u-v处得到)
//块:low[u]==dfn[u];(最终从stack取出x)
//dfs时注意fa和重边处理
//有向图:
//支配树:
//半必经点(semi=mindep{通过非树枝边fa})定理:(semi[x]=id[temp]),
//temp=min(temp,dfn[pre]),dfn[x]>dfn[pre](树枝边|前向边)
//temp=min{temp,dfn[semi[ancestor_pre(fa)]]},dfn[x]<dfn[pre](横叉边|后向边)
//必经点(idom)定理:y=id[min{dfn[z]}],z:semi_path上的点
//idom[x]=semi[x],semi[x]==semi[y]
//idom[x]=idom[y],semi[x]!=semi[y]
//割边:将边变成点,然后跑支配树即可
struct Edge {
    int to,next;
    Edge(int _to=0,int _next=-1):to(_to),next(_next) {};
} edge[maxn*4];
int head[maxn],pre[maxn],dom[maxn],etot; //edges
inline void addedge(int head[],int u,int v) {
    edge[++etot]=Edge(v,head[u]);
    head[u]=etot;
}
int dfn[maxn],tot,par[maxn]; //dfs-tree
int Fa[maxn],best[maxn]; //disjoint-set
int semi[maxn],id[maxn],idom[maxn]; //dom-tree
inline int getfa(int x) {
    if(Fa[x]==x) return x;
    int F=getfa(Fa[x]);
    if(dfn[semi[best[x]]]>dfn[semi[best[Fa[x]]]])
        best[x]=best[Fa[x]];
    return Fa[x]=F;
}
void dfs(int x) {
    dfn[x]=++tot;
    id[tot]=x;
    for(int i=head[x]; ~i; i=edge[i].next) {
        int v=edge[i].to;
        if(!dfn[v]) par[v]=x,dfs(v);
    }
}
void tarjan(int n) {
    int i;
    FOR(i,1,n) dom[i]=-1;
    FOR(i,1,n) best[i]=semi[i]=Fa[i]=i;
    rFOR(i,2,tot) {
        int x=id[i];
        for(int j=pre[x]; ~j; j=edge[j].next) {
            int v=edge[j].to;
            if(!dfn[v]) continue; //could not reach
            getfa(v); //pre_dfn:not changed
            if(dfn[semi[best[v]]]<dfn[semi[x]])
                semi[x]=semi[best[v]];
        }
        addedge(dom,semi[x],x);
        Fa[x]=par[x];
        x=id[i-1];
        for(int j=dom[x]; ~j; j=edge[j].next) { //path
            int v=edge[j].to;
            getfa(v); //id[min{dfn[z]}]
            if(semi[best[v]]==x) idom[v]=x;
            else idom[v]=best[v];
        }
    }
    FOR(i,2,tot) {
        int x=id[i];
        if(idom[x]!=semi[x]) idom[x]=idom[idom[x]];
    }
}
LL n,m;
LL CNT[maxn];
LL solve() {
    LL ret=(LL)tot*(tot-1)/2;
    int i;
    rFOR(i,2,tot) {
        int x=id[i];
        CNT[x]++;
        if(idom[x]==1) ret-=CNT[x]*(CNT[x]-1)/2;
        else CNT[idom[x]]+=CNT[x];
    }
    return ret;
}
int main() {
    int i;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) head[i]=pre[i]=-1;
    FOR(i,1,m) {
        int u,v;
        scanf("%d%d",&u,&v);
        addedge(head,u,v);
        addedge(pre,v,u);
    }
    dfs(1);
    tarjan(n);
//    FOR(i,1,n) printf("%2d ",par[i]);puts("");
//    FOR(i,1,n) printf("%2d ",id[i]);puts("");
//    FOR(i,1,n) printf("%2d ",idom[i]);puts("");
    printf("%lld\n",solve());
}
/*
*/
