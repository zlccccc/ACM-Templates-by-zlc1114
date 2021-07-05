#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

int a[maxn<<2];
vector<int> num[maxn<<2];
void build(int x,int l,int r){
	if (l==r){
		vector<int>().swap(num[x]);
		num[x].push_back(a[l]);
		return;
	}
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	num[x].resize(num[x<<1].size()+num[x<<1|1].size());
	merge(num[x<<1].begin(),num[x<<1].end(),num[x<<1|1].begin(),num[x<<1|1].end(),num[x].begin());
}
int query(int x,int l,int r,int L,int R,int H){
	if (l<=L&&R<=r) return upper_bound(num[x].begin(),num[x].end(),H)-num[x].begin();
	int mid=(L+R)/2;
	int ret=0;
	if (mid>=l) ret+=query(x<<1,l,r,L,mid,H);
	if (r>mid) ret+=query(x<<1|1,l,r,mid+1,R,H); 
	return ret;
}
int n,m,T,t;
int l,r,h;
int i;
int main(){
	scanf("%d",&T);
	FOR(t,1,T){
		scanf("%d%d",&n,&m);
		FOR(i,1,n) scanf("%d",&a[i]);
		build(1,1,n);
		printf("Case %d:\n",t);
		REP(i,m){
			scanf("%d%d%d",&l,&r,&h);
			printf("%d\n",query(1,l+1,r+1,1,n,h));
		}
	}
}
