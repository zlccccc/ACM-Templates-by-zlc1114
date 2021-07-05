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
const LL MOD=1e9+7;
const LL maxn=3e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a,T b) {return a>0?a:-a;}

struct Segtree{
	int val[maxn*4];
	struct node{
		int left,right;
	}tree[maxn*4];
	void pushdown(int x){
		if (val[x]){
			val[x<<1]=(val[x<<1]+val[x])%MOD;
			val[x<<1|1]=(val[x<<1|1]+val[x])%MOD;
			val[x]=0;
		}
	}
	void build(int x,int l,int r){
		tree[x].left=l;tree[x].right=r;
		val[x]=0;
		if (l==r) return;
		int mid=(l+r)/2;
		build(x<<1,l,mid);
		build(x<<1|1,mid+1,r);
	}
	void update(int x,int l,int r,int k){
		int L=tree[x].left,R=tree[x].right;
		if (l<=L&&R<=r){
			val[x]=(val[x]+k)%MOD;
			return;
		}
		int mid=(L+R)/2;
		if (mid>=l) update(x<<1,l,r,k);
		if (r>mid) update(x<<1|1,l,r,k);
	}
	int query(int x,int pos){
		int L=tree[x].left,R=tree[x].right;
		if (L==R) return val[x];
		pushdown(x);
		int mid=(L+R)/2;
		if (mid>=pos) return query(x<<1,pos);
		else return query(x<<1|1,pos);
	}
}T1,T2;
int n,m,q,type;
int i,j,k,f,v,x;
int in[maxn],out[maxn],tot,height[maxn];
vector<int> edge[maxn];
void dfs(int u,int k){
	int i,v;
	in[u]=++tot;
	height[u]=k;
	REP(i,edge[u].size()){
		v=edge[u][i];
		dfs(v,k+1);
	}
	out[u]=tot;
}
int main(){
	scanf("%d",&n);
	FOR(i,2,n) scanf("%d",&f),edge[f].push_back(i);
	dfs(1,0);
	scanf("%d",&q);
	T1.build(1,1,tot);
	T2.build(1,1,tot);
	while (q--){
		scanf("%d",&type);
		if (type==1){
			scanf("%d%d%d",&v,&x,&k);
			T1.update(1,in[v],out[v],(0ll+x+1ll*height[v]*k)%MOD);
			T2.update(1,in[v],out[v],k);
		}
		else {
			scanf("%d",&v);
			k=((0ll+T1.query(1,in[v])-1ll*T2.query(1,in[v])*height[v])%MOD+MOD)%MOD;
			printf("%d\n",k);
		}
	}
}
/*
*/
