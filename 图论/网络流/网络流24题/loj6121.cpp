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

struct node {
	int x,y,limit;
	node(int _x=0,int _y=0,int _limit=0):
		x(_x),y(_y),limit(_limit) {};
};
int w[17][17][17][17],v[17][17];
int dis[17][17][1<<10|7];
int ax[4]= {1,-1,0,0};
int ay[4]= {0,0,1,-1};
queue<node> Q;
int main() {
	int k;
	scanf("%d%d%*d",&n,&m);
	scanf("%d",&k);
	while (k--) {
		int x1,y1,x2,y2,q;
		scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&q);
		if (q){
			q--;
			w[x1][y1][x2][y2]|=1<<q;
			w[x2][y2][x1][y1]|=1<<q;
		}else{
			w[x1][y1][x2][y2]|=INF;
			w[x2][y2][x1][y1]|=INF;
		}
	} scanf("%d",&k);
	while (k--){
		int x,y,q;
		scanf("%d%d%d",&x,&y,&q); q--;
		v[x][y]|=1<<q;
	}
	memset(dis,0x3f,sizeof(dis));
	dis[1][1][0]=0; Q.push(node(1,1,0));
	int ans=INF;
	while (Q.size()) {
		auto now=Q.front(); Q.pop();
		int x=now.x,y=now.y,z=now.limit;
		REP(k,4) {
			int _x=x+ax[k],_y=y+ay[k],_z=z|v[_x][_y];
			if (1<=_x&&_x<=n&&1<=_y&&_y<=m&&
				(z&w[x][y][_x][_y])==w[x][y][_x][_y]) {
				if (dis[_x][_y][_z]==INF) {
					dis[_x][_y][_z]=dis[x][y][z]+1;
					if (_x==n&&_y==m) min_(ans,dis[_x][_y][_z]);
					Q.push(node(_x,_y,_z));
				}
			}
		}
	}if (ans!=INF) printf("%d\n",ans);
	else puts("-1");
}
/*
*/
