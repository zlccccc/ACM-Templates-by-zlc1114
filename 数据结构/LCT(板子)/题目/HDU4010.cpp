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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}
//已确认没写错=_= 
int a[maxn],cnt;
struct LCT{
	struct node{
		int son[2],max,add,val;
		bool rev;
		init(int _val){
			son[0]=son[1]=rev=add=0;
			max=val=_val;
		}
	}T[maxn];
	bool root[maxn];
	int fa[maxn];
	void Reverse(int x){
		T[x].rev^=1;
		swap(T[x].son[0],T[x].son[1]);
	}
	void Add(int x,int val){
		T[x].max+=val;
		T[x].val+=val;
		T[x].add+=val;
	}
	void pushup(int x){
		T[x].max=T[x].val;
		if (T[x].son[0]) T[x].max=max(T[x].max,T[T[x].son[0]].max);
		if (T[x].son[1]) T[x].max=max(T[x].max,T[T[x].son[1]].max);
	}
	void pushdown(int x){
		if (T[x].rev){
			if (T[x].son[0]) Reverse(T[x].son[0]);
			if (T[x].son[1]) Reverse(T[x].son[1]);
			T[x].rev=0;
		}
		if (T[x].add){
			if (T[x].son[0]) Add(T[x].son[0],T[x].add);
			if (T[x].son[1]) Add(T[x].son[1],T[x].add);
			T[x].add=0;
		}
	}
	void rotate(int x,int kind){
		int y=fa[x],z=fa[y];
		T[y].son[!kind]=T[x].son[kind],fa[T[x].son[kind]]=y;
		T[x].son[kind]=y,fa[y]=x;
		if (root[y]) {root[x]=true;root[y]=false;} 
		else T[z].son[T[z].son[1]==y]=x;
		fa[x]=z;
		pushup(y);
	}
	void Prechange(int x){
		if (!root[x]) Prechange(fa[x]);
		pushdown(x);
	}
	void splay(int x){//to root
		Prechange(x);
		while (!root[x]){
			int y=fa[x],z=fa[y];
			int rx=T[y].son[0]==x,ry=T[z].son[0]==y;
			if (root[y]) rotate(x,rx);
			else{
				if (rx==ry) rotate(y,ry);
				else rotate(x,rx);
				rotate(x,ry);
			}
		}
		pushup(x);
	}
	int access(int x){//只有这条链上的是mark的 
		int y=0;
		for (;x;x=fa[x]){
			splay(x);
			root[T[x].son[1]]=true;
			T[x].son[1]=y;
			root[y]=false;
			y=x;
			pushup(x);
		}
		return y;
	}
	bool judge(int u,int v){
		while (fa[u]) u=fa[u];
		while (fa[v]) v=fa[v];
		return u==v;
	}
	void makeroot(int x){
		access(x);
		splay(x);
		Reverse(x);
	}
	bool link(int u,int v){
		if (judge(u,v)) return 1;
		makeroot(u);
		fa[u]=v;
		return 0;
	}
	bool cut(int u,int v){
		if (u==v||!judge(u,v)) return 1;
		makeroot(u);
		splay(v);
		fa[T[v].son[0]]=fa[v];
		fa[v]=0;
		root[T[v].son[0]]=true;
		T[v].son[0]=0;
		pushup(v);
		return 0;
	}
	bool add(int u,int v,int val){
		if (!judge(u,v)) return 1;
		makeroot(u);
		access(v);
		splay(v);
		Add(v,val);
		return 0;
	}
	int ask(int u,int v){
		if (!judge(u,v)) return -1;
		makeroot(u);
		access(v);
		splay(v);
		return T[v].max;
	}
}T;
vector<int> edge[maxn];
void dfs(int x,int fa){
	T.fa[x]=fa;
	for (int v:edge[x]) if (v!=fa) dfs(v,x);
}
int n,m,Q;
int i,j,k;
int u,v;
int main(){
	while (~scanf("%d",&n)){
		REP(i,n-1){
			scanf("%d%d",&u,&v);
			edge[u].push_back(v);
			edge[v].push_back(u);
		}
		FOR(i,1,n){
			int val;
			scanf("%d",&val);
			T.T[i].init(val);
		}
		FOR(i,1,n) T.root[i]=1;
		dfs(1,0);
		scanf("%d",&Q);
		while(Q--){
			scanf("%d",&k);
			int x,y;
			if (k==1){
				scanf("%d%d",&x,&y);
				if (T.link(x,y)) puts("-1");
			}else if (k==2){
				scanf("%d%d",&x,&y);
				if (T.cut(x,y)) puts("-1");
			}else if (k==3){
				int w;
				scanf("%d%d%d",&w,&x,&y);
				if (T.add(x,y,w)) puts("-1");
			}else if (k==4){
				scanf("%d%d",&x,&y);
				printf("%d\n",T.ask(x,y));
			}
		}
		puts("");
		FOR(i,1,n) edge[i].clear();
	}
}
/*
*/
