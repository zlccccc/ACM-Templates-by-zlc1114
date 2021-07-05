#pragma comment(linker,"/STACK:102400000,102400000") 
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=1e6+7;
const LL M=1e6+3;
const LL INF=0x3f3f3f3fll;

inline LL powMM(LL a,LL b){
	LL ret=1;
	while (b){
		if (b&1) ret=ret*a%M;
		a=a*a%M;
		b>>=1;
	}
	return ret;
}
int n;
LL K;
LL val[maxn];
pair<int,int> ans;
vector<int> edge[maxn];
int size[maxn];
bool mark[maxn];
int minweight,root;
void dfs1(int u,int fa,int n){//findroot
	int weight=0;
	size[u]=1;
	for (int v:edge[u]){
		if (v==fa||mark[v]) continue;
		dfs1(v,u,n);
		size[u]+=size[v];
		weight=max(weight,size[v]);
	}
	weight=max(weight,n-size[u]);
	if (weight<minweight) {root=u;minweight=weight;}
}
vector<pair<LL,int> > now;
map<LL,int> MP;
LL REV[maxn];
inline LL getVal(LL a){
	return K*REV[a]%M;
}
void dfs2(int u,int fa,LL num){
	now.push_back(make_pair(num*val[u]%M,u));
	for (int v:edge[u]){
		if (v==fa||mark[v]) continue;
		dfs2(v,u,num*val[u]%M);
	}
}
void calc(int x){//work
	MP.clear();
	MP[val[x]]=x;
	int i;
	for(int u:edge[x]) if (!mark[u]){
		vector<pair<LL,int> >().swap(now);
		dfs2(u,x,1);
		REP(i,now.size()) if (MP.count(getVal(now[i].first))){
			int U=now[i].second,V=MP[getVal(now[i].first)];
			if (U>V) swap(U,V);
			ans=min(ans,make_pair(U,V));
		}
		REP(i,now.size()){
			if (MP.count(now[i].first*val[x]%M))
				MP[now[i].first*val[x]%M]=min(MP[now[i].first*val[x]%M],now[i].second);
			else MP[now[i].first*val[x]%M]=now[i].second;
		}
	}
	MP.clear();
//	printf("x=%d\n",x);
//	for (pair<LL,int> P:MP[x]) printf("%d:%d\n",P.second,P.first);
}
void dfs3(int x){//find//log
	mark[x]=1;
	calc(x);
	for (int v:edge[x]) if (!mark[v]){
//		printf("u=%d ",v);
		minweight=size[v];
		dfs1(v,0,size[v]);
//		printf("len=%d root=%d,x=%d\n",minweight,root,x);
		dfs3(root);
	}
}
int main()
{
	int i;
	FOR(i,1,M-1) REV[i]=powMM(i,M-2)%M;
	while (~scanf("%d%d",&n,&K)){
		FOR(i,1,n) scanf("%lld",&val[i]);
		REP(i,n-1){
			int u,v;
			scanf("%d%d",&u,&v);
			edge[u].push_back(v);
			edge[v].push_back(u);
		}
		ans.first=ans.second=INF;
		minweight=n;
		dfs1(1,0,n);
//		printf("dfs from:%d %d\n",minweight,root);
		dfs3(root);
		if (ans.first==INF) puts("No solution");
		else printf("%d %d\n",ans.first,ans.second);
		FOR(i,1,n) mark[i]=0;
		FOR(i,1,n) vector<int>().swap(edge[i]);
	}
    return 0;
}
/*
*/
