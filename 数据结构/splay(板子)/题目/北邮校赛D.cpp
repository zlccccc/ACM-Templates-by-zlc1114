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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}
 
int a[maxn];
struct splay_tree{
	struct node{
		int son[2],size;
		int min,max,val;
		bool rev;
		void init(int _val){
			val=min=max=_val;size=1;
			if (_val==INF) max=-INF;
			son[0]=son[1]=rev=0;
		}
	}T[maxn];
	int fa[maxn],root,tot;
	void pushup(int x){
		T[x].min=T[x].max=T[x].val;T[x].size=1;
		if (T[x].val==INF) T[x].max=-INF;
		if (T[x].son[0]){
			T[x].min=min(T[x].min,T[T[x].son[0]].min);
			T[x].max=max(T[x].max,T[T[x].son[0]].max);
			T[x].size+=T[T[x].son[0]].size;
		}
		if (T[x].son[1]){
			T[x].min=min(T[x].min,T[T[x].son[1]].min);
			T[x].max=max(T[x].max,T[T[x].son[1]].max);
			T[x].size+=T[T[x].son[1]].size;
		}
	}
	void pushdown(int x){
		if (x==0) return;
		if (T[x].rev){
			if (T[x].son[0]) T[T[x].son[0]].rev^=1;
			if (T[x].son[1]) T[T[x].son[1]].rev^=1;
			swap(T[x].son[0],T[x].son[1]);
			T[x].rev=0;
		}
	}
	void rotate(int x,int kind){
		int y=fa[x],z=fa[y];
		T[y].son[!kind]=T[x].son[kind],fa[T[x].son[kind]]=y;
		T[x].son[kind]=y;fa[y]=x;
		T[z].son[T[z].son[1]==y]=x,fa[x]=z;
		pushup(y);
	}
	void splay(int x,int goal){
		if (x==goal) return;
		while (fa[x]!=goal){
			int y=fa[x],z=fa[y];
			pushdown(z),pushdown(y),pushdown(x);
			int rx=T[y].son[0]==x,ry=T[z].son[0]==y;
			if (z==goal) rotate(x,rx);
			else{
				if (rx==ry) rotate(y,ry);
				else rotate(x,rx);
				rotate(x,ry);
			}
		}
		pushup(x);
		if (goal==0) root=x;
	}
	int select(int pos){
		int u=root;
		pushdown(u);
		while (T[T[u].son[0]].size!=pos){
			if (pos<T[T[u].son[0]].size) u=T[u].son[0];
			else {
				pos-=T[T[u].son[0]].size+1;
				u=T[u].son[1];
			}
			pushdown(u);
		}
		return u;
	}

	void exchange(int l1,int r1,int l2,int r2){
		if (l1>l2) {swap(l1,l2);swap(r1,r2);}
		int u=select(l1-1),v=select(r1+1);
		splay(u,0);splay(v,u);
		int tmp=T[v].son[0];T[v].son[0]=0;
		pushup(v);pushup(u);
		l2-=T[tmp].size;r2-=T[tmp].size;
		u=select(l2-1),v=select(r2+1);
		splay(u,0);splay(v,u);
		fa[tmp]=v;
		swap(T[v].son[0],tmp);
		pushup(v);pushup(u);
		u=select(l1-1),v=select(l1);
		splay(u,0);splay(v,u);
		fa[tmp]=v;
		T[v].son[0]=tmp;
		pushup(v);pushup(u);
	}
	void reverse(int l,int r){
		int u=select(l-1),v=select(r+1);
		splay(u,0);splay(v,u);
		T[T[v].son[0]].rev^=1;
	}
	int dfs(int x,int k){
		if (x==0) return 0;
		if (T[x].min!=INF&&T[x].min>=k) return 0;
		if (T[x].max!=-INF&&T[x].max<k) return T[x].size;
		int ret=T[x].val<k;
		if (T[x].son[0]) ret+=dfs(T[x].son[0],k);
		if (T[x].son[1]) ret+=dfs(T[x].son[1],k);
		return ret;
	}
	int query(int l,int r,int k){
		int u=select(l-1),v=select(r+1);
		splay(u,0);splay(v,u);
		return dfs(T[v].son[0],k);
	}
	int build(int l,int r){
		if (l>r) return 0;
		if (l==r) return l;
		int mid=(l+r)/2;
		T[mid].son[0]=build(l,mid-1);
		T[mid].son[1]=build(mid+1,r);
		fa[T[mid].son[0]]=fa[T[mid].son[1]]=mid;
		pushup(mid);
		return mid;
	}
	void init(int n){
		tot=0;
		int i;
		T[tot++].init(INF);
		T[tot++].init(INF);
		FOR(i,1,n) T[tot++].init(a[i]);
		T[tot++].init(INF);
		root=build(1,tot-1);
		fa[0]=0;T[0].son[1]=root;T[0].size=0;
	}
	void print(int now=-1){
		if (now==-1) now=root;
		pushdown(now);
		if (T[now].son[0]) print(T[now].son[0]);
//		printf("val-%d	%d %d  size=%d\n",T[now].val,T[now].min,T[now].max,T[now].size);
		printf("%d ",T[now].val);
		if (T[now].son[1]) print(T[now].son[1]);
		pushup(now);
	}
}T;
int n,m;
int i;
char s[50];
int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&a[i]);
	T.init(n);
	scanf("%d",&m);
	while (m--){
		scanf("%s",s);
		if (s[0]=='S'){
			int l1,l2,r1,r2;
			scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
			T.exchange(l1,r1,l2,r2);
		}
		if (s[0]=='R'){
			int l,r;
			scanf("%d%d",&l,&r);
			T.reverse(l,r);
		}
		if (s[0]=='A'){
			int l,r,k;
			scanf("%d%d%d",&l,&r,&k);
			printf("%d\n",T.query(l,r,k));
		}
//		T.print();puts("");
	}
}
