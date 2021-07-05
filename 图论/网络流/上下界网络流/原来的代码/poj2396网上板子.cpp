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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
//先写那个简单的吧。。 
int n,m,q;
int i,j,k;
int mn[207][27];
int mx[207][27];
int row[207],col[207];
int pos[207][27];
int s,t,ss,tt;
struct node{
	int to,cap,next;
}edge[maxn*5];
int tot;
int head[maxn];
inline int addedge(int from,int to,int cap){
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
bool vis[maxn];
int d[maxn];
queue<int> Q;
bool bfs(int s,int t){
	memset(vis,0,sizeof(vis));
	while (Q.size()) Q.pop();
	Q.push(s);
	d[s]=0;vis[s]=1;
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
int dfs(int x,int t,int flow){
	if (x==t||flow==0) return flow;
	int i,ret=0,f;
	for (i=head[x];i!=-1;i=edge[i].next){
		if (d[x]+1==d[edge[i].to]&&(f=dfs(edge[i].to,t,min(flow,edge[i].cap)))>0){
			edge[i].cap-=f;
			edge[i^1].cap+=f;
			ret+=f;
			flow-=f;
			if (flow==0) break;
		}
	}
	return ret;
}
int in[maxn],out[maxn],E[maxn];//边的流量 
inline int add(int u,int v,int low,int high){
	int ret=addedge(u,v,high-low);
	in[v]+=low;
	out[u]+=low;
	return ret;
}
int cnt;
int solve(){
	scanf("%d%d",&n,&m);
	memset(head,0xff,sizeof(head));
	memset(in,0,sizeof(in));
	memset(out,0,sizeof(out));
	cnt=0;tot=0;
	ss=cnt++;tt=cnt++;
	s=cnt++;t=cnt++;
	FOR(i,1,n) row[i]=cnt++;
	FOR(i,1,m) col[i]=cnt++;
	FOR(i,1,n){
		FOR(j,1,m){
			pos[i][j]=cnt++;
			mn[i][j]=0;
			mx[i][j]=2000;
		}
	}
	add(t,s,0,4e6);
	FOR(i,1,n){
		scanf("%d",&k);
		add(s,row[i],k,k);
	}
	FOR(i,1,m){
		scanf("%d",&k);
		add(col[i],t,k,k);
	}
	scanf("%d",&q);
	while(q--){
		int x,y,val;
		char a[3];
		scanf("%d%d%s%d",&x,&y,a,&val);
		int xl=x,xr=x,yl=y,yr=y;
		if (x==0) xl=1,xr=n;
		if (y==0) yl=1,yr=m;
		FOR(x,xl,xr){
			FOR(y,yl,yr){
				if (a[0]=='<') mx[x][y]=min(mx[x][y],val-1);
				if (a[0]=='>') mn[x][y]=max(mn[x][y],val+1);
				if (a[0]=='=') {
					mn[x][y]=max(mn[x][y],val);
					mx[x][y]=min(mx[x][y],val);
				}
			}	
		}
	}
	FOR(i,1,n){
		FOR(j,1,m){
			if (mx[i][j]<mn[i][j]) return 0*puts("IMPOSSIBLE");
			E[pos[i][j]]=add(row[i],pos[i][j],mn[i][j],mx[i][j]);
			add(pos[i][j],col[j],mn[i][j],mx[i][j]);
		}
	}
	int flow=0,sum=0;
	REP(i,cnt) if (i!=ss&&i!=tt){
		sum+=max(in[i]-out[i],0);
		if (in[i]>out[i]) addedge(ss,i,in[i]-out[i]);
		if (in[i]<out[i]) addedge(i,tt,out[i]-in[i]);
	}
	while (bfs(ss,tt)){
		int f;
		while (f=dfs(ss,tt,INF)) flow+=f;
	}
	if (flow!=sum) return 0*puts("IMPOSSIBLE");
	FOR(i,1,n){
		FOR(j,1,m){
			printf("%d ",mn[i][j]+edge[E[pos[i][j]]].cap);
		}
		puts("");
	}
}
int main()
{
	int T;
	scanf("%d",&T);
	while (T--){
		solve();
		puts("");
	}
}
/*
*/
