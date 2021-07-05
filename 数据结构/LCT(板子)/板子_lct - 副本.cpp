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
	inline void MakeSame(info &_info,int value) {
		_info.max1=make_pair(value,_info.size);
		_info.max2=make_pair(-INF,0);
	}
	inline void MakeSame(tag &_tag,int value) {
		_tag.same=value;
	}
	inline void AddValue(info &_info,int value) {
		_info.max1.first+=value;
		if (_info.max2.first!=-INF) _info.max2.first+=value;
	}
	inline void AddValue(tag &_tag,int value) {
		_tag.add+=value;
		if (_tag.tagsame()) _tag.same+=value;
	}
	struct node {
		int son[2],fa;
		int val;
		info chain; tag chaintag;
		bool rev,isroot;//root=1:isroot
		void init(int _val) {
			val=_val;
			chain=info(val);
			chaintag=tag();
			rev=0; son[0]=son[1]=0;
			fa=0; isroot=1;
		}
	} T[maxn];
	void Reverse(int x) {
		T[x].rev^=1;
		swap(T[x].son[0],T[x].son[1]);
	}
	void AddValue(node &x,int val) {//Add_To_Node
		x.val+=val;
		AddValue(x.chain,val);
		AddValue(x.chaintag,val);
	}
	void MakeSame(node &x,int val) {
		x.val=val;
		MakeSame(x.chain,val);
		MakeSame(x.chaintag,val);
	}
	void pushup(int x) {
		T[x].chain=info(T[x].val);//clear
		if (T[x].son[0])
			T[x].chain=merge(T[T[x].son[0]].chain,T[x].chain);
		if (T[x].son[1])
			T[x].chain=merge(T[x].chain,T[T[x].son[1]].chain);
	}
	void pushdown(int x) {
		if (T[x].rev) {
			if (T[x].son[0]) Reverse(T[x].son[0]);
			if (T[x].son[1]) Reverse(T[x].son[1]);
			T[x].rev=0;
		}
		if (T[x].chaintag.tagadd()) {
			if (T[x].son[0]) AddValue(T[T[x].son[0]],T[x].chaintag.add);
			if (T[x].son[1]) AddValue(T[T[x].son[1]],T[x].chaintag.add);
			T[x].chaintag.add=0;
		}
		if (T[x].chaintag.tagsame()) {
			if (T[x].son[0]) MakeSame(T[T[x].son[0]],T[x].chaintag.same);
			if (T[x].son[1]) MakeSame(T[T[x].son[1]],T[x].chaintag.same);
			T[x].chaintag.same=-INF;
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
		AddValue(T[v],val);
		return 0;
	}
	bool change(int u,int v,int val) {
		makeroot(u); access(v); splay(v);
		MakeSame(T[v],val);
		return 0;
	}
	pair<int,int> ask(int u,int v) {
		makeroot(u); access(v); splay(v);
		return T[v].chain.max2;
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