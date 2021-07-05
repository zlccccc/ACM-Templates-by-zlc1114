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
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=200007;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}

int cnt;
struct node{
	int l,r,sum;
}T[maxn*40];
void update(int l,int r,int &x,int y,int pos,int v){
	T[++cnt]=T[y],T[cnt].sum+=v,x=cnt;
	if (l==r) return;
	int mid=(l+r)/2;
	if (mid>=pos) update(l,mid,T[x].l,T[y].l,pos,v);
	else update(mid+1,r,T[x].r,T[y].r,pos,v);
}
int findsum(int l,int r,int x,int L,int R){//每个点记录的都是这个点往后的相同数(前面把后面短路了)
	if (L<=l&&r<=R) return T[x].sum;
	int mid=(l+r)/2;
	int sum=0;
	if (mid>=L) sum+=findsum(l,mid,T[x].l,L,R);
	if (R>mid) sum+=findsum(mid+1,r,T[x].r,L,R);
	return sum;
}
int query(int l,int r,int x,int k){
	if (l==r) return l;
	int mid=(l+r)/2;
	int sum=T[T[x].l].sum;
	if (sum>=k) return query(l,mid,T[x].l,k);
	else return query(mid+1,r,T[x].r,k-sum);
}
int n,m;
int i,j,k,pos;
int t,TT;
int ans[maxn],a[maxn];
int last[maxn],root[maxn];
int main()
{
	scanf("%d",&TT);
	FOR(t,1,TT){
		scanf("%d%d",&n,&m);
		FOR(i,1,n) scanf("%d",&a[i]);
		FOR(i,1,n) last[a[i]]=0,root[i]=0;
		cnt=0;
		rFOR(i,1,n){
			if (!last[a[i]]) update(1,n,root[i],root[i+1],i,1);
			else {
				update(1,n,root[i],root[i+1],last[a[i]],-1);
				update(1,n,root[i],root[i],i,1);
			}
			last[a[i]]=i;
		}
		FOR(i,1,m){
			scanf("%d%d",&j,&k);
			j=(j+ans[i-1])%n+1;
			k=(k+ans[i-1])%n+1;
			if (j>k) swap(j,k);
			pos=(findsum(1,n,root[j],j,k)+1)/2;
			ans[i]=query(1,n,root[j],pos);
		}
		printf("Case #%d:",t);
		FOR(i,1,m) printf(" %d",ans[i]);
		puts("");
	}
	return 0;
}
/*
*/
