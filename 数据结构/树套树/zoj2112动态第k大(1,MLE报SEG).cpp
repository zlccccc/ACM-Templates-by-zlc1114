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
const LL maxn=70000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct node{
	int l,r,cnt;
	node(){l=r=cnt=0;}
}T[maxn*500];
int cnt;
int SIZE;
inline int lowbit(int x){
	return x&(-x);
}
int n;
void Update(int &x,int y,int l,int r,int pos,int val){
//	printf("U:%d %d  l,r=%d %d  pos=%d val=%d\n",x,y,l,r,pos,val);
	T[++cnt]=T[y];T[cnt].cnt+=val;x=cnt;
	if (l==r) return;
	int mid=(l+r)/2;
	if (mid>=pos) Update(T[x].l,T[y].l,l,mid,pos,val);
	else Update(T[x].r,T[y].r,mid+1,r,pos,val);
	T[x].cnt=T[T[x].l].cnt+T[T[x].r].cnt;
}
int root[maxn];
void update(int x,int pos,int val){
//	printf("update:%d %d  val=%d\n",x,pos,val);
	while (x<=SIZE){
//		printf("U:%d %d  val=%d\n",x,pos,val);
		Update(root[x],root[x],1,n,pos,val);
		x+=lowbit(x);
	}
}
int Query(int x,int l,int r,int L,int R){
//	printf("Q:%d %d-%d  %d->%d\n",x,l,r,L,R); 
	if (l<=L&&R<=r) return T[x].cnt;
	int mid=(L+R)/2;
	int ret=0;
	if (mid>=l) ret+=Query(T[x].l,l,r,L,mid);
	if (r>mid) ret+=Query(T[x].r,l,r,mid+1,R);
	return ret;
}
int query(int l,int r,int L,int R,int pos){
	if (l==r) return l;
	int x;
	int mid=(l+r)/2,nowcnt=0;
	for(x=l-1;x;x-=lowbit(x)) nowcnt-=Query(root[x],L,R,1,n);
//	printf("query:%d %d %d %d %d precnt=%d\n",l,r,L,R,pos,nowcnt);
	for(x=mid;x;x-=lowbit(x)) nowcnt+=Query(root[x],L,R,1,n);
//	printf("query:%d %d %d %d %d cnt=%d\n",l,r,L,R,pos,nowcnt);
	if (nowcnt>=pos) return query(l,mid,L,R,pos);
	else return query(mid+1,r,L,R,pos-nowcnt);
}
char K[maxn],Q[20];
int A[maxn][5];
int a[maxn];
int m;
vector<int> H;
inline int getid(int x){return lower_bound(H.begin(),H.end(),x)-H.begin()+1;}
void solve(){
	scanf("%d%d",&n,&m);
	int i;
	FOR(i,1,n) scanf("%d",&a[i]),H.push_back(a[i]);
	REP(i,m){
		scanf("%s",Q);
		K[i]=Q[0];
		if (K[i]=='Q') scanf("%d%d%d",&A[i][0],&A[i][1],&A[i][2]);
		if (K[i]=='C') scanf("%d%d",&A[i][0],&A[i][1]),H.push_back(A[i][1]);
	}
	sort(H.begin(),H.end());H.erase(unique(H.begin(),H.end()),H.end());
	SIZE=H.size();
	cnt=0;
	FOR(i,1,n) update(getid(a[i]),i,1);
	REP(i,m){
		if (K[i]=='Q') printf("%d\n",H[query(1,SIZE,A[i][0],A[i][1],A[i][2])-1]);//l,r,pos
		if (K[i]=='C'){
			update(getid(a[A[i][0]]),A[i][0],-1);
			a[A[i][0]]=A[i][1];
			update(getid(A[i][1]),A[i][0],1);
		}
	}
	FOR(i,1,SIZE) root[i]=0;
	FOR(i,1,cnt) T[i]=node();
	vector<int>().swap(H);
//	puts("OK3");
}
int main(){
	int T_T;
	scanf("%d",&T_T);
	while (T_T--) solve();
//	printf("%d",cnt);
}
/*
*/
