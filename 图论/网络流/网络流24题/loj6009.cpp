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
const LL maxn=1<<20|7;
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

int B1[maxn],B2[maxn],F1[maxn],F2[maxn],v[maxn];
int dis[maxn];
priority_queue<pii,vector<pii>,greater<pii> > Q;
int main() {
	int i,j;
	scanf("%d%d",&n,&m);
	FOR(i,1,m){
		scanf("%d",&v[i]);
		scanf("%s",str);
		REP(j,n) B1[i]=B1[i]*2+(str[j]=='+');
		REP(j,n) B2[i]=B2[i]*2+(str[j]=='-');
		scanf("%s",str);
		REP(j,n) F1[i]=F1[i]*2+(str[j]=='-');
		REP(j,n) F2[i]=F2[i]*2+(str[j]=='+');
	} int N=1<<n;
	memset(dis,0x3f,N*sizeof(int));
	dis[N-1]=0;	Q.push(make_pair(0,N-1));
	while (Q.size()){
		auto now=Q.top(); Q.pop();
		int x=now.second;
		if (dis[x]!=now.first) continue;
		FOR(i,1,m) if ((B1[i]&x)==B1[i]&&(B2[i]&x)==0){
			int y=(x&~F1[i])|F2[i];
			if (dis[y]>dis[x]+v[i]){
				dis[y]=dis[x]+v[i];
				Q.push(make_pair(dis[y],y));
			}
		}
	} if (dis[0]==INF) puts("0");
	else printf("%d\n",dis[0]);
}
/*
*/
