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
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+9;
const LL maxn=1e5+7;
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

vector<int> P[maxn];
namespace seives { // 抄的define
#define clr(ar) memset(ar, 0, sizeof(ar))
#define chkbit(ar, i) (((ar[(i) >> 6]) & (1 << (((i) >> 1) & 31))))
#define setbit(ar, i) (((ar[(i) >> 6]) |= (1 << (((i) >> 1) & 31))))
#define isprime(x) (( (x) && ((x)&1) && (!chkbit(ar, (x)))) || ((x) == 2))
    const int MAXP=666666;
    const int MAX=2000010;
    int mu[MAX],sigma1[MAX],c1[MAX],f[MAX];
    int p[MAXP],tot;
    ui ar[(MAX>>6)+7]= {0};
    void init() {
        setbit(ar,0); setbit(ar,1);
        int i,j; tot=0; mu[1]=1; sigma1[1]=1;
        rep(i,2,MAX) {
            if (isprime(i)) p[tot++]=i,mu[i]=-1,sigma1[i]=i+1,c1[i]=i+1;
            REP(j,tot) {
                if (i*p[j]>=MAX) break;
                if ((i*p[j])&1) setbit(ar,i*p[j]);
                if (i%p[j]==0) {
                    c1[i*p[j]]=p[j]*c1[i]+1;
                    sigma1[i*p[j]]=sigma1[i]/c1[i]*c1[i*p[j]];
                    break;
                } else {
                    c1[i*p[j]]=p[j]+1;
                    sigma1[i*p[j]]=sigma1[i]*(p[j]+1);
                    mu[i*p[j]]=-mu[i];
                }
            }
        } rep(i,1,MAX) f[i]=sigma1[i],add_(f[i],f[i-1]);
    }
    map<int,int> HASH;
    int get2(ll x){
        x%=M; return x*(x+1)%M*500000005%M;
    }
    int get_f(ll x){//直接sqrt也行
        if (x<MAX) return f[x];
        if (HASH.count(x)) return HASH[x];
        ll ret=0; ll l;
        FOR(l,1,x) {
            ll t=x/l,r=x/t;
            add_(ret,(get2(r)-get2(l-1)+M)%M*(t%M)%M);
            l=r;
        } return HASH[x]=ret;
    }
}
int main() {
    // startTimer();
    seives::init(); ll n;
    // printTimer();
    while (~scanf("%lld",&n)){
        // startTimer();
        int ans=0;
        for (ll d=1;d*d<=n;d++) add_(ans,(M+seives::mu[d])*d%M*seives::get_f(n/d/d)%M);
        printf("%d\n",ans);
        // printTimer();
    }
}
/*
1 10
*/
