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


struct node{
	int left,right;
}tree[maxn*4];
int lmax[maxn*4],rmin[maxn*4],len[maxn*4];//free
int mark[maxn*4];
inline void change(int x){
	int &L=tree[x].left,&R=tree[x].right;
	if (mark[x]==1){
		lmax[x]=L-1; rmin[x]=R+1;
		len[x]=0;
	}else if (!mark[x]){
		lmax[x]=R; rmin[x]=L;
		len[x]=R-L+1;
	}else{
		len[x]=max(len[x<<1],len[x<<1|1]);
		len[x]=max(len[x],lmax[x<<1|1]-rmin[x<<1]+1);
//		printf("-=x %d, %d %d=-",x,lmax[x<<1|1],rmin[x<<1]);
		if (mark[x<<1|1]==0) rmin[x]=rmin[x<<1];
		else rmin[x]=rmin[x<<1|1];
		if (mark[x<<1]==0) lmax[x]=lmax[x<<1|1];
		else lmax[x]=lmax[x<<1];
		if (len[x]==0) mark[x]=1;
		if (len[x]==R-L+1) mark[x]=0;
	}
}
void pushdown(int x){
	if (mark[x]==1){
//	printf("-%d %d  %d-",tree[x].left,tree[x].right,mark[x]);
		mark[x<<1]=1;
		mark[x<<1|1]=1;
		change(x<<1);
		change(x<<1|1);
	}else if (mark[x]==0){
//	printf("-%d %d  %d-",tree[x].left,tree[x].right,mark[x]);
		mark[x<<1]=0;
		mark[x<<1|1]=0;
		change(x<<1);
		change(x<<1|1);
	}
}
void build(int x,int l,int r){
	tree[x].left=l;tree[x].right=r;
	change(x);
	if (l==r) return;
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
}
void add(int x,int l,int r){
	int L=tree[x].left,R=tree[x].right;
	if (l<=L&&R<=r){
		mark[x]=1;
		change(x);
		return;
	}
	pushdown(x);
	int mid=(L+R)/2;
	if (mid>=l) add(x<<1,l,r);
	if (r>mid) add(x<<1|1,l,r);
	mark[x]=-1;
	change(x);
}
void del(int x,int l,int r){
	int L=tree[x].left,R=tree[x].right;
	if (l<=L&&R<=r){
		mark[x]=0;
		change(x);
		return;
	}
	pushdown(x);
	int mid=(L+R)/2;
	if (mid>=l) del(x<<1,l,r);
	if (r>mid) del(x<<1|1,l,r);
	mark[x]=-1;
	change(x);
}
int n,m;
int i,j,k;
int v,l; 
int main()
{
	scanf("%d%d",&n,&m);
	build(1,1,n);
	REP(i,m){
		scanf("%d",&k);
		if (k==1){
			scanf("%d%d",&v,&l);
			add(1,v,v+l-1);
		}else if (k==2){
			scanf("%d%d",&v,&l);
			del(1,v,v+l-1);
		}else if (k==3){
			printf("%d\n",len[1]);
		}
		/*
		puts("");
		printf("left:  ");FOR(j,1,30) printf("%3d",tree[j].left);puts("");
		printf("right: ");FOR(j,1,30) printf("%3d",tree[j].right);puts("");
		printf("flag:  ");FOR(j,1,30) printf("%3d",mark[j]);puts("");
		printf("lmax:  ");FOR(j,1,30) printf("%3d",lmax[j]);puts("");
		printf("rmin:  ");FOR(j,1,30) printf("%3d",rmin[j]);puts("");
		printf("LEN->  ");FOR(j,1,30) printf("%3d",len[j]);puts("");
		puts("");
		*/
	}
}
/*
10 20
1 1 6
1 5 5
2 1 5
2 4 4
*/
