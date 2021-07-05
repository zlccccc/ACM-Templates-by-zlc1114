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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}
//将所有操作计算成为add和del,然后solve(l,r),再去除影响 
struct node{
	int pos,val,t,i;
	node(int _pos=0,int _val=0,int _t=0,int _i=0):pos(_pos),val(_val),t(_t),i(_i){};
}a[maxn*7],p[maxn*7];
int n,m;
LL sum[maxn];
inline int lowbit(int x){
	return x&-x;
}
void update(int x,int val){
//	printf("Update:%d %d\n",x,val);
	while (x<=n){
		sum[x]+=val;
		x+=lowbit(x);
	}
}
LL query(int x){
	LL ret=0;
	while (x){
		ret+=sum[x];
		x-=lowbit(x);
	}
	return ret;
}
LL ans[maxn];
void solve(int l,int r){
	if (l==r) return;
	int mid=(l+r)/2;
	solve(l,mid);
	solve(mid+1,r);
	int t1=l,t2=mid+1,t=l,i;
	while (t1<=mid||t2<=r){
//		printf("%d %d %d\n",t,t1,t2);
		if (t2>r||(t1<=mid&&a[t1].t<=a[t2].t)){
			node &now=p[t++]=a[t1++];
			if (now.i) continue;
			update(now.pos,now.val);//每一次修正一些 
		}else{
			node &now=p[t++]=a[t2++];
			if (!(now.i)) continue;
			ans[now.i]+=query(now.t)-query(now.pos-1);
		}
	}
	FOR(i,l,mid) if (a[i].t) update(a[i].pos,-a[i].val);
	FOR(i,l,r) a[i]=p[i];
}
int all;
set<int> S[maxn];
void ins(int pos,int val){
	S[val].insert(pos);
	set<int>::iterator it=S[val].find(pos),itt=it;itt++;
	int pre=0,suf=0;
	if (it!=S[val].begin()) it--,pre=*it;
	if (itt!=S[val].end()) suf=*itt;
	if (pre) a[++all]=node(pre,pos-pre,pos,0);
	if (suf) a[++all]=node(pos,suf-pos,suf,0);
	if (pre&&suf) a[++all]=node(pre,pre-suf,suf,0);
}
void del(int pos,int val){
	set<int>::iterator it=S[val].find(pos),itt=it;itt++;
	int pre=0,suf=0;
	if (it!=S[val].begin()) it--,pre=*it;
	if (itt!=S[val].end()) suf=*itt;
	if (pre) a[++all]=node(pre,-(pos-pre),pos,0);
	if (suf) a[++all]=node(pos,-(suf-pos),suf,0);
	if (pre&&suf) a[++all]=node(pre,-(pre-suf),suf,0);
	S[val].erase(pos);
}
int val[maxn];
int i;
int main(){
	scanf("%d%d",&n,&m);
	FOR(i,1,n){
		scanf("%d",&val[i]);
		ins(i,val[i]);
	}
	FOR(i,1,m){
		int k,l,r;
		scanf("%d%d%d",&k,&l,&r);
		if (k==1){
			del(l,val[l]);
			val[l]=r;
			ins(l,val[l]);
			ans[i]=-1;
		}else a[++all]=node(l,0,r,i);
	}
//	FOR(i,1,all) printf("time %d :%2d - %2d %d\n",a[i].t,a[i].pos,a[i].val,a[i].i);
	solve(1,all);
	FOR(i,1,m) if (~ans[i]) printf("%I64d\n",ans[i]);
}
/*
*/
