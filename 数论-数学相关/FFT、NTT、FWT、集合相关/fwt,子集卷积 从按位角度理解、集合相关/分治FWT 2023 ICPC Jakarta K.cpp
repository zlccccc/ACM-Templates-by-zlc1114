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
const LL maxn=1e6+7;
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

mint inv2=mint(1)/2;
void fwt(vector<mint> &A,int inv)//对拍对了 
{
    int len=A.size();
    int i,j,k;
    for(i=2;i<=len;i<<=1){
        for(j=0;j<len;j+=i){
            for(k=j;k<j+i/2;k++){
                // printf("len=%d; k=%d; i=%d\n",len,k,i);
                if (inv==1){
                    mint a=A[k],b=A[k+i/2];
                    A[k]=a+b;
                    A[k+i/2]=a-b;
                }else{
                    mint a=A[k],b=A[k+i/2];
                    A[k]=(a+b)*inv2;
                    A[k+i/2]=(a-b)*inv2;
                }
            }
        }
    }
}
vector<mint> conv(vector<mint> A,vector<mint> B) {
    fwt(A,1); fwt(B,1);
    REP_(i,A.size()) A[i]*=B[i];
    fwt(A,-1);
    return A;
}

// 题意的话是, 给定n个数字, 然后你要选两个子集出来, 问两个子集xor相同的集合数量有多少种
// 也就是1+2*x^k, FWT乘积问f[0]答案是多少
// 分治FWT做法: 枚举左右分别选择了多少个数字; ret[0]和ret[1]分别就是用了0/1个数字
// 考虑a=[l,l+p)和b=[l+p,r)两个子集合并过程
// 如果b选的子集个数=1那么最终生成的res范围在[l+p,r); 否则res范围在[l,l+p)
mint pw2[maxn];
int Cnt[maxn];
array<vector<mint>,2> solve(int l,int r) {
    if (l+1==r) {
        array<vector<mint>,2> ret({vector<mint>(1),vector<mint>(1)});
        FOR_(i,0,Cnt[l]) ret[i&1][0]+=C(Cnt[l],i)*pw2[i];
        return ret;
    } else {
        int p=(r-l)/2;
        array<vector<mint>,2> a=solve(l,l+p);
        array<vector<mint>,2> b=solve(l+p,r);
        array<vector<mint>,2> ret({vector<mint>(p*2),vector<mint>(p*2)});
        // printf("solve [%d -> %d)\n",l,r);
        // for (mint v:a[0]) printf("%lld ",v.x); puts(" <- a[0]");
        // for (mint v:a[1]) printf("%lld ",v.x); puts(" <- a[1]");
        // for (mint v:b[0]) printf("%lld ",v.x); puts(" <- b[0]");
        // for (mint v:b[1]) printf("%lld ",v.x); puts(" <- b[1]");
        REP_(x,2) REP_(y,2) {
            auto vec=conv(a[x],b[y]);
            REP_(i,p) ret[x^y][(y&1)*p+i]+=vec[i];
        }
        return ret;
    }
}
int val[maxn];
int main() {
    pw2[0]=1;
    rep_(i,1,maxn) pw2[i]=pw2[i-1]*2;
    int n,MAX=1;
    cin>>n;
    FOR_(i,1,n) cin>>val[i],max_(MAX,val[i]),Cnt[val[i]]++;
    int len=1;
    while (len<=MAX) len<<=1;
    auto res=solve(0,len);
    cout<<(res[0][0]+res[1][0]).x;
}
/*
*/