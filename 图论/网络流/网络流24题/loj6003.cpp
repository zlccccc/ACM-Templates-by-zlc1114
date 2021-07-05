#include <sstream>
#include <fstream>
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
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

namespace maxflow {
	typedef int type;
	const type INF=0x3f3f3f3f;
	struct node {
		int to; type cap; int next;
		node(int t=0,type c=0,int n=0):to(t),cap(c),next(n) {};
	} edge[maxn*50];
	int head[maxn],tot;
	int addedge(int from,int to,type cap,type rcap=0) {
		edge[tot]=node(to,cap,head[from]); head[from]=tot++;
		edge[tot]=node(from,rcap,head[to]); head[to]=tot++;
		return tot-2;
	}
	int dep[maxn],cur[maxn];//µ±Ç°»¡ÓÅ»¯
	bool bfs(int s,int t,int n) {
		static int Q[maxn],ST,ED;
		memset(dep+1,0,n*sizeof(int));
		ST=0; ED=-1;
		Q[++ED]=s; dep[s]=1;
		while (ST<=ED) {
			int u=Q[ST++];
			for (int i=head[u]; i!=-1; i=edge[i].next) {
				int v=edge[i].to;
				if (!dep[v]&&edge[i].cap) {
					Q[++ED]=v; dep[v]=dep[u]+1;
				}
			}
		} return (dep[t]!=0);
	}
	type dfs(int x,const int &t,type flow=INF) {
		if (x==t||flow==0) return flow;
		type ret=0;
		for (int i=cur[x]; i!=-1; i=edge[i].next) {
			if (dep[x]+1==dep[edge[i].to]&&edge[i].cap) {
				int f=dfs(edge[i].to,t,min(flow,edge[i].cap));
				edge[i].cap-=f; edge[i^1].cap+=f;
				ret+=f; flow-=f; cur[x]=i;
				if (flow==0) break;
			}
		} if (!ret) dep[x]=0;
		return ret;
	}
	type maxflow(int s,int t,int n) {
		int ret=0;
		while (bfs(s,t,n)) {
			int f;
			memcpy(cur+1,head+1,n*sizeof(int));
			while ((f=dfs(s,t))>0) ret+=f;
		} return ret;
	}
	void init(int n) {
		memset(head+1,0xff,n*sizeof(int)); tot=0;
	}
}
vector<int> v[maxn]; int tot;
int D[maxn],nxt[maxn];
int main() {
	scanf("%d",&n); int i,k=0,cnt=0;
	maxflow::init(10000);
	int s=++cnt,t=++cnt;
	while (1) {
		k++;
		maxflow::addedge(s,k*2+1,1);
		maxflow::addedge(k*2+2,t,1);
		for (int i=1; i*i<k*2; i++) if (k<i*i){
			maxflow::addedge((i*i-k)*2+1,k*2+2,1);
		}
		n--; n+=maxflow::maxflow(s,t,k*2+2);
		if (n==-1) break;
		int x;
		FOR(x,1,k) D[x]=0;
		FOR(x,1,k) {
			nxt[x]=0;
			for (int i=maxflow::head[x*2+1]; i!=-1; i=maxflow::edge[i].next)
				if (!maxflow::edge[i].cap&&maxflow::edge[i].to!=x+1&&
					maxflow::edge[i].to!=s&&maxflow::edge[i].to!=t){
					nxt[x]=maxflow::edge[i].to/2-1,D[maxflow::edge[i].to/2-1]++;
			}
		} 
		FOR(i,1,tot) v[i].clear(); tot=0;
		FOR(x,1,k) if (!D[x]){
			tot++;
			for (int i=x;i;i=nxt[i]) v[tot].push_back(i);
		}
	} k--; printf("%d\n",k);
	FOR(i,1,tot){
		for (auto now:v[i]) printf("%d ",now);
		puts("");
	}
}
/*
*/
