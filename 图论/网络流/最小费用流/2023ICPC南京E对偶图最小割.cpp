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
    if (!a) return b;
    ll az=__builtin_ctzll(a),bz=__builtin_ctzll(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctzll(diff);
        (b>a)&&(b=a); a=abs(diff);
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

// const int mod = 1e9+7;
const int mod=998244353;
// int mod=1;
struct mint {
    long long x;
    mint():x(0) {}
    mint(long long x):x((x%mod+mod)%mod) {}
    // mint(long long x):x(x){}
    mint &fix() { x = (x%mod+mod)%mod; return *this;}
    mint operator-() const { return mint(0) - *this;}
    mint operator~() const { return mint(1) / *this;}
    mint &operator+=(const mint &a) { if ((x+=a.x)>=mod) x-=mod; return *this;}
    mint &operator-=(const mint &a) { if ((x+=mod-a.x)>=mod) x-=mod; return *this;}
    mint &operator*=(const mint &a) { (x*=a.x)%=mod; return *this;}
    mint &operator/=(const mint &a) { (x*=a.pow(mod-2).x)%=mod; return *this;}
    mint operator+(const mint &a)const { return mint(*this) += a;}
    mint operator-(const mint &a)const { return mint(*this) -= a;}
    mint operator*(const mint &a)const { return mint(*this) *= a;}
    mint operator/(const mint &a)const { return mint(*this) /= a;}
    mint pow(long long t) const {
        mint ret=1,cur=x;
        for (; t; t>>=1ll,cur=cur*cur)
            if (t&1) ret=ret*cur;
        return ret;
    }
    bool operator<(const mint &a)const { return x < a.x;}
    bool operator==(const mint &a)const { return x == a.x;}
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

namespace mincostflow {
    typedef ll type;
    const type inf=0x3f3f3f3f3f3f3f3f;
    struct node {
        int to; type cap,cost; int next;
        node(int t=0,type c=0,type _c=0,int n=0):
            to(t),cap(c),cost(_c),next(n) {};
    } edge[maxn*2]; int tot;
    int head[maxn];
    int add_edge(int from,int to,type cap,type cost,type rcap=0) {
        // printf("%d->%d: cap=%d; cost=%d\n",from,to,cap,cost);
        edge[tot]=node(to,cap,cost,head[from]); head[from]=tot++;
        edge[tot]=node(from,rcap,-cost,head[to]); head[to]=tot++;
        return tot-1;
    }
    pii add_underiected_edge(int from,int to,type cap,type cost) {
        int x=add_edge(from,to,cap,cost);
        int y=add_edge(to,from,cap,cost);
        return {x,y};
    }
    type dis[maxn];
    bool mark[maxn];
    void spfa(int s,int t,int n) {
        memset(dis+1,0x3f,n*sizeof(type));
        memset(mark+1,0,n*sizeof(bool));
        static int Q[maxn],ST,ED;
        dis[s]=0; ST=ED=0; Q[ED++]=s;
        while (ST!=ED) {
            int v=Q[ST]; mark[v]=0;
            if ((++ST)==maxn) ST=0;
            for (int i=head[v]; ~i; i=edge[i].next) {
                node &e=edge[i];
                if (e.cap>0&&dis[e.to]>dis[v]+e.cost) {
                    dis[e.to]=dis[v]+e.cost;
                    if (!mark[e.to]) {
                        if (ST==ED||dis[Q[ST]]<=dis[e.to]) {
                            Q[ED]=e.to,mark[e.to]=1;
                            if ((++ED)==maxn) ED=0;
                        } else {
                            if ((--ST)<0) ST+=maxn;
                            Q[ST]=e.to,mark[e.to]=1;
                        }
                    }
                }
            }
        }
    } int cur[maxn];
    type dfs(int x,int t,type flow) {
        if (x==t||!flow) return flow;
        type ret=0; mark[x]=1;
        for (int i=cur[x]; ~i; i=edge[i].next) if (!mark[edge[i].to]) {
                if (dis[x]+edge[i].cost==dis[edge[i].to]&&edge[i].cap) {
                    int f=dfs(edge[i].to,t,min(flow,edge[i].cap));
                    edge[i].cap-=f; edge[i^1].cap+=f;
                    ret+=f; flow-=f; cur[x]=i;
                    if (flow==0) break;
                }
            }
        mark[x]=0;
        return ret;
    }
    pair<type,type> mincostflow(int s,int t,int n,type flow=inf) {
        type ret=0,ans=0;
        while (flow) {
            spfa(s,t,n); if (dis[t]==inf) break;
            // 这样加当前弧优化会快, 我也不知道为啥
            memcpy(cur+1,head+1,n*sizeof(int));
            type len=dis[t],f;
            if ((f=dfs(s,t,flow))>0)//while也行
                ret+=f,ans+=len*f,flow-=f;
        } return make_pair(ret,ans);
    }
    void init(int n) {
        memset(head+1,0xff,n*sizeof(int));
        tot=0;
    }
}

// 题意: 给一个平面图, 问你第一列到最后一列的最短路, 大小增大k<=100 最少需要把边权增大多少, 最小化更改的边权和, 输出方案
// *-*-*-*-*
// |#|#|#|#|
// *-*-*-*-*
// |#|#|#|#|
// *-*-*-*-*
// 首先看到最短路肯定想到对偶图最小费用流(*变#), 相当于上下平面最小割
// 相当于对偶图最小费用流割边让流量增加k的时候, 费用最小是多少
// 先把刚开始图建出来, 把流量流完; 然后加上费用为1的边再流k
// 这里留个对偶图板子; 需要注意加边的时候要加双向边
int R[507][507],D[507][507];
pii Rid[507][507],Did[507][507];
int solve() {
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    int S=n*m+1,T=n*m+2;
    mincostflow::init(n*m+2);
    auto getid=[&](int i,int j){return (i-1)*(m-1)+j;};
    FOR_(i,1,n) FOR_(j,1,m-1) {  // 注意
        scanf("%d",&R[i][j]);
        if (i==1) {mincostflow::add_underiected_edge(S,getid(i,j),R[i][j],0); continue;}
        if (i==n) {mincostflow::add_underiected_edge(getid(i-1,j),T,R[i][j],0); continue;}
        mincostflow::add_underiected_edge(getid(i-1,j),getid(i,j),R[i][j],0);
    }
    FOR_(i,1,n-1) FOR_(j,1,m) {
        scanf("%d",&D[i][j]);
        if (j==1||j==m) continue;
        mincostflow::add_underiected_edge(getid(i,j-1),getid(i,j),D[i][j],0);
    }
    auto res=mincostflow::mincostflow(S,T,n*m+2);
    // printf("flow=%lld; w=%lld\n",res.first,res.second);

    // mincostflow::addedge(SS,S,k,0);
    FOR_(i,1,n) FOR_(j,1,m-1) {
        Rid[i][j]={-1,-1};
        if (i==1) {Rid[i][j]=mincostflow::add_underiected_edge(S,getid(i,j),INF,1); continue;}
        if (i==n) {Rid[i][j]=mincostflow::add_underiected_edge(getid(i-1,j),T,INF,1); continue;}
        Rid[i][j]=mincostflow::add_underiected_edge(getid(i-1,j),getid(i,j),INF,1);
    }
    FOR_(i,1,n-1) FOR_(j,1,m) {
        Did[i][j]={-1,-1};
        if (j==1||j==m) continue;
        Did[i][j]=mincostflow::add_underiected_edge(getid(i,j-1),getid(i,j),INF,1);
    }

    res=mincostflow::mincostflow(S,T,n*m+2,k);
    // printf("flow=%lld; w=%lld\n",res.first,res.second);
    printf("%lld\n",res.second);
    FOR_(i,1,n) {
        FOR_(j,1,m-1) {
            int cur=0;
            if (Rid[i][j].first!=-1) cur+=mincostflow::edge[Rid[i][j].first].cap;
            if (Rid[i][j].second!=-1) cur+=mincostflow::edge[Rid[i][j].second].cap;
            printf("%d ",cur+R[i][j]);
        } puts("");
    }
    FOR_(i,1,n-1) {
        FOR_(j,1,m) {
            int cur=0;
            if (Did[i][j].first!=-1) cur+=mincostflow::edge[Did[i][j].first].cap;
            if (Did[i][j].second!=-1) cur+=mincostflow::edge[Did[i][j].second].cap;
            printf("%d ",cur+D[i][j]);
        } puts("");
    }
    return 0;
}
int main() {
    int T; T=1;
    scanf("%d",&T);
    startTimer();
    FOR_(_,1,T) {
        solve();
    }
    // printTimer();
}
/*
*/