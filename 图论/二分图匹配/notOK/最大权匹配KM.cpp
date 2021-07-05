#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <cstdlib>
#include <cstring>
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
const LL maxn=1e4+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

int n,m;
int i,j,k,t;
vector<pair<int,LL> >edge[N];
int used[N];
int matching[N];
int 
bool dfs(int u){
	int v,i;
	REP(i,edge[u].size()){
		v=edge[u][i].first;
		if (!used[v]&&lx[u]+ly[v]==edge[u][i].second){
			used[v]=1;
			if (matching[v]==-1||dfs(matching[v])){
				matching[v]=u;
				matching[u]=v;
				return 1;
			}
		}
	}
	return 0;
}
int KM(){
	int ans=0;
	memset(matching,-1,sizeof(matching));
	int u;
	return ans;
}
int main(){
	int T;
	scanf("%d",&T);
	while (T--){
		scanf("%d%d",&n,&m);
	}
}
/*
*/
