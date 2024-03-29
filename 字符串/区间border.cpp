#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <stack>
 
#define rep(i, a, n) for (int i = a; i < n; ++i)
#define per(i, a, n) for (int i = n - 1; i >= a; --i)
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef std::vector<int> VI;
typedef long long ll;
typedef std::pair<int, int> PII;
 
#define gcd(a, b) std::__gcd((a), (b))
 
const int N = 1000010;
int ff[N], n, a[N], sql[N], sqr[N], sqr2[N];
 
struct SuffixArray {
    int sa[N], rk[N], ht[N];
    bool t[N << 1];
    int hv[21][N];
 
    bool islms(const int i, const bool *t) {
        return i > 0 && t[i] && !t[i - 1];
    }
 
    template<class T>
    inline void sort(T s, int *sa, const int len, const int sz, const int sigma, bool *t,
                     int *b, int *cb, int *p) {
        memset(b, 0, sizeof(int) * sigma);
        memset(sa, -1, sizeof(int) * len);
        rep(i, 0, len) b[(int) s[i]]++;
        cb[0] = b[0];
        rep(i, 1, sigma) cb[i] = cb[i - 1] + b[i];
        per(i, 0, sz) sa[--cb[(int) s[p[i]]]] = p[i];
        rep(i, 1, sigma) cb[i] = cb[i - 1] + b[i - 1];
        rep(i, 0, len) if (sa[i] > 0 && !t[sa[i] - 1]) sa[cb[(int) s[sa[i] - 1]]++] = sa[i] - 1;
        cb[0] = b[0];
        rep(i, 1, sigma) cb[i] = cb[i - 1] + b[i];
        per(i, 0, len) if (sa[i] > 0 && t[sa[i] - 1]) sa[--cb[(int) s[sa[i] - 1]]] = sa[i] - 1;
    }
 
    template<class T>
    inline void sais(T s, int *sa, const int len, bool *t, int *b, int *b1, const int sigma) {
        int p = -1, *cb = b + sigma;
        t[len - 1] = 1;
        per(i, 0, len - 1) t[i] = s[i] < s[i + 1] || (s[i] == s[i + 1] && t[i + 1]);
        int sz = 0, cnt = 0;
        rep(i, 1, len) if (t[i] && !t[i - 1]) b1[sz++] = i;
        sort(s, sa, len, sz, sigma, t, b, cb, b1);
        sz = 0;
        rep(i, 0, len) if (islms(sa[i], t)) sa[sz++] = sa[i];
        rep(i, sz, len) sa[i] = -1;
        rep(i, 0, sz) {
            int x = sa[i];
            rep(j, 0, len) {
                if (p == -1 || s[x + j] != s[p + j] || t[x + j] != t[p + j]) {
                    ++cnt;
                    p = x;
                    break;
                } else if (j > 0 && (islms(x + j, t) || islms(p + j, t))) {
                    break;
                }
            }
            sa[sz + (x >>= 1)] = cnt - 1;
        }
        for (int i = len - 1, j = len - 1; i >= sz; --i) if (sa[i] >= 0) sa[j--] = sa[i];
        int *s1 = sa + len - sz, *b2 = b1 + sz;
        if (cnt < sz) sais(s1, sa, sz, t + len, b, b1 + sz, cnt);
        else
            rep(i, 0, sz) sa[s1[i]] = i;
        rep(i, 0, sz) b2[i] = b1[sa[i]];
        sort(s, sa, len, sz, sigma, t, b, cb, b2);
    }
 
    template<class T>
    inline void getHeight(T s, int n) {
        rep(i, 1, n + 1) rk[sa[i]] = i;
        int j = 0, k = 0;
        for (int i = 0; i < n; ht[rk[i++]] = k) {
            for (k ? k-- : 0, j = sa[rk[i] - 1]; s[i + k] == s[j + k]; ++k);
        }
    }
 
    template<class T>
    inline void init(T s, const int len, const int sigma) {
        sais(s, sa, len, t, rk, ht, sigma);
    }
 
    inline void solve(int *s, int len) {
        init(s, len + 1, 8);
        getHeight(s, len);
        rk[len] = 0;
        rep(i, 1, len + 1) hv[0][i] = ht[i];
        rep(j, 1, 20) for (int i = 1; i + (1 << j) - 1 <= len; ++i) {
                hv[j][i] = std::min(hv[j - 1][i], hv[j - 1][i + (1 << (j - 1))]);
            }
    }
 
    int lcp(int p, int q) {
        if (q > n) return 0;
        if (p == q) return n - p + 1;
        p = rk[p - 1];
        q = rk[q - 1];
        if (p > q) std::swap(p, q);
        int w = ff[q - p];
        return std::min(hv[w][p + 1], hv[w][q - (1 << w) + 1]);
    }
} s1, s2;
 
char s[N];
 
