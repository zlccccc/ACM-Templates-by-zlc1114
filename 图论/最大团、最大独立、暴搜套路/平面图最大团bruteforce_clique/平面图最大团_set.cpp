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
    if (!a) return b;
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
    
// 2024 ICPC Asia Pacific Championship B
// 题意: 给一个平面图, 问子集中\sum{w[edges]}-1e6*{没有连边的pair数量^2}最大是多少; w上限1e6
// n>2个点的平面图中最多有3n-6条边
// 每次新加一个点相当于从n-1条边中最多多加3条边; 剩下n-4条都没有连上, 带来的都是负收益
// n>=6的时候, 新增点n都是负收益了(注意上面pair数量有平方); 所以最多考虑大小为5的子图即可
// 考虑大小为5的子图, 每个点度数最大是4, 如果有2条边没连上那不如删掉一个点变成4个(2->1,少减3e6的结果)
// 所以结论是: 只需要枚举 (1)度数<=4,没有删掉边的clique (2)度数=5,删掉一条边的clique
    
// 平面图的团数量是O(n)的, 计算的话可以枚举度数最小的点, 和S相连的边实际上不会特别多
// 考虑删除一条边的团; 其实等价于[a,b,c]是个团, 然后找到[a,b,c,d]和[a,b,c,e]都是个团; 求d和e带来的收益最大值; 题解是离线算的
int solve() {
    int n,m;
    scanf("%d%d",&n,&m);
    vector<map<int,int>> edge(n+1);
    vector<int> dx(n+1),dy(n+1);
    FOR_(i,1,n) scanf("%d%d",&dx[i],&dy[i]);  // nouse
    FOR_(i,1,m) {
        int x,y,len;
        scanf("%d%d%d",&x,&y,&len);
        edge[x].insert({y,len});
        edge[y].insert({x,len});
    }
    int res=0;
    map<set<int>,int> cliques;
    // 点数1e5; 边数3e5; map跑了4.5s; vec跑了2.5s
    {
        priority_queue<pii,vector<pii>,greater<pii>> Q;
        FOR_(i,1,n) Q.push({edge[i].size(),i});
        vector<int> vis(n+1);
        while (Q.size()) {
            auto [d,x]=Q.top(); Q.pop();
            if (vis[x]) continue;
            vis[x]=1;
            set<int> current_clique = {x};
            vector<pii> current_edge;
            for (auto &p:edge[x]) current_edge.push_back(p);
            function<void(int,int)> solve_subset=[&](int id,int sum) {  // 计算含有x的subset
                if (id==current_edge.size()) {
                    // solve
                    max_(res,sum);
                    cliques.insert({current_clique,sum});  // O(n)个
                    // for (int v:current_clique) printf("%d ",v); puts("<- clique");
                    return;
                };
                solve_subset(id+1,sum);  // not choose
                auto [v,len]=current_edge[id];
                if (!vis[v]) {
                    int current_sum=sum;
                    bool okay=true;
                    for (int u:current_clique) {
                        auto it=edge[u].find(v);
                        if (it==edge[u].end()) {
                            okay=false; break;
                        } else {
                            current_sum+=it->second;
                        }
                    }
                    if (okay) {
                        current_clique.insert(v);
                        solve_subset(id+1,current_sum);
                        current_clique.erase(v);
                    }
                }
            };
            // for (auto [v,len]:current_edge) {
            //     printf("cur edge: %d %d\n",v,len);
            // }
            
            solve_subset(0,0);
            for (auto [v,len]:current_edge) {
                edge[v].erase(x);
                Q.push({edge[v].size(),v});
            }
            edge[x].clear();
        }
    }
    
    {
        map<set<int>,vector<int>> link;
        for (auto [clique,sum]:cliques) {
            if (clique.size()>2) {  // 计算a,b,c相连; d,e不相连的情况
                for (int v:clique) {
                    set<int> cur;
                    for (int u:clique) if (u!=v)
                        cur.insert(u);
                    link[cur].push_back(sum-cliques[cur]);
                }
            }
        }
        for (auto &[cur,edge]:link) {
            if (edge.size()==1) continue;
            sort(edge.begin(), edge.end());
            reverse(edge.begin(), edge.end());
            max_(res,edge[0]+edge[1]+cliques[cur]-1000000);
        }
    }
    printf("%d\n",res);
    return 0;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T = 1;
    // cin>>T;
    // scanf("%d",&T);
    startTimer();
    FOR_(_, 1, T) { solve(); }
    // printTimer();
}
/*
*/