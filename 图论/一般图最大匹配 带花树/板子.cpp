#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
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
const LL maxn=1e4+7;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a*=a) ret=1ll*ret*a%M; return ret;}

//缩奇环
//nowcoder2021七夕节题目:
//有k个set,每个set选两次算被选中,问能选几个set
//将set拆点之后就变成了一般图最大匹配
//很多这样的题拆点/边->点匹配都可以这么做, 边和点黑白染色后匹配即可
int n,m;
vector<int> edge[maxn];
bool inQueue[maxn];
int belong[maxn];
int getbelong(int x) {
    if (belong[x]==x) return x;
    return belong[x]=getbelong(belong[x]);
}
int match[maxn],nxt[maxn],mark[maxn],vis[maxn];
int cnt;
queue<int> Q;
int used[maxn];
int lca(int u,int v) {
    cnt++;
    while (1) {
        u=getbelong(u);
        if (vis[u]==cnt) return u;
        vis[u]=cnt;
        u=nxt[match[u]];
        if (v) swap(u,v);
    }
}
void merge(int u,int p) {
    while (u!=p) {
        int mu=match[u],v=nxt[mu];
        if (getbelong(v)!=p) nxt[v]=mu;
        if (mark[mu]==2) mark[mu]=1,Q.push(mu);
        if (mark[v]==2) mark[v]=1,Q.push(v);
        int x,y;
        x=getbelong(u),y=getbelong(mu);
        if (x!=y) belong[x]=y;
        x=getbelong(mu),y=getbelong(v);
        if (x!=y) belong[x]=y;
        u=v;
    }
}
void solve(int s) { //增广
    int i;
    FOR(i,1,n) belong[i]=i,mark[i]=nxt[i]=0;
    while (Q.size()) Q.pop();
    Q.push(s);
    while (Q.size()) {
        if (match[s]) return;
        int u=Q.front();
        Q.pop();
        for (int v:edge[u]) {
            if (match[u]==v) continue;
            if (getbelong(u)==getbelong(v)) continue;
            if (mark[v]==2) continue; //T型点
            if (mark[v]==1) { //S型点,缩点
                int p=lca(u,v);
                if (getbelong(u)!=p) nxt[u]=v;
                if (getbelong(v)!=p) nxt[v]=u;
                merge(u,p);
                merge(v,p);
            } else if (!match[v]) { //增广
                nxt[v]=u;
                for (int x=v; x;) {
                    int y=nxt[x],xx=match[y];
                    match[x]=y;
                    match[y]=x;
                    x=xx;
                }
                break;
            } else {
                nxt[v]=u;
                mark[match[v]]=1;
                Q.push(match[v]);
                mark[v]=2;
            }
        }
    }
}
bool E[maxn][maxn];
int ans;
int main() {
    scanf("%d%d",&n,&m);
    int i;
    while (m--) {
        int u,v;
        scanf("%d%d",&u,&v);
        if (u!=v&&!E[u][v]) {
            edge[u].push_back(v);
            edge[v].push_back(u);
            E[u][v]=E[v][u]=1;
        }
    }
    memset(match,0,sizeof(match));
    FOR(i,1,n) if (!match[i]) solve(i);
    FOR(i,1,n) if (match[i]) ans++;
    ans/=2;
    printf("%d\n",ans);
    FOR(i,1,n) printf("%d ",match[i]);
}
/*
*/
