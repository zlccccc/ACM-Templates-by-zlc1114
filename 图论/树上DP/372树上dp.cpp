#include <cstdio>
#include <vector>
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
const LL maxn=1007;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a*=a) ret=1ll*ret*a%M;return ret;}


vector<int> edge[maxn];
int A[maxn],B[maxn],num[maxn];
int dp[maxn][maxn];//point,num
int n,tot;
int i,j,k;
int u,v;
void dfs(int u,int fa){
	int i,j;
	num[u]=1;
	FOR(i,0,tot) dp[u][i]=0;
	dp[u][0]=B[u];dp[u][1]=A[u];
	for (int v:edge[u]){
		if (v==fa) continue;
		dfs(v,u);
		rFOR(i,0,num[u])
			rFOR(j,0,min(tot-i,num[v]))
				dp[u][i+j]=max(dp[u][i+j],dp[u][i]+dp[v][j]);
		num[u]+=num[v];
	}
	FOR(i,0,min(num[u],tot))
		dp[u][i]+=(tot-i)*(num[u]-i)+i*(n-num[u]-(tot-i));
}
int main(){
	while (~scanf("%d",&n)){
		FOR(i,1,n) edge[i].clear();
		REP(i,n-1){
			scanf("%d%d",&u,&v);
			edge[u].push_back(v);
			edge[v].push_back(u);
		}
		FOR(i,1,n) scanf("%d",&A[i]);
		FOR(i,1,n) scanf("%d",&B[i]);
		FOR(i,0,n){
			tot=i;
			dfs(1,0);
			printf("%d ",dp[1][i]);
		}
		puts("");
	}
}
