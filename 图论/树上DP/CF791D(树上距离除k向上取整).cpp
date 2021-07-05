#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <cmath>
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
const LL M=1e9+7;
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

LL count[maxn][6];
vector<int> edge[maxn];
LL num[maxn],cnt[maxn];//端点,满足条件的次数
int k;
LL ans;
void dfs(int u,int from) {
	int i,j,c1,c2;
	count[u][0]=1;
	cnt[u]=1;
	REP(i,edge[u].size()) {
		int v=edge[u][i];
		if (from==v) continue;
		dfs(v,u);
		REP(c1,k) REP(c2,k) {
			ans+=count[u][c1]*count[v][c2];
			if (c1+c2+1>k) ans+=count[u][c1]*count[v][c2];
		}
		ans+=cnt[u]*num[v]+num[u]*cnt[v];
		num[u]+=num[v]+count[v][k-1];
		cnt[u]+=cnt[v];
		REP(c1,k) count[u][c1]+=count[v][(c1-1+k)%k];
	}
}
int n,m;
int i,j;
int u,v;
int main() {
	scanf("%d%d",&n,&k);
	REP(i,n-1) {
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	dfs(1,0);
	printf("%I64d",ans);
}
