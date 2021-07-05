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

// 带权二分:
// 解决凸包的问题, 求出方程后斜率优化即可
ll A[maxn];
ll dp[maxn]; int pre[maxn];
inline int getY(int id) {return dp[id]+A[id]*A[id];}
inline int getX(int id) {return A[id];}
int solve_solpe(ll w) {//slope
	static int Q[maxn],head,tail;
	int i,qi,qj,qk;
	head=tail=0;
	dp[0]=0; Q[tail++]=0;
	FOR(i,1,n) {
		while (head+1<tail) {
			qi=Q[head],qj=Q[head+1];
			if (getY(qj)-getY(qi)<=2*A[i]*(getX(qj)-getX(qi))) head++;
			else break;
		} qi=Q[head]; pre[i]=qi;//一次就.. 由之前的转移过来呗
		dp[i]=dp[qi]+(A[i]-A[qi])*(A[i]-A[qi])+w;
		while (head+1<tail) {
			qi=Q[tail-2]; qj=Q[tail-1]; qk=i;
			ll y1=getY(qj)-getY(qi),x1=getX(qj)-getX(qi);
			ll y2=getY(qk)-getY(qj),x2=getX(qk)-getX(qj);
			if (y2*x1<=y1*x2) tail--;//y2/x2>y1/x1
			else break;
		} Q[tail++]=i;
	} int ret=0;
	for (int x=n; x; x=pre[x]) ret++;
	return ret;
}
ll solve() {//n,m
	ll l=-1000000000,r=1000000000; int i;
	while (l+1<r) {
		ll mid=l+(r-l)/2;
		FOR(i,1,n) dp[i]=0;
		if (solve_solpe(mid)<=m) r=mid;
		else l=mid;
	} solve_solpe(l);
	// 这里的意义: 假设每次的答案都是最后一次的斜率
	// 然后, 二分这个斜率, 找到答案后减去每次的贡献
	return dp[n]-l*m;
}
int main() {
	int i;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%lld",&A[i]),A[i]+=A[i-1];
	printf("%lld\n",solve()*m-A[n]*A[n]);
}
/*
*/
