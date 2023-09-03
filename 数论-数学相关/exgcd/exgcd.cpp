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
const LL maxn=1e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
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

const int mod = 998244353;
struct mint {
    long long x;
    mint():x(0) {}
    mint(long long x):x((x%mod+mod)%mod) {}
    // mint(long long x):x(x){}
    mint &fix() { x = (x%mod+mod)%mod; return *this;}
    mint operator-() const { return mint(0) - *this;}
    // mint operator~() const { return mint(1) / *this;}
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
        for (;t;t>>=1ll,cur=cur*cur)
            if (t&1) ret=ret*cur;
        return ret;
    }
    bool operator<(const mint &a)const { return x < a.x;}
    bool operator==(const mint &a)const { return x == a.x;}
};
struct comb {
    vector<mint> fac,inv; // f:fac; g:inv
    comb() {}
    comb(int MAX):fac(MAX),inv(MAX) {
        fac[0] = 1;
        rep_(i,1,MAX) fac[i] = fac[i-1]*i;
        inv[MAX-1] = fac[MAX-1].pow(mod-2);
        rrep_(i,1,MAX) inv[i-1] = inv[i]*i;
    }
    mint operator()(int a, int b) {
        if (a < b) return 0;
        return fac[a]*inv[b]*inv[a-b];
    }
} C(maxn);

// exgcd
void exgcd(__int128 a,__int128 b,__int128 &d,__int128 &x,__int128 &y){//d==0时存在逆元 //(x+p)%p为逆元
    if (!b) {d=a;x=1;y=0;}
    else {exgcd(b,a%b,d,y,x);y-=a/b*x;}
}
// 求l->r范围内的x
pair<__int128,__int128> limit(__int128 a,__int128 b,__int128 l,__int128 r) { // l<=ax+b<=r
    // ll A=a,B=b,L=l,R=r;
    if (a<0) a=-a,b=-b,l=-l,r=-r,swap(l,r);
    if (a==0) {
        if (l<=b&&b<=r) return {-INFF,INFF};
        else return {1,0}; // zero
    }
    l=l-b+a-1; r=r-b;
    ll fl=l/a,fr=r/a;
    if (l-fl*a<0) fl--;
    if (r-fr*a<0) fr--;
    // FOR_(x,fl,fr) printf("%lld(%lld,%lld->%lld) ",A*x+B,a*x+b,L,R); puts("  <- solve");
    return {fl,fr};
}
// Ax+By=C求通解,1<=x,y<=MAX; 计算过程中可能很大
ll solve(__int128 A,__int128 B,__int128 C,__int128 MAX) { // A*(x+kb)+B*(y-ka)=C
    __int128 d,x,y;
    exgcd(A,B,d,x,y);
    if (C%d!=0) return 0; // d=gcd,这个是没有解
    // printf("solve %lld %lld %lld\n",A,B,C);
    __int128 a=A/d,b=B/d,c=C/d;
    x=x*c; y=y*c;
    // 合法的解: x'=x+kb; y'=y-ka;

    // printf("solve %lld x + %lld y = %lld; sum=%lld; x,y=%lld %lld\n",a,b,c,x*A+y*B,x,y);

    pair<__int128,__int128> limx=limit(b,x,1,MAX);
    pair<__int128,__int128> limy=limit(-a,y,1,MAX);

    // printf("solve lx,rx=%lld %lld; ly,ry=%lld %lld\n",limx.first,limx.second,limy.first,limy.second);

    __int128 left=max(limx.first,limy.first),right=min(limx.second,limy.second);
    // FOR_(k,left,right) {
    //     ll dx=x+k*b,dy=y-k*a;
    //     printf("solve %lld x + %lld y = %lld; sum=%lld; k=%d, x,y=%lld %lld\n",a,b,c,dx*A+dy*B,k,dx,dy);
    // }
    if (left<=right) return right-left+1;
    else return 0;
}
// ATC 315G
// 题意:Ax+By+Cz=X,1<=x,y<=N,求答案
int main() {
    int T,_; T=1;
    // T=10000;
    // scanf("%d",&T);
    FOR(_,1,T){
        ll N,A,B,C,X;
        ll ans=0;
        scanf("%lld%lld%lld%lld%lld",&N,&A,&B,&C,&X);
        FOR_(i,1,N) {
            if (X-C*i<=0) break;
            ans+=solve(A,B,X-C*i,N);
        }
        printf("%lld\n",ans);
    }
}
/*
5 3 4 5 40

*/