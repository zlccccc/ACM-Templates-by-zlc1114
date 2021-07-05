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
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M; return ret;}

namespace KDT {
	const double alpha=0.75;
	const int DIM=2;
	struct point {
		int A[DIM],max[DIM],min[DIM];
		int l,r; int size;
		void init() {
			l=r=0; initval();
		}
		void initval() {
			int i; size=1;
			REP(i,DIM) min[i]=max[i]=A[i];
		}
	} T[maxn*2]; int TOT;
	int Cur; int root;
	bool cmp(int x,int y) {
		return T[x].A[Cur]<T[y].A[Cur];
	}
	void update(int x) {
		int i; T[x].initval();
		int l=T[x].l,r=T[x].r;
		if (l) T[x].size+=T[l].size;
		if (r) T[x].size+=T[r].size;
		REP(i,DIM) {
			if (l) {
				T[x].max[i]=max(T[x].max[i],T[l].max[i]);
				T[x].min[i]=min(T[x].min[i],T[l].min[i]);
			} if (r) {
				T[x].max[i]=max(T[x].max[i],T[r].max[i]);
				T[x].min[i]=min(T[x].min[i],T[r].min[i]);
			}
		}
	}
	int id[maxn],tot;
	void build(int &x,int l,int r,int cur) {
		x=0; if (l>r) return;
		int m=(l+r)/2; Cur=cur;
		nth_element(id+l,id+m,id+r+1,cmp);
		x=id[m];
		build(T[x].l,l,m-1,cur^1);
		build(T[x].r,m+1,r,cur^1);
		update(x);
	}
	void getid(int x) {
		id[++tot]=x;
		if (T[x].l) getid(T[x].l);
		if (T[x].r) getid(T[x].r);
	}
	void rebuild(int &x,int cur) {
		tot=0; getid(x);
		build(x,1,tot,cur);
	}
	void insert(int &x,int now,int cur) {
		if (!x) {x=now; return;}
		Cur=cur;
		if (cmp(now,x)) insert(T[x].l,now,cur^1);
		else insert(T[x].r,now,cur^1);
		update(x);
		if (T[x].size*alpha+3<max(T[T[x].l].size,T[T[x].r].size))
			rebuild(x,cur);
	}
	void addnode(int &x,int px,int py) {
		TOT++; T[TOT].A[0]=px; T[TOT].A[1]=py;
		T[TOT].init(); insert(x,TOT,0);
	}
	int x,y,ans;
	int distance(int _x,int _y) {
		return abs(x-_x)+abs(y-_y);
	}
	int mindis(point &A) {
		int ret=0;
		if (A.min[0]>x) ret+=A.min[0]-x;
		if (A.max[0]<x) ret+=x-A.max[0];
		if (A.min[1]>y) ret+=A.min[1]-y;
		if (A.max[1]<y) ret+=y-A.max[1];
		return ret;
	}
	void query(int x) {
		if (!x) return;
		// printf("q:%d %d;size=%d\n",T[x].A[0],T[x].A[1],T[x].size);
		ans=min(ans,distance(T[x].A[0],T[x].A[1]));
		if (T[x].size==1) return;
		int l=T[x].l,r=T[x].r;
		int dl=INF,dr=INF;
		if (l) dl=mindis(T[l]);
		if (r) dr=mindis(T[r]);
		if (dl>dr) swap(l,r),swap(dl,dr);
		if (dl<ans) query(l);
		if (dr<ans) query(r);
	}
}
int n,m;
char buffer[36000000],*buf=buffer;
void read(int &x){
    for(x=0;*buf<48;++buf);
    while(*buf>=48)x=x*10+*buf-48,++buf;
}
int main() {
	int i;
    fread(buffer,1,36000000,stdin);
	read(n);read(m);
	FOR(i,1,n) {
		int x,y;
		read(x);read(y);
		KDT::T[i].A[0]=x;
		KDT::T[i].A[1]=y;
		KDT::id[i]=i;
	}KDT::TOT=n;
	KDT::build(KDT::root,1,n,0);
	FOR(i,1,m) {
		int op,x,y;
		read(op);read(x);read(y);
		if (op==1) KDT::addnode(KDT::root,x,y);
		else {
			KDT::x=x; KDT::y=y;
			KDT::ans=INF*2;
			KDT::query(KDT::root);
			printf("%d\n",KDT::ans);
		}
	}
}
/*
*/
