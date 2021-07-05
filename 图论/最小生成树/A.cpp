#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
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
const LL maxn=1e4+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a*=a) ret=1ll*ret*a%M;return ret;}


#define x x_x
#define y y_y
#define hash ha_ah
struct node{
	int u,v;
	LL len;
}edge[maxn];
bool cmp(node x,node y){
	return x.len<y.len;
}
int fa[maxn],len[maxn];
int getfather(int x){
	if (fa[x]==x) return x;
	int t=getfather(fa[x]);
	return fa[x]=t;
}
int n,m,T;
int i,j,k;
int x,y;
int ans,mark1,mark2,ff;
int main(){
	scanf("%d",&T);
	while (T--){
		scanf("%d%d",&n,&m);
		REP(i,m) scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].len);
		sort(edge,edge+m,cmp);
		ans=mark1=mark2=0;
		FOR(i,1,n) fa[i]=i;
		memset(len,0,sizeof(len));
		REP(i,m){
			x=getfather(edge[i].u);
			y=getfather(edge[i].v);
			if (x==y){
				if (len[x]==edge[i].len||len[y]==edge[i].len) mark2=1;
			}
			else{
				fa[x]=y;
				len[y]=edge[i].len;
				ans+=len[y];
			}
		}
		ff=getfather(1);
		FOR(i,1,n) if (getfather(i)!=ff) mark1=1;
		if (mark1) puts("0");
		else if (mark2) puts("Not Unique!");
		else printf("%d\n",ans);
	}
}
