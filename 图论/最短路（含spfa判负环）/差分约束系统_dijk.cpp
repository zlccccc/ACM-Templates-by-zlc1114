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

// dijk一般都会比spfa快很多~
// 连边u->v,len代表val(v)-val(u)<=len
// 链接：https://ac.nowcoder.com/acm/contest/71/E
// 有一个长为 n 的数列 A，其中有 m 个限制条件，条件有两种：
// 1、对于区间 [l,r]，其区间元素按位或和等于 x
// 2、对于区间 [l,r]，其区间元素按位与和等于 x
// 求出一个数列 A，使得满足给定的 m 个条件，保证有解。
// 先按位分一下, 然后按前缀和进行差分约束; 约束的话包括每一位是1等等
struct Dijkstra {
    vector<vector<pii>> edge;
    vector<ll> dis;
    Dijkstra(int n): edge(n+1),dis(n+1,INFF) {}
    void clear() {
        edge.assign(edge.size(),vector<pii>());
        dis.assign(dis.size(),INFF);
    }
    void addedge(int x,int y,int w) {
        assert(x<edge.size());
        assert(y<edge.size());
        edge[x].push_back({y,w});
    }
    void solve(int x) {
        priority_queue<pair<ll,int>> Q;
        Q.push({0,x}); dis[x]=0;
        while (!Q.empty()) {
            auto [disu,u]=Q.top(); Q.pop();
            if (dis[u]!=-disu) continue;  // 这个情况下可能会有负数更新
            for (auto [v,w]:edge[u]) {
                if (dis[u]+w<dis[v]) {
                    dis[v]=dis[u]+w;
                    Q.push({-dis[v],v});
                }
            }
        }
    }
};
int ans[maxn];
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    vector<ar4> limits(m+1);
    FOR_(i,1,m) REP_(k,4) scanf("%d",&limits[i][k]);
    Dijkstra dij(n);
    REP_(k,20) {
        dij.clear();
        FOR_(i,1,n) {  // 每个位置只能是0或者1
            dij.addedge(i-1,i,1);
            dij.addedge(i,i-1,0);
        }
        FOR_(i,1,m){
            auto [op,l,r,x]=limits[i];
            if (op==1) {  // or
                if ((x>>k)&1) dij.addedge(r,l-1,-1);  // sum[r]-sum[l-1]>=1
                else dij.addedge(l-1,r,0);  // sum[r]-sum[l-1]=0
            } else {  // and
                if ((x>>k)&1) dij.addedge(r,l-1,-(r-l+1));  // sum[r]-sum[l-1]>=r-l+1
                else dij.addedge(l-1,r,r-l);  // sum[r]-sum[l-1]<=r-l
            }
        }
        dij.solve(0);
        FOR_(i,1,n) ans[i]|=(dij.dis[i]-dij.dis[i-1])<<k;
    }
    FOR_(i,1,n) printf("%d ",ans[i]);
}
/*
*/
