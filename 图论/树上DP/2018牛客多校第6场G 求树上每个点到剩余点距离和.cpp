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
typedef unsigned int UI;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=4e5+7;
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
void initialize() {}
char str[maxn];

//2018牛客多校第6场G 求树上每个点到剩余点距离和
vector<pair<int,int> > edge[maxn];
int sz[maxn];
ll ans[maxn];
void dfs_up(int x,int fa) {
	sz[x]=1; ans[x]=0;
	for (auto v:edge[x])
		if (v.first!=fa) {
			dfs_up(v.first,x); sz[x]+=sz[v.first];
			ans[x]+=ans[v.first]; ans[x]+=sz[v.first]*v.second;//down
		}
}
void dfs_down(int x,int fa) {
	for (auto v:edge[x])
		if (v.first!=fa) {
			ans[v.first]=ans[x]+(ll)v.second*(n-2*sz[v.first]);//more
			dfs_down(v.first,x);
		}
}
__int128 Ans;
void out(__int128 x) {
	if (x>9) out(x/10);
	putchar(x%10+'0');
}
int main() {
	int T,_T;
	scanf("%d",&T);
	FOR(_T,1,T) {
		int i;
		scanf("%d",&n);
		FOR(i,1,n-1) {
			int u,v,len;
			scanf("%d%d%d",&u,&v,&len);
			edge[u].push_back(make_pair(v,len));
			edge[v].push_back(make_pair(u,len));
		} Ans=0;
		dfs_up(1,0); dfs_down(1,0);
		sort(ans+1,ans+1+n);
		FOR(i,1,n) Ans+=(__int128)ans[i]*(n-i);
		printf("Case #%d: ",_T);
		out(Ans); puts("");
		FOR(i,1,n) edge[i].clear();
	}
}
/*
2
3
1 2 1
2 3 1
5
1 2 1
2 3 1
2 4 1
4 5 2
*/