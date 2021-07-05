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
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a) {return a>0?a:-a;}

int size;
int cnt[maxn*4];
double len[maxn*2];
struct Seg{
	struct node{
		int left,right;
		double sum;
		int lazy;
		void update(LL x){
			lazy+=x;
		}
	}tree[maxn*4];
	void push_up(int x){
		if (tree[x].lazy) tree[x].sum=len[tree[x].right+1]-len[tree[x].left];
		else if (tree[x].right==tree[x].left) tree[x].sum=0;
		else tree[x].sum=tree[x<<1].sum+tree[x<<1|1].sum;
	}
	void build(int x,int l,int r){//void
		tree[x].left=l;tree[x].right=r;
		tree[x].sum=tree[x].lazy=0;
		if (l==r) return;
		else {
			int mid=(l+r)/2;
			build(x<<1,l,mid);
			build(x<<1|1,mid+1,r);
		}
	}//这里pushdown没用
	void update(int x,int l,int r,int val){
		int L=tree[x].left,R=tree[x].right;
		if (l<=L&&R<=r){
			tree[x].update(val);
			push_up(x);
		}else {
			int mid=(L+R)/2;
			if (mid>=l) update(x<<1,l,r,val);
			if (r>mid) update(x<<1|1,l,r,val);
			push_up(x);
		}
	}
}T;
int n,m;
int i,j,k;
struct point{
	double x1,x2,h;
	int n;
	bool operator <(const point&a)const{
		return h<a.h;
	}
}a[maxn];
map<double,int> hash;
double x1,x2,y1,y2;
double ans;
int main()
{
	int TT=0;
	while (~scanf("%d",&n)){
		if (n==0) break;
		FOR(i,1,n){
			scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
			len[i*2-1]=x1; len[i*2]=x2;
			a[i*2-1].x1=x1;a[i*2-1].x2=x2;
			a[i*2-1].n=1;  a[i*2-1].h=y1;
			a[i*2].x1=x1;a[i*2].x2=x2;
			a[i*2].n=-1; a[i*2].h=y2;
		}
		sort(a+1,a+n*2+1);
		sort(len+1,len+n*2+1);
		hash.clear();
		FOR(i,1,2*n) hash[len[i]]=i;
		T.build(1,1,n*2);
//		FOR(i,1,2*n) printf("%lf ",len[i]);
//		puts("");
//		FOR(i,1,2*n) printf("%d %d   %lf %d\n",hash[a[i].x1],hash[a[i].x2],a[i].h,a[i].n);
		ans=0;
		FOR(i,1,2*n){
//			printf("%lf\n",T.tree[1].sum);
			ans+=T.tree[1].sum*(a[i].h-a[i-1].h);
			T.update(1,hash[a[i].x1],hash[a[i].x2]-1,a[i].n);
		}
		printf("Test case #%d\n",++TT);
		printf("Total explored area: %.2lf\n",ans);
		puts(""); 
	}
}
/*
*/
