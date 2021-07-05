#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3f;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a) {return a>0?a:-a;}



int a[maxn];
struct node{
	int left,right;
	int m;
	LL sm;
}tree[maxn*4];
inline pushup(int x){
	tree[x].sm=tree[x<<1].sm+tree[x<<1|1].sm;
	tree[x].m=max(tree[x<<1].m,tree[x<<1|1].m);
}
void build(int x,int l,int r){
	tree[x].left=l;tree[x].right=r;
	if (l==r){
		tree[x].sm=tree[x].m=a[l];
	}else {
		int mid=(l+r)/2;
		build(x<<1,l,mid);
		build(x<<1|1,mid+1,r);
		pushup(x);
	}
}
void mod(int x,int l,int r,int mm){//±©Á¦ 
	if (tree[x].m<mm) return;
	int L=tree[x].left,R=tree[x].right;
	if (L==R){
		a[L]%=mm;
		tree[x].sm=tree[x].m=a[L];
//		printf("/%d/",l);
	}else{
		int mid=(L+R)/2;
		if (l<=mid) mod(x<<1,l,r,mm);
		if (mid<r) mod(x<<1|1,l,r,mm);
		pushup(x);
	}
}
LL query(int x,int l,int r){
	int L=tree[x].left,R=tree[x].right;
	if (l<=L&&R<=r){
		return tree[x].sm;
	}else{
		int mid=(L+R)/2;
		LL sum=0;
		if (l<=mid) sum+=query(x<<1,l,r);
		if (mid<r) sum+=query(x<<1|1,l,r);
		return sum;
	}
}
void change(int x,int pos,int nm){
	int l=tree[x].left,r=tree[x].right;
	if (l==r){
		a[l]=nm;
		tree[x].m=tree[x].sm=a[l];
	}else{
		int mid=(l+r)/2;
		if (pos<=mid) change(x<<1,pos,nm);
		else change(x<<1|1,pos,nm);
		pushup(x);
	}
}
int n,m;
int i,j,k;
int l,r;
int main()
{
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%d",&a[i]);
	build(1,1,n);
	REP(i,m){
		scanf("%d",&k);
		if (k==1){
			scanf("%d%d",&l,&r);
			printf("%I64d\n",query(1,l,r));
		}else if (k==2){
			scanf("%d%d%d",&l,&r,&j);
			mod(1,l,r,j);
		}else if (k==3){
			scanf("%d%d",&l,&j);
			change(1,l,j);
		}
//		FOR(j,1,n) printf("%d ",a[j]);
//		puts("");
	}
}
/*
*/
