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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

//这个题题意: 求所有只属于一个简单环上的边
int U[maxn],V[maxn];
vector<pair<int,int> > edge[maxn];
int dfn[maxn],low[maxn],vis[maxn],tot;
int S[maxn],top;
bool used[maxn];
set<int> H;
vector<int> E;
vector<int> ans;
void tarjan(int x,int fa){
	low[x]=dfn[x]=++tot;
	vis[x]=1;
	for(auto i:edge[x]) {
		int v=i.first;
		if (used[i.second]) continue;
		if (v==fa) continue;
		S[++top]=i.second;
		used[i.second]=1;
		if(!dfn[v]) {
			tarjan(v,x);
			low[x]=min(low[x],low[v]);
			if (dfn[x]<=low[v]){
				int nodecnt=0;
				E.clear();H.clear();
				while (1){
					int id=S[top--];nodecnt++;
					H.insert(U[id]);H.insert(V[id]);
					E.push_back(id);
					if (id==i.second) break;
				}if (low[v]==dfn[x]&&nodecnt==(int)H.size()){
					for (int v:E) ans.push_back(v);
				}
			}
		} else if(vis[v])
			low[x]=min(low[x],dfn[v]);
	}
}
int n,m;
int main(){
	int i;
	scanf("%d%d",&n,&m);
	FOR(i,1,m){
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(make_pair(v,i));
		edge[v].push_back(make_pair(u,i));
		U[i]=u;V[i]=v;
	}
	FOR(i,1,n) if (!dfn[i]) tarjan(i,0);
	sort(ans.begin(), ans.end());
	printf("%d\n",ans.size());
	for (int v:ans) printf("%d ",v);
}
/*
*/