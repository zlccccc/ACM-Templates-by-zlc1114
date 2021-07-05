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
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=100007;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a) {return a>0?a:-a;}


struct Tnode{
	int left,right;
}tree[maxn*4];
LL color[maxn*4],sum[maxn*4],lazy[maxn*4];//lazy和color是分开计算的 
inline void pushup(int x){
	sum[x]=sum[x<<1]+sum[x<<1|1];
	if (color[x<<1]!=0&&(color[x<<1]==color[x<<1|1])) color[x]=color[x<<1];
	else color[x]=0;
}
inline void change(int x,LL val){
	int L=tree[x].left,R=tree[x].right;
	sum[x]+=abs(val-color[x])*(R-L+1);
	lazy[x]+=abs(val-color[x]);
	color[x]=val;
}
inline void pushdown(int x){//如果错了pushup修正 
	if (lazy[x]){
		sum[x<<1]+=lazy[x]*(tree[x<<1].right-tree[x<<1].left+1);
		lazy[x<<1]+=lazy[x];
		sum[x<<1|1]+=lazy[x]*(tree[x<<1|1].right-tree[x<<1|1].left+1);
		lazy[x<<1|1]+=lazy[x];
		lazy[x]=0;
	}
	if (color[x]) color[x<<1]=color[x<<1|1]=color[x];
}
void build(int x,int l,int r){
	tree[x].left=l;tree[x].right=r;
	sum[x]=color[x]=lazy[x]=0;
	if (l==r){
		color[x]=l;
		return;
	}
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
}
void update(int x,int l,int r,LL val){
	int L=tree[x].left,R=tree[x].right;
	if (l<=L&&R<=r&&color[x]){
		change(x,val);
		return;
	}
	int mid=(L+R)/2;
	pushdown(x);
	if (mid>=l) update(x<<1,l,r,val);
	if (r>mid) update(x<<1|1,l,r,val);
	pushup(x);
}
LL query(int x,int l,int r){
	int L=tree[x].left,R=tree[x].right;
	if (l<=L&&R<=r) return sum[x];
	int mid=(L+R)/2;
	LL ret=0;
	pushdown(x);
	if (mid>=l) ret+=query(x<<1,l,r);
	if (r>mid) ret+=query(x<<1|1,l,r);
	return ret;
}
int n,m,s;
int i,j,k;
int l,r,u,v;
LL val;
int main()
{
	scanf("%d%d",&n,&m);
	build(1,1,n);
	REP(i,m){
		scanf("%d",&k);
		if (k==1){
			scanf("%d%d%d",&l,&r,&val);
			update(1,l,r,val);
		}
		if (k==2){
			scanf("%d%d",&l,&r);
			printf("%I64d\n",query(1,l,r));
		}
	}
}
/*
*/
