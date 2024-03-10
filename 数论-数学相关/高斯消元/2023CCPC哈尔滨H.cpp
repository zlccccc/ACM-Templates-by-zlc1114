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
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=1e-10;
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
inline ll fastgcd(ll a, ll b) {  // __gcd()
    if (!b) return a;
    ll az=__builtin_ctzll(a),bz=__builtin_ctzll(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az, diff=b-a, az=__builtin_ctzll(diff);
        (b>a)&&(b=a), a=abs(diff);
    }
    return b<<z;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
typedef array<int,2> ar2;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));
vector<pii> direction4 = {{-1,0},{0,-1},{0,1},{1,0}};
vector<pii> direction8 = {{-1,-1},{-1,0},{1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

// const int mod = 1e9+7;
const int mod=998244353;
struct mint {
    long long x;
    mint():x(0) {}
    mint(long long x):x((x%mod+mod)%mod) {}
    // mint(long long x):x(x){}
    mint &fix() { x = (x%mod+mod)%mod; return *this; }
    mint operator-() const { return mint(0) - *this; }
    mint operator~() const { return mint(1) / *this; }
    mint &operator+=(const mint &a) { if ((x+=a.x)>=mod) x-=mod; return *this; }
    mint &operator-=(const mint &a) { if ((x+=mod-a.x)>=mod) x-=mod; return *this; }
    mint &operator*=(const mint &a) { (x*=a.x)%=mod; return *this; }
    mint &operator/=(const mint &a) { (x*=a.pow(mod-2).x)%=mod; return *this; }
    mint operator+(const mint &a)const { return mint(*this) += a; }
    mint operator-(const mint &a)const { return mint(*this) -= a; }
    mint operator*(const mint &a)const { return mint(*this) *= a; }
    mint operator/(const mint &a)const { return mint(*this) /= a; }
    mint pow(long long t) const {
        mint ret=1,cur=x;
        for (; t; t>>=1ll,cur=cur*cur)
            if (t&1) ret=ret*cur;
        return ret;
    }
    bool operator<(const mint &a)const { return x < a.x; }
    bool operator==(const mint &a)const { return x == a.x; }
};
istream & operator>>(istream &o,mint &a) { o>>a.x; a=a.fix(); return o; }
ostream & operator<<(ostream &o,const mint &a) { o<<a.x; return o; }

struct comb {
    vector<mint> f, g; // f:fac; g:inv
    comb() {}
    comb(int mx) : f(mx + 1), g(mx + 1) {
        f[0] = 1;
        FOR_(i, 1, mx) f[i] = f[i - 1] * i;
        g[mx] = f[mx].pow(mod - 2);
        rFOR_(i, 1, mx) g[i - 1] = g[i] * i;
    }
    mint operator()(int a, int b) {
        if (a < b)
            return 0;
        return f[a] * g[b] * g[a - b];
    }
} C(maxn);

struct Matrix {
    typedef double Type;
    vector<vector<Type>> D;
    vector<Type> X;
    int n;
    Matrix() {n=0;}
    Matrix(int n) : n(n), D(n, vector<Type>(n)), X(n,1) {}
    vector<Type>& operator[](const int &x) {return D[x];}
    const vector<Type>& operator[](const int &x) const {return D[x];}
    Matrix lead(const vector<int> &x, const vector<int> &y) { // 只有x行y列
        Matrix res(x.size());
        assert(x.size()==y.size());
        for(int i = 0; i < x.size(); i++) {
            res.X[i] = X[x[i]];
            for(int j = 0; j < y.size(); j++)
                res[i][j] = D[x[i]][y[j]];
        }
        return res;
    }
    bool gauss(int N=INF) {  // 连着N个位置有值
        REP_(i, n) {
            int r = i;
            while(r < n - 1 && D[r][i] == 0) r++;
            if (r == n-1) continue;  // not found
            if (r != i) swap(D[r], D[i]), swap(X[r], X[i]);
            Type inv=Type(1)/D[i][i];
            rep_(k,i+1,min(n,i+N+1)) if (D[k][i]) {
                auto R=D[k][i]*inv;  // div R times
                X[k]-=R*X[i];
                rrep_(j,i,min(n,i+N+1)) D[k][j]-=R*D[i][j];
            }
        }
        rREP_(i,n){
            if (D[i][i]==0) {
                if (X[i]==0) continue; // 没有找到解
                else return 0;
            }
            X[i]=X[i]/D[i][i]; D[i][i]=1;
            REP_(j,i) X[j]-=D[j][i]*X[i];
        }
        return 1;
    }

    void output() {
        REP_(i,n) {
            REP_(j,n) cout<<D[i][j]<<" ";
            cout<<" = "<<X[i]<<endl;
        }
    }
};

// CCPC2023 harbin H题意:
// 给一个矩阵all[n][n]
// 问你, 让你去取w[n], 让w[i]w[j]*all[i][j]的和最大; all里面的都是正数
// 要求w的取值范围[0,1]
// 如果没有w取值范围要求; ans最大的时候就是偏导相等; all两列相等
// 但是会算出负数; 所以就取一下所有子集高斯消元就行了
int solve() {
    int n;
    scanf("%d",&n);
    Matrix all(n);
    REP_(i,n) REP_(j,n) scanf("%lf",&all[i][j]);
    // all.output();
    double res=0;
    vector<int> cur;
    function<void(int)> dfs=[&](int x) {
        if (x==n) {
            if (cur.size()) {
                // for (int v:cur) printf("%d ",v); puts("<- solve");
                auto weight=all.lead(cur,cur);
                // weight.output(); puts("<- w");
                Matrix mat(cur.size());
                REP_(i,cur.size()) mat[0][i]=1; mat.X[0]=1;
                rep_(i,1,cur.size()) {
                    mat.X[i]=0;
                    REP_(j,cur.size()) mat[i][j]=weight[i][j]-weight[0][j];
                }
                // mat.output(); puts("<- mat");
                if (mat.gauss()) {
                    // REP_(i,mat.n) printf("%lf ",mat.X[i]); puts("<- fin val");
                    bool okay=true;
                    REP_(i,mat.n) if (mat.X[i]<-eps) okay=false;
                    if (okay) {
                        double curres=0;
                        REP_(i,cur.size()) rep_(j,i,cur.size())
                            curres+=mat.X[i]*mat.X[j]*weight[i][j];
                        max_(res,curres);
                    }
                }
            }
            return;
        }
        cur.push_back(x);
        dfs(x+1);
        cur.pop_back();
        dfs(x+1);
    };
    dfs(0);
    printf("%.10f\n",res);
    return 0;
}
int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(0), cout.tie(0);
    int T = 1;
    // cin>>T;
    // scanf("%d",&T);
    startTimer();
    FOR_(_, 1, T) { solve(); }
    // printTimer();
}
/*
6 3
1 2
3 4
5 6
*/