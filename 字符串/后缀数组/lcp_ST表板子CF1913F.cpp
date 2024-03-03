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
        assert(0 <= from && from <= to && to < n);
        int lg = 32 - __builtin_clz(to - from + 1) - 1;
        return std::min(sparse[lg][from], sparse[lg][to - (1 << lg) + 1], cmp);
    }
};

struct SuffixArray {
    vector<int> sa, rnk, lcp_array;
    template <typename T> SuffixArray(const T &str, int length = -1, int bound = -1) {
        if (length == -1)
            length = str.length();
        sa.resize(length);
        rnk.resize(length);
        lcp_array.resize(length - 1); // resize(length-1)
        if (bound == -1) {
            iota(sa.begin(), sa.end(), 0); // 0, 1, ... length-1
            sort(sa.begin(), sa.end(), [&str](int i, int j) { return str[i] < str[j]; });
        } else {
            vector<int> count(bound + 1);
            for (int i = 0; i < length; i++)
                ++count[str[i]];
            for (int i = 1; i <= bound; ++i)
                count[i] += count[i - 1];
            for (int i = 0; i < length; i++)
                sa[--count[i]] = i; // sort(计数排序)
        }
        rnk[sa[0]] = 0;
        for (int i = 1; i < length; i++)
            rnk[sa[i]] = rnk[sa[i - 1]] + (str[sa[i]] != str[sa[i - 1]]);
        int k = 1;
        vector<int> tmp, count(length);
        tmp.reserve(length);
        while (rnk[sa[length - 1]] < length - 1) {
            tmp.clear();
            for (int i = 0; i < k; i++)
                tmp.push_back(length - k + i);
            for (auto i : sa)
                if (i >= k)
                    tmp.push_back(i - k);
            std::fill(count.begin(), count.end(), 0);
            for (int i = 0; i < length; ++i)
                ++count[rnk[i]];
            for (int i = 1; i < length; ++i)
                count[i] += count[i - 1];
            for (int i = length - 1; i >= 0; --i)
                sa[--count[rnk[tmp[i]]]] = tmp[i];
            std::swap(rnk, tmp);
            rnk[sa[0]] = 0;
            for (int i = 1; i < length; ++i)
                rnk[sa[i]] = rnk[sa[i - 1]] + (tmp[sa[i - 1]] < tmp[sa[i]] || sa[i - 1] + k == length || tmp[sa[i - 1] + k] < tmp[sa[i] + k]);
            k *= 2;
        }
        // calculate lcp_array
        for (int i = 0, j = 0; i < length; ++i) {
            if (rnk[i] == 0) {
                j = 0;
            } else {
                for (j -= j > 0; i + j < length && sa[rnk[i] - 1] + j < length && str[i + j] == str[sa[rnk[i] - 1] + j]; ++j)
                    ;
                lcp_array[rnk[i] - 1] = j;
            }
        }
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
