// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define REP_(I, N) for (int I = 0, END = (N); I < END; I++)
#define rREP_(I, N) for (int I = (N)-1; I >= 0; I--)
#define rep_(I, S, N) for (int I = (S), END = (N); I < END; I++)
#define rrep_(I, S, N) for (int I = (N)-1, START = (S); I >= START; I--)
#define FOR_(I, S, N) for (int I = (S), END = (N); I <= END; I++)
#define rFOR_(I, S, N) for (int I = (N), START = (S); I >= START; I--)

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n", str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef long long LL;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int INF = 0x3f3f3f3f;
const LL INFF = 0x3f3f3f3f3f3f3f3fll;
const LL maxn = 1e6 + 7;
const double pi = acos(-1.0);
const double eps = 1e-10;
template <typename T> inline void pr2(T x, int k = 64) {
    REP_(i, k) debug("%d", (x >> i) & 1);
    putchar(' ');
}
template <typename T> inline void max_(T &A, T B) { (A < B) && (A = B); }
template <typename T> inline void min_(T &A, T B) { (A > B) && (A = B); }
inline ll fastgcd(ll a, ll b) { // __gcd()
    if (!a)
        return b;
    ll az = __builtin_ctzll(a), bz = __builtin_ctzll(b), z = min(az, bz), diff;
    b >>= bz;
    while (a) {
        a >>= az, diff = b - a, az = __builtin_ctzll(diff);
        (b > a) && (b = a), a = abs(diff);
    }
    return b << z;
}
int startTime;
void startTimer() { startTime = clock(); }
void printTimer() { debug("/--- Time: %ld milliseconds ---/\n", clock() - startTime); }
typedef array<int, 4> ar4;
typedef array<int, 3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));
vector<pii> direction4 = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
vector<pii> direction8 = {{-1, -1}, {-1, 0}, {1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

// const int mod = 1e9+7;
const int mod = 998244353;
struct mint {
    long long x;
    mint() : x(0) {}
    mint(long long x) : x((x % mod + mod) % mod) {}
    // mint(long long x):x(x){}
    mint &fix() {
        x = (x % mod + mod) % mod;
        return *this;
    }
    mint operator-() const { return mint(0) - *this; }
    mint operator~() const { return mint(1) / *this; }
    mint &operator+=(const mint &a) {
        if ((x += a.x) >= mod)
            x -= mod;
        return *this;
    }
    mint &operator-=(const mint &a) {
        if ((x += mod - a.x) >= mod)
            x -= mod;
        return *this;
    }
    mint &operator*=(const mint &a) {
        (x *= a.x) %= mod;
        return *this;
    }
    mint &operator/=(const mint &a) {
        (x *= a.pow(mod - 2).x) %= mod;
        return *this;
    }
    mint operator+(const mint &a) const { return mint(*this) += a; }
    mint operator-(const mint &a) const { return mint(*this) -= a; }
    mint operator*(const mint &a) const { return mint(*this) *= a; }
    mint operator/(const mint &a) const { return mint(*this) /= a; }
    mint pow(long long t) const {
        mint ret = 1, cur = x;
        for (; t; t >>= 1ll, cur = cur * cur)
            if (t & 1)
                ret = ret * cur;
        return ret;
    }
    bool operator<(const mint &a) const { return x < a.x; }
    bool operator==(const mint &a) const { return x == a.x; }
};
istream &operator>>(istream &o, mint &a) {
    o >> a.x;
    a = a.fix();
    return o;
}
ostream &operator<<(ostream &o, const mint &a) {
    o << a.x;
    return o;
}

// 这个形式就是(0,0)走到(a,b), 向右就是ia++, 向上就是ib++
// 2023 CCPC qinhuangdao B 题面: 问这个01字符串本质不同的子串有多少个
std::string gen_string(int64_t a, int64_t b) {
    std::string res;
    int64_t ia = 0, ib = 0;
    while (ia + ib < a + b) {
        if ((__int128)ia * b <= (__int128)ib * a) {
            res += '0', ia++;
        } else {
            res += '1', ib++;
        }
    }
    return res;
}
// 底下这玩意就是经典类欧几里得计算方式; 考虑向上和向右走的次数
// 假设a<=b; 那就是01111(1)这样; 把这一段merge掉
// 否则a>b; 那就是(0)00001这样; 把这一段merge掉
// 计算一下发现可以递归下去
std::string gen_string_fix(int64_t a, int64_t b, string x, string y) {
    std::string res;
    if (a == 0 || b == 0) {
        REP_(i, a) res += x;
        REP_(i, b) res += y;
        return res;
    }
    // cout << "Gen " << a << " " << b << " " << x << " " << y << endl;
    if (a <= b) {
        string cur = x;
        FOR_(i, 1, b / a) cur += y;
        return gen_string_fix(a, b % a, cur, y);
    } else {
        string cur = y;
        FOR_(i, 1, (a - 1) / b) cur += x;
        return gen_string_fix(a - (a - 1) / b * b, b, x, cur);
    }
    return res;
}

// 子序列自动机: 以x开头, 不能接y的子序列个数
// 原理是这样的; 考虑一个字符串如何dp
// 假设某个字符y之后第一次出现位置为nxt[x][y]
// 那么x开头的字符串为f[x]=\sum{f[nxt[x][y]]}; 所以字符串dp只和最初始那个字符有关
// 用trans[head][last(nextvalue)]保存的是第一个head处的值(转移), 就可以矩阵乘法了
// 可以多加一个节点保存到结尾位置的ans是多少; 最后子序列个数是\sum{x,N} (算空串还要+1)
// 例题: 2018 wannafly camp j
// 题意: 给个字符串, 每次在原串的每两个字符中间加个字符, 问你最后的子序列个数
// 做法: 倒着发现是个复制后中间加个字符, 用子序列自动机来做
// 本题: 01子序列自动机pow
template <int N, typename T> struct substr_matrix {
    T trans[N+1][N+1];
    bool have[N+1+1];
    substr_matrix() {
        memset(trans, 0, sizeof(trans));
        memset(have, 0, sizeof(have));
    }
    substr_matrix(int c) { // 一个c字符
        assert(0 <= c && c < N+1);
        memset(trans, 0, sizeof(trans));
        memset(have, 0, sizeof(have));
        have[c] = 1;
        REP_(i, N+1) trans[c][i] = 1;
    }
    substr_matrix pow(long long t) const {
        substr_matrix ret, cur = *this;
        for (; t; t >>= 1ll, cur = cur * cur)
            if (t & 1)
                ret = ret * cur;
        return ret;
    }
    substr_matrix operator*(const substr_matrix &mat) {
        substr_matrix ret;
        REP_(i, N+1) {
            if (have[i]) {
                REP_(j, N+1) {
                    if (mat.have[j])
                        REP_(k, N+1) ret.trans[i][k] += trans[i][j] * mat.trans[j][k];
                    else
                        ret.trans[i][j] += trans[i][j];
                }
            } else
                REP_(j, N+1) ret.trans[i][j] += mat.trans[i][j];
        }
        REP_(i, N+1) ret.have[i] = have[i] | mat.have[i];
        return ret;
    }
};

typedef substr_matrix<2, mint> mat;
// 子序列自动机套个上面的类欧就行了
mat solve(int64_t a, int64_t b, mat x, mat y) {
    // if (a == 0 || b == 0) {
    //     mat ret;
    //     int64_t ia = 0, ib = 0;
    //     while (ia + ib < a + b) {
    //         if ((__int128)ia * b <= (__int128)ib * a)
    //             ia++, ret = ret*x;
    //         if ((__int128)ia * b > (__int128)ib * a)
    //             ib++, ret = ret*y;
    //     }
    //     return ret;
    // }
    if (a == 0 || b == 0) {
        if (!b)
            return x.pow(a);
        if (!a)
            return y.pow(b);
    }
    // cout << "Gen " << a << " " << b << " " << x << " " << y << endl;
    if (a <= b) {
        mat cur = x * y.pow(b / a);
        return solve(a, b % a, cur, y);
    } else {
        mat cur = y * x.pow((a - 1) / b);
        return solve(a - (a - 1) / b * b, b, x, cur);
    }
}

ll A[maxn], B[maxn];
int solve() {
    ll n, m;
    cin >> n >> m;
    // cout << gen_string(n, m) << "\n";
    // cout << gen_string_fix(n, m, "0", "1") << "\n";
    mat res = solve(n, m, mat(0), mat(1));
    mint ans = 1;                      // 空串
    REP_(i, 2) ans += res.trans[i][2]; // 子序列自动机以i开头, k结尾
    printf("%lld\n", ans.x);
    return 0;
}
int main() {
    int T;
    T = 1;
    cin >> T;
    startTimer();
    FOR_(_, 1, T) { solve(); }
    // printTimer();
    // printTimer();
}
/*
 */