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
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}


int cnt,root[maxn];
struct Tnode{
	int l,r,sum;
}T[maxn*40];
void update(int l,int r,int &x,int y,int pos){//主席树查找L~R数字个数 
	T[++cnt]=T[y];T[cnt].sum++;x=cnt;
	if (l==r) return;
	int mid=(l+r)/2;
	if (mid>=pos) update(l,mid,T[x].l,T[y].l,pos);
	else update(mid+1,r,T[x].r,T[y].r,pos);
}
int query(int l,int r,int x,int y,int L,int R){
	if (L<=l&&r<=R) return T[y].sum-T[x].sum;
	int mid=(l+r)/2;
	int sum=0;
	if (mid>=L) sum+=query(l,mid,T[x].l,T[y].l,L,R);
	if (R>mid) sum+=query(mid+1,r,T[x].r,T[y].r,L,R);
	return sum;
}
int n,m;
int i,j,k;
int l,r;
int main()
{
	scanf("%d",&n);
	FOR(i,1,n){
		scanf("%d",&j);
		update(1,n,root[i],root[i-1],j);
		printf("%d ",root[i]);
	}
	FOR(i,1,1000){
		scanf("%d%d%d%d",&j,&k,&l,&r);
		printf("%d\n",query(1,n,root[j-1],root[k],l,r));
	}
	return 0;
}
/*
*/
