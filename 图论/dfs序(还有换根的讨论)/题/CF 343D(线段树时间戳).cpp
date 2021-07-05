#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
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
const LL hash=1e9+7;
const LL maxn=5e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a,T b) {return a>0?a:-a;}

struct Segtree{
	struct node{
		int left,right;
	}tree[maxn*4];
	int mx[maxn*4],lazy[maxn*4];
	void pushdown(int x){
		if (lazy[x]){
			mx[x<<1]=lazy[x<<1]=lazy[x];
			mx[x<<1|1]=lazy[x<<1|1]=lazy[x];
			lazy[x]=0;
		}
	}
	void pushup(int x){
		mx[x]=max(mx[x<<1],mx[x<<1|1]);
	}
	void build(int x,int l,int r){
		tree[x].left=l;tree[x].right=r;lazy[x]=0;
		if (l==r) return;
		int mid=(l+r)/2;
		build(x<<1,l,mid);
		build(x<<1|1,mid+1,r);
	}
	void update(int x,int l,int r,int val){
		int L=tree[x].left,R=tree[x].right;
		if (l<=L&&R<=r){
			lazy[x]=mx[x]=val;
			return;
		}
		pushdown(x);
		int mid=(L+R)/2;
		if (mid>=l) update(x<<1,l,r,val);
		if (r>mid) update(x<<1|1,l,r,val);
		pushup(x);
	}
	int query(int x,int l,int r){
		int L=tree[x].left,R=tree[x].right;
		if (l<=L&&R<=r) return mx[x];
		pushdown(x);
		int mid=(L+R)/2,t=0;
		if (mid>=l) t=max(t,query(x<<1,l,r));
		if (r>mid) t=max(t,query(x<<1|1,l,r));
//		pushup(x);
		return t;
	}
}T1,T2;

int n,q;
int i,j,k;
int u,v;
vector<int> edge[maxn];
int in[maxn],out[maxn];
int tot;
void dfs(int u,int from){
	int v,i;
	in[u]=++tot;
	REP(i,edge[u].size()){
		v=edge[u][i];
		if (v==from) continue;
		dfs(v,u);
	}
	out[u]=tot;
}
int main(){
	scanf("%d",&n);
	REP(i,n-1){
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	dfs(1,0);
	T1.build(1,1,tot);
	T2.build(1,1,tot);
//	FOR(i,1,n) printf("%d:/%d:%d/\n",i,in[i],out[i]);
	scanf("%d",&q);
	FOR(i,1,q){
		scanf("%d%d",&j,&k);
		if (j==1){
			T1.update(1,in[k],out[k],i);//Ê±¼ä´Á 
		}
		if (j==2){
			T2.update(1,in[k],in[k],i);
		}
		if (j==3){
			printf("%d\n",T1.query(1,in[k],in[k])>T2.query(1,in[k],out[k]));
		}
//		FOR(j,1,20) printf("%3d",tree[j].left);
//		puts("");
//		FOR(j,1,20) printf("%3d",tree[j].right);
//		puts("");
//		FOR(j,1,20) printf("%3d",lazy[j]);
//		puts("");
	}
}
/*
*/
