#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=1e5+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const double eps=0.000000001;
const double pi=acos(-1);
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}


vector<int> edge[maxn];
int fa1[maxn],fa2[maxn];
inline int getfa(int *fa,int x) {
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa,fa[x]);
}
int n,m,q,i,k,u,v;
int ans[maxn];
vector<pair<int,int> > Q[maxn];//v,id
void dfs(int x) {
    int i;
    for (int v:edge[x]) {
        dfs(v); fa2[v]=x;
    }
    REP(i,Q[x].size()) {
        if (fa2[Q[x][i].first]!=Q[x][i].first)
            ans[Q[x][i].second]=getfa(fa2,Q[x][i].first);
    }
}
void solve() {
    scanf("%d%d%d",&n,&m,&q);
    FOR(i,1,n) fa1[i]=fa2[i]=i;
    REP(i,m) {
        scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        fa1[v]=u;
    }
    REP(i,q) {
        scanf("%d%d%d",&k,&u,&v);
        if (k==1) {
            if (getfa(fa1,u)!=getfa(fa1,v)) ans[i]=-1;
            else {
                if (u==v) ans[i]=u;
                else {
                    Q[u].push_back(make_pair(v,i));
                    Q[v].push_back(make_pair(u,i));
                }
            }
        } else {
            edge[u].push_back(v);
            fa1[v]=u; ans[i]=0;
        }
    }
    FOR(i,1,n) if (fa1[i]==i) dfs(i);
    FOR(i,1,n) edge[i].clear(),Q[i].clear();
    REP(i,q) if (ans[i]) printf("%d\n",ans[i]);
}
int T;
int main() {
    scanf("%d",&T);
    while (T--) solve();
}
