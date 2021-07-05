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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL hash=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a,T b) {return a>0?a:-a;}


int n,m;
int i,j,k;
int v,u;
vector<int> edge[maxn];
int in[maxn],out[maxn],tot,p[maxn];
void dfs(int u,int from){
	int i,v;
	in[u]=++tot;
	p[tot]=u;
	REP(i,edge[u].size()){
		v=edge[u][i];
		if (v==from) continue;
		dfs(v,u);
	}
	out[u]=tot;
}
struct node{
	int l,r,k,id;
}Q[maxn];
int pos[maxn];
bool cmp(node a,node b){
	if (pos[a.l]==pos[b.l]) return a.r<b.r;
	return pos[a.l]<pos[b.l];
}
int num[maxn],now[maxn],ans[maxn];
int a[maxn];
inline void del(int x){
	now[num[a[p[x]]]]--;
	num[a[p[x]]]--;
}
inline void add(int x){
	num[a[p[x]]]++;
	now[num[a[p[x]]]]++;
}
int size;
int main(){
	scanf("%d%d",&n,&m);
	size=sqrt(n);
	FOR(i,1,n) scanf("%d",&a[i]);
	REP(i,n-1){
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	dfs(1,0);
//	FOR(i,1,n) printf("%d:%d %d\n",i,in[i],out[i]);
	FOR(i,1,n) pos[i]=i/size;
	FOR(i,1,m) scanf("%d%d",&v,&k),Q[i].l=in[v],Q[i].r=out[v],Q[i].k=k,Q[i].id=i;
	sort(Q+1,Q+m+1,cmp);
	int L=1,R=0;
	FOR(i,1,m){
		while (L<Q[i].l) {del(L);L++;}
		while (L>Q[i].l) {L--;add(L);}
		while (R<Q[i].r) {R++;add(R);}
		while (R>Q[i].r) {del(R);R--;}
		ans[Q[i].id]=now[Q[i].k];
	}
	FOR(i,1,m) printf("%d\n",ans[i]);
}
/*
       1
   2      5
  3 4   6 7 8  
*/
