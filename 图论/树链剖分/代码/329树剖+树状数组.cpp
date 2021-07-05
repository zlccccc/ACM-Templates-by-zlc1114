#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define mp(A,B) make_pair(A,B)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL hash=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a,T b) {return a>0?a:-a;}

int tot;
inline int lowbit(int x) {return x&-x;}
int c[maxn];
int getsum(int x) {
    int ret=0;
    while(x) {
        ret+=c[x];
        x-=lowbit(x);
    }
    return ret;
}
int query(int l,int r) {
    return getsum(r)-getsum(l-1);
}
void add(int x,int d) {
    while(x<=tot) {
        c[x]+=d;
        x+=lowbit(x);
    }
}
void build() {
    int i;
    FOR(i,1,tot) c[i]=0;
}
int n,i,q,k;
int u,v;
int U[maxn],V[maxn];
vector<int> edge[maxn];
int fa[maxn],son[maxn],sz[maxn],top[maxn],id[maxn],dep[maxn];
void dfs1(int u,int from,int depth) {
    int v,i,mx=-1;
    sz[u]=1;
    fa[u]=from;
    dep[u]=depth;
    son[u]=0;
    REP(i,edge[u].size()) {
        v=edge[u][i];
        if(v==from) continue;
        dfs1(v,u,depth+1);
        sz[u]+=sz[v];
        if(sz[v]>mx) son[u]=v;
    }
}
void dfs2(int u,int x) {
    int v,i;
    top[u]=x;
    id[u]=++tot;
    if(son[u]) dfs2(son[u],x);
    REP(i,edge[u].size()) {
        v=edge[u][i];
        if(v==fa[u]||v==son[u]) continue;
        dfs2(v,v);
    }
}
inline int Query(int x,int y) {
    int ret=0;
    while(top[x]!=top[y]) {
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        if(query(id[top[x]],id[x])) return -1;
        ret+=id[x]-id[top[x]]+1;
        x=fa[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    if(son[x]) {
        if(query(id[son[x]],id[y])) return -1;
        ret+=id[y]-id[son[x]]+1;
    }
    return ret;
}
int main() {
    scanf("%d",&n);
    FOR(i,1,n-1) {
        scanf("%d%d",&U[i],&V[i]);
        edge[U[i]].push_back(V[i]);
        edge[V[i]].push_back(U[i]);
    }
    tot=0;
    dfs1(1,0,1);
    dfs2(1,1);
    FOR(i,1,n-1) if(dep[U[i]]>dep[V[i]]) swap(U[i],V[i]);
    build();
    scanf("%d",&q);
    while(q--) {
        scanf("%d",&k);
        if(k==1) {
            scanf("%d",&i);
            add(id[V[i]],-1);
        }
        if(k==2) {
            scanf("%d",&i);
            add(id[V[i]],1);
        }
        if(k==3) {
            scanf("%d%d",&u,&v);
            printf("%d\n",Query(u,v));
        }
    }
}
/*
*/
