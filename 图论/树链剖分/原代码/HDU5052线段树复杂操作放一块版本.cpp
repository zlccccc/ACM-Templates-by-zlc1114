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
int a[maxn];
int mxr[maxn<<2],mxl[maxn<<2],mx[maxn<<2],mn[maxn<<2],lazy[maxn<<2];//profit=mx-mn
void change(int x,int val){
	lazy[x]+=val;
	mx[x]+=val;
	mn[x]+=val;
}
void pushup(int x){
	mxr[x]=max(max(mxr[x<<1],mxr[x<<1|1]),mx[x<<1|1]-mn[x<<1]);//->
	mxl[x]=max(max(mxl[x<<1],mxl[x<<1|1]),mx[x<<1]-mn[x<<1|1]);//<-
	mx[x]=max(mx[x<<1],mx[x<<1|1]);
	mn[x]=min(mn[x<<1],mn[x<<1|1]);
}
void pushdown(int x){
	if (lazy[x]){
		change(x<<1,lazy[x]);
		change(x<<1|1,lazy[x]);
		lazy[x]=0;
	}
}
void build(int x,int l,int r){
	mxr[x]=mxl[x]=mx[x]=mn[x]=lazy[x]=0;
	if (l==r){
		mx[x]=mn[x]=a[l];
		return;
	}
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}
//void update(int x,int l,int r,int L,int R,int val){
//	if (l<=L&&R<=r){
//		change(x,val);
//		return;
//	}
//	pushdown(x);
//	int mid=(L+R)/2;
//	if (mid>=l) update(x<<1,l,r,L,mid,val);
//	if (r>mid) update(x<<1|1,l,r,mid+1,R,val);
//	pushup(x);
//}
int query(int x,int l,int r,bool flag,int &vmin,int &vmax,int L,int R,int val){//flag:-> (top->bottom yes)
//	printf("%d %d %d %d %d %d\n",x,l,r, L, R,flag);
	if (l<=L&&R<=r){
		change(x,val);//上面好像可去 
		vmin=mn[x];
		vmax=mx[x];
		return flag?mxr[x]:mxl[x];
	}
	pushdown(x);
	int mid=(L+R)/2,ret=0,mx1=-INF,mx2=-INF,mn1=INF,mn2=INF;
	if(mid>=l) ret=max(ret,query(x<<1,l,r,flag,mn1,mx1,L,mid,val));
	if(r>mid) ret=max(ret,query(x<<1|1,l,r,flag,mn2,mx2,mid+1,R,val));
	if (flag) ret=max(ret,mx2-mn1);
	else ret=max(ret,mx1-mn2);
	vmax=max(mx1,mx2);
	vmin=min(mn1,mn2);
	pushup(x);
	return ret;	
}
int n,q;
int i,j,k;
int u,v,val;
int b[maxn]; 
vector<int> edge[maxn];
int sz[maxn],fa[maxn],dep[maxn],son[maxn],top[maxn],id[maxn];
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
//void Change(int x,int y,int val){
//	while(top[x]!=top[y]){
//		if (dep[top[x]]<dep[top[y]]) swap(x,y);
//		update(1,id[top[x]],id[x],1,tot,val);
//		x=fa[top[x]];
//	}
//	if (dep[x]>dep[y]) swap(x,y);
//	update(1,id[x],id[y],1,tot,val);
//}
int Query(int x,int y,int val){
	int ret=0,mxx=-INF,mnx=INF,mxy=-INF,mny=INF,vmax,vmin;
	while(top[x]!=top[y]){
		if (dep[top[x]]>dep[top[y]]){
			ret=max(ret,query(1,id[top[x]],id[x],0,vmin,vmax,1,tot,val));
			ret=max(ret,vmax-mnx);
			mxx=max(mxx,vmax);
			mnx=min(mnx,vmin);
			x=fa[top[x]];
		}
		else{
			ret=max(ret,query(1,id[top[y]],id[y],1,vmin,vmax,1,tot,val));
			ret=max(ret,mxy-vmin);
			mxy=max(mxy,vmax);
			mny=min(mny,vmin);
			y=fa[top[y]];
		}
	}
	if (dep[x]>dep[y]){
		ret=max(ret,query(1,id[y],id[x],0,vmin,vmax,1,tot,val));
		ret=max(ret,vmax-mnx);
		mxx=max(mxx,vmax);
		mnx=min(mnx,vmin);
	}
	else{
		ret=max(ret,query(1,id[x],id[y],1,vmin,vmax,1,tot,val));
		ret=max(ret,mxy-vmin);
		mxy=max(mxy,vmax);
		mny=min(mny,vmin);
	}
	ret=max(ret,mxy-mnx);
	return ret;
}
int T;
int main(){
	scanf("%d",&T);
	while (T--){
		scanf("%d",&n);
		FOR(i,1,n) scanf("%d",&b[i]);
		FOR(i,1,n) edge[i].clear();
		FOR(i,1,n-1){
			scanf("%d%d",&u,&v);
			edge[u].push_back(v);
			edge[v].push_back(u);
		}
		tot=0;
		dfs1(1,0,1);
		dfs2(1,1);
		FOR(i,1,tot) a[id[i]]=b[i];
		build(1,1,tot);
//	printf("id  :");FOR(i,1,20) printf("%3d",id[i]);puts("");
//	printf("top :");FOR(i,1,20) printf("%3d",top[i]);puts("");
//	printf("i   :");FOR(i,1,20) printf("%3d",i);puts("");
//	printf("fa  :");FOR(i,1,20) printf("%3d",fa[i]);puts("");
//	printf("son :");FOR(i,1,20) printf("%3d",son[i]);puts("");
//	printf("dep :");FOR(i,1,20) printf("%3d",dep[i]);puts("");
//	printf("size:");FOR(i,1,20) printf("%3d",sz[i]);puts("");
//	printf("a   :");FOR(i,1,20) printf("%3d",a[i]);puts("");
		scanf("%d",&q);
		REP(i,q){
			scanf("%d%d%d",&u,&v,&val);
			printf("%d\n",Query(u,v,val));
//				puts("");
//				printf("l:   "); FOR(j,1,20) printf("%3d",tree[j].l);puts("");
//				printf("r:   "); FOR(j,1,20) printf("%3d",tree[j].r);puts("");
//				printf("mxr: "); FOR(j,1,20) printf("%3d",mxr[j]);puts("");
//				printf("mxl: "); FOR(j,1,20) printf("%3d",mxl[j]);puts("");
//				printf("mx:   "); FOR(j,1,20) printf("%3d",mx[j]);puts("");
//				printf("mn:   "); FOR(j,1,20) printf("%3d",mn[j]);puts("");
//				puts("");
//			Change(u,v,val);
		}
	}
}
/*
	  1
	3 2 4
   5
   
1
5
10 3 5 7 10 
2 1
3 1
4 1
5 3
5
4 5 8
5 5 9
1 2 5
5 4 10
2 5 2

*/
