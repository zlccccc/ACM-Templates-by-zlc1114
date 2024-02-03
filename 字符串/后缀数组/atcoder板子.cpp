// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-sparseh")
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
const LL maxn = 1e4 + 7;
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
namespace atcoder {

namespace internal {

std::vector<int> sa_naive(const std::vector<int> &s) {
    int n = int(s.size());
    std::vector<int> sa(n);
    std::iota(sa.begin(), sa.end(), 0);
    std::sort(sa.begin(), sa.end(), [&](int l, int r) {
        if (l == r)
            return false;
        while (l < n && r < n) {
            if (s[l] != s[r])
                return s[l] < s[r];
            l++;
            r++;
        }
        return l == n;
    });
    return sa;
}

std::vector<int> sa_doubling(const std::vector<int> &s) {
    int n = int(s.size());
    std::vector<int> sa(n), rnk = s, tmp(n);
    std::iota(sa.begin(), sa.end(), 0);
    for (int k = 1; k < n; k *= 2) {
        auto cmp = [&](int x, int y) {
            if (rnk[x] != rnk[y])
                return rnk[x] < rnk[y];
            int rx = x + k < n ? rnk[x + k] : -1;
            int ry = y + k < n ? rnk[y + k] : -1;
            return rx < ry;
        };
        std::sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        }
        std::swap(tmp, rnk);
    }
    return sa;
}

// SA-IS, linear-time suffix array construction
// Reference:
// G. Nong, S. Zhang, and W. H. Chan,
// Two Efficient Algorithms for Linear Time Suffix Array Construction
template <int THRESHOLD_NAIVE = 10, int THRESHOLD_DOUBLING = 40> std::vector<int> sa_is(const std::vector<int> &s, int upper) {
    int n = int(s.size());
    if (n == 0)
        return {};
    if (n == 1)
        return {0};
    if (n == 2) {
        if (s[0] < s[1]) {
            return {0, 1};
        } else {
            return {1, 0};
        }
    }
    if (n < THRESHOLD_NAIVE) {
        return sa_naive(s);
    }
    if (n < THRESHOLD_DOUBLING) {
        return sa_doubling(s);
    }

    std::vector<int> sa(n);
    std::vector<bool> ls(n);
    for (int i = n - 2; i >= 0; i--) {
        ls[i] = (s[i] == s[i + 1]) ? ls[i + 1] : (s[i] < s[i + 1]);
    }
    std::vector<int> sum_l(upper + 1), sum_s(upper + 1);
    for (int i = 0; i < n; i++) {
        if (!ls[i]) {
            sum_s[s[i]]++;
        } else {
            sum_l[s[i] + 1]++;
        }
    }
    for (int i = 0; i <= upper; i++) {
        sum_s[i] += sum_l[i];
        if (i < upper)
            sum_l[i + 1] += sum_s[i];
    }

    auto induce = [&](const std::vector<int> &lms) {
        std::fill(sa.begin(), sa.end(), -1);
        std::vector<int> buf(upper + 1);
        std::copy(sum_s.begin(), sum_s.end(), buf.begin());
        for (auto d : lms) {
            if (d == n)
                continue;
            sa[buf[s[d]]++] = d;
        }
        std::copy(sum_l.begin(), sum_l.end(), buf.begin());
        sa[buf[s[n - 1]]++] = n - 1;
        for (int i = 0; i < n; i++) {
            int v = sa[i];
            if (v >= 1 && !ls[v - 1]) {
                sa[buf[s[v - 1]]++] = v - 1;
            }
        }
        std::copy(sum_l.begin(), sum_l.end(), buf.begin());
        for (int i = n - 1; i >= 0; i--) {
            int v = sa[i];
            if (v >= 1 && ls[v - 1]) {
                sa[--buf[s[v - 1] + 1]] = v - 1;
            }
        }
    };

    std::vector<int> lms_map(n + 1, -1);
    int m = 0;
    for (int i = 1; i < n; i++) {
        if (!ls[i - 1] && ls[i]) {
            lms_map[i] = m++;
        }
    }
    std::vector<int> lms;
    lms.reserve(m);
    for (int i = 1; i < n; i++) {
        if (!ls[i - 1] && ls[i]) {
            lms.push_back(i);
        }
    }

    induce(lms);

    if (m) {
        std::vector<int> sorted_lms;
        sorted_lms.reserve(m);
        for (int v : sa) {
            if (lms_map[v] != -1)
                sorted_lms.push_back(v);
        }
        std::vector<int> rec_s(m);
        int rec_upper = 0;
        rec_s[lms_map[sorted_lms[0]]] = 0;
        for (int i = 1; i < m; i++) {
            int l = sorted_lms[i - 1], r = sorted_lms[i];
            int end_l = (lms_map[l] + 1 < m) ? lms[lms_map[l] + 1] : n;
            int end_r = (lms_map[r] + 1 < m) ? lms[lms_map[r] + 1] : n;
            bool same = true;
            if (end_l - l != end_r - r) {
                same = false;
            } else {
                while (l < end_l) {
                    if (s[l] != s[r]) {
                        break;
                    }
                    l++;
                    r++;
                }
                if (l == n || s[l] != s[r])
                    same = false;
            }
            if (!same)
                rec_upper++;
            rec_s[lms_map[sorted_lms[i]]] = rec_upper;
        }

        auto rec_sa = sa_is<THRESHOLD_NAIVE, THRESHOLD_DOUBLING>(rec_s, rec_upper);

        for (int i = 0; i < m; i++) {
            sorted_lms[i] = lms[rec_sa[i]];
        }
        induce(sorted_lms);
    }
    return sa;
}

} // namespace internal

