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
const LL M=998244353;
const LL maxn=1e5+107;
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
inline ll powMM(ll a,ll b,ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

// 题意: 给n个区间, 求与0的距离差期望
// 做法: 考虑每一次, 都是个区间分段积分形式
// 所以直接考虑每一段, 2-pointer求2^n项系数即可
const int maxk=20;
int inv[maxk];
inline void init() {
	int i; inv[0]=1;
	rep(i,1,maxk) inv[i]=powMM(i,M-2);
}
struct poly {
	int A[maxk],n;//base
	void init(int n) {memset(A,0,sizeof(A)); this->n=n;};
	poly(int n=0) {init(n);}
	int getvalue(int x) {
		int i; ll ret=0;
		// rREP(i,n+1) if (A[i]<0) printf("i=%d: %d\n",i,A[i]);
		rREP(i,n+1) ret=(ret*x+A[i])%M;
		return ret;
	}
	poly integral() {//ret.A[0]需要自己算
		poly ret; int i; ret.n=n+1; ret.A[0]=0;
		REP(i,n+1) ret.A[i+1]=(ll)A[i]*inv[i+1]%M;
		return ret;
	}
	poly derivative(){
		poly ret; int i; ret.n=n-1; ret.A[0]=0;
		REP(i,n) ret.A[i]=(ll)A[i+1]*(i+1)%M;
		return ret;
	}
	poly move(poly base[]) {
		poly ret; ret.init(n); int i,j;
		REP(i,n+1) REP(j,i+1) {
			add_(ret.A[j],(ll)A[i]*base[i].A[j]%M);
		} return ret;
	}
	poly mul(const poly &p) {
		poly ret; ret.init(n+p.n); int i,j;
		REP(i,n+1) REP(j,p.n+1) {
			add_(ret.A[i+j],(ll)A[i]*p.A[j]%M);
		} return ret;
	}
	poly del(const poly &p) {
		poly ret; ret.init(max(n,p.n)); int i;
		REP(i,n+1) add_(ret.A[i],A[i]);
		REP(i,p.n+1) add_(ret.A[i],M-p.A[i]);
		return ret;
	}
}; //(x-r)
int len[maxn];
typedef pair<int,poly> pip;// 从first往后一段区间内的poly_value是second
int base=0,multi=1;
void getintegral(pip now[],pip nxt[],int n) {//得到一个连续的积分,并从0开始算常数项
	int i;
	FOR(i,1,n) {
		int k=nxt[i].first=now[i].first;
		nxt[i].second=now[i].second.integral();
		nxt[i].second.A[0]=(nxt[i-1].second.getvalue(k)
		                    -nxt[i].second.getvalue(k)+M*2)%M;
	}
}
void getbase(poly base[],int k,int n) {//(x-k)^n; 用于移动整个区间
	int i; base[0].init(0);
	base[0].A[0]=1;//1
	poly mul; mul.init(1);
	mul.A[0]=(M-k%M)%M; mul.A[1]=1;
	FOR(i,1,n) base[i]=base[i-1].mul(mul);
}
pip now[1<<15|7],inter[1<<15|7],nxt[1<<15|7];
poly multibase[maxk];
int ans=0; int mbase=1;
int main() {
	init();
	int n,i;
	scanf("%d",&n);
	FOR(i,1,n) {
		int l,r;
		scanf("%d%d",&l,&r);
		add_(ans,(l+r)*powMM(2ll,M-2)%M);//之后加两倍负数即可
		r-=l; base-=l; len[i]=r;
		if (r) mbase=mbase*powMM(r,M-2)%M;
	}
	reverse(len+1,len+1+n);
	now[0].second.init(0);
	now[0].second.A[0]=0;
	now[1].first=0;
	now[1].second.init(0);
	now[1].second.A[0]=1;//integeal_ed
	int m=1;//Count
	FOR(i,1,n) {
		if (len[i]==0) continue;
		getintegral(now,inter,m);
		// swap(now,inter);
		// printf("%d (inter):\n",i);
		// for (int _i=1;_i<=m;_i++) {
		// 	printf("%d(",now[_i].first);
		// 	for (int j=0;j<=now[_i].second.n;j++)
		// 		printf("%d%c",now[_i].second.A[j],"+)"[j==now[_i].second.n]);
		// 	printf(" ");
		// } puts("");
		// printf("%d (inter_move):\n",i);
		// for (int _i=1;_i<=m;_i++) {
		// 	printf("%d(",now[_i].first);
		// 	for (int j=0;j<=now[_i].second.n;j++)
		// 		printf("%d%c",now[_i].second.move(multibase).A[j],"+)"[j==now[_i].second.n]);
		// 	printf(" ");
		// } puts("");
		// swap(now,inter);
		//开始积分
		getbase(multibase,len[i],n);
		int l=1,r=1,nxtm=0;
		while (l<=m||r<=m) {
			int pos=INF;
			if (l<=m) pos=min(pos,now[l].first+len[i]);
			if (r<=m) pos=min(pos,now[r].first);
			while (l<=m&&now[l].first+len[i]==pos) l++;//相同pos只有一次
			while (r<=m&&now[r].first==pos) r++;
			++nxtm; nxt[nxtm].first=pos;
			nxt[nxtm].second=inter[r-1].second.del(inter[l-1].second.move(multibase));
		}
		swap(now,nxt); m=nxtm;
		// printf("%d (now):\n",i);
		// for (int _i=1;_i<=m;_i++) {
		// 	printf("%d(",now[_i].first);
		// 	for (int j=0;j<=now[_i].second.n;j++)
		// 		printf("%d%c",now[_i].second.A[j],"+)"[j==now[_i].second.n]);
		// 	printf(" ");
		// 	printf("%d %d\n",now[_i].second.getvalue(now[_i].first),
		// 					now[_i-1].second.getvalue(now[_i].first));
		// } puts("");
	} poly x; x.init(1); x.A[1]=1;
	getbase(multibase,-base,n);
	// printf("%d (base):\n",i);
	// for (int _i=1; _i<=m; _i++) {
	// 	printf("%d(",_i);
	// 	for (int j=0; j<=multibase[_i].n; j++)
	// 		printf("%d%c",multibase[_i].A[j],"+)"[j==multibase[_i].n]);
	// 	printf(" ");
	// } puts("");
	FOR(i,1,m) {
		now[i].first-=base;
		now[i].second=now[i].second.move(multibase);
		now[i].second=now[i].second.derivative();
		now[i].second=now[i].second.mul(x);
	} getintegral(now,inter,m);
	// printf("%d (now):\n",i);
	// for (int _i=1; _i<=m; _i++) {
	// 	printf("%d(",now[_i].first);
	// 	for (int j=0; j<=now[_i].second.n; j++)
	// 		printf("%d%c",now[_i].second.A[j],"+)"[j==now[_i].second.n]);
	// 	printf(" ");
	// 	printf("%d %d\n",now[_i].second.getvalue(now[_i].first),
	// 	       now[_i-1].second.getvalue(now[_i].first));
	// } puts("");
	// swap(now,inter);
	// printf("%d (now):\n",i);
	// for (int _i=1; _i<=m; _i++) {
	// 	printf("%d(",now[_i].first);
	// 	for (int j=0; j<=now[_i].second.n; j++)
	// 		printf("%d%c",now[_i].second.A[j],"+)"[j==now[_i].second.n]);
	// 	printf(" ");
	// 	printf("%d %d\n",now[_i].second.getvalue(now[_i].first),
	// 	       now[_i-1].second.getvalue(now[_i].first));
	// } puts("");
	// printf("mbase=%d,mbase\n",mbase);
	// swap(now,inter);
	int last=0;
	FOR(i,1,m) if (inter[i].first<=0) last=i;
	// printf("last=%d; %lld\n",last,inter[last].second.getvalue(0)*2%M);
	add_(ans,(2ll*(M-(ll)inter[last].second.getvalue(0)*mbase%M))%M);
	printf("%d\n",ans);
}
/*
2
-2 3
-2 1

3
-3 3
-2 2
-1 1
*/