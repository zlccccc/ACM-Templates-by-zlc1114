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
const LL maxn=4e5+107;
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

namespace seives { // 抄的define
#define clr(ar) memset(ar, 0, sizeof(ar))
#define chkbit(ar, i) (((ar[(i) >> 6]) & (1 << (((i) >> 1) & 31))))
#define setbit(ar, i) (((ar[(i) >> 6]) |= (1 << (((i) >> 1) & 31))))
#define isprime(x) (( (x) && ((x)&1) && (!chkbit(ar, (x)))) || ((x) == 2))
    const int MAXP=666666;
    const int MAX=1000010;//euler_seive
    const int maxn=1000010;//min_25, =sqrt(n)
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
    ll n,m;//blocksize
    ll H[maxn][4],L[maxn][4];
    // p%4==1那么p可以表示为两个平方因子的和
    void pcf() {
        ll p,k; int i;
        FOR(p,1,m) {
            REP(i,4) L[p][i]=(p-i+4)/4;
            REP(i,4) H[p][i]=(n/p-i+4)/4;
            REP(i,2) H[p][i%4]--,L[p][i%4]--;
        }
        FOR(p,2,m) {
            if (L[p][p%4]==L[p-1][p%4]) continue;//not_prime
            static int nxt[4];
            REP(i,4) nxt[i]=i*p%4;
            FOR(k,1,min(m,n/p/p)) {
                if (p*k<=m) REP(i,4) H[k][nxt[i]]-=H[p*k][i]-L[p-1][i];
                else REP(i,4) H[k][nxt[i]]-=L[n/p/k][i]-L[p-1][i];
            } rFOR(k,p*p,m) REP(i,4) L[k][nxt[i]]-=L[k/p][i]-L[p-1][i];
        }
    }
    ll F[maxn],G[maxn];//F[n/k]:H[n/k], G[i]:L[i]
    ll getans(ll x,int i) {
        if (x<=1||p[i]>x) return 0;
        if (p[i]>m) return F[n/x]-G[m];
        ll ans=((x<=m)?G[x]:F[n/x])-G[p[i]-1];
        for (; (ll)p[i]*p[i]<=x; i++) {
            for (ll _x=x/p[i],c=1; _x>=p[i]; _x/=p[i],c++) {
                if (p[i]%4==1) ans+=getans(_x,i+1)*(c*3+1)+((c+1)*3+1);
                else ans+=getans(_x,i+1)+1;
            }
        } return ans;
    }
    ll solve() {
        int p;
        for (m=1; m*m<=n; ++m); m--; pcf();
        // FOR(p,1,m) printf("%lld ",H[p][1]); puts(" <- F");
        // FOR(p,1,m) printf("%lld ",L[p][1]); puts(" <- G");
        FOR(p,1,m) {
            F[p]=H[p][1]*(3+1)+H[p][2]+H[p][3];
            G[p]=L[p][1]*(3+1)+L[p][2]+L[p][3];
        }
        return getans(n,0)+1;//1:1
    }
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    seives::init();
    FOR(_,1,T){
        scanf("%lld",&seives::n);
        printf("%lld\n",seives::solve());
    }
}
/*
10
100000000000
10000000000000
*/