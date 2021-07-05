#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <cmath>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=2e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

struct node {
	int l,r,id;
} Q[maxn]; //new direction
int pos[maxn];
LL ans[maxn];
LL flag[maxn];
int a[maxn];
bool cmp(node a,node b) {
	if (pos[a.l]==pos[b.l]) return a.r<b.r;
	return pos[a.l]<pos[b.l];
}
int n,m,k;
int i,j;
LL Ans;
int L=1,R=0;
void add(int x) {
	Ans+=flag[a[x]^k];
	flag[a[x]]++;
}
void del(int x) {
	flag[a[x]]--;
	Ans-=flag[a[x]^k];
}
int main() {
	scanf("%d%d%d",&n,&m,&k);
	int sz=sqrt(n);
	FOR(i,1,n) {
		scanf("%d",&a[i]);
		a[i]^=a[i-1];
		pos[i]=i/sz;
	}
	FOR(i,1,m) {
		scanf("%d%d",&Q[i].l,&Q[i].r);
		Q[i].id=i;
	}
	sort(Q+1,Q+1+m,cmp);
	flag[0]=1;
	FOR(i,1,m) {
		while (L<Q[i].l) {del(L-1); L++;}
		while (L>Q[i].l) {L--; add(L-1);}
		while (R<Q[i].r) {R++; add(R);}
		while (R>Q[i].r) {del(R); R--;}
		ans[Q[i].id]=Ans;
	}
	FOR(i,1,m) printf("%I64d\n",ans[i]);
}
/*
*/
