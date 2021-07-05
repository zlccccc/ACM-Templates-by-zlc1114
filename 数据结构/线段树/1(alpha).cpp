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


int n,m;
LL a[maxn];
int i,j,k,kk;
LL val;
char s;
int T;
struct node{
	int left,right;
	LL sum,lazy;
	LL max;
	void update(LL x){
		sum+=1ll*(right-left+1)*x;
		lazy+=x;
	}
}tree[maxn*4];
void push_up(int x){
	tree[x].sum=tree[x<<1].sum+tree[x<<1|1].sum;
	tree[x].max=max(tree[x<<1].max,tree[x<<1|1].max); 
}
void push_down(int x){
	LL lazyval=tree[x].lazy;
	if (lazyval){
		tree[x<<1].update(lazyval);
		tree[x<<1|1].update(lazyval);
		tree[x].lazy=0;
	}
}
void build(int x,int l,int r){
	tree[x].left=l;tree[x].right=r;
	tree[x].sum=tree[x].lazy=0;
	tree[x].max=0; 
	if (l==r){
		tree[x].sum=a[l];
		tree[x].max=a[l];
	}else{
		int mid=(l+r)/2;
		build(x<<1,l,mid);
		build(x<<1|1,mid+1,r);
		push_up(x);
	}
}
void update(int x,int l,int r,LL val){
	int L=tree[x].left,R=tree[x].right;
	if (l<=L&&R<=r){
		tree[x].update(val);
	}else{
		push_down(x);
		int mid=(L+R)/2;
		if (mid>=l) update(x<<1,l,r,val);
		if (r>mid) update(x<<1|1,l,r,val);
		push_up(x);
	}
}
LL query(int x,int l,int r){
	int L=tree[x].left,R=tree[x].right;
	if (l<=L&&R<=r){
		return tree[x].sum;
	}else{
		push_down(x);
		int mid=(L+R)/2;
		LL ans=0;
		if (mid>=l) ans+=query(x<<1,l,r);
		if (r>mid) ans+=query(x<<1|1,l,r);
		push_up(x);
		return ans;
	}
}
int main()
{
   	scanf("%d%d",&n,&m);
   	FOR(i,1,n) scanf("%lld",&a[i]);
	build(1,1,n);
   	REP(kk,m){
   		scanf("%c",&s);
		while (s!='Q'&&s!='C') scanf("%c",&s);
   		scanf("%d%d",&j,&k);
   		if (s=='Q') printf("%lld\n",query(1,j,k));
   		if (s=='C') {scanf("%lld",&val);update(1,j,k,val);}
	}
}
/*
*/
