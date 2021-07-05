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
const LL maxn=200+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

struct node{
	int to,cap,next;
}edge[1007];
int tot;
int head[107];
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
bool vis[107];
int d[107];
queue<int> Q;
bool bfs(int s,int t){
	memset(vis,0,sizeof(vis));
	while (Q.size()) Q.pop();
	Q.push(s);
	d[s]=0;vis[s]=1;
	int i;
	while (Q.size()){
		int x=Q.front();Q.pop();
//							printf("bfs--%d---%d\n",x,t);
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
int cur[107];
int dfs(int x,int t,int flow){
//	printf("dfs-->%d %d %d\n",x,t,flow); 
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
int in[107],out[107];
int add(int u,int v,int low,int high){
	int ret=addedge(u,v,high-low);
	out[u]+=low;in[v]+=low;
	return ret;
}
int n,m;
int ss,tt,s,t;
int solve(){
	memset(head,0xff,sizeof(head));
	memset(in,0,sizeof(in));
	memset(out,0,sizeof(out));
	tot=0;
	ss=n+3;tt=n+4;
	s=n+1,t=n+2;
	int i;
	REP(i,m){
		int u,v,val;
		static char str[50];
		scanf("%s",str);
		if (str[0]=='+') u=s;
		else if (str[0]=='-') u=t;
		else sscanf(str,"%d",&u);
		scanf("%s",str);
		if (str[0]=='+') v=s;
		else if (str[0]=='-') v=t;
		else sscanf(str,"%d",&v);
		scanf("%d",&val);
		add(u,v,val,20000);
//		printf("-->%d %d %d %d\n",u,v,val,20000);
	}
	FOR(i,1,n+2){
		if (in[i]>out[i]) addedge(ss,i,in[i]-out[i]);
		if (in[i]<out[i]) addedge(i,tt,out[i]-in[i]);
	}
	while (bfs(ss,tt)){
		int f;
		memcpy(cur,head,sizeof(head));
		while (dfs(ss,tt,INF));
	}
//	puts("OK");
	int pos=addedge(t,s,INF);
	while (bfs(ss,tt)){
		int f;
		memcpy(cur,head,sizeof(head));
		while (f=dfs(ss,tt,INF));
	}
	for (i=head[ss];i!=-1;i=edge[i].next)
		if (edge[i].cap) return 0*puts("impossible");
	printf("%d\n",edge[pos].cap);
}
int main()
{
	int T;
	while (~scanf("%d%d",&n,&m)&&(m||n)) solve();
}
/*
*/
