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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a) {return a>0?a:-a;}

int n,m,q,l,r,i,j;
int a[11][maxn];
struct node{
	int lnum[11],rnum[11],ans,l,r;
}tree[maxn*4];
int fa[44],to[44];
int getfather(int x){
	if (fa[x]==x) return x;
	return fa[x]=getfather(fa[x]);
}
node merge(node x,node y){
	node z;
	int i,num,cnt;
	REP(i,n*4) fa[i]=i,to[i]=-1;
	num=x.ans+y.ans;
	cnt=0;
	REP(i,n) if (a[i][x.r]==a[i][y.l]){
		int fx=getfather(x.rnum[i]),fy=getfather(y.lnum[i]+n*2);
//		printf("l=%d r=%d  color:%d %d  %d %d %d\n",x.l,y.r,x.rnum[i],y.lnum[i],fx,fy,i);
		if (fx!=fy){
			fa[fx]=fy;
			num--;
		}
	}
	cnt=0;
	REP(i,n){
		int f;
		f=getfather(x.lnum[i]);
		if (to[f]==-1) to[f]=cnt++;
		z.lnum[i]=to[f];
		f=getfather(y.rnum[i]+n*2);
		if (to[f]==-1) to[f]=cnt++;
		z.rnum[i]=to[f];
	}
	z.ans=num;z.l=x.l;z.r=y.r;
	return z;
}
void build(int x,int l,int r){
	tree[x].l=l;tree[x].r=r;
	if (l==r){
		int i,t=0;
		REP(i,n){
			tree[x].lnum[i]=tree[x].rnum[i]=t;
			if(a[i][l]!=a[i+1][l]) t++;
		}
		tree[x].ans=t;
		return;
	}
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	tree[x]=merge(tree[x<<1],tree[x<<1|1]);
}
node query(int x,int l,int r,int L,int R){
	if (l<=L&&R<=r) return tree[x];
	int mid=(L+R)/2;
	if (mid>=r) return query(x<<1,l,r,L,mid);
	if (l>mid) return query(x<<1|1,l,r,mid+1,R);
	return merge(query(x<<1,l,r,L,mid),query(x<<1|1,l,r,mid+1,R));
}
int main()
{
	scanf("%d%d%d",&n,&m,&q);
	REP(i,n)
		FOR(j,1,m) scanf("%d",&a[i][j]);
	build(1,1,m);
	while (q--){
		scanf("%d%d",&l,&r);
		printf("%d\n",query(1,l,r,1,m).ans);
	}
}
/*
*/
