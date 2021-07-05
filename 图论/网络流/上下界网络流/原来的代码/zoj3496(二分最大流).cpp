#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

struct node{
	int to,cap,next;
}edge[maxn*3];
int head[507];
int tot;
int addedge(int from,int to,int cap){
	edge[tot].to=to;
	edge[tot].next=head[from];
	edge[tot].cap=cap;
	head[from]=tot++;
	edge[tot].to=from;
	edge[tot].next=head[to];
	edge[tot].cap=0;
	head[to]=tot++;
	return tot-1;
}
bool vis[507];
int d[507];
queue<int> Q;
bool bfs(int s,int t){
	memset(vis,0,sizeof(vis));
	while (Q.size()) Q.pop();
	d[s]=0;vis[s]=1;
	Q.push(s);
	int i;
	while (Q.size()){
		int x=Q.front();Q.pop();
		for (i=head[x];i!=-1;i=edge[i].next){
			if (!vis[edge[i].to]&&edge[i].cap){
				vis[edge[i].to]=1;
				d[edge[i].to]=d[x]+1;
				Q.push(edge[i].to);
			}
		}
	}
	return vis[t];
}
int cur[507];
int dfs(int x,int t,int flow){
	if (x==t||flow==0) return flow;
	int i,ret=0,f;
	for (i=cur[x];i!=-1;i=edge[i].next){
		if (d[x]+1==d[edge[i].to]&&(f=dfs(edge[i].to,t,min(flow,edge[i].cap)))>0){
			edge[i].cap-=f;
			edge[i^1].cap+=f;
			ret+=f;
			flow-=f;
			cur[x]=i;
			if (flow==0) break;
		}
	}
	return ret;
}
int in[507],out[507];
int add(int u,int v,int low,int high){
	int ret=addedge(u,v,high-low);
	out[u]+=low;in[v]+=low;
	return ret;
}
int u[maxn],v[maxn],len[maxn];
int E[maxn],ans[maxn];
int n,m,s,t,ss,tt,p;
int maxflow;
int getflow(int lower,int higher){//×î´óÁ÷ 
	tot=0;
	memset(head,0xff,sizeof(head));
	memset(in,0,sizeof(in));
	memset(out,0,sizeof(out));
	int i;
	REP(i,m){
		int low=lower,high=min(higher,len[i]);
		if (low>high) return -1;
		add(u[i],v[i],low,high);
	}
	add(t,s,0,INF);
	ss=n;tt=n+1;
	int sum=0,flow=0;
	REP(i,n){
		sum+=max(in[i]-out[i],0);
		if (in[i]>out[i]) addedge(ss,i,in[i]-out[i]);
		if (in[i]<out[i]) addedge(i,tt,out[i]-in[i]);
	}
	while (bfs(ss,tt)){
		int f;
		REP(i,n+2) cur[i]=head[i];
		while (f=dfs(ss,tt,INF)) flow+=f;
	}
	if (flow!=sum) return -1;
	flow=0;
	while (bfs(s,t)){
		int f;
		memcpy(cur,head,sizeof(head));
		while (f=dfs(s,t,INF)) flow+=f;
	}
	return flow;
}
int l,r,mid;
int solve(){
	scanf("%d%d%d%d%d",&n,&m,&s,&t,&p);
	if (m==0) return 0*puts("0 0");
	int i;
	REP(i,m) scanf("%d%d%d",&u[i],&v[i],&len[i]);
	maxflow=getflow(0,INF);
	if (maxflow==0) return 0*puts("0 0");
	l=-1;r=INF;
	while (l+1<r){
		mid=(l+r)/2;
		if (getflow(0,mid)!=maxflow) l=mid;
		else r=mid;
	}
	printf("%lld ",1ll*p*r);
	l=0;r=INF;
	while (l+1<r){
		mid=(l+r)/2;
		if (getflow(mid,INF)==maxflow) l=mid;
		else r=mid;
	}
	printf("%lld",1ll*p*l);
	puts("");
}
int main()
{
	int T;
	scanf("%d",&T);
	while (T--) solve();
}
/*
*/
