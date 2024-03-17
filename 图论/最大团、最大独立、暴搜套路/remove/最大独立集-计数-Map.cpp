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
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T fastgcd(T a, T b) {
    int az=__builtin_ctzll(a),bz=__builtin_ctzll(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctzll(diff);
        min_(b,a); a=abs(diff);
    }
    return b<<z;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

const int mod = 1e9+7;
// const int mod=998244353;
// int mod=1;
struct mint {
    long long x;
    mint():x(0) {}
    mint(long long x):x((x%mod+mod)%mod) {}
    // mint(long long x):x(x){}
    mint &fix() { x = (x%mod+mod)%mod; return *this;}
    mint operator-() const { return mint(0) - *this;}
    mint operator~() const { return mint(1) / *this;}
    mint &operator+=(const mint &a) { if ((x+=a.x)>=mod) x-=mod; return *this;}
    mint &operator-=(const mint &a) { if ((x+=mod-a.x)>=mod) x-=mod; return *this;}
    mint &operator*=(const mint &a) { (x*=a.x)%=mod; return *this;}
    mint &operator/=(const mint &a) { (x*=a.pow(mod-2).x)%=mod; return *this;}
    mint operator+(const mint &a)const { return mint(*this) += a;}
    mint operator-(const mint &a)const { return mint(*this) -= a;}
    mint operator*(const mint &a)const { return mint(*this) *= a;}
    mint operator/(const mint &a)const { return mint(*this) /= a;}
    mint pow(long long t) const {
        mint ret=1,cur=x;
        for (; t; t>>=1ll,cur=cur*cur)
            if (t&1) ret=ret*cur;
        return ret;
    }
    bool operator<(const mint &a)const { return x < a.x;}
    bool operator==(const mint &a)const { return x == a.x;}
};

// 0、N比较大的时候可以试试随机shuffle一下贪心选择,或者转化为二分图
// 1、最大团点的数量=补图中最大独立集点的数量
// 2、二分图中，最大独立集+最小点覆盖=整个图的点数量
// 3、二分图中，最小点覆盖=最大匹配
// 4、二分图中，最小边覆盖=最大独立集
// 5、图的染色问题中，最少需要的颜色的数量=最大团点的数量

// 一般图最大团/计数:复杂度可以做到2^(n/2),加剪枝60应该没问题
// CCPC2023网络赛C
// 题意:n=1000; m=1000; 求团个数, 答案mod 1e9+7
// 按度数排一下序, 对于每个团, 枚举团中最小编号的点, 求答案加起来
// 那么团中的每个点向右最多sqrt(2m)条边(因为如果度数为k, 右边每个点度数都>=k)
// 答案加上[i的adj edge的团数量]

// 团和补图独立集是等价的; 求团的数量=求补图独立集数量
// 考虑一个n个点的连通图, 计算最大团个数: 枚举编号最大的点直接暴力复杂度是2^n
// 但是如果记忆化一下2^(n/2)，那么复杂度会变成2^(n/2)
// 这里就是枚举一下最大那个u是否被选择过了, dp[S]=dp[S^(1<<u)]+dp[S^(1<<u)^adj[u]];

// 状态数量很多所以这里只能记忆化一部分
// 但是很容易被卡满; 可以加剪枝
// 1.枚举的u度数最大
// 2.如果可以把团分成不相交的两份, 那就直接分成两半去搞然后乘起来

// 最差时间复杂度是, sqrt个点度数是sqrt, 总复杂度sqrt*2^(sqrt/2)=sqrt*1.414^sqrt

struct IndependentSet {  // ull in {int, long long}; 代表点数量>=k
    // 状态压缩一下N; N不要太大否则状态都存不下
    map<ull,ull> MP; // 记忆化
    vector<ull> edge;
    IndependentSet(int n=0) {init(n);}
    void init(int n) {
        assert(n<64);
        MP.clear();
        edge.resize(n);
        fill(edge.begin(),edge.end(),0);
    }
    void addedge(int x,int y) {
        assert(max(x,y)<edge.size());
        // printf("addedge %d %d\n",x,y);
        edge[x]|=1ull<<y;
        edge[y]|=1ull<<x;
    }
    void flip() { // 变成补图(团=补图独立集)
        for (ull &e:edge) e^=(1ull<<edge.size())-1;
    }
    ull independent_set(ull S) {
        // printf("solve %lld ",S);
        // pr2(S,edge.size());
        // puts("");
        // S: 当前存在哪些id set
        if (!S) return 1;
        if (MP.count(S)) return MP[S];
        int c=__builtin_popcountll(S),id=__builtin_ctzll(S),mxsz=-1;
        if (c>=10) { // 2.如果可以把团分成不相交的两份, 那就直接分成两半去搞然后乘起来
            auto mask=S; // mask:从id能走到的点
            for (auto cur=1ull<<id; cur;) {
                int x=__builtin_ctzll(cur); mask^=1ull<<x;
                cur=(cur|edge[x])&mask;
            }
            if (mask) { // 可以分成两块
                ull res1=independent_set(mask),res2=independent_set(S^mask);
                ull ans=res1*res2;
                return ans;
            }
        }
        for (auto cur=S; cur;) { // 1.枚举的点度数最大
            int x=__builtin_ctzll(cur),cursz=__builtin_popcountll(S&edge[x]);
            if (cursz>mxsz) mxsz=cursz,id=x;
            cur^=1ull<<x;
        }
        ull res1=independent_set(S^1ull<<id);
        ull res2=independent_set(S&~(edge[id]|1ull<<id));
        ull ans=res1+res2;
        if (c<=(int)edge.size()/2) MP[S]=ans;
        return ans;
    }
};

template<typename T>
T count_clique(vector<vector<int>> edge) {
    int n=edge.size();
    vector<int> deg(n),reid(n,-1);
    REP_(i,n) deg[i]=edge[i].size();
    T ans=0;
    IndependentSet clique;
    REP_(i,n) {
        int x=-1,cur_n=0;
        REP_(k,n) if (deg[k]!=-1&&(x==-1||deg[k]<deg[x])) x=k;
        deg[x]=-1;
        for (int y:edge[x]) if (deg[y]!=-1) reid[y]=cur_n++;
        clique.init(cur_n);
        for (int y:edge[x]) if (reid[y]!=-1)
            for (int z:edge[y]) if (reid[z]!=-1)
                    clique.addedge(reid[y],reid[z]);
        clique.flip();
        ans+=clique.independent_set((1ull<<cur_n)-1);
        for (int y:edge[x]) reid[y]=-1;
    }
    return ans;
}

int solve() {
    int n,m;
    scanf("%d%d",&n,&m);
    vector<vector<int>> edge(n);
    FOR_(i,1,m) {
        int x,y;
        scanf("%d%d",&x,&y);
        x--; y--;
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    printf("%lld\n",count_clique<mint>(edge).x);
    return 0;
}

int main() {
    solve();
    // while (1) solve();
}
/*
3 2
1 2
2 3

3 3
1 2
1 3
2 3
*/