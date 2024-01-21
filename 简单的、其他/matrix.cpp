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
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL maxn=2e5+7;
const double pi=acos(-1.0);
const double eps=1e-10;
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
inline ll fastgcd(ll a, ll b) {  // __gcd()
    if (!a) return b;
    ll az=__builtin_ctzll(a),bz=__builtin_ctzll(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctzll(diff);
        (b>a)&&(b=a); a=abs(diff);
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
istream & operator>>(istream &o,mint &a) { o>>a.x; a=a.fix(); return o; }
ostream & operator<<(ostream &o,const mint &a) { o<<a.x; return o; }

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

template<int N,typename T>
struct matrix:array<array<T,N>,N> {
    matrix(T val=0) {REP_(i,N) (*this)[i].fill(val);}
    matrix operator +(const matrix &mat) {
        matrix ret;
        REP_(i,N) REP_(j,N)
            ret[i][j]=(*this)[i][j]+mat[i][j];
        return ret;
    }
    matrix operator -(const matrix &mat) {
        matrix ret;
        REP_(i,N) REP_(j,N)
            ret[i][j]=(*this)[i][j]-mat[i][j];
        return ret;
    }
    matrix operator *(const matrix &mat) {
        matrix ret;
        REP_(i,N) REP_(k,N) REP_(j,N)
            ret[i][j]+=(*this)[i][k]*mat[k][j];
        return ret;
    }
    constexpr matrix I() const {
        matrix res;
        REP_(i,N) res[i][i]=1;
        return res;
    }
    matrix pow(long long t) const {
        matrix ret=I(),cur=*this;
        for (; t; t>>=1ll,cur=cur*cur)
            if (t&1) ret=ret*cur;
        return ret;
    }
    void print() {
        REP_(i,N) {
            REP_(j,N) cout<<(*this)[i][j]<<' ';
            cout<<"\n";
        }
    }
};
// ARC170E
// https://atcoder.jp/contests/arc170/tasks/arc170_e
// 题意: 给一个长度为n的环N
// 从1出发进行bfs染色,假设v可以到x(1的话先x=2再x=n),你要维护一个queue
// 那么会把{x,f[v]+1}以P的概率push到queue的front,1-P的概率push到queue的back
// 从queue里面去取数字,然后如果没vis过,就把数字填到f里面去
// 比如可能染完以后颜色是0 [1 2 3 4 5 6] [3 2 1]这样;问最后这个f的sum的概率

// 做法: 染色总共染了n-1次,假设左边染了x次右边染了y次,答案就是x(x+1)/2+y(y+1)/2;
// 答案就等价于[被染色的格子里面选i<=j的两个位置]的数量
// 然后queue的大小就是2,因为除了1以外,其他数字都是有1个相邻的
// 把一个x放到queue前面相当于不更换type; 大概就是dp-status={L-{prob,L1,R1},R-{prob,L1,R1},Sum2}算下转移
// 所以直接矩阵快速幂

using type=mint;
// using type=double;
int solve() {
    ll n; type p;
    cin>>n>>p; p/=100;
    matrix<7,type> mat;  // status: L-status[p,l1,r1],R-status[p,l1,r1],l2(枚举俩)
    // 初始状态是R(先算2再算n), 也就是3
    mat[0][0]=p; mat[0][3]=type(1)-p; // 1-p概率更换status
    mat[0][1]=p; mat[0][5]=type(1)-p; // 加到L1或者R1(L或者R期望次数)
    mat[1][1]=p; mat[1][4]=type(1)-p; mat[1][6]=p; // L; p概率加到answer
    mat[2][2]=p; mat[2][5]=type(1)-p; mat[2][6]=type(1)-p; // R; 1-p概率加到answer

    mat[3][3]=p; mat[3][0]=type(1)-p; // 1-p概率更换status
    mat[3][5]=p; mat[3][1]=type(1)-p; // 加到L1或者R1(L或者R期望次数)
    mat[4][4]=p; mat[4][1]=type(1)-p; mat[4][6]=type(1)-p; // L; p概率加到answer
    mat[5][5]=p; mat[5][2]=type(1)-p; mat[5][6]=p; // R; 1-p概率加到answer

    mat[6][6]=1;  // 累加; sum_i-pre = i*(i-1)/2

    auto fin=mat.pow(n-1);
    type res=fin[3][1]+fin[3][2]+fin[3][4]+fin[3][5]+fin[3][6];
    cout<<res<<"\n";
    return 0;
}
int main() {
    int T; T=1;
    cin>>T;
    // scanf("%d",&T);
    startTimer();
    FOR_(_,1,T) {
        solve();
    }
    // printTimer();
}
/*
10 3
0 0 1 0 0 0 1 0 1 0
*/