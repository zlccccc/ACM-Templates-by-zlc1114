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
const LL maxn=2e5+7;
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

struct node{
	int to,len,next;
	node(int _to=0,int _len=0,int _next=0):to(_to),len(_len),next(_next){};
}edge[maxn*20];
int head[maxn],tot;
void addedge(int x,int y,int len){
	edge[tot]=node(y,len,head[x]); head[x]=tot++;
} int dis[maxn];
priority_queue<pii,vector<pii>,greater<pii> > Q;
void dij(int s,int n){
	memset(dis+1,0x3f,sizeof(int)*n);
	dis[s]=0; Q.push(make_pair(0,s));
	while (Q.size()){
		auto now=Q.top(); Q.pop();
		int x=now.second;
		if (dis[x]!=now.first) continue;
		for (int i=head[x];~i;i=edge[i].next){
			if (dis[edge[i].to]>dis[x]+edge[i].len){
				dis[edge[i].to]=dis[x]+edge[i].len;
				Q.push(make_pair(dis[edge[i].to],edge[i].to));
			}
		}
	}
} 
inline int getid(int x,int y,int k){
	return n*n*k+n*(x-1)+y;
}
int mask[107][107];
int ax[4]={-1,1,0,0};
int ay[4]={0,0,-1,1};
int main() {
	int i,j,k,A,B,C;
	scanf("%d%d%d%d%d",&n,&k,&A,&B,&C);
	FOR(i,1,n) FOR(j,1,n) scanf("%d",&mask[i][j]);
	memset(head+1,0xff,((k+1)*n*n+1)*sizeof(int));
	int s=getid(1,1,k),t=(k+1)*n*n+1;
	int x,y,_x,_y;
	FOR(x,1,n) FOR(y,1,n) FOR(i,0,k){
		if (i!=k&&mask[x][y]) addedge(getid(x,y,i),getid(x,y,k),A);
		if (i!=k&&!mask[x][y]) addedge(getid(x,y,i),getid(x,y,k),A+C);
		if (i!=k&&mask[x][y]) continue;//must
		if (x==n&&y==n) addedge(getid(x,y,i),t,0);
		if (i==0) continue; int t;
		REP(t,4){
			_x=x+ax[t],_y=y+ay[t];
			if (1<=_x&&_x<=n&&1<=_y&&_y<=n){
				int val=(!(t&1))*B;
				addedge(getid(x,y,i),getid(_x,_y,i-1),val);
			}
		}
	} dij(s,n*n*(k+1)+1);
	printf("%d\n",dis[t]);
}
/*
*/
