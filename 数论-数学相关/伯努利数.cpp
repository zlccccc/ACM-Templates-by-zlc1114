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
typedef long long LL;
typedef long long ll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=3e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void add(T &A,int B) {A+=B; (A>=M) &&(A-=M);}
template<typename T>inline void mul(T &A,ll B) {(A*=B)%=M;}
template<typename T>inline void mod_M(T &A,ll B=M) {A%=B; A+=B; A%=B;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int n,m;
char S[maxn];

//sum{pow(i,k)}(1->n)
ll B[maxn],pw[maxn];
ll A[maxn];
ll INV[10007];
LL inv[10002];//inverse
LL fac[10002];//Factorial
LL C(int n,int m) {
    return fac[n]*inv[m]%M*inv[n-m]%M;
} ll SUM_N_K(int n,int k) {
    ll pw=1,now=0; int i;
    FOR(i,1,k+1) {
        pw=pw*(n+1)%M;
        now+=INV[k+1]*C(k+1,i)%M*B[k+1-i]%M*pw%M;
    } mod_M(now);
    return now;
}
void initialize() {
    int i,j;
    fac[0]=1;
    FOR(i,1,10000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1; INV[0]=INV[1]=1;
    FOR(i,2,10000) INV[i]=inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,10000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
    B[0]=1;
    FOR(i,1,2000) {
        FOR(j,0,i-1) B[i]-=INV[i+1]*C(i+1,j)%M*B[j]%M; mod_M(B[i]);
    }
//    FOR(i,0,2000) printf("%lld ",B[i]);
}
void Task_one() {TaskA();}
void Task_T() {int T; scanf("%d",&T); while (T--) TaskA();}
void Task_more_n() {while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m() {while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_string() {while (~scanf("%s",S)) TaskA();}
int main() {
    int startTime=clock();
    //initialize
    initialize();
    debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
    Task_more_n();
}
/*
*/
