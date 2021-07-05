#include <sstream>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
#include <cassert>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG
#ifdef DEBUG
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#define dbg(x)
#define dbgln(x)
#endif // DEBUG
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=25*25*16+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}

// 题意: 给你个矩阵,相邻的可能满足和或者差大于或者小于定值
// 你可以将某个位置/2无限次，代价是val[i][j]，问最小代价，或者不可能
// 做法：奇偶染色，然后最小割
// 最小割填INF边的意义：使得一个矩形不可行！
struct node {
	int to,cap,next;
	node(int t=0,int c=0,int n=0):to(t),cap(c),next(n) {};
} edge[maxn*50];
int head[maxn],tot;
void addedge(int from,int to,int cap,int rcap=0) {
	edge[tot]=node(to,cap,head[from]); head[from]=tot++;
	edge[tot]=node(from,rcap,head[to]); head[to]=tot++;
}
queue<int> Q;
int gap[maxn],dep[maxn],cur[maxn];
void bfs(int s,int t) {
	memset(dep,0xff,sizeof(dep));
	memset(gap,0,sizeof(gap));
	gap[0]=1; dep[t]=0; Q.push(t);
	while (Q.size()) {
		int u=Q.front(); Q.pop();
		for (int i=head[u]; ~i; i=edge[i].next) {
			int v=edge[i].to;
			if (dep[v]!=-1) continue;
			Q.push(v); dep[v]=dep[u]+1;
			gap[dep[v]]++;
		}
	}
}
int S[maxn];
int sap(int s,int t,int n) {
	bfs(s,t);
	memcpy(cur,head,sizeof(head));
	int top=0,u=s,ret=0;
	while (dep[s]<n) {
		if (u==t) {
			int MIN=INF,inser=0,i;
			REP(i,top) if (MIN>edge[S[i]].cap)
				MIN=edge[S[i]].cap,inser=i;
			REP(i,top) {
				edge[S[i]].cap-=MIN; edge[S[i]^1].cap+=MIN;
			} ret+=MIN; top=inser; u=edge[S[top]^1].to;
			continue;
		} bool flag=0; int v;
		for (int i=cur[u]; ~i; i=edge[i].next) {
			v=edge[i].to;
			if (edge[i].cap&&dep[v]+1==dep[u]) {
				flag=1; cur[u]=i; break;
			}
		} if (flag) {
			S[top++]=cur[u]; u=v; continue;
		} int MIN=n;
		for (int i=head[u]; ~i; i=edge[i].next) {
			v=edge[i].to;
			if (edge[i].cap&&dep[v]<MIN)
				MIN=min(MIN,dep[v]),cur[u]=i;
		} gap[dep[u]]--;
		if (ret>INF) return ret;//not okay
		if (!gap[dep[u]]) return ret;
		dep[u]=MIN+1; gap[dep[u]]++;
		if (u!=s) u=edge[S[--top]^1].to;
	} return ret;
}
int n,m;
int getid(int x,int y,int k) { //the k-th
	return ((x-1)*m+y-1)*16+k;
}
int A[27][27][17],B[27][27];
int main() {
	int T;
	int i,j,k;
	scanf("%d",&T);
	while (T--) {//点在边上! 与流量无关, 我只考虑最小割
		memset(head,0xff,sizeof(head)); tot=0;
		scanf("%d%d",&n,&m);
		int s=getid(n,m+1,0),t=getid(n,m+1,1);
		FOR(i,1,n) FOR(j,1,m) scanf("%d",&A[i][j][0]);
		FOR(i,1,n) FOR(j,1,m) scanf("%d",&B[i][j]);
		FOR(i,1,n) FOR(j,1,m) {
			FOR(k,1,14) A[i][j][k]=A[i][j][k-1]/2;
			if ((i+j)&1) { //odd
				addedge(s,getid(i,j,0),INF);
				FOR(k,0,14) addedge(getid(i,j,k),getid(i,j,k+1),(14-k)*B[i][j]);
				addedge(getid(i,j,15),t,INF);
			} else { //even
				addedge(s,getid(i,j,0),INF);
				FOR(k,0,14) addedge(getid(i,j,k),getid(i,j,k+1),k*B[i][j]);
				addedge(getid(i,j,15),t,INF);
			}
		}
		scanf("%d",&k);
		while (k--) {
			int d,x1,x2,y1,y2;
			scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&d);
			if ((x1+y1)&1) swap(x1,x2),swap(y1,y2);
			REP(i,15) {
				rREP(j,15) if (A[x1][y1][i]+A[x2][y2][j]>d) break;
//                if (A[x1][y1][i]&&A[x2][y2][j]) printf("<= : i,j=%d %d\n",i,j);
				if (j==-1) continue;//not available
				else addedge(getid(x2,y2,14-j),getid(x1,y1,i+1),INF);
			}
		}
		scanf("%d",&k);
		while (k--) {
			int d,x1,x2,y1,y2;
			scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&d);
			if ((x1+y1)&1) swap(x1,x2),swap(y1,y2);
			REP(j,15) {// 割边意思是不共存
				REP(i,15) if (A[x1][y1][i]+A[x2][y2][j]<d) break;
//                if (A[x1][y1][i]&&A[x2][y2][j]) printf(">= : i,j=%d %d\n",i,j);
				if (i==15) continue;
				else addedge(getid(x1,y1,i),getid(x2,y2,14-j+1),INF);
			}
		} int ans=0;
		ans=sap(s,t,t+1);
//        printf("%d\n",ans);
		if (ans>=INF) puts("impossible");
		else printf("%d\n",ans);
	}
	return 0;
}
/*
2
2 2
10 7
5 8
1 2
2 1
4
1 1 1 2 7
1 1 2 1 5
2 2 2 1 6
2 2 1 2 5
4
1 1 1 2 5
1 1 2 1 4
2 2 2 1 6
2 2 1 2 5

2 2
10 7
5 8
1 2
2 1
4
1 1 1 2 5
1 1 2 1 3
2 2 2 1 4
2 2 1 2 6
4
1 1 1 2 1
1 1 2 1 1
2 2 2 1 2
2 2 1 2 4
*/
