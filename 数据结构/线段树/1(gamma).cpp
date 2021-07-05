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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a) {return a>0?a:-a;}

int a[maxn];
struct node{
	int left,right;
}tree[maxn*4];
LL sum[maxn*4],lazy[maxn*4];
void change(int x,int i){
	sum[x]+=1ll*(tree[x].right-tree[x].left+1)*i;
	lazy[x]+=i;
}
void pushup(int x){
	sum[x]=sum[x<<1]+sum[x<<1|1];
}
void pushdown(int x){
	if (lazy[x]){
		change(x<<1,lazy[x]);
		change(x<<1|1,lazy[x]);
		lazy[x]=0;
	}
}
void build(int x,int l,int r){
	tree[x].left=l;tree[x].right=r;
	sum[x]=lazy[x]=0;
	if (l==r){
		sum[x]=a[l];
		return;
	}
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}
void update(int x,int l,int r,LL val){
	int L=tree[x].left,R=tree[x].right;
	if (l<=L&&R<=r){
		change(x,val);
		return;
	}
	pushdown(x);
	int mid=(L+R)/2;
	if (mid>=l) update(x<<1,l,r,val);
	if (r>mid) update(x<<1|1,l,r,val);
	pushup(x);
}
LL query(int x,int l,int r){
	int L=tree[x].left,R=tree[x].right;
	if (l<=L&&R<=r){
		return sum[x];
	}
	pushdown(x);
	int mid=(L+R)/2;
	LL sum=0;
	if (mid>=l) sum+=query(x<<1,l,r);
	if (r>mid) sum+=query(x<<1|1,l,r);
	pushup(x);
	return sum;
}
int n,m;
int i,j,k;
int v,l;
int T,t;
char s[10000];
int main()
{
	scanf("%d",&T);
	FOR(t,1,T){
		scanf("%d",&n);
		FOR(i,1,n) scanf("%d",&a[i]);
		build(1,1,n);
		printf("Case %d:\n",t);
		while (scanf("%s",&s)&&s[0]!='E'){
			scanf("%d%d",&j,&k);
			if (s[0]=='Q') printf("%d\n",query(1,j,k));
			if (s[0]=='A') update(1,j,j,k);
			if (s[0]=='S') update(1,j,j,-k);
		}
	}
}
/*
*/
