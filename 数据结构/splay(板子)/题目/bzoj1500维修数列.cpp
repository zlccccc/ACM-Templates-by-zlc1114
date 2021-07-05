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
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=5e5+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}

const int MAXM=5e5+7;
int A[maxn];
struct splay_tree {
	struct node {
		int val,lsum,rsum,sum,maxsum,same;
		int size; bool rev;
		int son[2];
		void init(int _val) {
			maxsum=sum=val=_val; size=1;
			lsum=rsum=max(0,_val);
			rev=0; son[0]=son[1]=0;
			same=INF;
		}
	} T[maxn];
	int fa[maxn],tot,root;
	inline void updmax(int &x,int y) {
		if (x<y) x=y;
	}
	void pushup(int x) {
		T[x].maxsum=T[x].sum=T[x].val;
		T[x].lsum=T[x].rsum=0; T[x].size=1;
		int l=T[x].son[0],r=T[x].son[1];
		int L,R,M; L=R=M=T[x].val;
		if (l) {
			T[x].sum+=T[l].sum;
			updmax(T[x].maxsum,T[l].maxsum);
			T[x].size+=T[l].size;
			T[x].lsum=T[l].lsum;
			M+=T[l].rsum; L+=T[l].sum; R+=T[l].rsum;
		} if (r) {
			T[x].sum+=T[r].sum;
			updmax(T[x].maxsum,T[r].maxsum);
			T[x].size+=T[r].size;
			T[x].rsum=T[r].rsum;
			M+=T[r].lsum; R+=T[r].sum; L+=T[r].lsum;
		} updmax(T[x].rsum,R);
		updmax(T[x].lsum,L);
		updmax(T[x].maxsum,M);
	}
	void rev(int x) {
		if (!x||T[x].same!=INF) return;
		T[x].rev^=1;
		swap(T[x].son[0],T[x].son[1]);
		swap(T[x].rsum,T[x].lsum);
	}
	void makesame(int x,int val) {
		if (!x) return;
		T[x].val=T[x].same=val; T[x].rev=0;//not essential
		T[x].sum=T[x].maxsum=T[x].size*val;
		updmax(T[x].maxsum,val);
		T[x].lsum=T[x].rsum=max(0,T[x].sum);
	}
	void pushdown(int x) {
		if (x==0) return;
		int l=T[x].son[0],r=T[x].son[1];
		if (T[x].same!=INF) {
			if (l) makesame(l,T[x].same);
			if (r) makesame(r,T[x].same);
			T[x].same=INF;
		} if (T[x].rev) {
			if (l) rev(l);
			if (r) rev(r);
			T[x].rev=0;//must update
		}
	}
	void rotate(int x,int kind) {
		int y=fa[x],z=fa[y];
		T[y].son[!kind]=T[x].son[kind],fa[T[x].son[kind]]=y;
		T[x].son[kind]=y; fa[y]=x;
		T[z].son[T[z].son[1]==y]=x,fa[x]=z;
		pushup(y);
	}
	void splay(int x,int goal) {
		if (x==goal) return;
		while (fa[x]!=goal) {
			int y=fa[x],z=fa[y];
			pushdown(z); pushdown(y); pushdown(x);
			int rx=T[y].son[0]==x,ry=T[z].son[0]==y;
			if (z==goal) rotate(x,rx);
			else {
				if (rx==ry) rotate(y,ry);
				else rotate(x,rx);
				rotate(x,ry);
			}
		} pushup(x);
		if (goal==0) root=x;
	}
	int select(int pos) {
		int u=root;
		pushdown(u);
		while (T[T[u].son[0]].size!=pos) {
			if (pos<T[T[u].son[0]].size) u=T[u].son[0];
			else {
				pos-=T[T[u].son[0]].size+1;
				u=T[u].son[1];
			} pushdown(u);
		} return u;
	}
	int delbuf[MAXM],bufs;
	int build(int l,int r) { //add_list
		if (l>r) return 0;
		++tot; if (tot==MAXM) tot=1;
		int ret=delbuf[tot];
		int mid=(l+r)/2;
		T[ret].init(A[mid]);
		if (l==r) return ret;
		int ls=build(l,mid-1);
		int rs=build(mid+1,r);
		if (ls) fa[ls]=ret,T[ret].son[0]=ls;
		if (rs) fa[rs]=ret,T[ret].son[1]=rs;
		pushup(ret);
		return ret;
	}
	void del(int x) {
		if (x==0) return;
		bufs++; if (bufs==MAXM) bufs=1;
		delbuf[bufs]=x;
		del(T[x].son[0]);
		del(T[x].son[1]);
	}
	void init(int n) {
		int i; tot=0;
		REP(i,MAXM) delbuf[i]=i;
		rFOR(i,1,n) A[i+1]=A[i];
		A[1]=A[n+2]=-INF;
		root=build(1,n+2);
		fa[root]=0; T[0].init(-INF);
		fa[0]=0; T[0].son[1]=root; T[0].size=0;
	}

