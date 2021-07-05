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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a,T b) {return a>0?a:-a;}

int tot;
struct node{
	int lval,rval,ldown,lup,rdown,rup,upmx,downmx,len;
	int left,right;
	node():upmx(0),downmx(0){};
}tree[maxn<<2];
int a[maxn];
node merge(node L,node R){
	if (L.upmx==0) return R;
	if (R.upmx==0) return L;
	node ret;
	ret.len=L.len+R.len;
	ret.upmx=max(L.upmx,R.upmx);
	ret.downmx=max(L.downmx,R.downmx);
	ret.lval=L.lval;
	ret.lup=L.lup;
	ret.ldown=L.ldown;
	ret.rval=R.rval;
	ret.rup=R.rup;
	ret.rdown=R.rdown;
	if (L.rval<R.lval){
		ret.upmx=max(ret.upmx,L.rup+R.lup);
		if (L.upmx==L.len) ret.lup=L.lup+R.lup;
		if (R.upmx==R.len) ret.rup=L.rup+R.rup;
	}
	if (L.rval>R.lval){
		ret.downmx=max(ret.downmx,L.rdown+R.ldown);
		if (L.downmx==L.len) ret.ldown=L.ldown+R.ldown;
		if (R.downmx==R.len) ret.rdown=L.rdown+R.rdown;
	}
	return ret;
}
void build(int x,int l,int r){
	if (l==r){
		tree[x].lval=tree[x].rval=a[l];
		tree[x].lup=tree[x].ldown=tree[x].rup=tree[x].rdown=tree[x].upmx=tree[x].downmx=1;
		tree[x].len=1;
		return;
	}
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	tree[x]=merge(tree[x<<1],tree[x<<1|1]);
	tree[x].left=l;tree[x].right=r;
}
node query(int x,int l,int r,int L,int R){
	node ret;
	if (l<=L&&R<=r){
		return tree[x];
	}
	int mid=(L+R)/2;
	if (mid>=l&&r>mid) return merge(query(x<<1,l,r,L,mid),query(x<<1|1,l,r,mid+1,R));
	if (mid>=l) return query(x<<1,l,r,L,mid);
	return query(x<<1|1,l,r,mid+1,R);
}
int n,i,j,q;
int u,v;
vector<int> edge[maxn];
int fa[maxn],son[maxn],top[maxn],dep[maxn],id[maxn],sz[maxn];
int b[maxn];
void dfs1(int u,int depth){
	int v,i,mx=-1;
	son[u]=0;sz[u]=1;dep[u]=depth;
	REP(i,edge[u].size()){
		v=edge[u][i];
		dfs1(v,depth+1);
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
int Query(int x,int y){
	node up,down;
	int ret,mark1=0,mark2=0;
	while (top[x]!=top[y]){
		if (dep[top[x]]>dep[top[y]]){
			up=merge(query(1,id[top[x]],id[x],1,tot),up); 
			x=fa[top[x]];
			mark1=1;
		}else {
			down=merge(query(1,id[top[y]],id[y],1,tot),down);
			y=fa[top[y]];
			mark2=1;
		}
	}
	if (dep[x]>dep[y]) up=merge(query(1,id[y],id[x],1,tot),up),mark1=1;
	else down=merge(query(1,id[x],id[y],1,tot),down),mark2=1;
	ret=max(up.downmx,down.upmx);
	if (mark1&&mark2&&up.lval<down.lval) ret=max(ret,up.ldown+down.lup);
	return ret;
}
int T,t;
int main(){
	scanf("%d",&T);
	FOR (t,1,T){
		scanf("%d",&n);
		FOR(i,1,n) edge[i].clear();tot=0;
		FOR(i,1,n) scanf("%d",&b[i]);
		FOR(i,2,n){scanf("%d",&fa[i]); edge[fa[i]].push_back(i);}
		dfs1(1,1);
		dfs2(1,1);
		FOR(i,1,n) a[id[i]]=b[i];
		build(1,1,tot);
//	printf("id  :");FOR(i,1,20) printf("%3d",id[i]);puts("");
//	printf("top :");FOR(i,1,20) printf("%3d",top[i]);puts("");
//	printf("i   :");FOR(i,1,20) printf("%3d",i);puts("");
//	printf("fa  :");FOR(i,1,20) printf("%3d",fa[i]);puts("");
//	printf("son :");FOR(i,1,20) printf("%3d",son[i]);puts("");
//	printf("dep :");FOR(i,1,20) printf("%3d",dep[i]);puts("");
//	printf("size:");FOR(i,1,20) printf("%3d",sz[i]);puts("");

//	int lval,rval,ldown,lup,rdown,rup,upmx,downmx,len;
//	printf("a   :");FOR(i,1,20) printf("%3d",a[i]);puts("");
//		printf("LEFT:  ");FOR(j,1,20) printf("%3d",tree[j].left);puts("");
//		printf("RIGHT: ");FOR(j,1,20) printf("%3d",tree[j].right);puts("");
//		printf("len:   ");FOR(j,1,20) printf("%3d",tree[j].len);puts("");
//		printf("Lval:  ");FOR(j,1,20) printf("%3d",tree[j].lval);puts("");
//		printf("Rval:  ");FOR(j,1,20) printf("%3d",tree[j].rval);puts("");
//		printf("upmx:  ");FOR(j,1,20) printf("%3d",tree[j].upmx);puts("");
//		printf("downmx:");FOR(j,1,20) printf("%3d",tree[j].downmx);puts("");
//		printf("ldown: ");FOR(j,1,20) printf("%3d",tree[j].ldown);puts("");
//		printf("lup:   ");FOR(j,1,20) printf("%3d",tree[j].lup);puts("");
//		printf("rdown: ");FOR(j,1,20) printf("%3d",tree[j].rdown);puts("");
//		printf("rup  : ");FOR(j,1,20) printf("%3d",tree[j].rup);puts("");
		scanf("%d",&q);
		printf("Case #%d:\n",t);
		while (q--){
			scanf("%d%d",&u,&v);
			printf("%d\n",Query(u,v));
		}
		if (t!=T) puts("");
	}
}
/*
         1
         2
       3   5
     4  6   8
   7

1
8
8 7 6 5 4 3 2 1
1 2 3 2 3 4 5 
1
7 5
*/
