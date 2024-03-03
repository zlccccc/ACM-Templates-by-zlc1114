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
const LL maxn=1e5+7;
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
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));
vector<pii> direction4 = {{-1,0},{0,-1},{0,1},{1,0}};
vector<pii> direction8 = {{-1,-1},{-1,0},{1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

namespace fastIO {//感觉没问题, 测试几次
#define BUF_SIZE 100000
    namespace Istream {
        bool IOerror = 0;
        inline char ic() {
            static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
            if (p1==pend) {
                p1=buf;
                pend=buf+fread(buf,1,BUF_SIZE,stdin);
                if (pend == p1) {IOerror = 1; return -1;}
            } return *p1++;
        }
        inline bool blank(char ch) {
            return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
        }
        template<typename T>
        inline void readPositive(T &x) {//no
            char ch; x=0;
            while (blank(ch=ic()));
            if (IOerror) return;
            for (x=0; '0'<=ch&&ch<='9'; ch=ic()) x=x*10+ch-'0';
        }
        template<typename T>
        inline void read(T &x) {
            char ch; T op=1; x=0;
            while (blank(ch=ic()));
            if (IOerror) return;
            if (ch=='-') op=-1,ch=ic();
            for (x=0; '0'<=ch&&ch<='9'; ch=ic()) x=x*10+ch-'0';
            x*=op;
        }
        inline void read(char &c) {
            c=ic();
        }
        inline void read(char *s) { //len
            char ch;
            while (blank(ch=ic()));
            if (IOerror) return;
            for (; !blank(ch)&&!IOerror; ch=ic()) *s++=ch;
            *s='\0';
        }
    }
    namespace Ostream {
        char buf[BUF_SIZE], *p1 = buf, *pend = buf + BUF_SIZE;
        inline void flush() {
            fwrite(buf,1,p1-buf,stdout);
            p1=buf;
        }
        inline void oc(char ch) {
            if (p1 == pend) flush();
            *p1++=ch;
        }
        inline void println() {
            oc('\n');
        }
        template<typename T>
        inline void print(T x) {
            static char s[27],*s1=s;
            if (!x) *s1++='0';
            if (x<0) oc('-'),x=-x;
            while (x) *s1++=x%10+'0',x/=10;
            do {s1--; oc(*s1);} while (s1!=s);
        }
        inline void print(char s) {
            oc(s);
        }
        inline void print(char *s) {
            for (; *s; oc(*s++));
        }
        inline void print(const char *s) {
            for (; *s; oc(*s++));
        }
        inline void print(string s) {
            for (unsigned i=0; i<s.length(); i++) oc(s[i]);
        }
        struct _flush {
            ~_flush() {flush();}
        } fflush;
    };
    template<typename T>
    // inline void read(T &x) {Istream::readPositive(x);}
    inline void read(T &x) {Istream::read(x);} //negative
    inline void read(char *x) {Istream::read(x);}
    template<typename T>
    inline void print(T x) {Ostream::print(x);}
    template<typename T>
    inline void println(T x) {print(x); Ostream::oc('\n');}
}
using namespace fastIO;

template <typename T> struct SparseTable {
    int n;
    vector<vector<T>> sparse; // func: function
    function<bool(T,T)> cmp;
    SparseTable(const vector<T> &vec, function<bool(T,T)> func=nullptr) {
        if (func==nullptr) cmp=[](T x,T y) {return x<y;};
        else cmp=func;
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
        assert(cmp!=nullptr);
        int lg = 32 - __builtin_clz(to - from + 1) - 1;
        return std::min(sparse[lg][from], sparse[lg][to - (1 << lg) + 1], cmp);
    }
};
struct LeastCommonAncenstor {//内部和外部dfn不同...
    vector<vector<pair<int,ll>>> edge;
    void addedge(int u,int v,int l=1) {
        edge[u].push_back({v,l});
        edge[v].push_back({u,l});
    }
    vector<int> fa,dep; // fa,depth
    vector<ll> len,uplen;  // 每个点到root的距离; 到father距离
    vector<int> id_dfn,dfn;  // dfs序第i个位置是x, dfn[x]=i
    vector<int> st_id,st_vec;
    int n;
    LeastCommonAncenstor(int n=1) :n(n), edge(n+1), dfn(n+1), fa(n+1), uplen(n+1), dep(n+1), len(n+1),st_id(n+1) {}

    unique_ptr<SparseTable<int>> table;
    void dfs(int x,int f,int depth=0,ll length=0) {
        dep[x]=depth; len[x]=length;
        st_id[x]=st_vec.size(); st_vec.push_back(x);
        dfn[x]=id_dfn.size(); id_dfn.push_back(x);
        for (auto [v,l]:edge[x]) {
            if (v==f) continue;
            fa[v]=x; uplen[v]=l;
            dfs(v,x,depth+1,length+l);
            st_vec.push_back(x);
        }
    }
    inline int lca(int x,int y) {
        if (table==nullptr) {
            puts("Not Initialized!");
            return -1;
        }
        int l=st_id[x],r=st_id[y];
        if (l>r) swap(l,r);
        int f=table->get(l,r);
        return f;
    }
    inline ll dis(int x,int y) {
        return len[x]+len[y]-2*len[lca(x,y)];
    }
    void solve(int root) {
        dfs(1,0);
        table=make_unique<SparseTable<int>> (st_vec,[&](int x,int y) {return dep[x]<dep[y];});
    }
};

struct VirtualTree {
    LeastCommonAncenstor lca;
    vector<vector<int>> vedge;
    vector<int> mark,vfa;  // vid: 第x个位置的id, 从虚树root往下做的
    vector<ll> vuplen;  // 虚数上节点到father的距离; 需要注意, 中间的节点是没有合并的~ 如果要看中间有没有mark节点的话需要通过别的手段去检查
    VirtualTree() {};
    VirtualTree(int n): vedge(n+1), mark(n+1), vfa(n+1), vuplen(n+1), lca(n+1) {}
    vector<int> vid; // build结束以后的点有哪些
    void clear_lastvtree() {
        for (int v:vid) vedge[vfa[v]].clear(),mark[v]=0;
        vid.clear();
    }
    void build_vtree(vector<int> pid) {
        // puts("clear start");
        if (!pid.size()) return;
        clear_lastvtree();
        auto addvedge=[&](int u,int v) {
            vfa[v]=u; vuplen[v]=lca.dis(u,v);
            vedge[u].push_back(v);  // len记录在vuplen[v]
        };
        sort(pid.begin(),pid.end(),[&](int x,int y) { return lca.dfn[x]<lca.dfn[y]; });
        static int S[maxn],top;
        S[top=1]=pid[0];
        mark[pid[0]]=1;
        // for (int v:pid) printf("%d ",v); puts("<- pid");
        rep_(i,1,(int)pid.size()) {
            int f=lca.lca(pid[i-1],pid[i]);
            // printf("build %d %d; f=%d\n",pid[i-1],pid[i],f);
            while (top&&lca.dep[S[top]]>lca.dep[f]) {
                int v=S[top--];
                vid.push_back(v);
                if (top&&lca.dep[S[top]]>lca.dep[f]) addvedge(S[top],v);
                else addvedge(f,v);
            } if (!top||S[top]!=f) S[++top]=f;
            S[++top]=pid[i]; mark[pid[i]]=1;
        } while (top-1) addvedge(S[top-1],S[top]),vid.push_back(S[top--]);
        vid.push_back(S[1]);
        reverse(vid.begin(),vid.end());
        vfa[vid[0]]=0;
        // puts("build done");
    }
}vtree;

// 2018青岛网络赛B
// 题意: 给一颗树; 每个点红黑染色; 
// 定义toplen=每个点向上第一个红点有多远
// 给定k个点; 问你最多把一个点变成红点; toplen最小值多少; n点数1e6, k虚数点数2e6
// 做法的话可以按toplen从大到小排序; 变红点的一定是第一个点的祖先; 随便搞搞
// 这里是耿直建虚树的写法; 建完虚树dp; 每个点变红点能更改的就是son里向上的那些边; up[v]->up[v]-toplen[x]
// 需要注意有一些红点已经把树分开了; 所以需要单独算一下must的点... 就随便搞搞; 这里这个模板主要是为了留个虚树板子
// 这个虚树写法 题目跑了1.7s/2s
bool red[maxn];
ll toplen[maxn];  // towards-top
void dfs_top(int x,int f,ll tlen) {
    if (red[x]) tlen=0;
    toplen[x]=tlen;
    for (auto [v,l]:vtree.lca.edge[x]) {
        if (v==f) continue;
        dfs_top(v,x,tlen+l);
    }
}

void solve() {
    int n,m,q;
    // cin>>n>>m>>q;
    read(n); read(m); read(q);
    FOR_(i,1,n) red[i]=0;
    FOR_(i,1,m) {
        // int x; cin>>x;
        int x; read(x);
        red[x]=1;
    }
    vtree = VirtualTree(n);
    FOR_(i,1,n-1) {
        int x,y,len;
        // cin>>x>>y>>len;
        read(x); read(y); read(len);
        vtree.lca.addedge(x,y,len);
    }
    vtree.lca.solve(1);
    dfs_top(1,0,0);
    vector<ll> up(n+1),down(n+1),must(n+1);  // black; cnt
    FOR_(i,1,q) {
        int k;
        // cin>>k;
        read(k);
        vector<int> inds(k);
        REP_(x,k) read(inds[x]);
        vtree.build_vtree(inds);
        ll res=INFF;
        rREP_(_,vtree.vid.size()) {
            int x=vtree.vid[_],f=vtree.vfa[x];
            up[x]=down[x]=must[x]=0;
            if (vtree.mark[x]) up[x]=toplen[x];
            for (int v:vtree.vedge[x]) {
                // x->v中间有红色点: x变成红色就没用了
                if (toplen[v]<=vtree.vuplen[v]) max_(must[x],up[v]); // just done
                max_(up[x],up[v]);
                max_(must[x],must[v]);
            }
        }
        REP_(_,vtree.vid.size()) {
            int x=vtree.vid[_],f=vtree.vfa[x];
            ll cur;
            cur=down[x];
            if (vtree.mark[x]) max_(cur,toplen[x]);
            for (int v:vtree.vedge[x]) {
                max_(down[v],cur);
                max_(cur,up[v]);
            }
            reverse(vtree.vedge[x].begin(),vtree.vedge[x].end());
            cur=down[x];
            if (vtree.mark[x]) max_(cur,toplen[x]);
            for (int v:vtree.vedge[x]) {
                max_(down[v],cur);
                max_(cur,up[v]);
            }
            // printf("%d: up=%lld down=%lld; toplen=%lld\n",x,up[x],down[x],toplen[x]);
            min_(res,max(up[x]-toplen[x],max(down[x],must[x])));
        }
        println(res);
    }
}
int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(0), cout.tie(0);
    int T = 1;
    // cin>>T;
    read(T);
    // scanf("%d",&T);
    startTimer();
    FOR_(_, 1, T) { solve(); }
    // printTimer();
}
/*
2
12 2 4
1 9
1 2 1
2 3 4
3 4 3
3 5 2
2 6 2
6 7 1
6 8 2
2 9 5
9 10 2
9 11 3
1 12 10
4 4 5 7 8
*/