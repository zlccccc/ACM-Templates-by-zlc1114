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


namespace mincostflow {
	typedef int type;
	const type INF=0x3f3f3f3f;
	struct node {
		int to; type cap,cost; int next;
		node(int t=0,type c=0,type _c=0,int n=0):
			to(t),cap(c),cost(_c),next(n) {};
	} edge[maxn*2]; int tot;
	int head[maxn];
	int addedge(int from,int to,type cap,type cost,type rcap=0) {
		edge[tot]=node(to,cap,cost,head[from]); head[from]=tot++;
		edge[tot]=node(from,rcap,-cost,head[to]); head[to]=tot++;
		return tot-2;
	}
	type dis[maxn];
	bool mark[maxn];
	void spfa(int s,int t,int n) {
		memset(dis+1,0x3f,n*sizeof(type));
		memset(mark+1,0,n*sizeof(bool));
		static int Q[maxn],ST,ED;
		dis[s]=0; ST=ED=0; Q[ED++]=s;
		while (ST!=ED) {
			int v=Q[ST]; mark[v]=0;
			if ((++ST)==maxn) ST=0;
			for (int i=head[v]; ~i; i=edge[i].next) {
				node &e=edge[i];
				if (e.cap>0&&dis[e.to]>dis[v]+e.cost) {
					dis[e.to]=dis[v]+e.cost;
					if (!mark[e.to]) {
						if (ST==ED||dis[Q[ST]]<=dis[e.to]) {
							Q[ED]=e.to,mark[e.to]=1;
							if ((++ED)==maxn) ED=0;
						} else {
							if ((--ST)<0) ST+=maxn;
							Q[ST]=e.to,mark[e.to]=1;
						}
					}
				}
			}
		}
	} int cur[maxn];
	type dfs(int x,int t,type flow) {
		if (x==t||!flow) return flow;
		type ret=0; mark[x]=1;
		for (int i=cur[x]; ~i; i=edge[i].next) if (!mark[edge[i].to]) {
				if (dis[x]+edge[i].cost==dis[edge[i].to]&&edge[i].cap) {
					int f=dfs(edge[i].to,t,min(flow,edge[i].cap));
					edge[i].cap-=f; edge[i^1].cap+=f;
					ret+=f; flow-=f; cur[x]=i;
					if (flow==0) break;
				}
			}
		mark[x]=0;
		return ret;
	}
	pair<type,type> mincostflow(int s,int t,int n,type flow=INF) {
		type ret=0,ans=0;
		while (flow) {
			spfa(s,t,n); if (dis[t]==INF) break;
			// 这样加当前弧优化会快, 我也不知道为啥
			memcpy(cur+1,head+1,n*sizeof(int));
			type len=dis[t],f;
			if ((f=dfs(s,t,flow))>0)//while也行
				ret+=f,ans+=len*f,flow-=f;
		} return make_pair(ret,ans);
	}
	void init(int n) {
		memset(head+1,0xff,n*sizeof(int));
		tot=0;
	}
}

vector<string> V;
int s,t;
inline int getid(string x){
	int i; REP(i,(int)V.size()) if (V[i]==x) return i+1;
	assert(0); return 0*puts("-1");
}
bool mark;
void dfs(int x){
	bool okay=0;
	if (!mark&&x<=n) cout<<V[x-1]<<'\n',okay=1;
	if (x==t) mark=1;
	for (int i=mincostflow::head[x]; ~i; i=mincostflow::edge[i].next)
		if (!(i&1)) while (mincostflow::edge[i^1].cap)
			--mincostflow::edge[i^1].cap,dfs(mincostflow::edge[i].to);
	if (mark&&!okay&&x<n) cout<<V[x-1]<<'\n';
}
int main() {
	int i; cin>>n>>m;
	mincostflow::init(n+n);
	FOR(i,1,n) {
		string s;
		cin>>s; V.push_back(s);
	} s=1; t=n+n;
	FOR(i,1,n) mincostflow::addedge(i,i+n,1,0);
	mincostflow::addedge(1,n+1,INF,0);
	mincostflow::addedge(n,n+n,INF,0);
	FOR(i,1,m){
		string U,V;
		cin>>U; cin>>V;
		int u=getid(U),v=getid(V);
		if (u>v) swap(u,v);
		if (u==1&&n==v) mincostflow::addedge(u+n,v,1,-1);
		mincostflow::addedge(u+n,v,1,-1);
	} auto ans=mincostflow::mincostflow(s,t,n+n,2);
	if (ans.first!=2) puts("No Solution!");
	else {
		printf("%d\n",-ans.second);
		dfs(s); cout<<V[0]<<'\n';
	}
}
/*
*/
