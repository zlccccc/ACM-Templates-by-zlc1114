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
const ll INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=200+7;
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

ll g[maxn][maxn];
ll lx[maxn],ly[maxn],slack[maxn];
int linky[maxn],par[maxn];
int prex[maxn],prey[maxn];
void adjust(int v) {
	linky[v]=prey[v];
	if (prex[linky[v]]!=-2) adjust(prex[linky[v]]);
}
int search(int x) { //匈牙利
	int y; int tmp;
	FOR(y,1,n) if (prey[y]==-1) {
		tmp=lx[x]+ly[y]-g[x][y];
		if (slack[y]>tmp) {
			slack[y]=tmp; par[y]=x;
		} if (!tmp) {
			prey[y]=x;
			if (linky[y]==-1) {
				adjust(y);
				return 1;
			} if (prex[linky[y]]!=-1) continue;
			prex[linky[y]]=y;
			if (search(linky[y])) return 1;
		}
	} return 0;
}
ll KM() {
	int i,x,y;
	FOR(i,1,n) {
		lx[i]=0; ly[i]=0; linky[i]=-1;
		FOR(y,1,n) max_(lx[i],g[i][y]);
	}
	FOR(x,1,n) {
		FOR(i,1,n) slack[i]=INFF,prex[i]=prey[i]=-1;
		prex[x]=-2; if (search(x)) continue;
		bool flag=0;
		while (!flag) {
			ll d=INFF;
			FOR(i,1,n) if (prey[i]==-1) min_(d,slack[i]);
			FOR(i,1,n) {
				if (prex[i]!=-1) lx[i]-=d;
				if (prey[i]!=-1) ly[i]+=d;
				else slack[i]-=d;
			}
			FOR(i,1,n) if (prey[i]==-1&&!slack[i]) {
				prey[i]=par[i];
				if (linky[i]==-1) {
					adjust(i); flag=1; break;
				} prex[linky[i]]=i;
				if (search(linky[i])) {
					flag=1; break;
				}
			}
		}
	} ll ret=0;
	FOR(i,1,n) ret+=g[linky[i]][i];
	return ret;
}
int main() {
	int T,_T;
	scanf("%d",&T);
	FOR(_T,1,T) {
		scanf("%d",&n);
		int i,j;
		FOR(i,1,n) FOR(j,1,n) {
			int x;
			scanf("%d",&x);
			g[i][j]=-x;
		} ll ans=-KM();
		// printf("%d\n",ans);
		printf("Case #%d: %I64d\n",_T,ans);
	}
}
/*
*/
