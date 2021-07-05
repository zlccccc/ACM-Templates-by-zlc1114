#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
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
const LL maxn=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a*=a) ret=1ll*ret*a%M;return ret;}

struct node{
	int u,v,len,id;
	bool operator<(const node &A)const{
		if (len!=A.len) return len<A.len;
		if (u!=A.u) return u<A.u;
		return v<A.v;
	}
}Edge[maxn];
int fa[maxn],val[maxn],add[maxn],sz[maxn];
LL ans;
inline int Union(int u,int v,int len){
	int ret=0;
	while (u!=v&&(fa[u]!=u||fa[v]!=v)){
		if (fa[u]==u||fa[v]!=v&&sz[u]>sz[v]) {ret=max(ret,val[v]);v=fa[v];}
		else {ret=max(ret,val[u]);u=fa[u];}
	}
	if (u==v) return ret;
	if (sz[u]>sz[v]) swap(u,v);
	fa[u]=v;val[u]=len;
	sz[v]+=sz[u];ans=ans+len;
	return len;
}
int n,m;
int i;
int main()
{
	scanf("%d%d",&n,&m);
	REP(i,m) scanf("%d%d%d",&Edge[i].u,&Edge[i].v,&Edge[i].len),Edge[i].id=i;
	FOR(i,1,n) fa[i]=i,sz[i]=1;
	sort(Edge,Edge+m);
	REP(i,m) add[Edge[i].id]=Edge[i].len-Union(Edge[i].u,Edge[i].v,Edge[i].len);
	REP(i,m) printf("%I64d\n",ans+add[i]);
}
/*
*/
