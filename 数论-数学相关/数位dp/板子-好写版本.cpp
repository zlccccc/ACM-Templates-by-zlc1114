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
// template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
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
        for (;t;t>>=1ll,cur=cur*cur)
            if (t&1) ret=ret*cur;
        return ret;
    }
    bool operator<(const mint &a)const { return x < a.x;}
    bool operator==(const mint &a)const { return x == a.x;}
};

// CF 1073 E
// 不同位数最多k个
int k;
const int MLEN=18; // max-length
bool vis[MLEN][1024][2];
pair<mint,mint> f[MLEN][1024][2];
int lval[MLEN],rval[MLEN];
ll pw10[MLEN]; // 位
pair<mint,mint> calc(int x,int bit,int not_0,int l_limit,int r_limit) {
    if (x==-1) return {__builtin_popcount(bit)<=k,0}; // cnt,sum
    if (!l_limit&&!r_limit&&vis[x][bit][not_0]) return f[x][bit][not_0];
    pair<mint,mint> ret={0,0};
    int l=0,r=9;
    if (l_limit) l=max(l,lval[x]);
    if (r_limit) r=min(r,rval[x]);
    FOR_(i,l,r) {
        int nxtbit=bit;
        if (not_0||i) nxtbit|=1<<i;
        pair<mint,mint> cur=calc(x-1,nxtbit,not_0||i,l_limit&&(i==l),r_limit&&(i==r));
        ret.first+=cur.first;
        ret.second+=cur.second+cur.first*pw10[x]*i;
    }
    // printf("x=%d; bit=%d; not0=%d; l_limit=%d; r_limit=%d; ret=%lld %lld\n",x,bit,not_0,l_limit,r_limit,ret.first.x,ret.second.x);
    if (!l_limit&&!r_limit) f[x][bit][not_0]=ret,vis[x][bit][not_0]=1;
    return ret;
}
mint calc(ll l,ll r) {
    pw10[0]=1;
    rep_(i,1,MLEN) pw10[i]=pw10[i-1]*10;
    REP_(i,MLEN) lval[i]=l%10,l/=10;
    REP_(i,MLEN) rval[i]=r%10,r/=10;
    return calc(MLEN,0,0,1,1).second;
}
int main() {
    ll l,r;
    scanf("%lld%lld%d",&l,&r,&k);
    // FOR_(i,l,r) printf("%d : %lld\n",i,calc(i,i).x);
    printf("%lld\n",calc(l,r).x);
}
/*
10
1 10
*/
