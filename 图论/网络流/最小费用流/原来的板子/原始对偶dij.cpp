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
const LL maxn=1e6+7;
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

namespace mincostflow {
	typedef int type;
	const type INF=0x3f3f3f3f;
	struct node {
		int to; type cap,cost; int rev;
		node(int t=0,type c=0,type _c=0,int n=0):
			to(t),cap(c),cost(_c),rev(n) {};
	} edge[maxn*2]; int tot;
	int head[maxn];
	void addedge(int from,int to,type cap,type cost,type rcap=0) {
		edge[tot]=node(to,cap,cost,head[from]); head[from]=tot++;
		edge[tot]=node(from,rcap,-cost,head[to]); head[to]=tot++;
	}
	int pre[maxn];//pre_cnt
	type dis[maxn],h[maxn];
	pair<type,type> mincostflow(int s,int t,int n,type flow=INF) {
		type ret=0,ans=0;
		memset(h+1,0,n*sizeof(type));
		while (flow) {
			// dij
			typedef pair<type,int> pit;
			memset(dis+1,0x3f,n*sizeof(type));
			static priority_queue<pit,vector<pit>,greater<pit> > Q;
			dis[s]=0; pre[s]=-1; Q.push(pit(0,s));
			while (Q.size()) {
				auto now=Q.top(); Q.pop();
				if (dis[now.second]<now.first) continue;
				int v=now.second;
				for (int i=head[v]; ~i; i=edge[i].next) {
					node &e=edge[i];
					if (e.cap>0&&dis[e.to]>dis[v]+e.cost+h[v]-h[e.to]) {
						dis[e.to]=dis[v]+e.cost+h[v]-h[e.to]; pre[e.to]=i;
						Q.push(pit(dis[e.to],e.to));
					}
				}
			} int i;
			if (dis[t]==INF) break;
			FOR(i,1,n) h[i]+=dis[i];
			type d=flow;
			for (int i=pre[t]; ~i; i=pre[edge[i^1].to])
				d=min(d,edge[i].cap);
			flow-=d; ret+=d; ans+=d*h[t];
			for (int i=pre[t]; ~i; i=pre[edge[i^1].to])
				edge[i].cap-=d,edge[i^1].cap+=d;
			if (d==0) break;
		} return make_pair(ret,ans);
	}
	void init(int n) {
		memset(head+1,0xff,n*sizeof(int));
		tot=0;
	}
}
int i,j,k;
int main() {
	int n,m,s,t;
	scanf("%d%d%d%d",&n,&m,&s,&t);
	mincostflow::init(n);
	FOR(i,1,m) {
		int u,v,c,w;
		scanf("%d%d%d%d",&u,&v,&c,&w);
		mincostflow::addedge(u,v,c,w);
	}
	pair<int,int> ans=mincostflow::mincostflow(s,t,n);
	printf("%d %d",ans.first,ans.second);
}
