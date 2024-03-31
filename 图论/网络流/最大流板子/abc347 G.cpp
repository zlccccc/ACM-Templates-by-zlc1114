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
typedef array<int,5> ar5;
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));
vector<pii> direction4 = {{-1,0},{0,-1},{0,1},{1,0}};
vector<pii> direction8 = {{-1,-1},{-1,0},{1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

const int mod = 1e7+19;
// const int mod=998244353;
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

struct Maxflow {
    typedef LL type;
    const static type INF=0x3f3f3f3f3f3f3f3f;
    struct node {
        int to; type cap; int next;
        node(int t=0,type c=0,int n=0):to(t),cap(c),next(n) {};
    };
    Maxflow(int n=0) {init(n);}
    vector<node> edge;
    vector<int> head;
    int addedge(int from,int to,type cap,type rcap=0) {  // edge id
        // printf("addedge %d %d %d; rcap=%d\n",from,to,cap,rcap);
        assert(0<=from&&from<head.size());
        assert(0<=to&&to<head.size());
        edge.emplace_back(node(to,cap,head[from])); head[from]=edge.size()-1;
        edge.emplace_back(node(from,rcap,head[to])); head[to]=edge.size()-1;
        return edge.size()-2;  // index
    }
    vector<int> dep,gap;
    void bfs(int s,int t) {  // 从t开始bfs
        queue<int> Q;
        dep.resize(head.size());
        gap.resize(head.size()+1);
        fill(dep.begin(),dep.end(),head.size());
        fill(gap.begin(),gap.end(),0);
        gap[0]=1; dep[t]=0;
        Q.push(t);
        while (Q.size()) {
            int u=Q.front(); Q.pop();
            for (int i=head[u]; ~i; i=edge[i].next) {
                int v=edge[i].to;
                if (dep[v]!=head.size()) continue;
                Q.push(v); dep[v]=dep[u]+1;
                gap[dep[v]]++;
            }
        }
    }
    int Start,Target;
    vector<int> cur; // 优化
    type dfs(int u,type flow) {
        if (u==Target) return flow;
        type all=0;
        for (int i=cur[u]; ~i; i=cur[u]=edge[i].next) {
            int v=edge[i].to;
            if (edge[i].cap&&dep[v]+1==dep[u]) {
                type d=dfs(v,min(flow,edge[i].cap));
                all+=d; flow-=d;
                edge[i].cap-=d; edge[i^1].cap+=d;
            }
            if (!flow) return all;
        }
        gap[dep[u]]--;
        if (!gap[dep[u]]) dep[Start]=head.size()-1;  // 这个depth的没有值了; 不能增广了
        dep[u]=min(dep[u]+1,(int)head.size()); gap[dep[u]]++;
        return all;
    }
    vector<int> linked_with_source;  // 没有被cut
    void dfs_link(int u) {
        // printf("dfs-link %d\n",u);
        linked_with_source[u]=1;
        for (int i=head[u]; ~i; i=edge[i].next) {
            int v=edge[i].to;
            if (edge[i].cap&&!linked_with_source[v]) dfs_link(v);
        }
    }
    type maxflow(int s,int t,type flow=INF) {  // isap(improved shortest augmenting path)
        // 最大流
        Start=s; Target=t;
        bfs(s,t);
        type ret=0;
        while (dep[Start]<(int)head.size()-1) {
            cur=head;  // 优化
            ret+=dfs(s,flow-ret);
        }
        // 最小割
        linked_with_source.resize(head.size());
        fill(linked_with_source.begin(),linked_with_source.end(),0);
        dfs_link(s);
        return ret;
    }
    void init(int n) {
        edge.clear();
        head.resize(n+1);
        fill(head.begin(), head.end(),-1);
    }
};

// https://atcoder.jp/contests/abc347/editorial/9689; G
// 给个数组A; 有些位置可以填值1->5
// 问你\sum pow(相邻两个数字差,2)最小多少
// 做法: f(i,j,k)代表(i,j)位置上大小>k; 然后连边
// f(..,x)->f2(..,y) (x>y)连一条大小为2的边,(x=y)连一条大小为1的边就行了
int solve() {
    int n;
    scanf("%d",&n);
    vector<vector<int>> A(n,vector<int>(n));
    REP_(i,n) REP_(j,n) scanf("%d",&A[i][j]);
    Maxflow maxflow(n*n*4+2);
    int s=n*n*4+1,t=n*n*4+2;
    auto index=[&](int x,int y,int z) {  // limit: A[x][y] > z
        // printf("index %d %d %d: %d; all=%d\n",x,y,z,x*n*4+y*4+z,n*n*4+2);
        return x*n*4+y*4+z;
    };
    REP_(i,n) REP_(j,n) {
        if (A[i][j]) {
            // FOR_(k,1,4) if (A[i][j]>k) maxflow.addedge(s,index(i,j,k),INF);  // 一定成立
            // else maxflow.addedge(index(i,j,k),t,INF);  // 一定不成立
            if (A[i][j]<5) maxflow.addedge(index(i,j,A[i][j]),t,INF);
            if (A[i][j]>1) maxflow.addedge(s,index(i,j,A[i][j]-1),INF);
        }
        // A[i][j]>k  => A[i][j]>k-1
        FOR_(k,2,4) maxflow.addedge(index(i,j,k),index(i,j,k-1),INF);
        for (auto [ax,ay]:direction4) {
            int x=i+ax,y=j+ay;
            if (0<=x&&x<n&&0<=y&&y<n) {
                // A[i][j]>=a => A[x][y]>=b (b<=a)的不满足weight
                FOR_(a,1,4) FOR_(b,1,a) {
                    int cur=(a==b)?1:2;
                    maxflow.addedge(index(i,j,a),index(x,y,b),cur);
                }
            }
        }
    }
    auto flow=maxflow.maxflow(s,t);
    // printf("flow=%lld\n",flow);
    REP_(i,n) {
        REP_(j,n) {
            int cur=1;
            FOR_(k,1,4) if (maxflow.linked_with_source[index(i,j,k)]) cur++;
            printf("%d ",cur);
        }
        puts("");
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
30 9
5
1 2 3 4 5
6
1
4
2 3
3 0
4
3 2
*/