void gao(int l, int r, int ty) {
    int pi = l - s2.lcp(n + 1 - r, n + 1 - (l - 1));
    int pj = r + s1.lcp(l, r + 1);
    int p = r - l + 1;
    if (pj - pi + 1 >= 2 * p && pi < l && l <= pi + p && (ty == 0 || pj != n)) {
        for (int k = pi + 2 * p - 1; k <= pj; ++k) {
            sqr[k] = std::min(sqr[k], 2 * p);
            sql[k - 2 * p + 1] = std::min(sql[k - 2 * p + 1], 2 * p);
            sqr2[k] = std::max(sqr2[k], k - 2 * p + 1);
        }
    }
}
 
void gao(int *a) {
    s1.solve(a + 1, n);
    std::reverse(a + 1, n + a + 1);
    a[n + 1] = 0;
    s2.solve(a + 1, n);
    //std::reverse(a + 1, n + a + 1);
    std::stack<PII> st;
    st.push({n + 1, n + 1});
    per(i, 1, n + 1) {
        int j = i;
        while (SZ(st) > 1) {
            auto seg = st.top();
            if (s1.rk[i - 1] >= s1.rk[seg.fi - 1]) break;
            j = seg.se;
            st.pop();
        }
        st.push({i, j});
        gao(i, j, 0);
    }
    st = std::stack<PII>();
    st.push({n + 1, n + 1});
    per(i, 1, n + 1) {
        int j = i;
        while (SZ(st) > 1) {
            auto seg = st.top();
            if (s1.rk[i - 1] <= s1.rk[seg.fi - 1]) break;
            j = seg.se;
            st.pop();
        }
        st.push({i, j});
        gao(i, j, 1);
    }
}
 
namespace border {
    int tmp1[N], tmp2[N], c[N], sa[N], rk[21][N], lev;
    PII pos[21][N];
 
    void buildDict(char *s, int *sa, int *x, int *y, int n, int m = 128) {
        rep(i, 0, m) c[i] = 0;
        rep(i, 0, n) c[x[i] = s[i]]++;
        rep(i, 1, m) c[i] += c[i - 1];
        per(i, 0, n) sa[--c[x[i]]] = i;
        rep(i, 0, n) rk[0][i] = x[i];
        rep(i, 0, n) pos[0][i] = {rk[0][sa[i]], sa[i]};
        lev = 1;
        for (int k = 1; k < n; k <<= 1, ++lev) {
            int p = 0;
            per(i, n - k, n) y[p++] = i;
            rep(i, 0, n) if (sa[i] >= k) y[p++] = sa[i] - k;
            rep(i, 0, m) c[i] = 0;
            rep(i, 0, n) c[x[y[i]]] ++;
            rep(i, 1, m) c[i] += c[i - 1];
            per(i, 0, n) sa[--c[x[y[i]]]] = y[i];
            std::swap(x, y);
            p = 1;
            x[sa[0]] = 0;
            y[n] = -1;
            //rep(i, 1, n) if (y[sa[i - 1]] == y[sa[i]]) assert(sa[i - 1] + k <= n && sa[i] + k <= n);
            rep(i, 1, n) x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k]) ? p - 1 : p++;
            rep(i, 0, n) rk[lev][i] = x[i];
            rep(i, 0, n) pos[lev][i] = {rk[lev][sa[i]], sa[i]};
            m = p;
        }
    }
 
    struct seq {
        int a, k, sz;
        bool contain(int x) {
            if (sz == 0) return 0;
            if (x < a || x > a + (sz - 1) * k) return 0;
            if (x == a) return 1;
            return (x - a) % k == 0;
        }
    };
 
    ll Inv(ll q, ll m) {
        if (q == 0) return 0;
        //assert(q >= 0);
        ll a1 = m, b1 = 0, a2 = q, b2 = 1, a3, b3, t;
        while (a2 != 1) {
            t = a1 / a2, a3 = a1 - t * a2, b3 = b1 - t * b2 % m,
            a1 = a2, a2 = a3, b1 = b2, b2 = b3;
            if (b2 < 0) b2 += m;
        }
        return b2;
    }
 
    std::pair<ll, ll> merge(ll a, ll b, ll c, ll d) {
        c -= a;
        ll dd = gcd(b, d);
        if (c % dd != 0) return {-1, -1};
        b /= dd;
        c /= dd;
        d /= dd;
        ll t = c * Inv(b, d) % d;
        if (t < 0) t += d;
        return {b * t * dd + a, b * d * dd};
    }
 
    seq intersect(seq a, seq b) {
        if (a.sz > b.sz) std::swap(a, b);
        if (a.sz == 0) return a;
        else if (a.sz == 1) {
            if (b.contain(a.a)) return a;
            else return (seq) {0, 0, 0};
        } else {
            std::pair<ll, ll> d = merge(a.a % a.k, a.k, b.a % b.k, b.k);
            if (d.se == -1) return (seq) {0, 0, 0};
            int l = std::max(a.a, b.a), r = std::min(a.a + (a.sz - 1) * a.k, b.a + (b.sz - 1) * b.k);
            int pl = (l - d.fi + d.se - 1) / d.se, pr = (r - d.fi + d.se) / d.se - 1;
            if (pl > pr) return (seq) {0, 0, 0};
            else return (seq) {(int) (d.fi + pl * d.se), (pl == pr) ? 1 : (int) d.se, pr - pl + 1};
        }
    }
 
    int findprev(int p, int lev, int r) { // <=r start position
        PII *ps = std::lower_bound(pos[lev], pos[lev] + n, std::make_pair(rk[lev][p], r + 1));
        if (ps != pos[lev]) --ps; else return -1;
        if (ps->fi != rk[lev][p]) return -1;
        else return ps->se;
    }
 
    int findnxt(int p, int lev, int l) {// >=l
        PII *ps = std::lower_bound(pos[lev], pos[lev] + n, std::make_pair(rk[lev][p], l));
        if (ps == pos[lev] + n || ps->fi != rk[lev][p]) return -1;
        else return ps->se;
    }
 
    int bit[24];
