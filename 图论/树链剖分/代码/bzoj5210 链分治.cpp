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

#define DEBUG1
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=2e5+7;
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

// f[x]:this_ans=max(g[x]+f[heavy],0)
// g[x]:light_ans=A[x]+sigma{f[light]}
// w[x]:dp[heavy_son]
// 把轻链和重链分开维护, 在重链上一个序列上DP
struct heap {
	multiset<ll> S;
	inline void ins(ll x) {
		S.insert(x);
	}
	inline void del(ll x) {
		multiset<ll>::iterator it=S.lower_bound(x);
		if (it!=S.end()) S.erase(it);
	}
	inline ll top() {
		if (!S.size()) return 0;
		return *S.rbegin();
	}
} SON[maxn]; // light
vector<int> edge[maxn];
int fa[maxn],dep[maxn],sz[maxn],tot;
int top[maxn],id[maxn],rid[maxn],son[maxn],leaf[maxn];
void dfs1(int u,int father,int depth) {
	int mx=-1,i; sz[u]=1;
	fa[u]=father; son[u]=0; dep[u]=depth;
	REP(i,(int)edge[u].size()) {
		int v=edge[u][i];
		if (v==father) continue;
		dfs1(v,u,depth+1); sz[u]+=sz[v];
		if (sz[v]>mx) mx=sz[v],son[u]=v;
	}
}
int A[maxn];
// f[x]:this_ans=max(g[x]+f[heavy],0)
// g[x]:light_ans=A[x]+sigma{f[light]}
// w[x]:dp[heavy_son]
ll f[maxn],g[maxn],w[maxn];
void dfs2(int u,int x) {
	top[u]=x; id[u]=++tot; rid[tot]=u;
	g[u]=A[u]; f[u]=0; int i;
	if (son[u]) dfs2(son[u],x);
	REP(i,(int)edge[u].size()) {
		int v=edge[u][i];
		if (v==fa[u]||v==son[u]) continue;
		dfs2(v,v); SON[u].ins(w[v]);
		g[u]+=f[v]; max_(w[u],w[v]);
	} if (son[u]) {
		leaf[u]=leaf[son[u]];
		max_(f[u],g[u]+f[son[u]]);
		max_(w[u],w[son[u]]);
	} else leaf[u]=u;
	max_(f[u],g[u]); max_(w[u],f[u]);
}
struct node {
	ll ls,rs,sum,ans;
	node(ll val=0) {sum=val; ls=rs=ans=max(0ll,val);}
} T[maxn<<2];
node merge(const node &A,const node &B) {
	node ret;
	ret.ls=max(A.ls,A.sum+B.ls);
	ret.rs=max(B.rs,B.sum+A.rs);
	ret.ans=max(A.ans,B.ans);
	ret.ans=max(ret.ans,A.rs+B.ls);
	ret.sum=A.sum+B.sum;
	return ret;
}
// f[x]:this_ans=max(g[x]+f[heavy],0)
// g[x]:light_ans=A[x]+sigma{f[light]}
void build(int x,int L,int R) {
	if (L==R) {
		T[x]=node(g[rid[L]]);
		max_(T[x].ans,SON[rid[L]].top());
		return;
	} int mid=(L+R)/2;
	build(x<<1,L,mid);
	build(x<<1|1,mid+1,R);
	T[x]=merge(T[x<<1],T[x<<1|1]);
}
void update(int x,int pos,int L,int R) {
	if (L==R) {
		T[x]=node(g[rid[L]]);
		max_(T[x].ans,SON[rid[L]].top());
		return;
	} int mid=(L+R)/2;
	if (pos<=mid) update(x<<1,pos,L,mid);
	if (mid<pos) update(x<<1|1,pos,mid+1,R);
	T[x]=merge(T[x<<1],T[x<<1|1]);
}
node query(int x,int l,int r,int L,int R) {
	if (l<=L&&R<=r) return T[x];
	int mid=(L+R)/2;
	if (r<=mid) return query(x<<1,l,r,L,mid);
	if (mid<l) return query(x<<1|1,l,r,mid+1,R);
	return merge(query(x<<1,l,r,L,mid),query(x<<1|1,l,r,mid+1,R));
}
inline void Update(int x,ll y) {
	g[x]-=A[x]; A[x]=y; g[x]+=A[x];
	while (x) {
		update(1,id[x],1,n);
		node nxtval=query(1,id[top[x]],id[leaf[x]],1,n);
		ll initw=w[top[x]]; w[top[x]]=nxtval.ans;
		ll initg=f[top[x]]; f[top[x]]=nxtval.ls;
		x=fa[top[x]];
		if (x) {
			g[x]-=initg;
			g[x]+=nxtval.ls;
			SON[x].del(initw);
			SON[x].ins(nxtval.ans);
		}
	}
}
inline ll Query(int x) {
	return query(1,id[x],id[leaf[x]],1,n).ans;
}
int main() {
	int i;
	scanf("%d%d",&n,&q); tot=0;
	FOR(i,1,n) scanf("%d",&A[i]);
	FOR(i,1,n) edge[i].clear();
	FOR(i,1,n-1) {
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	} dfs1(1,0,0); dfs2(1,1);
	FOR(i,1,n) debug("%d ",id[i]); deputs("");
	FOR(i,1,n) debug("%d ",rid[i]); deputs("");
	build(1,1,n);
	REP(i,q) {
		char op[2];
		scanf("%s",op);
		if (op[0]=='M') {
			int x; ll y;
			scanf("%d%lld",&x,&y);
			Update(x,y);
		} else {
			int x;
			scanf("%d",&x);
			printf("%lld\n",Query(x));
		}
	}
	return 0;
}
/*
*/
