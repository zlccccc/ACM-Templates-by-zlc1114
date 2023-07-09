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
const LL M=998244353;
const LL maxn=1e5+107;
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
// char str[maxn];

map<int,int> toPower;
int ini[3007];
const int mod=998244352;
void mul(ll *a,ll *b,int k) {
    int i,j;
    static ll tmp[3007];
    REP(i,k+k) tmp[i]=0;
    REP(i,k) if (a[i]) REP(j,k)
        ((tmp[i+j]+=a[i]*b[j])>=INFF)&&(tmp[i+j]%=mod);
    rrep(i,k,k+k) if (tmp[i]){
        tmp[i]%=mod;
        REP(j,k) ((tmp[i-k+j]+=tmp[i]*ini[k-j])>=INFF)&&(tmp[i-k+j]%=mod);
    }
    REP(i,k) a[i]=tmp[i]%mod;
}
ll A[3007],B[3007];
void power(int k,ll n) {
    if (k!=1) A[1]=1; else A[0]=ini[1]; B[0]=1;
    for (ll x=n; x; x>>=1) {
        if (x&1) mul(B,A,k);
        mul(A,A,k);
    }
}
int base=1,basecnt,rebase;
inline ll getC(int b) {
    ll ans=0;
    // int x;
    while (!toPower.count(b)) {
        b=(ll)b*rebase%M; ans+=basecnt;
        // x++;
    } ans+=toPower[b];
    // printf("b=%d; cnt=%d; x=%d\n",b,cnt[i],x);
    return ans;
}
void exgcd(LL a,LL b,LL &d,LL &x,LL &y) { //d==0时存在逆元 //(x+p)%p为逆元
    if (!b) {d=a; x=1; y=0;}
    else {exgcd(b,a%b,d,y,x); y-=a/b*x;}
}
int main() {
    int i,k;
    scanf("%d",&k);
    FOR(i,1,k) scanf("%d",&ini[i]);
    scanf("%d%d",&n,&m); power(k,n-1);

    // startTimer(); 
    toPower[1]=0;
    FOR(basecnt,1,1000000) base=(ll)base*3%M,toPower[base]=basecnt;
    rebase=powMM((ll)base,M-2); basecnt--;
    // printTimer();
    // REP(i,k) printf("%lld ",B[i]); puts("");
    int tar=getC(m);
    int x=B[k-1],md=mod;
    int g=gcd(x,md);
    if (tar%g!=0) return 0*puts("-1");
    // printf("%d %d %d\n",x,md,tar);
    x/=g; md/=g; tar/=g;
    ll d,A,B;
    exgcd(x,md,d,A,B); A=(A+md)%md;
    printf("%lld\n",powMM(3ll,(ll)tar*A%md));
}
/*
3
3 9 27
10 16
*/