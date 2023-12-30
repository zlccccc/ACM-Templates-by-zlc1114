// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
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
const LL maxn=2e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
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
        rFOR_(i,1,mx) g[i-1] = g[i]*i;
    }
    mint operator()(int a, int b) {
        if (a < b) return 0;
        return f[a]*g[b]*g[a-b];
    }
} C(maxn);

mint B[2007];
mint INV[10007];
mint SUM_N_K(int n,int k) {
    mint pw=1,now=0; int i;
    FOR_(i,1,k+1) {
        pw=pw*(n+1);
        now+=INV[k+1]*C(k+1,i)*B[k+1-i]*pw;
    }
    return now;
}
void initialize() {
    INV[0]=INV[1]=1;
    FOR_(i,2,10000) INV[i]=mint(mod-mod/i)*INV[mod%i];
    B[0]=1;
    FOR_(i,1,2000) FOR_(j,0,i-1) B[i]-=INV[i+1]*C(i+1,j)*B[j];
//    FOR(i,0,2000) printf("%lld ",B[i]);
}
// x个小于; y个大于均不满足的概率
// \sum [i/n]^x*[n-i+1/n]^y
mint pwsum[2007];
char op[2005];
int main() {
    initialize();
    int n,m;
    cin>>n>>m;
    FOR_(i,0,m) pwsum[i]=SUM_N_K(n,i); pwsum[0]-=1; // 0^0
    // FOR_(i,0,m) printf("%lld ",pwsum[i]); puts("<- pwsum");
    mint invn=mint(1)/n;
    FOR_(i,1,m) cin>>op[i];
    int x=0,y=0,z=0;
    FOR_(i,1,m) {
        auto Get=[&](int x,int y,int z) {
            mint ret;
            FOR_(k,0,y) {
                ret+=mint(n+1).pow(y-k)*mint(mod-1).pow(k)*C(y,k)*pwsum[x+k];
            }
            ret*=(mint(1)/mint(n)).pow(x+y);
            ret*=(mint(n-1)/mint(n)).pow(z);
            return ret;
        };
        mint pre=Get(x,y,z);
        if (op[i]=='=') z++;
        if (op[i]=='<') x++;
        if (op[i]=='>') y++;
        mint suf=Get(x,y,z);
        // printf("%lld --> %lld; div=%lld\n",pre.x,suf.x,(pre-suf).x);
        cout<<(pre-suf).x<<" ";
        if (i==m) cout<<suf.x<<" ";
    }
}
/*
10 2
< =
*/