	void Ins(int k,int cnt) {
		int i;
		FOR(i,1,cnt) scanf("%d",&A[i]);
		int u=select(k),v=select(k+1);
		splay(u,0); splay(v,u);
		T[v].son[0]=build(1,cnt);
		fa[T[v].son[0]]=v;
		pushup(v); pushup(u);
	}
	void Del(int k,int cnt) {
		int u=select(k-1),v=select(k+cnt);
//        printf("%d(%d) - %d(%d)\n",u,k-1,v,k+cnt);
		splay(u,0); splay(v,u);
		del(T[v].son[0]);
		T[v].son[0]=0;
		pushup(v); pushup(u);
	}
	void Same(int k,int cnt,int val) {
		int u=select(k-1),v=select(k+cnt);
		splay(u,0); splay(v,u);
		makesame(T[v].son[0],val);
		pushup(v); pushup(u);
	}
	void Rev(int k,int cnt) {
		int u=select(k-1),v=select(k+cnt);
		splay(u,0); splay(v,u);
		rev(T[v].son[0]);
		pushup(v); pushup(u);
	}
	void Getsum(int k,int cnt) {
		int u=select(k-1),v=select(k+cnt);
		splay(u,0); splay(v,u);
		printf("%d\n",T[T[v].son[0]].sum);
	}
	void Maxsum() {
		if (T[root].maxsum==0) puts("0");
		else printf("%d\n",T[root].maxsum);
	}

	void print(int now) {
		if (!now) return;
		pushdown(now);
		print(T[now].son[0]);
		printf("%d(p:%d) ",T[now].val,now);
		print(T[now].son[1]);
		pushup(now);
	} void print() {
		print(root); puts("");
	}
} Tree;
char op[20];
int main() {
	int m,n,i;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%d",&A[i]);
	Tree.init(n);
	REP(i,m) {
		scanf("%s",op);
		if (op[0]=='I') {
			int pos,tot;
			scanf("%d%d",&pos,&tot);
			Tree.Ins(pos,tot);
		} if (op[0]=='D') {
			int pos,tot;
			scanf("%d%d",&pos,&tot);
			Tree.Del(pos,tot);
		} if (op[0]=='M'&&op[2]=='K') {
			int pos,tot,c;
			scanf("%d%d%d",&pos,&tot,&c);
			Tree.Same(pos,tot,c);
		} if (op[0]=='R') {
			int pos,tot;
			scanf("%d%d",&pos,&tot);
			Tree.Rev(pos,tot);
		} if (op[0]=='G') {
			int pos,tot;
			scanf("%d%d",&pos,&tot);
			Tree.Getsum(pos,tot);
		} if (op[0]=='M'&&op[2]=='X') {
			Tree.Maxsum();
		}
	}
	return 0;
}
/*
*/
