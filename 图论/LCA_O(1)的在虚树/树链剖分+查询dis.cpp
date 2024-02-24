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
    REP_(i, k) printf("%d", (x >> i) & 1);
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
        a >>= az;
        diff = b - a;
        az = __builtin_ctzll(diff);
        (b > a) && (b = a);
        a = abs(diff);
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

struct LCA {
    vector<vector<pair<int, ll>>> edge;
    vector<int> sz, fa, son, top, dep, id;
    vector<ll> length;
    LCA(int n) : edge(n + 1), sz(n + 1), fa(n + 1), son(n + 1), top(n + 1), dep(n + 1), id(n + 1), length(n + 1) {}
    int tot = 0;
    void addedge(int x, int y, ll w) {
        edge[x].push_back({y, w});
        edge[y].push_back({x, w});
    }
    void dfs1(int u, int f, int depth) {
        int mx = -1;
        fa[u] = f, sz[u] = 1, dep[u] = depth, son[u] = 0;
        for (auto &[v, w] : edge[u]) {
            if (v == f)
                continue;
            length[v] = length[u] + w;
            dfs1(v, u, depth + 1);
            sz[u] += sz[v];
            if (sz[v] > mx)
                mx = sz[v], son[u] = v;
        }
    }
    void dfs2(int u, int f, int x) {
        top[u] = x, id[u] = ++tot;
        if (son[u])
            dfs2(son[u], u, x);
        for (auto &[v, w] : edge[u]) {
            if (v == son[u] || v == f)
                continue;
            dfs2(v, u, v);
        }
    }
    int lca(int x, int y) {
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]])
                swap(x, y);
            x = fa[top[x]];
        }
        if (dep[x] > dep[y])
            swap(x, y);
        return x;
    }
    ll dis(int x, int y) {
        int f = lca(x, y);
        return length[x] + length[y] - length[f] * 2;
    }
    void solve(int root) {
        dfs1(root, 0, 0);
        dfs2(root, 0, root);
    }
};

int main() {}
/*
 */