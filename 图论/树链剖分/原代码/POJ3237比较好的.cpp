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
const LL maxn=1e4+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a,T b) {return a>0?a:-a;}

int a[maxn];
int lazy[maxn*4],mx[maxn*4],mn[maxn*4];
void change(int x){
	int tmp;
	tmp=mx[x];
	mx[x]=-mn[x];
	mn[x]=-tmp;
	lazy[x]^=1;
}
void pushup(int x){
	mx[x]=max(mx[x<<1],mx[x<<1|1]);
	mn[x]=min(mn[x<<1],mn[x<<1|1]);
}
void pushdown(int x){
	if (lazy[x]){
		change(x<<1);
		change(x<<1|1);
		lazy[x]=0;
	}
}
void build(int x,int l,int r){
	lazy[x]=mx[x]=mn[x]=0;
	if (l==r){
		mx[x]=mn[x]=a[l];
		return;
	}
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}
void update1(int x,int l,int r,int L,int R){//negative
	if (l<=L&&R<=r){
		change(x);
		return;
	}
	pushdown(x); 
	int mid=(L+R)/2;
	if (mid>=l) update1(x<<1,l,r,L,mid);
	if (r>mid) update1(x<<1|1,l,r,mid+1,R);
	pushup(x); 
}
void update2(int x,int pos,int val,int L,int R){//change
	if (L==R){
		mn[x]=mx[x]=val;
		return;
	}
	pushdown(x);
	int mid=(L+R)/2;
	if (mid>=pos) update2(x<<1,pos,val,L,mid);
	else update2(x<<1|1,pos,val,mid+1,R);
	pushup(x);
}
int query(int x,int l,int r,int L,int R){
	if (l<=L&&R<=r) return mx[x];
	pushdown(x);
	int mid=(L+R)/2,mx=-INF;
	if (mid>=l) mx=max(mx,query(x<<1,l,r,L,mid));
	if (r>mid) mx=max(mx,query(x<<1|1,l,r,mid+1,R));
	pushup(x);
	return mx;
}
int n,T,i;
int U[maxn],V[maxn],len[maxn];
vector<int> edge[maxn];
int fa[maxn],son[maxn],sz[maxn],top[maxn],id[maxn],dep[maxn];
int tot;
void dfs1(int u,int from,int depth){
	int v,i,mx=-1;
	sz[u]=1;fa[u]=from;dep[u]=depth;son[u]=0;
	REP(i,edge[u].size()){
		v=edge[u][i];
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
	REP(i,edge[u].size()){
		v=edge[u][i];
		if (v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
inline void Change(int i,int val){
	update2(1,id[V[i]],val,1,tot);
}
inline void Negative(int x,int y){
	while (top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		update1(1,id[top[x]],id[x],1,tot);
		x=fa[top[x]];
	}
	if (dep[x]>dep[y]) swap(x,y);
	if (son[x]) update1(1,id[son[x]],id[y],1,tot);
}
inline int Query(int x,int y){
	int mx=-INF;
	while (top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		mx=max(mx,query(1,id[top[x]],id[x],1,tot));
		x=fa[top[x]];
	}
	if (dep[x]>dep[y]) swap(x,y);
	if (son[x])	mx=max(mx,query(1,id[son[x]],id[y],1,tot));
	return mx; 
}
char s[50];
int main(){
	scanf("%d",&T);
	while (T--){
		scanf("%d",&n);
		FOR(i,1,n) edge[i].clear();
		FOR(i,1,n-1){
			scanf("%d%d%d",&U[i],&V[i],&len[i]);
			edge[U[i]].push_back(V[i]);
			edge[V[i]].push_back(U[i]);
		}
		tot=0;
		dfs1(1,0,1);
		dfs2(1,1);
		FOR(i,1,n-1) if (dep[U[i]]>dep[V[i]]) swap(U[i],V[i]);
		FOR(i,1,n-1) a[id[V[i]]]=len[i];
		build(1,1,tot);
		while (~scanf("%s",&s)&&s[0]!='D'){
			int u,v;
			if (s[0]=='C'){
				scanf("%d%d",&i,&v);
				Change(i,v);
			}
			if (s[0]=='N'){
				scanf("%d%d",&u,&v);
				Negative(u,v);
			}
			if (s[0]=='Q'){
				scanf("%d%d",&u,&v);
				printf("%d\n",Query(u,v));
			}
		}
	}
}
/*
*/
