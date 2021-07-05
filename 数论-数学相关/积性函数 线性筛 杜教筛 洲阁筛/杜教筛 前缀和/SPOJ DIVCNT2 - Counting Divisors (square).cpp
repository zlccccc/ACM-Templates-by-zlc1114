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

// \sum_{i=a}^{b} F(i)
// F(n)= \frac{\sum_{i}^{n} lcm(i,n)}{n}
namespace seives { // 抄的define
#define clr(ar) memset(ar, 0, sizeof(ar))
#define chkbit(ar, i) (((ar[(i) >> 6]) & (1 << (((i) >> 1) & 31))))
#define setbit(ar, i) (((ar[(i) >> 6]) |= (1 << (((i) >> 1) & 31))))
#define isprime(x) (( (x) && ((x)&1) && (!chkbit(ar, (x)))) || ((x) == 2))
	map<ll,int> HASH;
	const int MAXP=6666666;
	const int MAX=100000010;
	int mu[MAX],mu2[MAX],sigma[MAX],c[MAX];
	int p[MAXP],tot;
	ui ar[(MAX>>6)+7]= {0};
	void init(int MAX) {
		setbit(ar,0); setbit(ar,1);
		int i,j; tot=0; mu[1]=1; sigma[1]=1;
		rep(i,2,MAX) {
			if (isprime(i)) p[tot++]=i,mu[i]=-1,c[i]=1,sigma[i]=2;
			REP(j,tot) {
				if (i*p[j]>=MAX) break;
				if ((i*p[j])&1) setbit(ar,i*p[j]);
				if (i%p[j]==0) {
					c[i*p[j]]=c[i]+1; mu[i*p[j]]=0;
					sigma[i*p[j]]=sigma[i]*(c[i*p[j]]+1)/c[i*p[j]]; break;
				} else {
					mu[i*p[j]]=-mu[i]; c[i*p[j]]=1;
					sigma[i*p[j]]=sigma[i]<<1;
				}
			}
		}
		rep(i,1,MAX) {
			mu2[i]=mu[i]*mu[i];
			mu2[i]+=mu2[i-1];
			sigma[i]+=sigma[i-1];
		}
	}
	ll sum_sigma(ll x){
		if (x<MAX) return sigma[x];
		ll l; ll ret=0;
		FOR(l,1,x){
			ll t=x/l,r=x/t;
			ret+=(r-l+1)*t;
			l=r;
		} return ret;
	}
	ll sum_mu(ll x){
		if (x<MAX) return mu2[x];
		ll i; ll ret=0;
		for (i=1;i*i<=x;i++) if (mu[i]){
			ret+=mu[i]*(x/i/i);
		} return ret;
	}
}
ll queries[maxn];
int main() {
	int T,i; ll MAX=0;
	scanf("%d",&T);
	FOR(i,1,T) scanf("%lld",&queries[i]),max_(MAX,queries[i]);
	seives::init(min(MAX+1,(ll)seives::MAX));
	FOR(i,1,T){
		ll n=queries[i];
		ll ans=0;
		// ll i,j,k;
		//first
		// FOR(i,1,n) FOR(j,1,i) if (i%j==0) FOR(k,1,i) if (j%k==0)
		// 	add_(ans,seives::mu[k]*seives::mu[k]);
		//second
		// FOR(i,1,n) FOR(j,1,n/i)
		// 	add_(ans,seives::mu[i]*seives::mu[i]*(n/i/j));
		ll l;
		FOR(l,1,n) {
			ll t=n/l,r=n/t;
			ans+=seives::sum_sigma(t)*(seives::sum_mu(r)-seives::sum_mu(l-1));
			l=r;
		}
		printf("%lld\n",ans);
	}
}
/*
1
10000000000000
*/