std::vector<int> suffix_array(const std::vector<int> &s, int upper) {
    assert(0 <= upper);
    for (int d : s) {
        assert(0 <= d && d <= upper);
    }
    auto sa = internal::sa_is(s, upper);
    return sa;
}

template <class T> std::vector<int> suffix_array(const std::vector<T> &s) {
    int n = int(s.size());
    std::vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int l, int r) { return s[l] < s[r]; });
    std::vector<int> s2(n);
    int now = 0;
    for (int i = 0; i < n; i++) {
        if (i && s[idx[i - 1]] != s[idx[i]])
            now++;
        s2[idx[i]] = now;
    }
    return internal::sa_is(s2, now);
}

std::vector<int> suffix_array(const std::string &s) {
    int n = int(s.size());
    std::vector<int> s2(n);
    for (int i = 0; i < n; i++) {
        s2[i] = s[i];
    }
    return internal::sa_is(s2, 255);
}

// Reference:
// T. Kasai, G. Lee, H. Arimura, S. Arikawa, and K. Park,
// Linear-Time Longest-Common-Prefix Computation in Suffix Arrays and Its
// Applications
template <class T> std::vector<int> lcp_array(const std::vector<T> &s, const std::vector<int> &sa) {
    int n = int(s.size());
    assert(n >= 1);
    std::vector<int> rnk(n);
    for (int i = 0; i < n; i++) {
        rnk[sa[i]] = i;
    }
    std::vector<int> lcp(n - 1);
    int h = 0;
    for (int i = 0; i < n; i++) {
        if (h > 0)
            h--;
        if (rnk[i] == 0)
            continue;
        int j = sa[rnk[i] - 1];
        for (; j + h < n && i + h < n; h++) {
            if (s[j + h] != s[i + h])
                break;
        }
        lcp[rnk[i] - 1] = h;
    }
    return lcp;
}

std::vector<int> lcp_array(const std::string &s, const std::vector<int> &sa) {
    int n = int(s.size());
    std::vector<int> s2(n);
    for (int i = 0; i < n; i++) {
        s2[i] = s[i];
    }
    return lcp_array(s2, sa);
}

// Reference:
// D. Gusfield,
// Algorithms on Strings, Trees, and Sequences: Computer Science and
// Computational Biology
template <class T> std::vector<int> z_algorithm(const std::vector<T> &s) {
    int n = int(s.size());
    if (n == 0)
        return {};
    std::vector<int> z(n);
    z[0] = 0;
    for (int i = 1, j = 0; i < n; i++) {
        int &k = z[i];
        k = (j + z[j] <= i) ? 0 : std::min(j + z[j] - i, z[i - j]);
        while (i + k < n && s[k] == s[i + k])
            k++;
        if (j + z[j] < i + z[i])
            j = i;
    }
    z[0] = n;
    return z;
}

std::vector<int> z_algorithm(const std::string &s) {
    int n = int(s.size());
    std::vector<int> s2(n);
    for (int i = 0; i < n; i++) {
        s2[i] = s[i];
    }
    return z_algorithm(s2);
}

} // namespace atcoder

template <typename T, class Cmp = std::less<T>> struct SparseTable {
    int n;
    vector<vector<T>> sparse; // func: function
    const Cmp cmp = Cmp();
    SparseTable(const vector<T> &vec) {
        n = static_cast<int>(vec.size());
        int max_log = 32 - __builtin_clz(n);
        sparse.resize(max_log);
        sparse[0] = vec;
        for (int level = 1; level < max_log; level++) {
            sparse[level].resize(n - (1 << level) + 1);
            for (int i = 0; i <= n - (1 << level); i++) {
                sparse[level][i] = std::min(sparse[level - 1][i], sparse[level - 1][i + (1 << (level - 1))], cmp);
            }
        }
    }
    T get(int from, int to) const {
        assert(0 <= from && from <= to && to <= n);
        int lg = 32 - __builtin_clz(to - from + 1) - 1;
        return std::min(sparse[lg][from], sparse[lg][to - (1 << lg) + 1], cmp);
    }
};

