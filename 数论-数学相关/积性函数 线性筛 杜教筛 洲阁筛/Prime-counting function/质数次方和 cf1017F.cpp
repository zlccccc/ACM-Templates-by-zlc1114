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

namespace pcf {
	typedef unsigned int ll;
	ll H[maxn],L[maxn];
	ll getsum(ll n,ll k) {
		if (k==0) return n;
		if (k==1) {
			ll a=n,b=n+1;
			if (a%2==0) a/=2; else b/=2;
			return a*b;
		} if (k==2) {
			ll a=n,b=n+1,c=2*n+1;
			if (a%2==0) a/=2; else b/=2;
			if (a%3==0) a/=3; else if (b%3==0) b/=3; else c/=3;
			return a*b*c;
		} if (k==3) {
			ll a=n,b=n+1;
			if (a%2==0) a/=2; else b/=2;
			return a*b*a*b;
		} return 0*debug("getsum:wrong!");
	}
	ll power(ll n,ll k) {
		ll ret=1;
		while(k--) ret*=n;
		return ret;
	}
	ll cal(ll n,ll K) {//小于n的质数K次方和
		ll p,k,m;
		for (m=1; m*m<=n; ++m) H[m]=getsum(n/m,K)-1;
		FOR(p,1,m) L[p]=getsum(p,K)-1;
		FOR(p,2,m) {
			if (L[p]==L[p-1]) continue;//not_prime
			FOR(k,1,min(m-1,n/p/p)) {
				if (p*k<m) H[k]-=power(p,K)*(H[p*k]-L[p-1]);
				else H[k]-=power(p,K)*(L[n/p/k]-L[p-1]);
			} rFOR(k,p*p,m) L[k]-=power(p,K)*(L[k/p]-L[p-1]);
		}
		// return H[1];
		ll ret=0; ui l;
		FOR(l,1,n){//val+=n/i
			ll r=n/(n/l);
			if (r<=m) ret+=n/l*(L[r]-L[l-1]);
			else ret+=n/l*(H[n/l]-H[n/l+1]);
			l=r;
		} return ret;
	}
}
ui A,B,C,D;
inline ui get(ui x){return A*x*x*x+B*x*x+C*x+D;}
bool mark[maxn];
int main() {
	int i,j;
	scanf("%d%u%u%u%u",&n,&A,&B,&C,&D);
	int m; for (m=1; m*m<=n; ++m);
	ui ans=0;
	FOR(i,2,m) if (!mark[i]){// 这里只算大于i*i<=n的段(剩下的可以直接算)
		for (j=i*i;j<=m;j+=i) mark[j]=1;
		for (j=n/i/i;j;j/=i) ans+=get(i)*j;
	}
	ans+=pcf::cal(n,3)*A;
	ans+=pcf::cal(n,2)*B;
	ans+=pcf::cal(n,1)*C;
	ans+=pcf::cal(n,0)*D;
	printf("%u",ans);
}
/*
*/
