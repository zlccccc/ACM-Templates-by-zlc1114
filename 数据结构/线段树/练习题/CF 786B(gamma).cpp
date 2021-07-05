#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=100007;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a) {return a>0?a:-a;}


const int P=maxn*4;
struct node{
	int n;
	LL d;
	node(){}
	node(int a,LL b):n(a),d(b){}
	const bool operator<(const node &a)const{
		if (d==a.d) return n<a.n;
		return d>a.d;
	}
};
vector<node> edge[maxn*8];//from和to不在同一点出现 
LL dis[maxn*8];
struct Tnode{
	int left,right;
}tree[maxn*8];
void addedge(int u,int v,LL val){
	edge[u].push_back(node(v,val));
}
void build(int x,int l,int r){
	tree[x].left=l;tree[x].right=r;
	if (l==r){
		addedge(x+P,x,0);
		addedge(x,x+P,0);
	}
	else if (l!=r){
		int mid=(l+r)/2;
		build(x<<1,l,mid);
		addedge(x<<1,x,0);//up 
		addedge(x+P,(x<<1)+P,0);//dowm
		build(x<<1|1,mid+1,r);
		addedge(x<<1|1,x,0);//up 
		addedge(x+P,(x<<1|1)+P,0);//dowm
	}
}
void add1(int x,int l,int r,int v,LL val){
	int L=tree[x].left,R=tree[x].right;
	if (l<=L&&R<=r){
		addedge(v,x+P,val);
	}else{
		int mid=(L+R)/2;
		if (mid>=l) add1(x<<1,l,r,v,val);
		if (r>mid) add1(x<<1|1,l,r,v,val);
	}
}
void add2(int x,int l,int r,int v,LL val){
	int L=tree[x].left,R=tree[x].right;
	if (l<=L&&R<=r){
		addedge(x,v+P,val);
	}else{
		int mid=(L+R)/2;
		if (mid>=l) add2(x<<1,l,r,v,val);
		if (r>mid) add2(x<<1|1,l,r,v,val);
	}
}
int find(int x,int i){
	if (tree[x].left==tree[x].right) return x;
	int mid=(tree[x].left+tree[x].right)/2;
	if (mid>=i) return find(x<<1,i);
	else return find(x<<1|1,i);
}
void dijkstra(int s){
	int i;
	priority_queue<node> Q;
	REP(i,maxn*8) dis[i]=INFF;
	dis[s]=0;Q.push(node(s,0));
	while (!Q.empty()){
		node x=Q.top();Q.pop();
		REP(i,edge[x.n].size()){
			node y=edge[x.n][i];
			if (dis[y.n]>dis[x.n]+y.d){
				dis[y.n]=dis[x.n]+y.d;
				Q.push(node(y.n,dis[y.n]));
			}
		}
	}
}
int n,m,s;
int i,j,k;
int l,r,u,v;
LL val;
int pos[maxn];
int main()
{
	scanf("%d%d%d",&n,&m,&s);
	build(1,1,n);
	FOR(i,1,n) pos[i]=find(1,i);
	REP(i,m){
		scanf("%d",&k);
		if (k==1){
			scanf("%d%d%I64d",&v,&l,&val);
			add1(1,l,l,pos[v],val);
		}else if (k==2){
			scanf("%d%d%d%I64d",&v,&l,&r,&val);
			add1(1,l,r,pos[v],val);
		}else if (k==3){
			scanf("%d%d%d%I64d",&v,&l,&r,&val);
			add2(1,l,r,pos[v],val);
		}
	}
	dijkstra(pos[s]);
	FOR(i,1,n) {
		if (dis[pos[i]]==INFF) printf("-1 ");
		else printf("%I64d ",dis[pos[i]]);
	}
}
/*
*/
