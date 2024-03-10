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
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));
vector<pii> direction4 = {{-1,0},{0,-1},{0,1},{1,0}};
vector<pii> direction8 = {{-1,-1},{-1,0},{1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

// 求负环尽量dfs; bfs速度很慢
struct SPFA {
    vector<vector<pii>> edge;
    vector<int> dis;
    vector<bool> vis;
    SPFA(int n): edge(n+1),dis(n+1,INF),vis(n+1) {}
    void addedge(int x,int y,int w) {
        edge[x].push_back({y,w});
    }
    bool spfa(int x){
        vis[x]=1;
        for (auto [v,d]:edge[x]) {
            if (dis[x]+d<dis[v]){
                dis[v]=dis[x]+d;
                if (vis[v]) return 1;
                else {
                    dis[v]=dis[x]+d;
                    if (spfa(v)) return 1;
                }
            }
        }
        vis[x]=0;
        return 0; // judge negative ring
    }
    bool solve(int x) {
        dis[x]=0;
        return spfa(x);  // 0: 有负环
    }
};
// 题意: 给n个点m条边; 每条边上有(或者)
// 问你 是否存在一个路径形成的序列是一个合法括号序列, 而且每条边走过不止一次
// 首先如果所有环上的val都是0, 那意思也就是判一下是否是个连通块就行了
// 如果有正环有负环, 那么肯定可以抵消(走lcm就行了); 如果全是负环或者全是正环那就不可能
// 所以SPFA求下负环就可以了
int solve() {
    int n,m;
    scanf("%d%d",&n,&m);
    vector<int> fa(n+1),in(n+1),out(n+1);
    iota(fa.begin(),fa.end(),0);
    function<int(int)> getfa=[&](int x) {
        if (fa[x]==x) return x;
        return fa[x]=getfa(fa[x]);
    };
    SPFA forw(n+1),backw(n+1);
    FOR_(i,1,m) {
        int x,y;
        char s[2];
        scanf("%d%d%s",&x,&y,s);
        {
            int a=getfa(x),b=getfa(y);
            if (a!=b) fa[a]=b;
        }
        if (s[0]=='(') forw.addedge(x,y,1),backw.addedge(x,y,-1);
        else forw.addedge(x,y,-1),backw.addedge(x,y,1);
        in[y]++; out[x]++;
    }
    set<int> S;
    FOR_(i,1,n) if (!out[i]) return 0*puts("No");
    FOR_(i,1,n) if (forw.edge[i].size()) S.insert(getfa(i));
    if (S.size()!=1) return 0*puts("No");  // not merged
    FOR_(i,1,n) if (forw.edge[i].size()) {
        if (forw.solve(i)==backw.solve(i)) return 0*puts("Yes");
        else return 0*puts("No");
    }
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
*/