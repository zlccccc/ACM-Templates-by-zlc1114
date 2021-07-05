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
//不定根:新加一个节点，向所有点加一条INF的边，最后减一下即可 
//主要思路:缩点 
struct node{
	int u,v,val,id;//id->usedID
}edge[maxn];
int pre[maxn],len[maxn],vis[maxn],id[maxn];
struct used{
	int pre,id;//original
}U[maxn*20];//edges
int UID[maxn],used[maxn*20];
int OK[maxn];
int solve(int root,int n,int m){
	int ret=0,i,tot=m,em=m;
	REP(i,m) edge[i].id=U[i].id=i;
	while (1){
		FOR(i,1,n) len[i]=INF,vis[i]=0,id[i]=0;
		REP(i,m) if (edge[i].u!=edge[i].v&&edge[i].val<len[edge[i].v]){
			pre[edge[i].v]=edge[i].u;
			len[edge[i].v]=edge[i].val;
			UID[edge[i].v]=edge[i].id;
		}
		FOR(i,1,n) if (i!=root&&len[i]==INF) return -1;
		int cnt=0;len[root]=0;
		FOR(i,1,n){
			if (i!=root) used[UID[i]]++;
			ret+=len[i];int v;
			for(v=i;vis[v]!=i&&!id[v]&&v!=root;v=pre[v]) vis[v]=i;
			if (v!=root&&!id[v]){
				cnt++;id[v]=cnt;
				for (int u=pre[v];u!=v;u=pre[u]) id[u]=cnt;
			}
		}if (!cnt) break;
		FOR(i,1,n) if (!id[i]) id[i]=++cnt;
		REP(i,m){
			int v=edge[i].v; 
			edge[i].u=id[edge[i].u];edge[i].v=id[edge[i].v];
			if (edge[i].u==edge[i].v) edge[i--]=edge[--m];
			else {U[tot].id=edge[i].id;U[tot].pre=UID[v];edge[i].id=tot++;edge[i].val-=len[v];}
		}n=cnt;root=id[root];
	}
	rrep(i,em,tot) if (used[i]){
		used[U[i].id]++;
		used[U[i].pre]--;
	}
	return ret;
}
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int n,m,root;
	int i,j,k;
	scanf("%d%d",&n,&m);
	REP(i,m) scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].val);
	REP(i,m) OK[i]=edge[i].val;
	int ans=solve(1,n,m);
	printf("%d\n",ans);
	if (ans!=-1){
		REP(i,m) if (OK[i]&&used[i]) printf("%d ",i+1),ans--;
		if (ans) printf("\n%d\n",ans);
	}
}
/*
*/