struct SuffixArray {
    vector<int> sa, rnk, lcp_array;
    template <typename T> SuffixArray(const T &str) {
        int n = str.size();
        sa = atcoder::suffix_array(str);
        rnk.assign(n, 0);
        for (int i = 0; i < n; i++)
            rnk[sa[i]] = i;
        lcp_array = atcoder::lcp_array(str, sa);
    }
};

// CF1913F
// 题意: 给你一个字符串, 问你更改其中一个字符(可以不更改)能获得的最大回文串数量是多少; 输出字典序最小的方案
// 首先本质不同的回文串就O(n)个; 考虑manacher是从中心开始往左右扩展的, 如果某回文串内部更改那就相当于截断, 贡献是线性的;
// 否则只有最外边的那个地方更改会带来长度增长 算一算LCP啥的就做完了
int main() {
    int n;
    string s;
    cin >> n >> s;
    s += "#" + string(s.rbegin(), s.rend());
    SuffixArray suf(s);

    // for (int v : suf.sa) printf("%d ", v); puts("<- sa");
    // for (int v : suf.rnk) printf("%d ", v); puts("<- rnk");
    // for (int i = 0; i < suf.sa.size(); i++) printf("%s %d\n", s.c_str() + suf.sa[i], suf.lcp_array[i]); puts("<- lcp_array");

    SparseTable<int> table(suf.lcp_array);
    auto lcp = [&](int x, int y) {
        // printf("lcp %d -> %d\n", x, y);
        if (x == y || max(x, y) == s.size())
            return (int)s.size() - max(x, y);
        int l = suf.rnk[x], r = suf.rnk[y];
        if (l > r)
            swap(l, r);
        return table.get(l, r - 1);
    };

    // for (int i = 0; i < s.size(); i++) {
    //     for (int j = 0; j < s.size(); j++) {
    //         printf("lcp %s %s: %d\n", s.c_str() + i, s.c_str() + j, lcp(i, j));
    //     }
    // }

    vector<array<ll, 26>> Arr(n);
    vector<ll> x0(n + 1), x1(n + 1);
    ll all = 0;
    // 通过后缀数组算回文串数量
    REP_(i, n) {
        auto chgleft = [&](int l, int r) { // 0, 0, 0, -1...
            if (r + 1 == l)
                return;
            // printf("chgleft %d %d\n", l, r);
            x0[l] += l - 1;
            x1[l]--;
            x0[r + 1] -= l - 1;
            x1[r + 1]++;
        };
        auto chgright = [&](int l, int r) { // ... -1, 0, 0...
            if (r + 1 == l)
                return;
            // printf("chgright %d %d\n", l, r);
            x0[l] -= r + 1;
            x1[l]++;
            x0[r + 1] += r + 1;
            x1[r + 1]--;
        };
        auto solve = [&](int x, int y) {
            if (x >= s.size() || y >= s.size())
                return;
            if (x == n)
                return;
            int maxlen = lcp(x + 1, y + 1) + 1;
            // printf("LCP %d %d\n", x, y);
            // // printf("solve %d %d\n", x, n * 2 - y);
            // printf("lcp=%d\n", maxlen);
            Arr[x][s[n * 2 - y] - 'a'] += maxlen;
            Arr[n * 2 - y][s[x] - 'a'] += maxlen;
        };
        if (i) {
            int len = lcp(i, n * 2 - i + 1);
            chgleft(i - len, i - 1);
            chgright(i, i + len - 1);
            solve(i + len, n * 2 - i + 1 + len);
            all += len;
            // printf("two %d\n", len);
        }
        {
            int len = lcp(i, n * 2 - i);
            chgleft(i - len + 1, i - 1);
            chgright(i + 1, i + len - 1);
            all += len;
            solve(i + len, n * 2 - i + len);
            // printf("one %d\n", len);
        }
    }
    FOR_(i, 1, n) x0[i] += x0[i - 1], x1[i] += x1[i - 1];
    // REP_(i, n) printf("%d %d\n", x0[i], x1[i]);
    ll pre = -INFF;
    pair<int, int> res; // id, less?
    REP_(i, n) {
        REP_(c, 26) if (c != s[i] - 'a') {
            ll cur = x0[i] + x1[i] * i + Arr[i][c] + all;
            if (cur > pre || (cur == pre && (res.first != i && res.second > s[res.first] - 'a'))) {
                pre = cur;
                res = {i, c};
            }
            // printf("change %d %d: %lld\n", i, c, cur);
        }
    }
    string result(s.begin(), s.begin() + n);
    if (pre < all || (pre == all && res.second > s[res.first] - 'a')) {
        pre = all;
    } else {
        result[res.first] = res.second + 'a';
    }
    cout << pre << "\n";
    cout << result;
}
/*
 */
