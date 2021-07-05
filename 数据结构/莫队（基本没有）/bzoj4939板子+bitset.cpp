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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

template<class T> 
bool read(T &num){
	char in;bool IsN=false;
	in=getchar();
	if (in==EOF) return false;
	while (in!= '-'&&(in<'0'||in>'9')) in=getchar();
	if (in=='-') {IsN=1;num=0;}
	else num=in-'0';
	while (in=getchar(),in>='0'&&in<='9') num=num*10+in-'0';
	if (IsN) num=-num;
	return 1;
}
int F[maxn];
const int MAXQ=30007;
struct BITSET{
	ULL a[1600];
	void change(int pos){
		a[pos>>6]^=1ull<<(pos&63);
	}
	int count(){
		int ret=0,i,j;
		REP(i,1600) ret+=F[a[i]&65535]+F[(a[i]>>16)&65535]+F[(a[i]>>32)&65535]+F[a[i]>>48];
		return ret;
	}
	void reset(){
		int i;
		REP(i,1600) a[i]=0;
	}
	void print(){
		int i;
		FOR(i,1,50){
			if ((a[0]>>i)&1) putchar('1');
			else putchar('0');
		}puts("");
	}
}now[MAXQ],all,ALL;
void Update(BITSET &A,BITSET &B){
	int i;
	REP(i,1600) A.a[i]&=B.a[i];
}
struct node{
	int l,r,id;
	node(int _l=0,int _r=0,int _id=0):l(_l),r(_r),id(_id){}
}Q[maxn];
int tot;
int BLOCK[maxn];
bool cmp(node a,node b){
	if (BLOCK[a.l]==BLOCK[b.l]) return a.r<b.r;
	return BLOCK[a.l]<BLOCK[b.l];
}
int ans[maxn];
int POS[maxn];
int A[maxn],H[maxn];
int L,R;
int main(){
	int n,m,M,i;
	FOR(i,1,65535) F[i]=F[i>>1]+(i&1);
	read(n);read(M);
	FOR(i,1,n) read(A[i]),H[i]=A[i];
	LL SIZE=sqrt(n); 
	FOR(i,1,n) BLOCK[i]=i/SIZE;
	sort(H+1,H+n+1);
	FOR(i,1,n) POS[i]=i;
	ALL.reset();
	FOR(i,1,n) A[i]=lower_bound(H+1,H+n+1,A[i])-H,ALL.change(i);
	while (M){
		m=min(30000,M);
		M-=m;
		tot=0;
		FOR(i,1,m){
			now[i]=ALL;ans[i]=0;
			int l,r;
			read(l);read(r);Q[tot++]=node(l,r,i);ans[i]+=(r-l+1);
			read(l);read(r);Q[tot++]=node(l,r,i);ans[i]+=(r-l+1);
			read(l);read(r);Q[tot++]=node(l,r,i);ans[i]+=(r-l+1);
		}
		L=1;R=0;
		all.reset();
		sort(Q,Q+tot,cmp);
		Q[tot++]=node(1,0,0);
		REP(i,tot){
			while (R<Q[i].r){R++;all.change(POS[A[R]]);POS[A[R]]++;}
			while (L>Q[i].l){L--;all.change(POS[A[L]]);POS[A[L]]++;}
			while (R>Q[i].r){POS[A[R]]--;all.change(POS[A[R]]);R--;}
			while (L<Q[i].l){POS[A[L]]--;all.change(POS[A[L]]);L++;}
			Update(now[Q[i].id],all);
		}
		FOR(i,1,m) ans[i]-=3*now[i].count();
		FOR(i,1,m) printf("%d\n",ans[i]); 
	}
}
/*
*/
