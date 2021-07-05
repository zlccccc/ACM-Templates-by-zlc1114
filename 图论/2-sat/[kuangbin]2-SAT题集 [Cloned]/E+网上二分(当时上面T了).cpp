#include <cstdio>
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
const LL maxn=2007;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}


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
	REP(i,n*2) dfn[i]=vis[i]=low[i]=belong[i]=0;
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
inline void addedge(int u,int v){
	edge[u].push_back(v);
}
int n,m,t;
int numA,numB;
int A[maxn][2],B[maxn][2];
int i,j;
struct node{
	int x,y;
}S1,S2,a[maxn];
int S12;
inline int dist(node A,node B){
	return abs(A.x-B.x)+abs(A.y-B.y);
}
bool solve(int x){
	init(n);
	int i,j;
	int u,v;
	REP(i,numA){
		u=A[i][0];v=A[i][1];
		addedge(u,v+n);addedge(u+n,v);
		addedge(v,u+n);addedge(v+n,u);
	}
	REP(i,numB){
		u=B[i][0];v=B[i][1];
		addedge(u,v);addedge(u+n,v+n);
		addedge(v,u);addedge(v+n,u+n);
	}
	REP(i,n)
		rep(j,i+1,n){
		if (dist(a[i],S1)+dist(a[j],S1)>x) {addedge(i,j+n);addedge(j,i+n);}
		if (dist(a[i],S2)+dist(a[j],S2)>x) {addedge(i+n,j);addedge(j+n,i);}
		if (dist(a[i],S1)+dist(a[j],S2)+S12>x) {addedge(i,j);addedge(j+n,i+n);}
		if (dist(a[i],S2)+dist(a[j],S1)+S12>x) {addedge(i+n,j+n);addedge(j,i);}
	}
	REP(i,n*2) if (!dfn[i]) dfs(i);
	REP(i,n) if (belong[i]==belong[i+n]) return 0;
	return 1;
}
int main(){
	int t,m;
	while (~scanf("%d%d%d",&n,&numA,&numB)){
		scanf("%d%d%d%d",&S1.x,&S1.y,&S2.x,&S2.y);
		S12=dist(S1,S2);
//		printf("%d\n",dist(S1,S2));
		REP(i,n) scanf("%d%d",&a[i].x,&a[i].y);
		REP(i,numA) {scanf("%d%d",&A[i][0],&A[i][1]);A[i][0]--;A[i][1]--;}/*careful!!!*/
		REP(i,numB) {scanf("%d%d",&B[i][0],&B[i][1]);B[i][0]--;B[i][1]--;}/*careful!!!*/
	    int l = 0, r = 8000000, ans = 0x7fffffff;
	    while(l <= r)
	    {
	        int mid = (l + r) / 2;
	        if (solve(mid)) {r = mid - 1; if (mid < ans) ans = mid;}
	        else l = mid + 1;
	    }
	    if (ans == 0x7fffffff) printf("-1\n");
	    else printf("%d\n", ans);
	}
}
