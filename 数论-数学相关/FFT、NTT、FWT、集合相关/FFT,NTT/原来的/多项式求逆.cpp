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
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=1<<18|7;
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

// http://codeforces.com/contest/438/problem/E
// 题意: 问你有多少个二叉树点权从c中取, 而且权值和是k
// 做法: 考虑多一个点, 所以f[x]=sigma{f[k]*f[x-k-s],(s in c)}
// 所以 满足 F=F^2*C+1, 左边是生成函数
// 所以 F=[1-sqrt(1-4C)]/2C
// 当且仅当常数项有逆元, 可以多项式求逆
// 求逆:C*A≡1(mod x^n)
// B*A≡1(mod x^(n/2))
// (B*A-1)*(B*A-1)≡0(mod x^(n/2))
// B*B*A*A-2*A*B+1≡0(mod x^n)
// B*B*A-2*B+C≡0(mod x^n)
// C≡B*(2-A*B)(mod x^n)

// 求根:C*C≡A(mod x^n)
// B*B≡A(mod x^n/2)
// (B*B-A)*(B*B-A)≡0(mod x^n)
// B*B*B*B-2*C*C*B*B+C*C*C*C≡0(mod x^n)
// (B*B+C*C)*(B*B+C*C)≡4*C*C*B*B(mod x^n)
// B*B+A≡2*C*B(mod x^n)
// C=(B*B+A)/(2*B)
namespace NTT {
	const ll MOD=998244353;
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
	void initwn(int l) {
		static int len=0;
		if (len==l) return; len=l;
		ll w=poww(g,(MOD-1)/len); int i;
		ll invw=poww(w,MOD-2); wn[0]=invwn[0]=1;
		rep(i,1,len) {
			wn[i]=mul(wn[i-1],w);
			invwn[i]=mul(invw,invwn[i-1]);
		}
	}
	void ntt(ll *A,int len,int inv) {
		int i,j,k; initwn(len);
		for (i=1,j=len/2; i<len-1; i++) {
			if (i<j) swap(A[i],A[j]);
			k=len/2;
			while (j>=k) j-=k,k/=2;
			if (j<k) j+=k;
		} for (i=2; i<=len; i<<=1) {
			for (j=0; j<len; j+=i) {
				for (k=j; k<(j+i/2); k++) {
					ll a,b; a=A[k];
					if (inv==-1) b=mul(A[k+i/2],invwn[(ll)(k-j)*len/i]);
					else b=mul(A[k+i/2],wn[(ll)(k-j)*len/i]);
					A[k]=(a+b); (A[k]>=MOD) &&(A[k]-=MOD);
					A[k+i/2]=(a-b+MOD); (A[k+i/2]>=MOD) &&(A[k+i/2]-=MOD);
				}
			}
		} if (inv==-1) {
			ll vn=poww(len,MOD-2);
			REP(i,len) A[i]=mul(A[i],vn);
		}
	}
	void mul(ll *A,ll *B,int len) { //A=A*B
		int i;
		ntt(A,len,1); ntt(B,len,1);
		REP(i,len) A[i]=mul(A[i],B[i]);
		ntt(A,len,-1);
	}
	void inv(ll *A,ll *B,int l) { //B=inv(A)
		static ll C[maxn];
		B[0]=poww(A[0],MOD-2); B[1]=0;
		for (int len=2; len<=l; len<<=1) {
			int i; fill(B+len,B+len+len,0);
			copy(A,A+len,C); fill(C+len,C+len+len,0);
			ntt(C,len*2,1); ntt(B,len*2,1);
			REP(i,len*2) B[i]=mul(B[i],(MOD+2-mul(C[i],B[i])));
			ntt(B,len*2,-1); fill(B+len,B+len+len,0);
		}
	}
	void sqrt(ll *A,ll *B,int l) { //B=sqrt(A)
		static ll C[maxn],_B[maxn];
		B[0]=1; B[1]=0;// 这里应该是个二次剩余
		for (int len=2; len<=l; len<<=1) {
			int i; ll inv2=poww(2,MOD-2);
			inv(B,_B,len); fill(B+len,B+len+len,0);
			copy(A,A+len,C); fill(C+len,C+len+len,0);
			ntt(C,len*2,1); ntt(_B,len*2,1); ntt(B,len*2,1);
			REP(i,len*2) B[i]=mul(inv2,B[i]+mul(C[i],_B[i]));
			ntt(B,len*2,-1); fill(B+len,B+len+len,0);
		}
	}
}
// F=[1-sqrt(1-4C)]/2C
ll C[maxn],A[maxn],ans[maxn],tmp[maxn];
int main() {
	int i,k;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%d",&k),C[k]++;
	int len=1;
	while (len<=m) len<<=1;
	REP(i,len) A[i]=-4*C[i]; A[0]++;
	REP(i,len) mod_(A[i]);
	NTT::sqrt(A,tmp,len);
	add_(tmp[0],1);
	NTT::inv(tmp,ans,len);
	REP(i,len) mul_(ans[i],2);
	FOR(i,1,m) printf("%lld\n",ans[i]);
}
/*
*/
