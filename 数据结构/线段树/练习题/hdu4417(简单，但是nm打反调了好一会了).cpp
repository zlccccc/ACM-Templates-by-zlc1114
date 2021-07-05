#include <cstdio>
#include <iostream>
#include <algorithm>
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
const LL maxn=100007;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a*=a) ret=1ll*ret*a%M;return ret;}

int sum[maxn*4];
void build(int x,int l,int r){
	sum[x]=0;
	if (l==r) return;
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
}
void update(int x,int pos,int L,int R){
	if (L==R) {sum[x]++; return;}
	int mid=(L+R)/2;
	if (pos<=mid) update(x<<1,pos,L,mid);
	else update(x<<1|1,pos,mid+1,R);
	sum[x]=sum[x<<1]+sum[x<<1|1];
}
int query(int x,int l,int r,int L,int R){
	if (l<=L&&R<=r) return sum[x];
	int ret=0,mid=(L+R)/2;
	if (l<=mid) ret+=query(x<<1,l,r,L,mid);
	if (mid<r) ret+=query(x<<1|1,l,r,mid+1,R);
	return ret;
}
struct node{
	int l,r,h,i;
}Q[maxn];
int pos[maxn],len[maxn],ans[maxn];
bool cmp(int l,int r){return len[l]<len[r];}
bool cmp2(node a,node b){return a.h<b.h;}
int n,m,T,t;
int i,j,k,tot;
int main(){
	scanf("%d",&T);
	FOR(t,1,T){
		scanf("%d%d",&n,&m);
		FOR(i,1,n)
			scanf("%d",&len[i]),pos[i]=i,len[i]++;
		sort(pos+1,pos+n+1,cmp);
		sort(len+1,len+n+1);
		REP(i,m){
			scanf("%d%d%d",&Q[i].l,&Q[i].r,&Q[i].h);
			Q[i].h++;Q[i].l++;Q[i].r++;
			Q[i].i=i;
		}
		sort(Q,Q+m,cmp2);
		tot=1;
		build(1,1,n);
//		FOR(i,1,n) printf("%d ",len[i]);puts("");
//		FOR(i,1,n) printf("%d ",pos[i]);puts("");
		REP(i,m){
			while (tot<=n&&len[tot]<=Q[i].h){
				update(1,pos[tot],1,n);
				tot++;
			}
			ans[Q[i].i]=query(1,Q[i].l,Q[i].r,1,n);
//			printf("%d %d %d    %d-%d\n",Q[i].l,Q[i].r,Q[i].h,ans[Q[i].i],len[tot]);
		}
		printf("Case %d:\n",t);
		REP(i,m) printf("%d\n",ans[i]);
	}
}
