#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <utility>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define mp(A,B) make_pair(A,B)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL hash=1e9+7;
const LL maxn=5e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a,T b) {return a>0?a:-a;}

int tot;
inline int lowbit(int x){return x&-x;}
int c[maxn],a[maxn];
int getsum(int x){
	int ret=0;
	while (x){
		ret+=c[x];
		x-=lowbit(x);
	}
	return ret;
}
int query(int l,int r){
	return getsum(r)-getsum(l-1);
}
void add(int x,int d){
	while (x<=tot){
		c[x]+=d;
		x+=lowbit(x);
	}
}
void build(){
	int i;
	FOR(i,1,tot) c[i]=0;
	FOR(i,1,tot) add(i,a[i]);
}

int n,q,s,T;
int i,j,k;
int fa[maxn],son[maxn],sz[maxn],top[maxn],id[maxn],dep[maxn];
int b[maxn];
struct node{
	int to,next;
}edge[maxn<<1];
int head[maxn],len[maxn],U[maxn],V[maxn];
int cnt;
inline void addedge(int u,int v){
	edge[cnt].to=v;edge[cnt].next=head[u];head[u]=cnt++;
}
void dfs1(int u,int from,int depth){
	int v,i,mx=-1;
	son[u]=0;sz[u]=1;fa[u]=from;dep[u]=depth;
	for (i=head[u];i!=-1;i=edge[i].next){
		v=edge[i].to;
		if (v==from) continue;
		dfs1(v,u,depth+1);
		sz[u]+=sz[v];
		if (sz[v]>mx) mx=sz[v],son[u]=v;
	}
}
void dfs2(int u,int x){
	int v,i;
	top[u]=x;id[u]=++tot;
	if (son[u]) dfs2(son[u],x);
	for (i=head[u];i!=-1;i=edge[i].next){
		v=edge[i].to;
		if (v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
void change(int x,int val){
	add(id[x],val-a[id[x]]);
	a[id[x]]=val;
}
int Query(int x,int y){
	int ret=0;
	while (top[x]!=top[y]) {
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		ret+=query(id[top[x]],id[x]);
		x=fa[top[x]];
	}
	if (dep[x]>dep[y]) swap(x,y);
	if (son[x]) ret+=query(id[son[x]],id[y]);//这里top不能加 
	return ret;
}
int main(){
	while (~scanf("%d%d%d",&n,&q,&s)){
		FOR(i,1,n) head[i]=-1;cnt=0;
		FOR(i,1,n-1){
			scanf("%d%d%d",&V[i],&U[i],&len[i]);
			addedge(U[i],V[i]);
			addedge(V[i],U[i]);
		}
		tot=0; 
		dfs1(1,0,1);
		dfs2(1,1);
		FOR(i,1,n-1) if (dep[U[i]]>dep[V[i]]) swap(U[i],V[i]);
		FOR(i,1,n-1) a[id[V[i]]]=len[i];//V=son
		build();
		REP(i,q){
			int v,w,k;
			scanf("%d",&k);
			if (k==1){
				scanf("%d%d",&v,&w);
				change(V[v],w);
			}
			if (k==0){
				scanf("%d",&v);
				printf("%d\n",Query(s,v));
				s=v;
			}
		}
	}
}
/*
*/
