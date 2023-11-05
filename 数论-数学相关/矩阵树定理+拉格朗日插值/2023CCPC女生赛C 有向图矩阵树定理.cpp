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
// const int mod=998244353;
// int mod=1;
template<int mod=998244353>
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

// 2023 CCPC女生赛C https://codeforces.com/gym/104725
// 给出一张n个点m条边的有向图,将这个图复制成K份,求整张图补图的以1为根的外向生成树的个数
// 也就是说可以从1到其他任何点,问生成树个数
// 有向图的矩阵树定理的话,就是u->v的时候,mat[u][v]--;mat[v][v]++即可
// 矩阵树定理,求det(A),假设原始有向图矩阵是B,那么A矩阵就是
// B1,-1,-1,...-1
// -1,B2,-1,...-1
// -1,-1,B3,...-1
// -1,-1,-1,...Bn
// 然后需要去除第一行第一列; 把-1都消掉就可以了
// 做法的话,如果不去掉第一列,竖列的和是0,可以先加到最底下Bn-n那行去
// 所以把第一行去掉的话,加完以后最后一列都是1; B1变成B1';然后Bn最后一行都是1;其他B2...都+1就可以了

struct Matrix {
    using type=mint<>;
    vector<vector<type>> D;
    int n;
    Matrix() {n=0;}
    Matrix(int n, int val = 0) : n(n), D(n, vector<type>(n, val)) {}
    vector<type>& operator[](const int &x) {return D[x];}
    const vector<type>& operator[](const int &x) const {return D[x];}
    Matrix lead(int k) { // 去除k行k列
        Matrix res(n - 1);
        REP_(i,n) {
            if(i == k) continue;
            REP_(j,n) {
                if(j == k) continue;
                res[i - (i > k)][j - (j > k)] = D[i][j];
            }
        }
        return res;
    }
    Matrix lead(const vector<int> &x, const vector<int> &y) { // 只有x行y列
        Matrix res(x.size());
        assert(x.size()==y.size());
        for(int i = 0; i < x.size(); i++) {
            for(int j = 0; j < y.size(); j++) {
                res[i][j] = D[x[i]][y[i]];
            }
        }
        return res;
    }
    type det() {
        type ans=1;
        REP_(i,n) {
            int r = i;
            while(r < n - 1 && D[r][i] == 0) r++;
            if (r != i) swap(D[r], D[i]), ans*=-1;
            if (D[i][i] == 0) return 0;
            type inv=type(1)/D[i][i];
            rep_(k,i+1,n) rrep_(j,i,n)
                D[k][j]-=D[k][i]*inv*D[i][j];
        }
        REP_(i,n) ans*=D[i][i];
        return ans;
    }
    void output() {
        REP_(i,n) {
            REP_(j,n) printf("%lld ",D[i][j].x);
            puts("");
        }
    }
};

int e[307][307];
int solve() {
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    Matrix ex(n),e0(n),ep(n),en(n);
    FOR_(i,1,n) FOR_(j,1,n) if (i!=j) e[i][j]=1;
    FOR_(i,1,m) {
        int x,y;
        scanf("%d%d",&x,&y); // 没有x->y的边
        e[x][y]=0;
    }

    FOR_(i,1,n) FOR_(j,1,n) if (e[i][j]) {
        int u=i-1,v=j-1;
        ex[u][v]-=1;
        ex[v][v]+=1;
    }
    REP_(i,n) ex[i][i]+=mint<>(k-1)*n;  // other
    if (k==1) return 0*printf("%lld\n",ex.lead(0).det().x);
    e0=ex; ep=ex; en=ex;
    rep_(i,1,n) rep_(j,0,n) e0[i][j]-=e0[0][j];
    e0=e0.lead(0);
    REP_(i,n) REP_(j,n) ep[i][j]+=1;
    REP_(j,n) en[n-1][j]=1;

    // puts("ex: ");
    // ex.output();
    // puts("e0: ");
    // e0.output();
    // puts("ep: ");
    // ep.output();
    // puts("en: ");
    // en.output();

    auto res=e0.det()*(ep.det().pow(k-2))*en.det();
    printf("%lld\n",res.x);
    return 0;
}
int main() {
    int T; T=1;
    FOR_(_,1,T) solve();
}
/*
*/