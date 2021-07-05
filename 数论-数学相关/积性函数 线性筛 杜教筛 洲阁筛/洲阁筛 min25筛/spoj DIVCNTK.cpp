#include <sstream>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
#include <cassert>
#include <bitset>
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
typedef unsigned int UI;
typedef unsigned int ui;
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
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
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

namespace seives { // 抄的define
#define clr(ar) memset(ar, 0, sizeof(ar))
#define chkbit(ar, i) (((ar[(i) >> 6]) & (1 << (((i) >> 1) & 31))))
#define setbit(ar, i) (((ar[(i) >> 6]) |= (1 << (((i) >> 1) & 31))))
#define isprime(x) (( (x) && ((x)&1) && (!chkbit(ar, (x)))) || ((x) == 2))
    const int MAXP=66666;
    const int MAX=100010;//euler_seive
    const int maxn=100010;//min_25, =sqrt(n)
    int p[MAXP],tot;
    ui ar[(MAX>>6)+7]= {0};
    void init() {//seives
        setbit(ar,0); setbit(ar,1);
        int i,j; tot=0;
        rep(i,2,MAX) {
            if (isprime(i)) p[tot++]=i;
            REP(j,tot) {
                if (i*p[j]>=MAX) break;
                if ((i*p[j])&1) setbit(ar,i*p[j]);
                if (i%p[j]==0) break;
            }
        }
    }
    // 普通pcf公式: g(i,j)=g(i-1,j)-p^k*g(i-1,j/p)
    // 只有小于等于sqrt的p有用, 所以枚举这个, 考虑对其他答案的贡献
    // 对于某个积性函数: (算贡献)
    // g(i,j)=g(i-1,j)+\sum_p^k F(p^k)*g(i-1,j/[p^k]),还要加p^k的贡献
    // 对于小于等于sqrt的p, 直接筛
    // 对于大于的, 贡献只会是F(p)! 也就是...直接洲阁筛把答案的贡献加进去
    // 这个加贡献=_= 竟然是直接pcf求个前缀和啥的就完事了啊=_=
    // typedef ull ll;
    // 注意如果想要去掉某个质数的贡献, 这个p[k]至少要筛到sqrtn...
    // 注意F1的贡献, 是要乘的...
    // 我这个F和G和一般的定义是反的...要先算G
    // F和G定义是质数处的前缀和
    // getans处记得如果质数贡献不同得改
    ll n,m;//blocksize
    ll H[maxn],L[maxn];
    void pcf() {
        ll p,k;
        FOR(p,1,m) L[p]=p-1,H[p]=n/p-1;
        FOR(p,2,m) {
            if (L[p]==L[p-1]) continue;//not_prime
            FOR(k,1,min(m,n/p/p)) {
                if (p*k<=m) H[k]-=H[p*k]-L[p-1];
                else H[k]-=L[n/p/k]-L[p-1];
            } rFOR(k,p*p,m) L[k]-=L[k/p]-L[p-1];
        }
    }
    ll F[maxn],G[maxn];//F[n/k]:H[n/k], G[i]:L[i]
    ll K;
    ll getans(ll x,int i) {
        if (x<=1||p[i]>x) return 0;
        if (p[i]>m) return F[n/x]-G[m];
        ll ans=((x<=m)?G[x]:F[n/x])-G[p[i]-1];
        for (; (ll)p[i]*p[i]<=x; i++) {
            for (ll _x=x/p[i],c=1; _x>=p[i]; _x/=p[i],c++)
                ans+=getans(_x,i+1)*(c*K+1)+((c+1)*K+1);
        } return ans;
    }
    ll solve() {
        int p;
        for (m=1; m*m<=n; ++m); m--; pcf();
        FOR(p,1,m) F[p]=H[p]*(K+1),G[p]=L[p]*(K+1);
        return getans(n,0)+1;//1:1
    }
}
int main() {
    seives::init();
    int T;
    scanf("%d",&T);
    while (T--) {
        scanf("%llu%llu",&seives::n,&seives::K);
        printf("%llu\n",seives::solve());
    }
}
/*
*/