//#define bit(k) (1<<(k))
#define bit(k) bit[k]
 
    seq occur(int p, int lev, int l, int r) {
        int fp = findnxt(p, lev, l);
        if (fp == -1 || fp > r) return (seq) {0, 0, 0};
        int fq = findnxt(p, lev, fp + 1);
        if (fq == -1 || fq > r) return (seq) {fp, 1, 1};
        int fr = findprev(p, lev, r);
        return (seq) {fp, fq - fp, (fr - fp) / (fq - fp) + 1};
    }
 
    int query(int l, int r) {
        --l;
        --r;
        for (int k = lev; k >= 1; k--) {
            if ((r - l + 1) <= bit(k - 1)) continue;
            seq a = occur(l, k - 1, std::max(r - bit(k) + 1, l), r - bit(k - 1) + 1);
            seq b = occur(r - bit(k - 1) + 1, k - 1, l, std::min(l + bit(k - 1), r - bit(k - 1) + 1));
            a.a = l + r - (a.a + (a.sz - 1) * a.k);
            b.a += bit(k - 1) - 1;
            seq c = intersect(a, b);
            if (c.sz != 0 && c.a + (c.sz - 1) * c.k == r) --c.sz;
            if (c.sz != 0) return c.a + (c.sz - 1) * c.k - l + 1;
        }
        return 0;
    }
 
    void init() {
        buildDict(s, sa, tmp1, tmp2, n);
 
        for (int i = 0; i < 24; ++i) bit[i] = 1 << i;
    }
}
 
std::pair<char, char> input[N];
char tmpa[5], tmpb[5];
 
char convert() {
    switch(tmpb[0]) {
        case 'd': return 'a';
        case 'r': return 'b';
        case 'm': return 'c';
        case 'f': return 'd';
        case 's':
            if (tmpb[1] == 'o') return 'e';
            if (tmpb[1] == 'i') return 'g';
        case 'l': return 'f';
    }
    //assert(0);
}
 
void gets() {
    std::deque<char> dq;
    for (int i = 1; i <= n; ++i) {
        scanf("%s%s", tmpa, tmpb);
        input[i] = {tmpa[0], convert()};
        //input[i].first = rand() & 1 ? 'a' : 'p';
        //input[i].second = (rand() % 7) + 'a';
        if (input[i].first == 'a') dq.push_back(input[i].second);
        else dq.push_front(input[i].second);
    }
    for (int i = 0; i < n; ++i) {
        s[i] = dq.front();
        dq.pop_front();
    }
}

// 题意:求循环节
int cntp[N];
int main() {
    //auto bg = clock();
    rep(i, 2, 1000001) ff[i] = ff[i >> 1] + 1;
    scanf("%d", &n);
    //n = 1000000;
    rep(i, 1, n + 1) sql[i] = n + 1, sqr[i] = n + 1;
 
    gets();
 
    rep(i, 1, n + 1) {
        a[i] = s[i - 1] - 'a' + 1;
    }
    //std::cout << clock() - bg << std::endl;
    gao(a);
    rep(i, 1, n + 1) sqr2[i] = std::max(sqr2[i], sqr2[i - 1]);
    border::init();
    //std::cout << clock() - bg << std::endl;
 
    for (int i = n; i; --i) {
        cntp[i] = cntp[i + 1] + input[i].first == 'p';
    }
    for (int i = 1; i <= n; ++i) {
        int l = cntp[i + 1] + 1;
        int r = l + i - 1;
        int bd = border::query(l, r);
        int tot = r - l + 1;
        int len = tot - bd;
        printf("%d\n", (tot + len - 1) / len);
    }
    //std::cout << clock() - bg << std::endl;
    return 0;
}