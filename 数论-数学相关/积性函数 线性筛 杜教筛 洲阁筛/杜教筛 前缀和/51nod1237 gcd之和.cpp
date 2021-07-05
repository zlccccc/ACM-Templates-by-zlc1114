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

// gcd之和 计算过程
//   \sum_{i} \sum_{j} gcd(i,j)
// = \sum_{d} d * \sum_{i}^{n/d} \sum_{j}^{n/d} [gcd(i,j)=1]
// = \sum_{d} d * \sum_{k} * \sum_{k|i} * \sum_{k|j} \mu{(k)}
// = \sum_{d} d * \sum_{k} * \frac{n}{d*k} ^ 2 * \mu{(k)}
// let t = d*k
// = \sum_{d|t} * \sum_{t} * \frac{n}{t} ^ 2 * d * \mu{(\frac{t}{d})}
// = \sum_{t} * \frac{n}{t} ^ 2 * \sum_{d|t} * d * \mu{(\frac{t}{d})}
// = \sum_{t} * \frac{n}{t} ^ 2 * \varphi{(t)}
// 后半部分杜教筛出来, 前半部分直接 \sqrt(n) 枚举
namespace seives { // 抄的define
#define clr(ar) memset(ar, 0, sizeof(ar))
#define chkbit(ar, i) (((ar[(i) >> 6]) & (1 << (((i) >> 1) & 31))))
#define setbit(ar, i) (((ar[(i) >> 6]) |= (1 << (((i) >> 1) & 31))))
#define isprime(x) (( (x) && ((x)&1) && (!chkbit(ar, (x)))) || ((x) == 2))
	map<ll,int> HASH;
	const int MAXP=666666;
	const int MAX=10000010;
	int phi[MAX];
	int p[MAXP],tot;
	ui ar[(MAX>>6)+7]= {0};
	void init() {
		setbit(ar,0); setbit(ar,1);
		int i,j; tot=0; phi[1]=1;
		rep(i,2,MAX) {
			if (isprime(i)) p[tot++]=i,phi[i]=i-1;
			REP(j,tot) {
				if (i*p[j]>=MAX) break;
				if ((i*p[j])&1) setbit(ar,i*p[j]);
				if (i%p[j]==0) {phi[i*p[j]]=(ll)phi[i]*p[j]%M; break;}
				else phi[i*p[j]]=(ll)phi[i]*(p[j]-1)%M;
			}
		}
		rep(i,2,MAX) add_(phi[i],phi[i-1]);
	}
	inline int sum_phi(ll x) {
		if (x<MAX) return phi[x];
		if (HASH.count(x)) return HASH[x];
		int ret=(ll)x%M*((x+1)%M)%M*500000004%M;ll l;
		FOR(l,2,x){
			ll r=x/(x/l);
			add_(ret,M-(ll)(r-l+1)%M*sum_phi(x/l)%M);
			l=r;
		} return HASH[x]=ret;
	}
}
int main() {
	ll x;
	seives::init();
	scanf("%lld",&x);
	ll l; ll ans=0;
	FOR(l,1,x){
		ll t=x/l;ll r=x/t; t%=M;
		add_(ans,t*t%M*(seives::sum_phi(r)-seives::sum_phi(l-1)+M)%M);
		l=r;
	} printf("%lld\n",ans);
}
/*
*/
