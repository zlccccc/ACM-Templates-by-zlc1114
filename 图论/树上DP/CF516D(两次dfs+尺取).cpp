/*
题意:寻找联通的最大子树个数，使得到叶结点的距离差小于k 
*/ 
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

vector< pair<int,LL> > edge[maxn];
LL l1[maxn],l2[maxn],len[maxn];
int son[maxn],fa[maxn];
void dfs1(int u,int from){
	int v,w,i;
	REP(i,edge[u].size()){
		v=edge[u][i].first;
		if (v==from) continue;
		w=edge[u][i].second;
		dfs1(v,u);
		if (l1[u]<l1[v]+w) l2[u]=l1[u],l1[u]=l1[v]+w,son[u]=v;
		else if (l2[u]<l1[v]+w) l2[u]=l1[v]+w;
	}
}
void dfs2(int u,int from,LL d){//从叶子开始 
	int v,w,i;
	len[u]=max(d,l1[u]);
	REP(i,edge[u].size()){
		v=edge[u][i].first;
		if (v==from) continue;
		w=edge[u][i].second;
		if (son[u]==v) dfs2(v,u,max(d,l2[u])+w);
		else dfs2(v,u,max(d,l1[u])+w);
	}
}
int dfs3(int u,int from){
	int v,ret=0,i;
	fa[u]=from;
	REP(i,edge[u].size()){
		v=edge[u][i].first;
		if (v==from) continue;
		dfs3(v,u);
	}
}
int fat[maxn];
int getfather(int u){
	if (fat[u]==u) return u;
	return fat[u]=getfather(fat[u]);
}
int pos[maxn],num[maxn];
int cmp(int i,int j){return len[i]<len[j];}
int n,q;
int i,j,k;
int root;
int u,v,val,ans;
LL l,r;
int main()
{
	scanf("%d",&n);
	REP(i,n-1){
		scanf("%d%d%d",&u,&v,&val);
		edge[u].push_back(make_pair(v,val));
		edge[v].push_back(make_pair(u,val));
	}
	dfs1(1,0);
	dfs2(1,0,0);
//	FOR(i,1,n) printf("%d ",l1[i]); puts("");
//	FOR(i,1,n) printf("%d ",l2[i]); puts("");
//	FOR(i,1,n) printf("%d ",len[i]); puts("");
	root=1;
	FOR(i,1,n) if (len[i]<len[root]) root=i;
	dfs3(root,0);
//	FOR(i,1,n) printf("%d ",fa[i]); puts("");
	FOR(i,1,n) pos[i]=i;
	len[root]--;
	sort(pos+1,pos+n+1,cmp);
	len[root]++;
	scanf("%d",&q);
	while (q--){
		scanf("%I64d",&l);
		FOR(i,1,n) num[i]=0,fat[i]=i;
		ans=0;r=n;
		rFOR(i,1,n){
			k=pos[i];
			num[k]++;
			while (len[pos[r]]-len[k]>l){
				num[getfather(pos[r])]--;r--;
			}
			ans=max(ans,num[k]);
			fat[k]=fa[k];
			num[fa[k]]+=num[k];
		}
		printf("%d\n",ans);
	}
}
