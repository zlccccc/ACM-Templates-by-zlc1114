#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a*=a) ret=1ll*ret*a%M;return ret;}


#define x x_x
#define y y_y
#define hash ha_ah
struct node{
	int u,v;
	LL len;
}E[maxn],EE[maxn];
vector<pair<int,LL> > edge[maxn];
int father[maxn];
LL dis[maxn],ans[maxn],dep[maxn];
bool mark[maxn];
void dfs(int x,int fa,int l,int depth){
	mark[x]=1;
	dis[x]=l;
	dep[x]=depth;
	father[x]=fa;
	int i;
	REP(i,edge[x].size()){
		pair<int,LL> y=edge[x][i];
		if (!mark[y.first]) dfs(y.first,x,l+y.second,depth+1);
	}
}
//每条边->  dis[u]+dis[v]-dis[i]+w;
//实际上只需要往上爬就行了
void merge(int x,int y,LL l){
	int grand,i,j;
	i=x;j=y;
	while (i!=j){
		if (dep[i]<dep[j]){
			if (ans[j]==-1) ans[j]=dis[x]+dis[y]+l-dis[j];
			j=father[j];
		}
		else{
			if (ans[i]==-1) ans[i]=dis[x]+dis[y]+l-dis[i];
			i=father[i];
		}
	}
	grand=i;
	while (x!=y){
		if (dep[x]<dep[y]){
			i=y;
			y=father[y];
			father[i]=grand;
		}
		else{
			i=x;
			x=father[x];
			father[i]=grand;
		}
	}
}
bool cmp(node x,node y){
	return dis[x.u]+dis[x.v]+x.len<dis[y.u]+dis[y.v]+y.len;
}
int n,m;
int i,j,k;
int main(){
	while (~scanf("%d%d",&n,&m)){
		FOR(i,1,n) edge[i].clear();
		FOR(i,1,m){
			scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].len);
		}
		FOR(i,1,n-1){
			scanf("%d",&k);
			edge[E[k].u].push_back(make_pair(E[k].v,E[k].len));
			edge[E[k].v].push_back(make_pair(E[k].u,E[k].len));
			E[k].len=INF;
		}
		memset(dis,0,sizeof(dis));
		memset(mark,0,sizeof(mark));
		dfs(1,0,0,1);
		memset(mark,0,sizeof(mark));
		memset(ans,-1,sizeof(ans));
		sort(E+1,E+m+1,cmp);
//		FOR(i,1,m) printf("edge::::%d %d %d\n",E[i].u,E[i].v,E[i].len+dis[E[i].u]+dis[E[i].v]);
//		FOR(i,1,n) printf("%lld ",father[i]);puts("");
//		FOR(i,1,n) printf("%lld ",dep[i]);puts("");
//		FOR(i,1,n) printf("%lld ",dis[i]);puts("");
//		FOR(i,1,n) printf("%lld ",ans[i]);puts("");
		FOR(i,1,m) if (E[i].len!=INF) merge(E[i].u,E[i].v,E[i].len);
		FOR(i,2,n) printf("%lld ",ans[i]);
		puts("");
	}
}
