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

//对于sans,diff,slink:
//sans是把之前的series_ans保留下来; dp on pam
//diff相同时,sans一定会与上一个相同(由于对称的特殊性)
//所以只需改变diff改变时的ans即可 dp on initial

//区间 本质不同 回文串数; 每个r对应的fail是一堆区间(son-max to x)所以区间更新
//由于border的特性, 可以通过等差数列的方法来分类更新答案
//bzoj5384,跳border+bit可以做到两个log

// 本题: 2023CCPC qinhuangdao C
// 给定一个字符串, 问s[l->r]最少删除一个多长的子串, 留下的串是回文子串; 同时问这种长度的串可以有多少个
// 做法: 先求长度, 再算数量; 比如一个abcd dee dcba
// 先把border删掉 -> dee
// 然后求左边和右边最长开始的回文串多长; 再pam上面跳fail
// 然后还要考虑shift; 这个串可以往左shift一下 (abc d deed cba; abcd d ee dcba); 需要再算一下lcp
struct PAM {
    int next[maxn][27];
    int fail[maxn];
    int len[maxn];//长度
    int diff[maxn];//length(this-fail)
    int anc[maxn];//diff不同的fail,共log个
    int S[maxn];//字符
    int last;//上一个字符节点
    int n,tot;//n表示字符位置
    int newnode(int l) {
        memset(next[tot],0,sizeof(next[tot]));
        len[tot]=l;//不是1...
        return tot++;
    }
    PAM() {init();}
    void init() {
        tot=0; last=n=0;
        newnode(0); newnode(-1);
        S[n]=-1; fail[0]=1;
    }
    int getfail(int x) {
        while (S[n-len[x]-1]!=S[n]) x=fail[x];
        return x;
    }
    int add(int c) {
        S[++n]=c;
        int cur=getfail(last);
        if (!next[cur][c]) {
            int now=newnode(len[cur]+2);
            fail[now]=next[getfail(fail[cur])][c];
            diff[now]=len[now]-len[fail[now]];
            if (diff[now]==diff[fail[now]])
                anc[now]=anc[fail[now]];
            else anc[now]=now;
            next[cur][c]=now;//这里一定要在fail后边=_=
        } return last=next[cur][c];
    }
    char a[maxn];
    void dfs(int p,int len=0) {
        printf("%-20s (p=%-5d, length=%-5d fail=%-5d anc=%-5d diff=%-5d)",a,p,this->len[p],fail[p],anc[p],diff[p]);
        // if (p>=2) printf("%d len=%lld\n",);
        puts("");
        REP_(c,26) if (next[p][c]) {
            a[len]=c+'a';
            dfs(next[p][c],len+1);
            a[len]=0;
        }
    }
    int maxBorder(int p,int length) { // x的status,向上border最大多长
        // printf("check maxborder p=%d; length=%d\n",p,length);
        for (; len[p]>0; p=fail[anc[p]]) {
            // printf("%d -> %d; border=%d\n",len[anc[p]],len[p],diff[p]);
            // l,l+dif,...,r
            int l=len[anc[p]],r=len[p],dif=diff[p];
            if (l>length) continue;
            return min(r,l+(length-l)/dif*dif);
        }
        return 0; // 不可能有这种情况
    }
};


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

char s[maxn];
PAM pamL,pamR;
int pamLid[maxn],pamRid[maxn]; // pam
int solve() {
    int n;
    scanf("%d%s",&n,s+1);
    FOR_(i,1,n) pamLid[i]=pamL.add(s[i]-'a');
    rFOR_(i,1,n) pamRid[i]=pamR.add(s[i]-'a');

    string lcp_s;
    FOR_(i,1,n) lcp_s+=s[i];
    lcp_s+='#';
    rFOR_(i,1,n) lcp_s+=s[i];
    SuffixArray suf(lcp_s);
    SparseTable<int> table(suf.lcp_array);
    auto LcpStr = [&](int x, int y) {
        // printf("lcp %d -> %d\n", x, y);
        if (x == y || max(x, y) == lcp_s.size())
            return (int)lcp_s.size() - max(x, y);
        int l = suf.rnk[x], r = suf.rnk[y];
        if (l > r)
            swap(l, r);
        return table.get(l, r - 1);
    };
    // id从1开始
    auto FrontStr=[&](int x) { return x-1; };
    auto BackStr=[&](int x) { return n*2+1-x; };

    int q;
    scanf("%d",&q);
    FOR_(i,1,q) {
        int l,r;
        scanf("%d%d",&l,&r);
        int lcp=LcpStr(FrontStr(l),BackStr(r));
        if (lcp>=r-l+1) {
            puts("0 0");
            continue;
        }
        l+=lcp; r-=lcp;
        // printf("solve %d %d\n",l,r);
        // printf("lcp=%d\n",lcp);
        // FOR_(i,l,r) printf("%c",s[i]); puts("<- s");
        int lenR=pamL.maxBorder(pamLid[r],r-l+1);
        int lenL=pamR.maxBorder(pamRid[l],r-l+1);
        // printf("border=%d %d\n",lenL,lenR);
        int cntL=1,cntR=1;
        // remove l->r-lenR;
        // printf("sol-L: %d %d\n",l+lenL-1,r+1-1);
        int shiftL=LcpStr(FrontStr(l+lenL),FrontStr(r+1));
        // remove l+lenL->r;
        // printf("sol-R: %d %d\n",l-1,r-lenR);
        int shiftR=LcpStr(BackStr(l-1),BackStr(r-lenR));
        // printf("shift = %d %d\n",shiftL,shiftR);
        cntL+=min(lcp,shiftL);
        cntR+=min(lcp,shiftR);

        lenL=r-l+1-lenL; lenR=r-l+1-lenR;
        if (lenL>lenR) printf("%d %d\n",lenR,cntR);
        if (lenL<lenR) printf("%d %d\n",lenL,cntL);
        if (lenL==lenR) printf("%d %d\n",lenL,cntL+cntR);
    }
    return 0;
}
int main() {
    int T;
    T = 1;
    startTimer();
    FOR_(_, 1, T) { solve(); }
    // printTimer();
    // printTimer();
}
/*

 */