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

vector<int> P[maxn];
namespace seives { // 抄的define
#define clr(ar) memset(ar, 0, sizeof(ar))
#define chkbit(ar, i) (((ar[(i) >> 6]) & (1 << (((i) >> 1) & 31))))
#define setbit(ar, i) (((ar[(i) >> 6]) |= (1 << (((i) >> 1) & 31))))
#define isprime(x) (( (x) && ((x)&1) && (!chkbit(ar, (x)))) || ((x) == 2))
	const int MAXP=666666;
	const int MAX=5000010;
	int phi[MAX],f[MAX],t[MAX];
	int p[MAXP],tot;
	ui ar[(MAX>>6)+7]= {0};
	void init() {
		setbit(ar,0); setbit(ar,1);
		int i,j; tot=0; phi[1]=1; t[1]=1;
		rep(i,2,MAX) {
			if (isprime(i)) p[tot++]=i,phi[i]=i-1,t[i]=i;
			REP(j,tot) {
				if (i*p[j]>=MAX) break;
				if ((i*p[j])&1) setbit(ar,i*p[j]);
				if (i%p[j]==0) {
					phi[i*p[j]]=phi[i]*p[j];
					t[i*p[j]]=t[i]; break;
				} else {
					phi[i*p[j]]=phi[i]*(p[j]-1);
					t[i*p[j]]=t[i]*p[j];
				}
			}
		}rep(i,1,MAX) f[i]=phi[i],add_(f[i],f[i-1]);
		rep(i,1,maxn) for (j=i;j<maxn;j+=i) P[j].push_back(i);
	}
	map<int,int> HASH;
	int get_f(int x){
		if (x<MAX) return f[x];
		if (HASH.count(x)) return HASH[x];
		int ret=(ll)x*(x+1)/2%M; ll l;
		FOR(l,2,x) {
			ll t=x/l,r=x/t;
			add_(ret,M-(ll)(r-l+1)*get_f(t)%M);
			l=r;
		} return HASH[x]=ret;
	}
}
map<int,int> MP[maxn];
int S(int t,int m){
	if (t==1) return seives::get_f(t*m);
	if (m<=1) return seives::phi[t*m];
	if (MP[t].count(m)) return MP[t][m];
	int ret=0,i;
	REP(i,(int)P[t].size()){
		int k=P[t][i];
		add_(ret,(ll)seives::phi[t/k]*S(k,m/k)%M);
	}
	return MP[t][m]=ret;
}
int main() {
	int i,ans=0;
	// startTimer();
	seives::init();
	// printTimer();
	scanf("%d%d",&n,&m);
	// startTimer();
	FOR(i,1,n) add_(ans,(ll)i/seives::t[i]*S(seives::t[i],m)%M);
	// printTimer();
	printf("%d\n",ans);
}
/*
1 10
*/
