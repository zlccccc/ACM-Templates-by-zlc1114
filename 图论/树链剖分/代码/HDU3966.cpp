//#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
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
const LL maxn=50007;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a,T b) {return a>0?a:-a;}

int lazy[maxn*4],a[maxn];//用lazy就好吧。。不会push下去 
void pushdown(int x){
	if (lazy[x]){
		lazy[x<<1]+=lazy[x];
		lazy[x<<1|1]+=lazy[x];
		lazy[x]=0;
	}
}
void build(int x,int l,int r){
	lazy[x]=0;
	if (l==r) {
		lazy[x]=a[l];
		return;
	}
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
}
void update(int x,int l,int r,int val,int L,int R){
	if (l<=L&&R<=r){
		lazy[x]+=val;
		return;
	}
	pushdown(x);
	int mid=(L+R)/2;
	if (mid>=l) update(x<<1,l,r,val,L,mid);
	if (r>mid) update(x<<1|1,l,r,val,mid+1,R);
}
int query(int x,int pos,int L,int R){
	if (L==R) return lazy[x];
	pushdown(x);
	int mid=(L+R)/2;
	if (mid>=pos) return query(x<<1,pos,L,mid);
	return query(x<<1|1,pos,mid+1,R);
}

int n,q,s,T;
int i,j,k;
int u,v,len;
vector<int> edge[maxn];
int fa[maxn],son[maxn],sz[maxn],top[maxn],id[maxn],dep[maxn];
int b[maxn];
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
void Change(int x,int y,int val){
	while (top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		update(1,id[top[x]],id[x],val,1,tot);
		x=fa[top[x]];
	}
	if (dep[x]>dep[y]) swap(x,y);
	update(1,id[x],id[y],val,1,tot);
}

int main(){
	while (~scanf("%d%d%d",&n,&i,&q)){
		FOR(i,1,n) scanf("%d",&b[i]);
		FOR(i,1,n) edge[i].clear();
		REP(i,n-1){
			scanf("%d%d",&u,&v);
			edge[u].push_back(v);
			edge[v].push_back(u);
		}
		tot=0;
		dfs1(1,0,1);
		dfs2(1,1);
		FOR(i,1,n) a[id[i]]=b[i];
		build(1,1,tot);
		REP(i,q){
			char c;
			int c1,c2,k;
			c=' ';
			while (c!='I'&&c!='D'&&c!='Q') c=getchar();
			if (c=='I'){
				scanf("%d%d%d",&c1,&c2,&k);
				Change(c1,c2,k);
			}
			if (c=='D'){
				scanf("%d%d%d",&c1,&c2,&k);
				Change(c1,c2,-k);
			}
			if (c=='Q'){
				scanf("%d",&c1);
				printf("%d\n",query(1,id[c1],1,tot));
			}
		}
	}
}
/*
*/
