#include <cstdio>
#include <iostream>
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
const LL maxn=3007;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a,T b) {return a>0?a:-a;}

int n,m,t;
int i,j;
int a1,a2,a3;
vector<int> edge[maxn*2];
stack<int> S;
int belong[maxn*2];
int dfn[maxn*2],low[maxn*2];
bool vis[maxn*2];
int tot,cnt;
bool mark;
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
bool solve(){
	int i;tot=0;cnt=0;
	REP(i,2*n) dfn[i]=0;
	REP(i,2*n) vis[i]=0;
	REP(i,2*n) if (!dfn[i]) dfs(i);
	REP(i,n) if (belong[i]==belong[i+n]) return 0;
	return 1;
}
int main(){
	int t,m;
	while (~scanf("%d%d",&t,&m)){
		n=t*3;
		REP(i,n*2) edge[i].clear();
		REP(i,t){
			scanf("%d%d%d",&a1,&a2,&a3);
			addedge(a1+n,a2);
			addedge(a1+n,a3);
			addedge(a2+n,a1);
			addedge(a3+n,a1);
		}
		REP(i,m){
			scanf("%d%d",&a1,&a2);
			addedge(a1,a2+n);
			addedge(a2,a1+n);
		}
		if (solve()) puts("yes");
		else puts("no");
	}
}
/*
*/
