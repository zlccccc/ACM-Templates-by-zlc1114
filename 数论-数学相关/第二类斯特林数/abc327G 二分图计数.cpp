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
#define REP_(I,N) for (int I=0,END=(N);I<END;I++)
#define rREP_(I,N) for (int I=(N)-1;I>=0;I--)
#define rep_(I,S,N) for (int I=(S),END=(N);I<END;I++)
#define rrep_(I,S,N) for (int I=(N)-1,START=(S);I>=START;I--)
#define FOR_(I,S,N) for (int I=(S),END=(N);I<=END;I++)
#define rFOR_(I,S,N) for (int I=(N),START=(S);I>=START;I--)

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
template<typename T>inline void add_(T &A,int B,ll MOD) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD) {A%=MOD; A+=MOD; A%=MOD;}
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
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

// const int mod = 1e9+7;
const int mod=998244353;
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
struct comb {
    vector<mint> f, g; // f:fac; g:inv
    comb() {}
    comb(int mx):f(mx+1),g(mx+1) {
        f[0] = 1;
        FOR_(i,1,mx) f[i] = f[i-1]*i;
        g[mx] = f[mx].pow(mod-2);
        for (int i=mx;i>0;i--) g[i-1] = g[i]*i;
    }
    mint operator()(int a, int b) {
        if (a < b) return 0;
        return f[a]*g[b]*g[a-b];
    }
} C(maxn);

// 第二类斯特林数: https://www.cnblogs.com/gzy-cjoier/p/8426987.html
// 有n个不同的小球, 要放在m个相同的盒子中, 且每个盒子不能为空, 问有多少种方案
// 枚举最后一个小球是单独一个箱子还是和之前一个盒子
// S(n,m)=S(n-1,m-1)+m*S(n,m)
// 容斥空的盒子个数,可以得到:
// S(n,m)=1/m!*\sum_i (-1)^i*C(m,i)*(m-i)^n; 其中1/m!是因为m个盒子相同; 这个是个卷积形式,mlogm可以都求出来
// 所以m^n=\sum S(n,k)*C(m,k)*k!; 先枚举m个盒子k个不为空, 然后直接放进去就可以了

// 题意: 问m条边组成的图可以是二分图的list数量, 边的id在n<=30内
// 比如vector<>{(1,2)(2,3)(2,4)}这种; 问list数量(不是二分图数量)
// 先init()求n个点m条边的无重边二分图个数; 然后第二类斯特林数搞一下就行了
mint pw[maxn];
// g: n个点m条边二分图数量(n个点颜色0/1,不需要连通); 枚举n个点哪些点是0哪些点是1即可
// h: m条边需要连通的数量 // 枚举最后一个node所在的块有多少个点/多少个边;
// f: 边用uid[x-y]区分; 如果边不可重复数量是多少;  // 枚举最后一个node所在的块有多少个点/多少个边
mint g[37][907],h[37][907],f[37][907];
void init() {
    const int MAX=30;
    mint inv2=mint(1)/2;
    FOR_(i,1,MAX) {
        FOR_(j,0,i) FOR_(k,0,j*(i-j))
            g[i][k]+=C(i,j)*C(j*(i-j),k); // j个0

        // h[i][k]需要/2; // n个点颜色未知; 也就是说之前同构的图01和10算了两次
        FOR_(k,0,i*(i-1)/2) {
            h[i][k]=g[i][k];
            FOR_(x,1,i-1) FOR_(y,0,x*(x-1)/2) // 枚举最后一个node所在的块有多少个点/多少个边
                h[i][k]-=C(i-1,x-1)*h[x][y]*g[i-x][k-y];
        }

        FOR_(k,0,i*(i-1)/2) {
            f[i][k]=h[i][k]*inv2;
            FOR_(x,1,i-1) FOR_(y,0,x*(x-1)/2) // 枚举最后一个node所在的块有多少个点/多少个边
                f[i][k]+=C(i-1,x-1)*h[x][y]*inv2*f[i-x][k-y];
        }
        // printf("i=%d\n",i);
        // FOR_(k,0,i*(i-1)) printf("%lld ",g[i][k]); puts(" <- g");
        // FOR_(k,0,i*(i-1)) printf("%lld ",h[i][k]/2); puts(" <- h");
        // FOR_(k,0,i*(i-1)) printf("%lld ",f[i][k]); puts(" <- f");
    }
}
void solve() {
    int n,m;
    scanf("%d%d",&n,&m);
    FOR_(i,0,n*n) pw[i]=mint(i).pow(m);
    mint res;
    FOR_(i,0,n*(n-1)/2) {
        if (f[n][i].x==0) continue;
        mint stirling;  // 第二类斯特林数
        FOR_(j,0,i) stirling+=(j-i)%2==0?C(i,j)*pw[j]:-C(i,j)*pw[j];
        // printf("%d: %lld * %lld\n",i,f[n][i].x,stirling.x);
        res+=f[n][i]*stirling;
    }
    res*=pw[2];
    printf("%lld\n",res.x);
}
int main() {
    init();
    int T; T=1;
    // scanf("%d",&T);
    // while (1) solve();
    FOR_(_,1,T){
        solve();
    }
}
/*
3 2
3 3
12 34
20 231104

36
168
539029838
966200489
*/