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
const LL maxn=2e5+7;
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

// Stern-Brocot树: 解决一系列分数比较的问题
// https://oi-wiki.org/math/number-theory/stern-brocot/
// 初始两个分数(0/1,1/0)
// 每次在相邻的两个分数(a/b,c/d)中间插入一个分数a+c/b+d作为一次迭代, 这样构建成了一颗树
// 本题要求给定一个小数r=0.xxxx最多18位, 求abs(r-p/q)最小值, 其中p和q有limit
// 所以我这里需要知道的是(a/b,c/d)这两个分数分别能下降到多少; 其中r在这个区间内部
// 当且仅当b+d大于等于limit, 或者a+c大于等于limit的时候, 就不能继续往下递归了
// 直接递归会T, 二分一下ax+b/cx+d;或者a+bx/c+dx这个x的系数就行了....
struct Frac {
    using type=__int128;
    type x,y;
    Frac(type x,type y):x(x),y(y) {
        // fix();
    };
    void fix() {
        type g=gcd(x,y);  // __int128的话__builtin_ctz失效,不能使用fastgcd
        x/=g; y/=g;
    }
    Frac operator - (const Frac& r)const
    {
        return Frac(x*r.y-y*r.x,y*r.y);
    }
    bool operator < (const Frac& r)const
    {
        return x*r.y<r.x*y;
    }
};
Frac input() {
    string s;
    cin>>s;
    bool should=0;
    ll x=0,y=1;
    for (char c:s) {
        if (c=='.') should=1;
        else {
            x=x*10+c-'0';
            if (should) y*=10;
        }
    }
    return Frac(x,y);
}
Frac solve(ll n,const Frac &target,const Frac &left,const Frac &right) {
    Frac mid(left.x+right.x,left.y+right.y);
    // printf("solve n=%lld\n  %lld/%lld  %lld/%lld\n",n,(ll)left.x,(ll)left.y,(ll)right.x,(ll)right.y);
    if (mid.y>n) return right-target<target-left?right:left;
    if (target<mid) {
        auto check=[&](__int128 k) {
            Frac cur=Frac(left.x*k+right.x,left.y*k+right.y);
            return target<cur&&cur.x<=n&&cur.y<=n;
        };
        __int128 l=1,r=1;
        while (check(r)) r*=2;
        while (l+1<r) {
            __int128 mid=(l+r)/2;
            if (check(mid)) l=mid;
            else r=mid;
        }
        return solve(n,target,left,Frac(left.x*l+right.x,left.y*l+right.y));
    } else if (mid<target) {
        auto check=[&](__int128 k) {
            Frac cur=Frac(left.x+right.x*k,left.y+right.y*k);
            return cur<target&&cur.x<=n&&cur.y<=n;
        };
        __int128 l=1,r=1;
        while (check(r)) r*=2;
        while (l+1<r) {
            __int128 mid=(l+r)/2;
            if (check(mid)) l=mid;
            else r=mid;
        }
        return solve(n,target,Frac(left.x+right.x*l,left.y+right.y*l),right);
    } else return mid;
}
int main() {
    Frac target=input();
    ll n; cin>>n;
    Frac res=solve(n,target,Frac(0,1),Frac(1,1));
    // cout<<(ll)target.x<<" "<<(ll)target.y<<endl;
    cout<<(ll)res.x<<" "<<(ll)res.y<<endl;
    // printf("%.16lf",(double)res.x/res.y);
    return 0;
}
/*
*/