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

#define DEBUG1
#ifdef DEBUG
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#define dbg(x)
#define dbgln(x)
#endif // DEBUG
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
const LL M=998244353;
const LL maxn=1e6+7;
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

// wannafly挑战赛16E
// 题意: 给个基环内向树, 每个点每时刻走1
// 问你最后某时刻 某个pos有几个点
// 做法是基环内向树dp一下, 分两部分贡献算一下
struct node {
    int l,r,val;
} T[maxn*20]; int ntot;
void ins(int &x,int pos,int L,int R) {
    if (!x) x=++ntot; T[x].val++;
    if (L==R) return;
    int mid=(L+R)/2;
    if (pos<=mid) ins(T[x].l,pos,L,mid);
    else ins(T[x].r,pos,mid+1,R);
}
int que(int x,int l,int r,int L,int R) {
    if (!x) return 0;
    if (l<=L&&R<=r) return T[x].val;
    int ret=0,mid=(L+R)/2;
    if (l<=mid) ret+=que(T[x].l,l,r,L,mid);
    if (mid<r) ret+=que(T[x].r,l,r,mid+1,R);
    return ret;
}

// 注意edge一定要加上; 而且一定要dfs
int A[maxn];
vector<int> cir,edge[maxn];
map<int,int> cirnum[maxn];
int vis[maxn],cfa[maxn],circnt[maxn],dep[maxn];
int in[maxn],out[maxn],dtot,ctot;
void dfs(int x,int depth,int cir_id) { // must dfs!
    vis[x]=1; in[x]=++dtot; cfa[x]=cir_id; dep[x]=depth;
    for (int v:edge[x]) dfs(v,depth+1,cir_id);
    out[x]=dtot;
}
void solve(int x) {
    cir.clear(); ctot++;
    while (A[x]&&!vis[A[x]]) x=A[x],vis[x]=1;
    while (A[x]&&vis[A[x]]==1) {
        vis[A[x]]=2; cir.push_back(x);
        cfa[x]=ctot; x=A[x];
    } int i; circnt[ctot]=cir.size();
    rREP(i,cir.size()-1) dep[cir[i]]=dep[A[cir[i]]]+1;
    for (int v:cir) for (int y:edge[v]) if (vis[y]!=2) dfs(y,1,v);
}

int n,m;
int root[maxn];
vector<pair<int,int> > t_t[maxn];
void update(int i,int k) {
    if (vis[k]==1) {
        ins(root[i+dep[k]],in[k],1,n);
        i+=dep[k]; k=cfa[k];
        t_t[i].push_back(make_pair(cfa[k],(i+dep[k])%circnt[cfa[k]]));
    } else cirnum[cfa[k]][(i+dep[k])%circnt[cfa[k]]]++;
}
int getans(int i,int k) {
    if (vis[k]==1) return que(root[i+dep[k]],in[k],out[k],1,n);
    else return cirnum[cfa[k]][(i+dep[k])%circnt[cfa[k]]];
}
int lastans;
int main() {
    int i,k;
    scanf("%d",&n);
    FOR(i,1,n) {
        scanf("%d",&A[i]);
        edge[A[i]].push_back(i);
    }
    FOR(i,1,n) if (!vis[i]) solve(i);
    scanf("%d",&m);
    FOR(i,1,m) {
        scanf("%d",&k);
        k^=lastans;
        update(i,k);
        for (auto now:t_t[i]) cirnum[now.first][now.second]++;
        lastans=getans(i,k);
        debug(" ans = ");
        printf("%d\n",lastans);
    }
    return 0;
}
/*
*/
