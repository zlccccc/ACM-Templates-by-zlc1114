#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL hash=1e9+7;
const LL maxn=200;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}


struct Tsat{
	vector<int> edge[maxn*2];
	stack<int> S;
	int belong[maxn*2];
	int dfn[maxn*2],low[maxn*2];
	bool vis[maxn*2];
	int tot,cnt;
	bool mark;
	void init(int n){
		tot=cnt=0;
		int i;
		REP(i,n*2) edge[i].clear();
		REP(i,n*2) dfn[i]=0;
		REP(i,n*2) vis[i]=0;
	}
	void dfs(int u){
		int i;
		dfn[u]=low[u]=++tot;
		S.push(u);vis[u]=1;
		REP(i,edge[u].size()){
			int v=edge[u][i];
			if (!dfn[v]){
				dfs(v);
				low[u]=min(low[u],low[v]);
			}else if (vis[v]){
				low[u]=min(low[u],dfn[v]);
			}
		}
		if (dfn[u]==low[u]){
			cnt++;
			while (1){
				int now=S.top();S.pop();
				vis[now]=0;
				belong[now]=cnt;
				if (now==u) break;
			}
		}
	}
	void addedge(int u,int v){
		edge[u].push_back(v);
	}
	bool solve(int n){
		int i;
		REP(i,n*2) if (!dfn[i]) dfs(i);
		REP(i,n) if (belong[i]==belong[i+n]) return 0;
		return 1;
	}
}Tsat;
struct node{
	double x,y;
};
node A[maxn][2];
int n,m,t;
int i,j;
int tot;
double dist(node A,node B){
	return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}
bool solve(double x){
	Tsat.init(n);
	REP(i,n)
		rep(j,i+1,n){
//			printf("%.2lf->%.2lf,%.2lf,%.2lf,%.2lf\n",x,dist(A[i][0],A[j][0]),dist(A[i][0],A[j][1]),dist(A[i][1],A[j][0]),dist(A[i][1],A[j][1]));
			if (dist(A[i][0],A[j][0])<x*2) {Tsat.addedge(i,j+n);Tsat.addedge(j,i+n);}
			if (dist(A[i][0],A[j][1])<x*2) {Tsat.addedge(i,j);Tsat.addedge(j+n,i+n);}
			if (dist(A[i][1],A[j][0])<x*2) {Tsat.addedge(i+n,j+n);Tsat.addedge(j,i);}
			if (dist(A[i][1],A[j][1])<x*2) {Tsat.addedge(i+n,j);Tsat.addedge(j+n,i);}
		}
	return Tsat.solve(n);
}
double l,r,mid;
int main(){
	int t,m;
	while (~scanf("%d",&n)){
		REP(i,n) scanf("%lf%lf%lf%lf",&A[i][0].x,&A[i][0].y,&A[i][1].x,&A[i][1].y);
		l=0;r=20000;
		while (abs(r-l)>0.0001){
			mid=(r+l)/2;
			if (solve(mid)) l=mid;
			else r=mid;
//			printf("%lf %d\n",mid,solve(mid));
		}
		printf("%.2lf\n",l);
	}
}
/*
*/
