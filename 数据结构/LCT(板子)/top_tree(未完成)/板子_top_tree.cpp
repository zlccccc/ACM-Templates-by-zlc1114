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
const LL maxn=1e6+107;
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
inline ll powMM(ll a, ll b, ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

//hdu5002, chain_makeSame; query secondary_max
namespace LCT {
	const int maxn=1e5+7;
	struct info {
		int max,min,sum; int size;
		info(int _val=0,int _size=1):
			max(_val),min(_val),sum(_val*_size),size(_size) {}
		info(int _max,int _min,int _sum,int _size):
			max(_max),min(_min),sum(_sum),size(_size) {}
		void print() {
			debug(" debug: infomation: max_min=(%d,%d)-(%d) size=%d\n",max,min,sum,size);
		}
	};
	struct tag {
		int mul,add;//same:lazy
		tag(int _mul=1,int _add=0):
			mul(_mul),add(_add) {}
		bool notempty() {return (mul!=1||add!=0);}
	};
	//info_merge
	//info_update and tag_update
	info merge(const info &x,const info &y) {
		return info(max(x.max,y.max),min(x.min,y.min),
		            x.sum+y.sum,x.size+y.size);
	}
	tag merge(const tag &x,const tag &y) {//merge y into x
		return tag(x.mul*y.mul,x.add*y.mul+y.add);
	}
	info merge(const info &_info,const tag &_tag) {
		info ret; ret.size=_info.size;
		int v0=_info.min*_tag.mul+_tag.add;
		int v1=_info.max*_tag.mul+_tag.add;
		ret.min=min(v0,v1); ret.max=max(v0,v1);
		ret.sum=ret.sum*_tag.mul+ret.size*_tag.add;
		return ret;
	}
	struct node {
		int son[4],fa;
		int val;
		info chain,subtree,all;
		tag chaintag,subtreetag;
		bool rev,isroot;//root=1:isroot
		void init(int _val) {
			val=_val;
			subtree=info(-INF,INF,0,0);//zero
			all=chain=info(val);
			subtreetag=chaintag=tag();
			rev=0; isroot=1;
			son[0]=son[1]=son[2]=son[3]=fa=0;
		}
	} T[maxn];
	void Reverse(int x) {
		T[x].rev^=1;
		swap(T[x].son[0],T[x].son[1]);
	}
	void ChangeValueChain(int x,tag &_tag) {
		T[x].val=T[x].val*_tag.mul+_tag.add;
		T[x].chain=merge(T[x].chain,_tag);
		T[x].chaintag=merge(T[x].chaintag,_tag);
		T[x].all=merge(T[x].chain,T[x].subtree);
	}
	void ChangeValueSubtree(int x,tag &_tag,bool downchain) {//²»º¬Á´(¿ÉÄÜÐé½Úµã)
		T[x].subtree=merge(T[x].subtree,_tag);
		T[x].subtreetag=merge(T[x].subtreetag,_tag);
		if (downchain) {
			T[x].val=T[x].val*_tag.mul+_tag.add;
			T[x].chain=merge(T[x].chain,_tag);
			T[x].chaintag=merge(T[x].chaintag,_tag);
		} T[x].all=merge(T[x].all,_tag);
	}
	void pushup(int x) {
		T[x].chain=info(T[x].val);//clear
		REP(i,2) if (T[x].son[i]) 
			T[x].chain=merge(T[x].chain,T[T[x].son[i]].chain);
		REP(i,4) if (T[x].son[i])
			T[x].chain=merge(T[x].chain,T[T[x].son[i]].chain,i>=2);
		
	}
	void pushdown(int x) {
		if (T[x].rev) {
			if (T[x].son[0]) Reverse(T[x].son[0]);
			if (T[x].son[1]) Reverse(T[x].son[1]);
			T[x].rev=0;
		} int i;
		if (T[x].chaintag.notempty()) {
			REP(i,2) if (T[x].son[i])
				ChangeValueChain(T[x].son[i],T[x].chaintag);
			T[x].chaintag=tag();
		}
		if (T[x].subtreetag.notempty()){
			REP(i,4) if (T[x].son[i])
				ChangeValueSubtree(T[x].son[i],T[x].subtreetag,i>=2);
			T[x].subtreetag=tag();
		}
	}
	void rotate(int x,int kind) {
		int y=T[x].fa,z=T[y].fa;
		T[y].son[!kind]=T[x].son[kind],T[T[x].son[kind]].fa=y;
		T[x].son[kind]=y,T[y].fa=x;
		if (T[y].isroot) {T[x].isroot=true; T[y].isroot=false;}
		else T[z].son[T[z].son[1]==y]=x;
		T[x].fa=z; pushup(y);
	}
	void PreChange(int x) {//change_from_root
		static int ids[maxn],i,k;
		for (k=0; !T[x].isroot; k++){
			ids[k]=x,x=T[x].fa;
		} ids[k++]=x;
		rREP(i,k) pushdown(ids[i]);
	}
	void splay(int x) { //to root
		PreChange(x);
		while (!T[x].isroot) {
			int y=T[x].fa,z=T[y].fa;
			int rx=T[y].son[0]==x,ry=T[z].son[0]==y;
			if (T[y].isroot) rotate(x,rx);
			else {
				if (rx==ry) rotate(y,ry);
				else rotate(x,rx);
				rotate(x,ry);
			}
		} pushup(x);
	}
	int access(int x) {
		int y=0;
		for (; x; x=T[x].fa) {
			splay(x);
			T[T[x].son[1]].isroot=true;
			T[x].son[1]=y;
			T[y].isroot=false;
			y=x; pushup(x);
		} return y;
	}
	bool judge(int u,int v) {
		while (T[u].fa) u=T[u].fa;
		while (T[v].fa) v=T[v].fa;
		return u==v;
	}
	void makeroot(int x) {
		access(x); splay(x);
		Reverse(x);
	}
	bool link(int u,int v) {
		if (judge(u,v)) return 1;
		makeroot(u); T[u].fa=v;
		return 0;
	}
	bool cut(int u,int v) {
		makeroot(u); splay(v);
		T[T[v].son[0]].fa=T[v].fa;
		T[v].fa=0;
		T[T[v].son[0]].isroot=true;
		T[v].son[0]=0;
		pushup(v);
		return 0;
	}
	bool add(int u,int v,int val) {
		makeroot(u); access(v); splay(v);
		// AddValueChain(v,val);
		return 0;
	}
	bool change(int u,int v,int val) {
		makeroot(u); access(v); splay(v);
		// MakeSameChain(v,val);
		return 0;
	}
	info ask(int u,int v) {
		makeroot(u); access(v); splay(v);
		return T[v].chain;
	}
};
vector<int> edge[maxn];
void dfs(int x,int fa) {
	LCT::T[x].fa=fa;
	LCT::T[x].isroot=1;
	for (int v:edge[x]) if (v!=fa) dfs(v,x);
}
int main() {
	int x=0;
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T) {
		int n,m,i;
		scanf("%d%d",&n,&m);
		FOR(i,1,n) {
			int val;
			scanf("%d",&val);
			LCT::T[i].init(val);
		}
		REP(i,n-1) {
			int u,v;
			scanf("%d%d",&u,&v);
			edge[u].push_back(v);
			edge[v].push_back(u);
		}
		dfs(1,0);
		printf("Case #%d:\n",++x);
		// while (m--) {
		// 	int k;
		// 	scanf("%d",&k);
		// 	int x,y;
		// 	if (k==1) {
		// 		int x0,y0;
		// 		scanf("%d%d%d%d",&x,&y,&x0,&y0);
		// 		LCT::cut(x,y);
		// 		LCT::link(x0,y0);
		// 	} else if (k==2) {
		// 		int val;
		// 		scanf("%d%d%d",&x,&y,&val);
		// 		LCT::change(x,y,val);
		// 	} else if (k==3) {
		// 		int val;
		// 		scanf("%d%d%d",&x,&y,&val);
		// 		LCT::add(x,y,val);
		// 	} else if (k==4) {
		// 		scanf("%d%d",&x,&y);
		// 		pair<int,int> t=LCT::ask(x,y);
		// 		if (t.first==-INF) puts("ALL SAME");
		// 		else printf("%d %d\n",t.first,t.second);
		// 	}
		// }
		FOR(i,1,n) edge[i].clear();
	}
}
/*
2
3 2
1 1 2
1 2
1 3
4 1 2
4 2 3
7 7
5 3 2 1 7 3 6
1 2
1 3
3 4
3 5
4 6
4 7
4 2 6
3 4 5 -1
4 5 7
1 3 4 2 4
4 3 6
2 3 6 5
4 3 6
*/