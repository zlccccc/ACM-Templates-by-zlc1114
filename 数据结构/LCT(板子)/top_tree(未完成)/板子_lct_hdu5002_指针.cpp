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
		int size;
		pii max1,max2;
		info(int _val=-INF,int _cnt=1,int _size=1):
			size(_size),max1(make_pair(_val,_cnt)),max2(make_pair(-INF,0)) {}
		void print() {
			debug(" debug: infomation: max=(%d,%d)(%d,%d) size=%d\n",max1.first,max1.second,max2.first,max2.second,size);
		}
	};
	struct tag {
		int same,add;//same:lazy
		tag() {same=-INF; add=0;}
		bool tagadd() {return (add!=0);}
		bool tagsame() {return (same!=-INF);}
	};
	//info_merge
	inline void merge(info &x,pii value) {
		if (x.max1.first==value.first)
			return (void)(x.max1.second+=value.second);
		if (x.max1<value) swap(x.max1,value);
		if (x.max2.first==value.first)
			return (void)(x.max2.second+=value.second);
		if (x.max2<value) swap(x.max2,value);
	}
	info merge(const info &x,const info &y) {
		info ret=x;
		ret.size+=y.size;
		merge(ret,y.max1);
		merge(ret,y.max2);
		return ret;
	}
	//info_update and tag_update
	inline void MakeSame(info &_info,tag &_tag,int value) {
		_info.max1=make_pair(value,_info.size);
		_info.max2=make_pair(-INF,0);
		_tag.same=value;
	}
	inline void AddValue(info &_info,tag &_tag,int value) {
		_info.max1.first+=value;
		_tag.add+=value;
		if (_info.max2.first!=-INF) _info.max2.first+=value;
		if (_tag.tagsame()) _tag.same+=value;
	}
	struct node {
		node *son[2],*fa;
		int val;
		info chain; tag chaintag;
		bool rev,isroot;//root=1:isroot
		void init(int _val) {
			val=_val;
			chain=info(val);
			chaintag=tag();
			rev=0; isroot=1;
			son[0]=son[1]=fa=nullptr;
		}
	} T[maxn];
	void Reverse(node *x) {
		x->rev^=1;
		swap(x->son[0],x->son[1]);
	}
	void AddValue(node *x,int val) {//Add_To_Node
		x->val+=val;
		AddValue(x->chain,x->chaintag,val);
	}
	void MakeSame(node *x,int val) {
		x->val=val;
		MakeSame(x->chain,x->chaintag,val);
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
		if (x->chaintag.tagadd()) {
			if (x->son[0]!=nullptr) AddValue(x->son[0],x->chaintag.add);
			if (x->son[1]!=nullptr) AddValue(x->son[1],x->chaintag.add);
			x->chaintag.add=0;
		}
		if (x->chaintag.tagsame()) {
			if (x->son[0]!=nullptr) MakeSame(x->son[0],x->chaintag.same);
			if (x->son[1]!=nullptr) MakeSame(x->son[1],x->chaintag.same);
			x->chaintag.same=-INF;
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
		AddValue(&T[v],val);
		return 0;
	}
	bool change(int u,int v,int val) {
		makeroot(&T[u]); access(&T[v]); splay(&T[v]);
		MakeSame(&T[v],val);
		return 0;
	}
	pair<int,int> ask(int u,int v) {
		makeroot(&T[u]); access(&T[v]); splay(&T[v]);
		return T[v].chain.max2;
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
				pair<int,int> t=LCT::ask(x,y);
				if (t.first==-INF) puts("ALL SAME");
				else printf("%d %d\n",t.first,t.second);
			}
		}
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