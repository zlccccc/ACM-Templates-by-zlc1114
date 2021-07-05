#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <cmath>
#include <utility>
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


int n,k;
vector<pair<int,int> > edge[maxn];
int size[maxn],root,minw;
bool mark[maxn];
void dfs1(int u,int from,int n){//root
	int i,v,weight=0;
	size[u]=1;
	REP(i,edge[u].size()){
		v=edge[u][i].first;
		if (v==from||mark[v]) continue;
		dfs1(v,u,n);
		size[u]+=size[v];
		weight=max(weight,size[v]);
	}
	weight=max(weight,n-size[u]);
	if (weight<minw) {root=u;minw=weight;}
}
vector<int> leng;
void dfs2(int u,int from,int depth){//len
	int i,v;
	size[u]=1;
	leng.push_back(depth);
	REP(i,edge[u].size()){
		v=edge[u][i].first;
		if (v==from||mark[v]) continue;
		dfs2(v,u,depth+edge[u][i].second);
		size[u]+=size[v];
	}
}
int calc(int root,int len){
	leng.clear();
	dfs2(root,0,len);
	sort(leng.begin(),leng.end());
	int l,r,ret=0;
	for (l=0,r=leng.size()-1;l<r;){
		if (leng[l]+leng[r]<=k) ret+=r-l,l++;
		else r--;
	}
	return ret;
}
int ans;
void dfs3(int u){
	int i,v,l,r;
	ans+=calc(u,0);
	mark[u]=1;
	REP(i,edge[u].size()){
		v=edge[u][i].first;
		if (mark[v]) continue;
		ans-=calc(v,edge[u][i].second);
		minw=size[v];//зЂвт 
		dfs1(v,0,size[v]);
		dfs3(root);
	}
}
int i,u,v,len;
int main(){
	while (~scanf("%d%d",&n,&k)&&(n||k)){
		FOR(i,1,n) edge[i].clear(),mark[i]=0;
		REP(i,n-1){
			scanf("%d%d%d",&u,&v,&len);
			edge[u].push_back(make_pair(v,len));
			edge[v].push_back(make_pair(u,len));
		}
		ans=0;
		minw=n;
		dfs1(1,0,n);
		size[root]=n;
		dfs3(root);
		printf("%d\n",ans);
	}
}
