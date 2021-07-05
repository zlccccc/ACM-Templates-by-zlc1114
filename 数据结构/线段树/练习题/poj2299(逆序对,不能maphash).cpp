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


struct node{
	int left,right;
}tree[maxn*4];
LL sum[maxn*4];
void build(int x,int l,int r){
	tree[x].left=l;tree[x].right=r;
	sum[x]=0;
	if (l==r) return;
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
}
void update(int x,int i){
	int L=tree[x].left,R=tree[x].right;
	if (L==R){
		sum[x]++;
		return;
	}
	int mid=(L+R)/2;
	if (mid>=i) update(x<<1,i);
	else update(x<<1|1,i);
	sum[x]=sum[x<<1]+sum[x<<1|1];
}
LL query(int x,int l,int r){
	int L=tree[x].left,R=tree[x].right;
	if (l<=L&&R<=r) return sum[x];
	int mid=(L+R)/2;
	LL sum=0;
	if (mid>=l) sum+=query(x<<1,l,r);
	if (r>mid) sum+=query(x<<1|1,l,r);
	return sum;
}
LL a[maxn];
int n,m;
int i,j,k;
vector<int> v;
int getid(int x){return lower_bound(v.begin(),v.end(),x)-v.begin()+1;}
LL ans;
int main()
{
	while (~scanf("%d",&n)&&n){
		ans=0;
		v.clear();
		REP(i,n) scanf("%d",&a[i]),v.push_back(a[i]);
		sort(v.begin(),v.end());v.erase(unique(v.begin(),v.end()),v.end());
		REP(i,n) a[i]=getid(a[i]);
		build(1,1,n);
		REP(i,n){
			ans+=query(1,a[i]+1,n);
			update(1,a[i]);
		}
		printf("%lld\n",ans);
	}
}
/*
*/
