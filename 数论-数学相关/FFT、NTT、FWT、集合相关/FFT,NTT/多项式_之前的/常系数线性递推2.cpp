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
const LL M=119;
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

// Cayley-Hamilton定理
namespace FFT {
	const int maxn=1<<18|7;
	struct complex {
		double a,b;
		complex(double _a=.0,double _b=.0):a(_a),b(_b) {}
		complex operator+(const complex x)const {return complex(a+x.a,b+x.b);}
		complex operator-(const complex x)const {return complex(a-x.a,b-x.b);}
		complex operator*(const complex x)const {return complex(a*x.a-b*x.b,a*x.b+b*x.a);}
	};
	complex wn[maxn];
	void initwn(int l) {
		static int len=0; int i;
		if (len==l) return; else len=l;
		REP(i,len) wn[i]=complex(cos(2*pi*i/l),sin(2*pi*i/l));
	}
	void fft(complex *A,int len,int inv) {
		int i,j,k; initwn(len);
		for (i=1,j=len/2; i<len-1; i++) {
			if (i<j) swap(A[i],A[j]);
			k=len/2;
			while (j>=k) j-=k,k/=2;
			if (j<k) j+=k;
		} for (i=2; i<=len; i<<=1) {
			for (j=0; j<len; j+=i) {
				for (k=j; k<(j+i/2); k++) {
					complex a,b; a=A[k];
					b=A[k+i/2]*wn[(ll)(k-j)*len/i];
					A[k]=a+b; A[k+i/2]=a-b;
				}
			}
		} if (inv==-1) REP(i,len) A[i]=complex(A[i].a/len,A[i].b/len);
	}
	inline complex conj(complex &A) {return complex(A.a,-A.b);}
	void mul(int *A,int *B,int *ans,int len,int mod) { //ans=A*B
		static complex x1[maxn],x2[maxn];
		static complex x3[maxn],x4[maxn];
		static const int S=1<<15 ; int i;
		REP(i,len) x1[i]=complex(A[i]/S,A[i]%S);
		REP(i,len) x2[i]=complex(B[i]/S,B[i]%S);
		fft(x1,len,1); fft(x2,len,1);
		REP(i,len) {//这个k1, b1就是前面的, 这就减掉了一半常数
			int j=(len-i)&(len-1);
			complex k1=(conj(x1[i])+x1[j])*complex(0.5,0);//dft k1
			complex b1=(conj(x1[i])-x1[j])*complex(0,0.5);//dft b1
			complex k2=(conj(x2[i])+x2[j])*complex(0.5,0);//dft k2
			complex b2=(conj(x2[i])-x2[j])*complex(0,0.5);//dft b2
			x3[i]=k1*k2+k1*b2*complex(0,1);
			x4[i]=b1*k2+b1*b2*complex(0,1);
		} fft(x3,len,-1); fft(x4,len,-1);
		REP(i,len) {
			ll kk=x3[i].a+0.5,kb=x3[i].b+0.5;
			ll bk=x4[i].a+0.5,bb=x4[i].b+0.5;
			ans[i]=((kk%mod*S%mod+kb+bk)%mod*S%mod+bb)%mod;
		}
	}

	static int A[maxn],B[maxn];
	void multiply(int *a,int *b,int *ans,int n,int m,int Mod) {//C=A*B(actual)
		int len=1,i;
		while (len<n+m-1) len<<=1;
		REP(i,n) A[i]=a[i]; rep(i,n,len) A[i]=0;
		REP(i,m) B[i]=b[i]; rep(i,m,len) B[i]=0;
		mul(A,B,ans,len,Mod);
	}
}
int H[maxn];
int C[maxn],D[maxn],E[maxn];
int solve(int k,ll a,ll b,int p,int q){
	int i,n=max(p,q); n++;//no!
	REP(i,n) {
		H[i]=0;
		if (i==0) H[i]=1;
		else {
			if (i<p) add_(H[i],a%M);
			else add_(H[i],(ll)a*H[i-p]%M);
			if (i<q) add_(H[i],b%M);
			else add_(H[i],(ll)b*H[i-q]%M);
			// printf("%d : %d\n",i,H[i]);
		}
	}
	C[0]=0; C[1]=1; D[0]=1; int lC=2,lD=1;
	// REP(i,n) printf("%d ",H[i]); puts("<- H "); printf("k=%d; n=%d\n",k,n);
	for (ll x=k; x; x>>=1) {
		if (x&1) {
			FFT::multiply(C,D,D,lC,lD,M);
			rrep(i,n,lC+lD-1) if (D[i]) {//divide
				D[i-p]=(D[i-p]+D[i]*a)%M;
				D[i-q]=(D[i-q]+D[i]*b)%M;
			} lD=min(lC+lD-1,n);
		} FFT::multiply(C,C,C,lC,lC,M);
		rrep(i,n,lC+lC-1) if (C[i]) {//divide
			C[i-p]=(C[i-p]+C[i]*a)%M;
			C[i-q]=(C[i-q]+C[i]*b)%M;
		} lC=min(lC+lC-1,n);
		// REP(i,lC) printf("%2d ",C[i]); puts("<- C ");
		// REP(i,lD) printf("%2d ",D[i]); puts("<- D ");
	} reverse(D,D+lD);
	int ans=0;
	// REP(i,lD) printf("%2d*%d ",D[i],H[n-1-i-1]); puts("<- D ");
	// REP(i,n) printf("%d ",B[i]); puts("<- B ");
	REP(i,lD) add_(ans,(ll)D[i]*H[lD-i-1]%M);
	return ans;
}
int f[1100000];
int main() {
	int n,a,b,p,q;
	// int i; REP(i,200) printf("%d ",solve(i,1,1,1,2)); puts("");
	// int i;
	// a=2; b=3; p=4; q=5;
	// // printf("%d ",solve(9,a,b,p,q));
	// FOR(i,0,1000000) {
	// 	f[i]=0;
	// 	if (i==0) f[i]=1;
	// 	else {
	// 		if (i<p) add_(f[i],a%M);
	// 		else add_(f[i],(ll)a*f[i-p]%M);
	// 		if (i<q) add_(f[i],b%M);
	// 		else add_(f[i],(ll)b*f[i-q]%M);
	// 		// printf("%d : %d\n",i,H[i]);
	// 	}
	// 	printf("%d: f=%d %d\n",i,f[i],solve(i,a,b,p,q));
	// }
	while (scanf("%d%d%d%d%d",&n,&a,&b,&p,&q)==5) printf("%d\n",solve(n,a,b,p,q));
	return 0;
}
/*
*/
