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


#define lson x<<1,L,mid
#define rson x<<1|1,mid+1,R
int n,m;
LL a[maxn];
LL lazy[maxn*4],sum[maxn*4]; 
int i,j,k,kk;
LL val;
char s;
int T;
inline void pushdown(int x,int L,int R){
	if (lazy[x]){
		int mid=(R+L)/2;
		lazy[x<<1]+=lazy[x];
		lazy[x<<1|1]+=lazy[x];
		sum[x<<1]+=lazy[x]*(mid-L+1);
		sum[x<<1|1]+=lazy[x]*(R-mid-1+1);
		lazy[x]=0;
	}
}
inline void pushup(int x){
	sum[x]=sum[x<<1]+sum[x<<1|1];
}
void build(int x,int L,int R){
	sum[x]=lazy[x]=0;
	if (L==R) {
		sum[x]=a[L];
		return;
	}
	int mid=(L+R)/2;
	build(lson);
	build(rson);
	pushup(x);
}
void update(int x,int L,int R,int l,int r,LL val){
	if (l<=L&&R<=r){
		sum[x]+=val*(R-L+1);
		lazy[x]+=val;
		return;
	}
	pushdown(x,L,R);
	int mid=(L+R)/2;
	if (l<=mid) update(lson,l,r,val);
	if (mid<r) update(rson,l,r,val);
	pushup(x);
}
LL query(int x,int L,int R,int l,int r){
	if (l<=L&&R<=r) return sum[x];
	LL ret=0;
	pushdown(x,L,R);
	int mid=(L+R)/2;
	if (l<=mid) ret+=query(lson,l,r);
	if (mid<r) ret+=query(rson,l,r);
	pushup(x);
	return ret;
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
   		if (s=='Q') printf("%lld\n",query(1,1,n,j,k));
   		if (s=='C') {scanf("%lld",&val);update(1,1,n,j,k,val);}
	}
}
/*
10 5
1 2 3 4 5 6 7 8 9 10
C 3 7 3
Q 2 4
Q 5 5
*/
