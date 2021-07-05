#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>
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
const LL maxn=1e6+7;
const double eps=0.00000001;
int gcd(int a,int b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M; return ret;}

//http://codeforces.com/contest/914/problem/E ,求回文子串贡献；
//在经典树分治后要加个简单DP，注意贡献！
vector<int> edge[maxn];
int root,minweight;
int size[maxn];
bool mark[maxn];
void dfs1(int x,int fa,int n) {
	int weight=0;
	size[x]=1;
	for (int v:edge[x]) {
		if (v==fa||mark[v]) continue;
		dfs1(v,x,n);
		size[x]+=size[v];
		weight=max(weight,size[v]);
	}
	weight=max(weight,n-size[x]);//max
	if (weight<minweight) root=x,minweight=weight;
} LL ans[maxn],f[maxn];
char s[maxn];
int MP[1<<20|7];
vector<int> have;
void dfsval(int x,int fa,int val,int k=0) {
	val^=1<<s[x];
	if (!k) {
		MP[val]++; f[x]=0;
		have.push_back(val);
	} else MP[val]+=k;
	for (int v:edge[x]) {
		if (v==fa||mark[v]) continue;
		dfsval(v,x,val,k);
	}
}
void dfs2(int x,int fa,int val) {
	val^=1<<s[x];
	for (int v:edge[x]) {
		if (v==fa||mark[v]) continue;
		dfs2(v,x,val);
		f[x]+=f[v];
	} f[x]+=MP[val]; int i;
	REP(i,20) f[x]+=MP[val^(1<<i)];
	ans[x]+=f[x];
}
void dfs3(int x) {
	int i;
	MP[1<<s[x]]++; have.push_back(1<<s[x]);
	mark[x]=1;
	for (int u:edge[x]) {
		if (mark[u]) continue;
		dfsval(u,0,1<<s[x]);
	}
	LL all=0;
	for (int v:edge[x]) {
		if (mark[v]) continue;
		dfsval(v,x,1<<s[x],-1);
		dfs2(v,0,0);
		dfsval(v,x,1<<s[x],1);
		all+=f[v];
	}
	all+=MP[0]; all++;
	REP(i,20) all+=MP[1<<i];
	ans[x]+=all/2;
	for (int v:have) MP[v]=0;
	have.clear();
	for (int u:edge[x]) {
		if (mark[u]) continue;
		minweight=size[u];
		dfs1(u,0,size[u]);
		dfs3(root);
	}
}
int n;
int main() {
	int i;
	scanf("%d",&n);
	FOR(i,1,n-1) {
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	} scanf("%s",s+1);
	FOR(i,1,n) s[i]-='a';
	minweight=n;
	dfs1(1,0,n);
	dfs3(root);
	FOR(i,1,n) printf("%I64d ",ans[i]);
}
/*
*/
