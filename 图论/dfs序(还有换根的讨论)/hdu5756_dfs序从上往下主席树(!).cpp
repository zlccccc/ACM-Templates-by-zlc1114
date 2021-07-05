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
const LL M=998244353;
const LL maxn=5e4+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
inline void add(int &A,int B) {A+=B; (A>=M) &&(A-=M);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int n,m;
char S[maxn];
int TaskA();
void Task_one() {TaskA();}
void Task_T() {int T; scanf("%d",&T); while (T--) TaskA();}
void Task_more_n() {while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m() {while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_string() {while (~scanf("%s",S)) TaskA();}

struct node {
	int max,min,lazy; ll sum;
	int l,r;
	node() {max=-INF; min=INF; lazy=sum=0; l=r=0;}
} T[maxn*40];
vector<int> edge[maxn];
int in[maxn],out[maxn],tot;
int dep[maxn];
void dfs_1(int x,int fa,int depth) {
	in[x]=++tot; dep[in[x]]=depth;
	for (int v:edge[x]) if (v!=fa) dfs_1(v,x,depth+1);
	out[x]=tot;
}
void pushup(int x,int size) {
	T[x].max=max(T[T[x].l].max,T[T[x].r].max)+T[x].lazy;
	T[x].min=min(T[T[x].l].min,T[T[x].r].min)+T[x].lazy;
	T[x].sum=T[T[x].l].sum+T[T[x].r].sum+T[x].lazy*size;
}
int root[maxn],rtot;
void build(int &x,int l,int r) {
	if (!x) x=++rtot; T[x]=node();
	if (l==r) {
		T[x].max=T[x].min=T[x].sum=dep[l];
		return;
	} int mid=(l+r)/2;
	build(T[x].l,l,mid);
	build(T[x].r,mid+1,r);
	pushup(x,r-l+1);
}
void change(int x,int len,int val) {
	T[x].lazy+=val; T[x].sum+=len*val;
	T[x].max+=val; T[x].min+=val;
}
void update(int &x,int y,int l,int r,int val,int L,int R) {
	x=++rtot; T[x]=T[y];
	if (l<=L&&R<=r) {
		change(x,R-L+1,val);
		return;
	}int mid=(L+R)/2;
	if (l<=mid) update(T[x].l,T[y].l,l,r,val,L,mid);
	if (mid<r) update(T[x].r,T[y].r,l,r,val,mid+1,R);
	pushup(x,R-L+1);
}
ll ans=0;
void query(int x,int l,int r,int t,int val,int L,int R) {
	if (l<=L&&R<=r) {
		if (t==1) ans+=T[x].sum+(ll)val*(R-L+1);
		if (t==2) ans=min(ans,(ll)T[x].min+val);
		if (t==3) ans=max(ans,(ll)T[x].max+val);
		return;
	} int mid=(L+R)/2;
	if (l<=mid) query(T[x].l,l,r,t,val+T[x].lazy,L,mid);
	if (mid<r) query(T[x].r,l,r,t,val+T[x].lazy,mid+1,R);
	pushup(x,R-L+1);
}
void dfs_2(int x,int fa) {
	if (fa) {
		update(root[x],root[fa],in[x],out[x],-2,1,n);
		update(root[x],root[x],1,n,1,1,n);
	}
	for (int v:edge[x]) if (v!=fa) dfs_2(v,x);
}
int TaskA() {
	int i; tot=rtot=0; ans=0;
	FOR(i,1,n) edge[i].clear(),root[i]=0;
	FOR(i,1,n-1) {
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	dfs_1(1,0,0);
	build(root[1],1,n);
	dfs_2(1,0);
	vector<pair<int,int> > have;
	FOR(i,1,m) {
		int j,k,p,t,A;
		have.clear();
		have.push_back(make_pair(1,0));
		have.push_back(make_pair(n+1,INF));
		scanf("%d%d%d",&k,&p,&t);
		p=(p+ans)%n+1;
		debug("query: %d %d %d\n",k,p,t);
		FOR(j,1,k) {
			scanf("%d",&A);
			have.push_back(make_pair(in[A],1));
			have.push_back(make_pair(out[A]+1,-1));
		} sort(have.begin(),have.end());
		int all=0;
		if (t==1) ans=0;
		if (t==2) ans=INF;
		if (t==3) ans=-INF;
		bool okay=0;
		REP(j,(int)have.size()) {
			all+=have[j].second;
			if (all==0&&have[j].first<=have[j+1].first-1) {
				// printf("query: %d %d\n",have[j].first,have[j+1].first-1);
				query(root[p],have[j].first,have[j+1].first-1,t,0,1,n);
				okay=1;
			}
		} if (!okay) {puts("-1"); ans=0;}
		else printf("%lld\n",ans);
	}
	return 0;
}
void initialize() {}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_more_n_m();
}
/*
6 5
1 3
2 1
4 2
6 4
5 6

3 5 3
3 3 3
3 4 3
4 5 1
3 3 1
1 5 6
3 5 2
3 4 2
3 3 3
6 5 3
*/
