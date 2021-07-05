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

#define DEBUG1
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
int TaskA();
void Task_one() {TaskA();}
void Task_T() {int T; scanf("%d",&T); while (T--) TaskA();}
void Task_more_n() {while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m() {while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_n_m_q() {while (~scanf("%d%d%d",&n,&m,&q)) TaskA();}
void Task_more_string() {while (~scanf("%s",str)) TaskA();}

const int len=32768;
const ll MOD=1004535809;
const ll g=3;
int wn[maxn],invwn[maxn];
ll mul(ll x,ll y) {
	return x*y%MOD;
}
ll poww(ll a,ll b) {
	ll ret=1;
	for (; b; b>>=1ll,a=mul(a,a))
		if (b&1) ret=mul(ret,a);
	return ret;
}
void initwn(int len) {
	ll w=poww(g,(MOD-1)/len); int i;
	ll invw=poww(w,MOD-2); wn[0]=invwn[0]=1;
	rep(i,1,len) {
		wn[i]=mul(wn[i-1],w);
		invwn[i]=mul(invw,invwn[i-1]);
	}
}
void ntt(ll *A,int len,int inv) {
	int i,j,k;
	for (i=1,j=len/2; i<len-1; i++) {
		if (i<j) swap(A[i],A[j]);
		k=len/2;
		while (j>=k) j-=k,k/=2;
		if (j<k) j+=k;
	} for (i=2; i<=len; i<<=1) {
		for (j=0; j<len; j+=i) {
			for (k=j; k<(j+i/2); k++) {
				ll a,b; a=A[k];
				if (inv==-1) b=mul(A[k+i/2],invwn[(k-j)*len/i]);
				else b=mul(A[k+i/2],wn[(k-j)*len/i]);
				A[k]=(a+b); (A[k]>=MOD) &&(A[k]-=MOD);
				A[k+i/2]=(a-b+MOD); (A[k+i/2]>=MOD) &&(A[k+i/2]-=MOD);
			}
		}
	} if (inv==-1) {
		ll vn=poww(len,MOD-2);
		REP(i,len) A[i]=mul(A[i],vn);
	}
}
// http://120.78.128.11/Problem.jsp?pid=3400
// Xk=\sum{xi*wn[k*i]};
// 某个区间ntt下
int A[1007];
int V[1007][len];
ll ini[len],nxt[len];
int TaskA() {
	int i,k,x;
	scanf("%d%d%d",&n,&m,&x);
	initwn(len);
	FOR(i,1,n) scanf("%d",&A[i]);
	FOR(i,1,n) REP(k,len) V[i][k]=(V[i-1][k]+wn[(k*A[i])%len])%MOD;
	REP(k,len) ini[k]=1;
	FOR(i,1,m) {
		int l,r; scanf("%d%d",&l,&r);
		REP(k,len) nxt[k]=(V[r][k]-V[l-1][k]+1+MOD)%MOD;
		REP(k,len) ini[k]=mul(ini[k],nxt[k]);
		if (i%22==0) {
			ntt(ini,len,-1);
			rep(k,10001,len) ini[k]=0;
			ntt(ini,len,1);
		}
	} ntt(ini,len,-1);
	printf("%lld\n",ini[x]);
	return 0;
}
void initialize() {}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_one();
}
/*
*/
