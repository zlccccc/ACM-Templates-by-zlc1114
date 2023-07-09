// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <sstream>
#include <fstream>
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
#include <bitset>
#include <functional>
#include <random>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define REP_(I,N) for (int I=0;I<N;I++)
#define rREP_(I,N) for (int I=N-1;I>=0;I--)
#define rep_(I,S,N) for (int I=S;I<N;I++)
#define rrep_(I,S,N) for (int I=N-1;I>=S;I--)
#define FOR_(I,S,N) for (int I=S;I<=N;I++)
#define rFOR_(I,S,N) for (int I=N;I>=S;I--)

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
// const LL M=1e9+7;
const LL M=998244353;
// ll M=1;
const LL maxn=2e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T fastgcd(T a, T b) {
    int az=__builtin_ctz(a),bz=__builtin_ctz(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctz(diff);
        min_(b,a); a=abs(diff);
    }
    return b<<z;
}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
typedef array<int,2> ar2;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

// CF 1814F
// 题意: x-y的边在l-r存在,求问对于所有l-r,1这个节点出发dfs能到的节点有哪些
// 做法: 首先是个按秩合并撤销并查集+CDQ分治
// 然后从1这个节点出发dfs可以认为是先按CDQ每一层加边,然后每层往下一层新建dfs边
// 等价于rollback的时候加一条边,每个时间点从root出发都是一颗树
// rollback的时候可以把很多棵树合并起来计算 (tag)
int tag[maxn]; // 按秩合并的话可以做到rollback的时候pushdown (x=i的时候从某个位置出发,询问有多少id可达)

template<bool path_compression=true>
struct DSU {
    vector<int> checkpoint_;
    vector<pii> changes_;
    vector<int> fa; // fa[x]<0: root; and we save its size
    DSU(int n) {fa.resize(n+1,-1);} // fa<0: size; else: real-getfather
    inline int getfa(int x) {
        if (path_compression) {
            if (fa[x]<0) return x;
            int ret=getfa(fa[x]);
            if (ret!=fa[x]) changes_.push_back({x,fa[x]});
            return fa[x]=ret;
        } else {
            while (fa[x]>=0) x=fa[x];
            return x;
        }
    }
    void checkpoint() {
        checkpoint_.push_back(changes_.size());
    }
    inline void undo() { // single undo
        pii p=changes_.back();
        if (fa[p.first]>=0) tag[p.first]+=tag[fa[p.first]]; // pushdown
        // if (fa[p.first]>=0) printf(" ======= undo %d %d: pushdown tag=%d %d\n",p.first,fa[p.first],tag[p.first],tag[p.second]);
        fa[p.first]=p.second;
        changes_.pop_back();
    }
    void rollback() { // rollback to checkpoint (stack)
        while ((int)changes_.size()!=checkpoint_.back()) undo();
        checkpoint_.pop_back();
    }
    void merge(int x,int y) {
        x=getfa(x); y=getfa(y);
        if (x==y) return;
        if (-fa[x]>-fa[y]) swap(x,y);
        changes_.push_back({x,fa[x]});
        changes_.push_back({y,fa[y]});
        fa[y]+=fa[x]; fa[x]=y; // sz and fa

        tag[x]-=tag[y]; // initial value to pushdown
        // printf(" -- -merge %d %d: pushup tag=%d %d; fa_1=%d\n",x,y,tag[x],tag[y],getfa(1));
    }
};
DSU<false> dsu(maxn);

void solve(int l,int r,vector<ar4> E) {
    // printf("solve %d=%d\n",l,r);
    vector<ar4> el,er;
    dsu.checkpoint();
    int mid=(l+r)/2;
    for (auto e:E) {
        if (e[0]<=l&&r<=e[1]) {
            dsu.merge(e[2],e[3]);
            continue;
        }
        if (e[0]<=mid) el.push_back(e);
        if (mid<e[1]) er.push_back(e);
    }
    if (l!=r) {
        solve(l,mid,el);
        solve(mid+1,r,er);
    } else tag[dsu.getfa(1)]++; // l=r的时候从1出发dfs,能够dfs到的点tag++(rollback的时候并查集的tag一起计算了)
    // printf("rollback %d=%d\n",l,r);
    dsu.rollback();
}
int L[maxn],R[maxn];
int main() {
    int n,m;
    scanf("%d%d",&n,&m);
    FOR_(i,1,n) scanf("%d%d",&L[i],&R[i]);
    vector<ar4> e;
    FOR_(i,1,m) {
        int x,y;
        scanf("%d%d",&x,&y);
        int l=max(L[x],L[y]);
        int r=min(R[x],R[y]);
        if (l<=r) e.push_back({l,r,x,y});
        // printf("edge %d->%d: l,r=%d %d\n",x,y,l,r);
    }
    tag[1]=1;
    solve(1,200000,e);
    vector<int> ans;
    FOR_(i,1,n) if (tag[i]) ans.push_back(i);
    for (int v:ans) printf("%d ",v);
}