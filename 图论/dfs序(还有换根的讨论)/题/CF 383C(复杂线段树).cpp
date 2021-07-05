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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a,T b) {return a>0?a:-a;}


struct node{
	int left,right;
}tree[maxn*4];
int a[maxn],lazy[maxn*4],mark[maxn];//lazy保存的是为1的pushdown
void pushdown(int x){
	if (lazy[x]){
		if (tree[x].left==tree[x].right){
			a[tree[x].left]+=mark[tree[x].left]*lazy[x];
			lazy[x]=0;
		}
		else { 
			lazy[x<<1]+=lazy[x];
			lazy[x<<1|1]+=lazy[x];
			lazy[x]=0;
		} 
	}
}
void build(int x,int l,int r){
	tree[x].left=l;tree[x].right=r;lazy[x]=0;
	if (l==r) return;
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
}
void update(int x,int l,int r,LL val){
	int L=tree[x].left,R=tree[x].right;
	if (l<=L&&R<=r) {
		lazy[x]+=val;
		return;
	}
	int mid=(L+R)/2;
	if (mid>=l) update(x<<1,l,r,val);
	if (r>mid) update(x<<1|1,l,r,val);
}
int query(int x,int pos){
	int L=tree[x].left,R=tree[x].right;
	pushdown(x);
	if (L==R) return a[L];
	int mid=(L+R)/2;
	if (mid>=pos) return query(x<<1,pos);
	else return query(x<<1|1,pos);
}
int n,m;
int i,j,k,val;
int u,v;
vector<int> edge[maxn];
int in[maxn],out[maxn],tot;
void dfs(int u,int from,int color){
	in[u]=++tot;
	if (color) mark[tot]=1;//这里已经映射 
	else mark[tot]=-1;
	int i,v;
	REP(i,edge[u].size()){
		v=edge[u][i];
		if (v==from) continue;
		dfs(v,u,color^1);
	}
	out[u]=tot;
}
int ori[maxn];
int main(){
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%d",&ori[i]);
	REP(i,n-1) {
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	dfs(1,0,1);
	FOR(i,1,n) a[in[i]]=ori[i];//映射 
	build(1,1,tot);
	REP(i,m){
		scanf("%d%d",&j,&k);
		if (j==1){
			scanf("%d",&val);
			update(1,in[k],out[k],val*mark[in[k]]);
		}
		else printf("%d\n",query(1,in[k]));
	}
}
/*
*/
