#include <bits/stdc++.h>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

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
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef array<int,3> ar3;
typedef array<int,4> ar4;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=1e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
template<typename T> powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M; return ret;}

// codeforces edu 130 F
// 输出一个数组1 2 2 2 3 3 4之类, 要求递增
// 给限制条件ai+aj<=x, ai+aj>=x, ai!=x ...
// 定义f[i][j]为i位置是否<=j
// 每行从左往右连边, f[i][j],1 -> f[i][j+1],1
// 递增: f[i][j],1 -> f[i-1][j],1
// [a!=x]  <->  [a<=x-1 || a>x]
// [a+b<=x]  <->  b>j.[a<=x-b]  <-> b>=j-1, a<=x-j-1
// [a+b>=x]  <->  b<=j,[a>x-b-1]  <-> b<=j, a>x-j-1
namespace T_SAT { // id start from 0; you shoud input N+1
    const static int maxn=1e6+7;
    int N;
    struct enode {
        int to,next;
        enode(int _to=0,int _next=-1):to(_to),next(_next) {};
    } edge[maxn*6];
    int head[maxn],etot;
    void addedge(int u,int v) {
        // printf("edge %d -> %d\n",u,v);
        edge[++etot]=enode(v,head[u]); head[u]=etot;
    }
    void link(int x,int op) { // x=op
        // printf("set %d %d\n",x-1,op);
        assert(0<=x&&x<N);
        assert(0<=op&&op<=1);
        addedge(x*2+(op^1),x*2+op);
    }
    void link(int x,int op_x,int y,int op_y) { // x=op_x -> y=op_y
        // printf("link %d %d  %d %d\n",x-1,op_x,y-1,op_y);
        assert(0<=x&&x<N&&0<=y&&y<N);
        assert(0<=op_x&&op_x<=1&&0<=op_y&&op_y<=1);
        addedge(x*2+op_x,y*2+op_y);
        addedge(y*2+(op_y^1),x*2+(op_x^1));
    }
    void OR(int x,int op_x,int y,int op_y) {
        link(x,op_x^1,y,op_y);
    }
    void SAME(int x,int op_x,int y,int op_y) {
        link(x,op_x,y,op_y);
        link(x,op_x^1,y,op_y^1);
    }
    void XOR(int x,int op_x,int y,int op_y) {
        SAME(x,op_x,y,op_y^1);
    }
    void init(int n) {
        memset(head,-1,sizeof(int)*(n+1)*2); etot=0; N=n;
    }
    int dfn[maxn],low[maxn],belong[maxn];
    bool vis[maxn];
    int tot,cnt;
    int S[maxn],top;
    void dfs(int x) {
        dfn[x]=low[x]=++tot;
        S[++top]=x; vis[x]=1;
        for (int i=head[x]; ~i; i=edge[i].next) {
            int v=edge[i].to;
            if (!dfn[v]) {
                dfs(v);
                low[x]=min(low[x],low[v]);
            } else if (vis[v])
                low[x]=min(low[x],dfn[v]);
        }
        if (dfn[x]==low[x]) {
            cnt++;
            while (1) {
                int now=S[top--];
                vis[now]=0; belong[now]=cnt;
                if (now==x) break;
            }
        }
        // printf("[%d,dfn=%d] ",x,belong[x]);
    }
    int solve() {
        int i; tot=cnt=0;
        REP(i,N*2) dfn[i]=vis[i]=0;
        REP(i,N*2) if (!dfn[i]) dfs(i);
        REP(i,N) if (belong[i*2]==belong[i*2+1]) return 0;
        return 1;
    }
}
int id[maxn][17];
void solve() {
    int n,m,k;
    int i,j;
    // id[i]:f(x)<=k?
    scanf("%d%d%d",&n,&m,&k);
    T_SAT::init(n*(k+1)+2);
    int tot=0;
    FOR(i,1,n) {
        FOR(j,0,k) id[i][j]=tot++;
        T_SAT::link(id[i][0],0);
        T_SAT::link(id[i][k],1);
        FOR(j,1,k) T_SAT::link(id[i][j-1],1,id[i][j],1);
        // if (i!=1) FOR(j,1,k-1) T_SAT::link(id[i-1][j],0,id[i][j],0); // f[i]>j
        if (i!=1) FOR(j,0,k) T_SAT::link(id[i][j],1,id[i-1][j],1); // f[i]>j
    }
    int _;
    FOR(_,1,m) {
        int op;
        scanf("%d",&op);
        if (op==1) { // [a!=x]  <->  [a<=x-1 || a>x]
            int i,x;
            scanf("%d%d",&i,&x);
            T_SAT::OR(id[i][x-1],1,id[i][x],0);
        } else if (op==2) {
            int i,ii,x;
            scanf("%d%d%d",&i,&ii,&x);
            FOR(j,0,k) { // [a+b<=x]  <->  [a<=x-b]  <-> b>j, a<=x-j-1
                int q=x-j-1;
                if (0<=q&&q<=k) T_SAT::link(id[i][j],0,id[ii][q],1);
            }
        } else {
            int i,ii,x;
            scanf("%d%d%d",&i,&ii,&x);
            FOR(j,0,k) { // [a+b>=x]  <->  [a>x-b-1]  <-> b<=j, a>x-j-1
                int q=x-j-1;
                if (0<=q&&q<=k) T_SAT::link(id[i][j],1,id[ii][q],0);
            }
        }
    }
    if (T_SAT::solve()) {
        // FOR(i,1,n) {
        //     FOR(j,1,k) 
        //         // printf("belong %d: %d %d\n",id[i][j],T_SAT::dfn[id[i][j]*2],T_SAT::dfn[id[i][j]*2+1]);
        //         if (T_SAT::belong[id[i][j]*2]<
        //             T_SAT::belong[id[i][j]*2+1]) printf("%2d(%2d,%2d) ",j,T_SAT::belong[id[i][j]*2],T_SAT::belong[id[i][j]*2+1]); else printf("       ");
        //     puts("");
        // } puts("");
        FOR(i,1,n) FOR(j,1,k) {
            // printf("belong %d: %d %d\n",id[i][j],T_SAT::dfn[id[i][j]*2],T_SAT::dfn[id[i][j]*2+1]);
            if (T_SAT::belong[id[i][j]*2]>
                T_SAT::belong[id[i][j]*2+1]) {printf("%d ",j); break;}
        } puts("");
        // FOR(i,1,n) FOR(j,0,k) printf("%d%c",(T_SAT::dfn[id[i][j]*2]>T_SAT::dfn[id[i][j]*2+1])," \n"[j==k]);
    } else puts("-1");
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        solve();
    }
}
/*
1 4 0 4

1
3 3 2
1 1 1
2 2 3 2
3 2 3 2

1
5 5 5
3 2 5 7
2 4 5 10
3 4 5 6
3 3 4 7
2 1 5 7



4 1 1 0 2

4 0 4
1 1 1
2 2 3
3 1 2 3
1 2 2

1
3 1 4
1 3 4
*/