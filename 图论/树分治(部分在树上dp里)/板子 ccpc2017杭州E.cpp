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

#define DEBUG
#ifdef DEBUG
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#define dbg(x)
#define dbgln(x)
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

//HDU6268
//ccpc2017杭州
//树分治后 树形依赖DP
int A[maxn];
vector<int> edge[maxn];
int sz[maxn];
bool mark[maxn];
int minweight,root;
void dfs1(int x,int fa,int n) {
    int weight=0; sz[x]=1;
    for (int v:edge[x]) {
        if (v==fa||mark[v]) continue;
        dfs1(v,x,n); sz[x]+=sz[v];
        weight=max(weight,sz[v]);
    } weight=max(weight,n-sz[x]);
    if (weight<minweight) root=x,minweight=weight;
}
bitset<100007> now[3007],ans;//depth
void dfs2(int x,int fa,int dep) {
    now[dep]=now[dep-1]; sz[x]=1;
    for (int v:edge[x]) {
        if (v==fa||mark[v]) continue;
        dfs2(v,x,dep+1); sz[x]+=sz[v];
    } now[dep-1]|=now[dep]<<A[x];
}
void calc(int x){
    now[0].reset(); now[0].set(0);
    dfs2(x,0,1); ans|=now[0];
}
void dfs3(int x) {
    debug("dfs3:%d\n",x);
    calc(x); mark[x]=1;
    for (int v:edge[x]) {
        if (mark[v]) continue;
        minweight=sz[v];
        dfs1(v,0,sz[v]);
        dfs3(root);
    }
}
int main() {
    int n,m,T;
    int i;
    scanf("%d",&T);
    while (T--) {
        scanf("%d%d",&n,&m);
        REP(i,n-1) {
            int u,v;
            scanf("%d%d",&u,&v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        } FOR(i,1,n) scanf("%d",&A[i]);
        minweight=n;
        dfs1(1,0,n); dfs3(root);
        FOR(i,1,m) printf("%d",(int)ans[i]);
        puts("");
        ans.reset();
        FOR(i,1,n) edge[i].clear(),mark[i]=0;
    }
    return 0;
}
/*
10
4 10 1 2 2 3 3 4 3 2 7 5
6 10 1 2 1 3 2 5 3 4 3 6 1 3 5 7 9 11

4 16
1 2 2 3 3 4
1 2 4 8
*/
