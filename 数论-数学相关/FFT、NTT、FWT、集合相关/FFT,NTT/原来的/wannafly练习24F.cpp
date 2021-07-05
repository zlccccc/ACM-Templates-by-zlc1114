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
template<typename T>inline T powMM(T a, T b,ll Mod=M) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%Mod)
		if (b&1) ret=(LL)ret*a%Mod;
	return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

// 主要思路不是这个裸的乘法啥的啊!
// from picks' blog
// 对G(F(x))=0进行泰勒展开
// G'(F_{t+1}(x))=G(F_t(x))+G'(F_t(x))/1*(F_{t+1}-F_t(x))^1+....
// 后方的系数在mod x^2^t+1的意义下全是0!(因为减的那里的系数是2^t)
// F_{t+1}(x)=F_t(x)-G(F_t(x))/G'(F_t(x))
// 所以手动求个导数即可!
// 注意这个G(F(t))就是满足的那个式子! 注意要有常数项(否则可以全是0 =_=!)
// 三角函数需要利用虚数来做, e^{iF(x)}=cos(F(x))+isin(F(x))
// exp(x): F_{t+1}(x)=F_t(x)-F_t(x)*((ln(F_t(x))-P(x))*F_t(x))
// ln(x) : ln(F(x))=\int(积分) F'(x)/F(x)

// http://codeforces.com/contest/438/problem/E
// 题意: 问你有多少个二叉树点权从c中取, 而且权值和是k
// 做法: 考虑多一个点, 所以f[x]=sigma{f[k]*f[x-k-s],(s in c)}
// 所以 满足 F=F^2*C+1, 左边是生成函数
// 所以 F=[1-sqrt(1-4C)]/2C=1/(1+sqrt(1-4C))
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

	const ll Mod=19260817;
	// 下方的东西和ntt就根本无关, 这个模数是可以改的, 是多项式相关的东西
	// 也就是说, 这个模数完全可以取其他的, 然后高精度的mtt来求, 不过可能会T到死
	int eInv[maxn];
	void initinv(int l) {
		int i; eInv[0]=eInv[1]=1;
		rep(i,2,l) eInv[i]=(Mod-Mod/i)*eInv[Mod%i]%Mod;
	}
	void Ftof(int *A,int *B,int l) {//derivative 求导
		int i;
		FOR(i,1,l) B[i-1]=(ll)A[i]*i%Mod;
	}
	void ftoF(int *A,int *B,int l) {//integral 积分
		int i; // todo:get B[0], getinv
		rFOR(i,1,l) B[i]=(ll)A[i-1]*eInv[i]%Mod;
		B[0]=0;
	}
	void inv(int *A,int *B,int l) { //B=inv(A)
		static int C[maxn],D[maxn];
		B[0]=eInv[A[0]]; B[1]=0;
		for (int len=2; len<=l; len<<=1) {
			int i; fill(B+len,B+len+len,0);
			copy(A,A+len,C); fill(C+len,C+len+len,0);
			mul(C,B,D,len*2,Mod); fill(D+len,D+len+len,0);
			mul(D,B,D,len*2,Mod);
			REP(i,len) B[i]=(B[i]*2-D[i]+Mod)%Mod;
			fill(B+len,B+len+len,0);
		}
	}
	void ln(int *A,int *B,int l) {
		static int C[maxn];
		inv(A,B,l); Ftof(A,C,l);
		// int i;
		// REP(i,l*2) debug("%d ",A[i]); deputs(" <- A(A)");
		// REP(i,l*2) debug("%d ",B[i]); deputs(" <- B(inv)");
		// REP(i,l*2) debug("%d ",C[i]); deputs(" <- C(F')");
		mul(B,C,B,l*2,Mod);
		// REP(i,l*2) debug("%d ",B[i]); deputs(" <- B(mul)");
		ftoF(B,B,l);
	}
	void exp(int *A,int *B,int l) {
		static int C[maxn],i;
		B[0]=1; B[1]=0;
		for (int len=2; len<=l; len<<=1) {
			// debug("exp: len=%d\n",len);
			fill(B+len,B+len+len,0);
			ln(B,C,len); fill(C+len,C+len+len,0);
			// REP(i,len) debug("%d ",B[i]); deputs(" <- B");
			// REP(i,len) debug("%d ",A[i]); deputs(" <- A");
			// REP(i,len) debug("%d ",C[i]); deputs(" <- C(ln)");
			REP(i,len) C[i]=(C[i]-A[i]+Mod)%Mod;
			mul(B,C,C,len*2,Mod);
			REP(i,len) B[i]=(B[i]-C[i]+Mod)%Mod;
			// REP(i,len) debug("%d ",B[i]); deputs(" <- nowans");
		}
	}
	//这里是更高一层的东西
	static int A[maxn],B[maxn];
	void multiply(int *a,int *b,int *ans,int n,int m) {//C=A*B(actual)
		int len=1,i;
		while (len<n+m-2) len<<=1;
		REP(i,n) A[i]=a[i]; rep(i,n,len) A[i]=0;
		REP(i,m) B[i]=b[i]; rep(i,m,len) B[i]=0;
		mul(A,B,ans,len,Mod);
	}
	void getexp(int *a,int *ans,int n) {
		int len=1,i;
		while (len<n) len<<=1;
		REP(i,n) A[i]=a[i]; rep(i,n,len) A[i]=0;
		exp(A,ans,len);
	}
	void solve(int *a,int *ans,int m) {
		static int A[maxn];
		int i,j;
		// deputs("solve");
		FOR(i,1,m) {//无穷背包
			int now=(ll)i*a[i]%Mod;
			for (j=i-1; j<=m; j+=i) A[j]=(now+A[j])%Mod;
		}
		// REP(i,m) printf("%d(%d) ",A[i],i); puts("");
		ftoF(A,A,m);
		// REP(i,m) printf("%d(%d) ",A[i],i); puts("");
		getexp(A,ans,m+1);
	}
}
int A[maxn],ans[maxn];
int main() {
	int i,k;
	FFT::initinv(maxn);
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%d",&k),A[k]++;
	FFT::solve(A,ans,m);
	// FOR(i,1,m) printf("%d ",ans[i]);
	int Ans=0;
	FOR(i,1,m) add_(Ans,ans[i],FFT::Mod);
	printf("%d\n",Ans);
}
/*
*/
