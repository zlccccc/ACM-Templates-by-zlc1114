#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;

struct Edge {
    int to,next;
    Edge(int _to=0,int _next=-1):to(_to),next(_next) {};
} edge[maxn*2];
int head[maxn],etot;
inline void addedge(int u,int v) {
    edge[++etot]=Edge(v,head[u]);
    head[u]=etot;
}
//lowlink是说,遇到的min
//无向图:
//u割点:low[v]>=dfn[u];(表示能到的点都在之后)
//u-v割边(桥):low[v]>dfn[u];(要在u-v处得到)
//块:low[u]==dfn[u];(最终从stack取出x)
//dfs时注意fa和重边处理
//无向图不用vis这个东西=_=,vis是为了避免横叉边
vector<int> nodes[maxn];
int cnt;
int dfn[maxn],low[maxn],tot;
bool vis[maxn];//instack
int S[maxn],top;
int id[maxn];
void tarjan(int x,int fa) {
    low[x]=dfn[x]=++tot;
    S[++top]=x;
    vis[x]=1;
    for(int i=head[x]; ~i; i=edge[i].next) {
        int v=edge[i].to;
        if(v==fa) continue;
        if(!dfn[v]) {
            tarjan(v,x);
            low[x]=min(low[x],low[v]);
        } else if(vis[v])
            low[x]=min(low[x],dfn[v]);
    }
    if(low[x]==dfn[x]) {
        cnt++;
        while(1) {
            int now=S[top--];
            vis[now]=0;
            id[now]=cnt;
            nodes[cnt].push_back(now);
            if(now==x) break;
        }
    }
}
int n,m;
int D[maxn],U[maxn],V[maxn];
set<pair<int,int> > H;
int ans,Ans;
int main() {
    int i;
    while(~scanf("%d%d",&n,&m)) {
        FOR(i,1,n) head[i]=-1,dfn[i]=0;
        FOR(i,1,cnt) D[i]=0;
        etot=tot=cnt=0;
        H.clear();
        FOR(i,1,m) {
            int u,v;
            scanf("%d%d",&u,&v);
            if(u>v) swap(u,v);
            if(H.count(make_pair(u,v))) continue;
            H.insert(make_pair(u,v));
            addedge(u,v);
            addedge(v,u);
            U[i]=u;
            V[i]=v;
        }
        Ans=0;
        tarjan(1,0);
        //  FOR(i,1,n) if (!dfn[i]) tarjan(i),Ans++;
        FOR(i,1,m) if(id[U[i]]!=id[V[i]]) D[id[U[i]]]++,D[id[V[i]]]++;
        FOR(i,1,tot) if(D[i]==1) Ans++;
        printf("%d\n",(Ans+1)/2);
    }
}
/*
*/
