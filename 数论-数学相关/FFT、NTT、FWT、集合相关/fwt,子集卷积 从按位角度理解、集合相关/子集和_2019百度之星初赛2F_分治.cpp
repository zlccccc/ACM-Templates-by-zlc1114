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

// f(x)=sum_(f(y)), f(x)在某些条件下=0
int f[1<<21|7],g[1<<21|7];
char str[1<<21|7];
void solve(int l,int r) {
	if (l+1==r) {
		if (!l) f[l]=1,g[l]=0;
		else if (str[l-1]=='+') f[l]=0;
		add_(g[l],f[l]);
		return;
	} int i,mid=(l+r)/2;
	solve(l,mid);
	REP(i,mid-l) add_(f[i+mid],g[i+l]);//left的影响
	// printf("%d-%d: (mid of f)\n",l,r);
	// REP(i,r-l) printf("%d ",f[l+i]); puts("<-f");
	// REP(i,r-l) printf("%d ",g[l+i]); puts("<-g");
	solve(mid,r);
	// printf("%d-%d: (mid of g)\n",l,r);
	REP(i,mid-l) add_(g[i+mid],g[i+l]);
}
int main() {
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T){
		/*to solve the problem*/
		scanf("%s",str);
		int n=strlen(str),MAX=1;
		while (MAX<=n+1) MAX<<=1;
		memset(f,0,MAX*sizeof(int));
		memset(g,0,MAX*sizeof(int));
		solve(0,MAX);
		// int i;
		// REP(i,MAX) printf("%d ",f[i]); puts("");
		// REP(i,MAX) printf("%d ",g[i]); puts("");
		printf("%d %d\n",n+1,f[n+1]);
	}
}
/*
10
??????
???????
*/
