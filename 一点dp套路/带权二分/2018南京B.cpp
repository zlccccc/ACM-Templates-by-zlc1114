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
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e7+107;
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
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
int n,m,q;

struct node {
    ll ans; int c;
} dp[maxn];
struct range {
    int l,p;//
} Q[maxn];
ll sum[maxn];
int A[maxn];
inline ll calc(int l,int r) {
    ll ret=dp[l].ans;
    l++; int mid=(l+r+1)/2;
    ret+=(sum[r]-sum[mid]-(ll)(r+l–mid*2)*A[mid])-
         (sum[mid-1]-sum[l-1]);

    // printf("%d-%d: ret=%lld  = %lld - %lld\n",l,r,ret,
    //        (sum[r]-sum[mid]-(r-mid)*A[mid]),
    //        (sum[mid-1]-sum[l-1]-(mid-l)*A[mid]));
    return ret;
}
inline bool check(int a,int b,int p) {
    return calc(a,p)>calc(b,p);
}
inline int solve_slope(ll x) {
    // 决策单调性优化,单调栈
    // 维护决策区间, range{range-right, from-position}
    int st=0,ed=-1,i;
    Q[++ed]=range{1,0}; Q[ed+1].l=n+1;
    FOR(i,1,n) {
        if (st<=ed&&Q[st+1].l-1<i) st++;
        dp[i]= {calc(Q[st].p,i)+x,dp[Q[st].p].c+1};
        // printf("%d->%d : %lld\n",Q[st].p,i,dp[i].ans-dp[Q[st].p].ans);
        if (i==n) return dp[n].c;
        if (!check(i,Q[ed].p,n)) {
            while (st<=ed&&!check(i,Q[ed].p,Q[ed].l)) ed--;
            if (st>ed) {
                Q[++ed]= {i+1,i}; Q[ed+1].l=n+1;
            } else {
                // printf("CHECK;\n");
                int l=Q[ed].l,r=n+1;
                while (l+1<r) {
                    int mid=l+(r-l)/2;
                    if (check(i,Q[ed].p,mid)) l=mid;
                    else r=mid;
                } Q[++ed]=range{r,i};
                Q[ed+1].l=n+1;
            }
        }
        // int k; FOR(i,st,ed)
        // printf(" x=%lld; %d - %d : %d; dp=%lld-%d\n",x,Q[ed].l,n,Q[ed].p,dp[i].ans,dp[i].c);
    }
    return 0;
}
inline ll solve(int m) {
    ll l=-100000000,r=100000001000000000;
    while (l+1<r) {
        ll mid=l+(r-l)/2;
        if (solve_slope(mid)<m) r=mid;
        else l=mid;
    } solve_slope(l);
    // printf(" ans=%lld %d\n",dp[n].ans,dp[n].c);
    return dp[n].ans-l*m;
}
int main() {
    int i,k;
    scanf("%d%d",&n,&k);
    FOR(i,1,n) scanf("%d",&A[i]),sum[i]=A[i]+sum[i-1];
    // solve_slope(100);
    printf("%lld\n",solve(k));
}
/*
5 2
0 4 7 9 10

9 3
0 1 10 11 20 21 22 30 32

*/
