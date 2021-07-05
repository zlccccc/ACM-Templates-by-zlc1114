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
//确认没写错
//修改边权:把边当成点,mark一下,然后左右端点连边即可 
//HDU5002
//静态没修改的也真TMD好用 
struct LCT{
	struct node{
		int son[2],val,size;
		int max,add,cnt1;//max
		int ans,lazy,cnt2;//second
		bool rev;
		void init(int _val){
			son[0]=son[1]=rev=add=0;
			max=val=_val;
			size=1;
			cnt1=1;cnt2=0;
			ans=lazy=-INF;
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
		T[x].add+=val;
		T[x].val+=val;
		if (T[x].ans!=-INF) T[x].ans+=val;;
		if (T[x].lazy!=-INF) T[x].lazy+=val;
	}
	void Change(int x,int val){//先change 
		T[x].max=val;
		T[x].add=0;
		T[x].val=val;
		T[x].ans=-INF;
		T[x].cnt2=-INF;
		T[x].cnt1=T[x].size;
		T[x].lazy=val;
	}
	void Update(int x,int val,int num){
		if (T[x].max==val) T[x].cnt1+=num;
		else if (T[x].max<val){
			T[x].ans=T[x].max;
			T[x].cnt2=T[x].cnt1;
			T[x].max=val;
			T[x].cnt1=num;
		}
		else if (T[x].ans==val) T[x].cnt2+=num;
		else if (T[x].ans<val){
			T[x].ans=val;
			T[x].cnt2=num;
		}
	}
	void pushup(int x){
		T[x].size=1;
		T[x].max=T[x].val;
		T[x].ans=T[x].lazy=-INF;
		T[x].cnt1=1;T[x].cnt2=0;
		if (T[x].son[0]){
			Update(x,T[T[x].son[0]].max,T[T[x].son[0]].cnt1);
			Update(x,T[T[x].son[0]].ans,T[T[x].son[0]].cnt2);
			T[x].size+=T[T[x].son[0]].size;
		}
		if (T[x].son[1]){
			Update(x,T[T[x].son[1]].max,T[T[x].son[1]].cnt1);
			Update(x,T[T[x].son[1]].ans,T[T[x].son[1]].cnt2);
			T[x].size+=T[T[x].son[1]].size;
		}
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
		if (T[x].lazy!=-INF){
			if (T[x].son[0]) Change(T[x].son[0],T[x].lazy);
			if (T[x].son[1]) Change(T[x].son[1],T[x].lazy);
			T[x].lazy=-INF;
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
		makeroot(u);
		access(v);
		splay(v);
		Add(v,val);
		return 0;
	}
	bool change(int u,int v,int val){
		makeroot(u);
		access(v);
		splay(v);
		Change(v,val);
		return 0;
	}
	pair<int,int> ask(int u,int v){
		makeroot(u);
		access(v);
		splay(v);
		return make_pair(T[v].ans,T[v].cnt2);
	}
}T;
vector<int> edge[maxn];
void dfs(int x,int fa){
	T.fa[x]=fa;
	for (int v:edge[x]) if (v!=fa) dfs(v,x);
}
int n,m,TT;
int i,j,k;
int u,v;
int main(){
}
/*
*/
