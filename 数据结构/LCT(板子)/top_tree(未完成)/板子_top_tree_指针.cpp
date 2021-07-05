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

//bzoj3153, sone1
//top tree虚子树不能有父子关系, 否则会直接炸
namespace LCT {
	const int NOTOK=-INF;
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
		tag() {mul=1; add=0;}
		bool notempty() {return (mul!=1||add!=0);}
	};
	//info_merge
	info merge(const info &x,const info &y) {
		return info(max(x.max,y.max),min(x.min,y.min),
		            x.sum+y.sum,x.size+y.size);
	}
	//info_update and tag_update
	inline void UpdateValue(info &_info,int mulval,int addval) {
		int v0=_info.min*mulval+addval;
		int v1=_info.max*mulval+addval;
		_info.min=min(v0,v1);
		_info.max=max(v0,v1);
		_info.sum=_info.sum*mulval+addval;
	}
	inline void UpdateValue(tag &_tag,int mulval,int addval) {
		_tag.mul=_tag.mul*mulval;
		_tag.add=_tag.add*mulval+addval;
	}
	struct node {
		node *son[2],*fa;
		int val;
		info chain,subtree,all;
		tag chaintag,subtreetag;
		bool rev,isroot;//root=1:isroot
		void init(int _val) {
			val=_val;
			all=subtree=chain=info(val);
			subtreetag=chaintag=tag();
			rev=0; isroot=1;
			son[0]=son[1]=fa=nullptr;
		}
	} T[maxn];
	void Reverse(node *x) {
		x->rev^=1;
		swap(x->son[0],x->son[1]);
	}
	void ChangeValueChain(node *x,int mulval,int addval) {//Add_To_Node
		x->val=x->val*mulval+addval;
		UpdateValue(x->chain,mulval,addval);
		UpdateValue(x->chaintag,mulval,addval);
	}
	
	void pushup(node *x) {
		x->chain=info(x->val);//clear
		if (x->son[0]!=nullptr)
			x->chain=merge(x->son[0]->chain,x->chain);
		if (x->son[1]!=nullptr)
			x->chain=merge(x->chain,x->son[1]->chain);
	}
	void pushdown(node *x) {
		if (x->rev) {
			if (x->son[0]!=nullptr) Reverse(x->son[0]);
			if (x->son[1]!=nullptr) Reverse(x->son[1]);
			x->rev=0;
		}
		if (x->chaintag.notempty()) {
			if (x->son[0]!=nullptr)
				ChangeValueChain(x->son[0],x->chaintag.mul,x->chaintag.add);
			if (x->son[1]!=nullptr)
				ChangeValueChain(x->son[1],x->chaintag.mul,x->chaintag.add);
			x->chaintag.mul=1;//clear
			x->chaintag.add=0;
		}
	}
	void rotate(node *x,int kind) {
		node *y=x->fa,*z=y->fa;
		y->son[!kind]=x->son[kind];
		if (x->son[kind]) x->son[kind]->fa=y;
		x->son[kind]=y,y->fa=x;
		if (y->isroot) {x->isroot=true; y->isroot=false;}
		else z->son[z->son[1]==y]=x;
		x->fa=z; pushup(y);
	}
	void PreChange(node *x) {//change_from_root
		static node *ids[maxn];
		int i,k;
		for (k=0; !x->isroot; k++)
			ids[k]=x,x=x->fa;
		ids[k++]=x;
		rREP(i,k) pushdown(ids[i]);
	}
	void splay(node *x) { //to root
		PreChange(x);
		while (!x->isroot) {
			node *y=x->fa,*z=y->fa;
			int rx=(y->son[0]==x);
			if (y->isroot) rotate(x,rx);
			else {
				int ry=z->son[0]==y;
				if (rx==ry) rotate(y,ry);
				else rotate(x,rx);
				rotate(x,ry);
			}
		} pushup(x);
	}
	node *access(node *x) {
		node *y=nullptr;
		for (; x!=nullptr; x=x->fa) {
			splay(x);
			if (x->son[1]!=nullptr)
				x->son[1]->isroot=true;
			if (y!=nullptr) y->isroot=false;
			x->son[1]=y;
			y=x; pushup(x);
		} return y;
	}
	bool judge(node *u,node *v) {
		while (u->fa!=nullptr) u=u->fa;
		while (v->fa!=nullptr) v=v->fa;
		return u==v;
	}
	void makeroot(node *x) {
		access(x); splay(x);
		Reverse(x);
	}
	bool link(int u,int v) {
		if (judge(&T[u],&T[v])) return 1;
		makeroot(&T[u]); T[u].fa=&T[v];
		return 0;
	}
	bool cut(int u,int v) {
		makeroot(&T[u]); splay(&T[v]);
		if (T[v].son[0]) {
			T[v].son[0]->fa=T[v].fa;
			T[v].son[0]->isroot=true;
		}
		T[v].fa=T[v].son[0]=nullptr;
		pushup(&T[v]);
		return 0;
	}
	bool add(int u,int v,int val) {
		makeroot(&T[u]); access(&T[v]); splay(&T[v]);
		AddValueChain(&T[v],val);
		return 0;
	}
	bool change(int u,int v,int val) {
		makeroot(&T[u]); access(&T[v]); splay(&T[v]);
		MakeSameChain(&T[v],val);
		return 0;
	}
	info ask(int u,int v) {
		makeroot(&T[u]); access(&T[v]); splay(&T[v]);
		return T[v].chain;
	}
};
vector<int> edge[maxn];
void dfs(int x,int fa) {
	if (fa) LCT::T[x].fa=&LCT::T[fa];
	LCT::T[x].isroot=1;
	for (int v:edge[x]) if (v!=fa) dfs(v,x);
}
int main() {
	int x=0;
	int T,_; T=1;
	// scanf("%d",&T);
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
		while (m--) {
			int k;
			scanf("%d",&k);
			int x,y;
			if (k==1) {
				int x0,y0;
				scanf("%d%d%d%d",&x,&y,&x0,&y0);
				LCT::cut(x,y);
				LCT::link(x0,y0);
			} else if (k==2) {
				int val;
				scanf("%d%d%d",&x,&y,&val);
				LCT::change(x,y,val);
			} else if (k==3) {
				int val;
				scanf("%d%d%d",&x,&y,&val);
				LCT::add(x,y,val);
			} else if (k==4) {
				scanf("%d%d",&x,&y);
				LCT::info info=LCT::ask(x,y);
			}
		}
		FOR(i,1,n) edge[i].clear();
	}
}
/*
*/