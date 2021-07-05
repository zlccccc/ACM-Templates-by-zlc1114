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
const LL maxn=2e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M; return ret;}

//dlx:求解精确覆盖
//link的意思是,r覆盖了c
//暴力枚举,n个点覆盖m个格子; 注意一定要init
struct DLX {
	const static int maxn=1e5+7;
	const static int maxd=1e4+7;
	int n,m,size;
	int U[maxn],D[maxn],R[maxn],L[maxn],col[maxn],row[maxn];
	int H[maxd],S[maxd];//S:cnt
	int ans[maxn];
	void init(int _n,int _m) {
		n=_n; m=_m; int i;
		FOR(i,0,m) {
			S[i]=0;
			U[i]=D[i]=i;
			L[i]=i-1,R[i]=i+1;
		} R[m]=0; L[0]=m;
		size=m;
		FOR(i,0,n) H[i]=-1;
	}
	void link(int r,int c) {
		S[col[++size]=c]++; row[size]=r;
		D[size]=D[c]; U[D[c]]=size;
		D[c]=size; U[size]=c;
		if (H[r]<0) H[r]=L[size]=R[size]=size;
		else {
			R[size]=R[H[r]];
			L[R[H[r]]]=size;
			L[size]=H[r];
			R[H[r]]=size;
		}
	}
	void remove(int c) {
		L[R[c]]=L[c]; R[L[c]]=R[c];
		for (int i=D[c]; i!=c; i=D[i])
			for (int j=R[i]; j!=i; j=R[j])
				U[D[j]]=U[j],D[U[j]]=D[j],S[col[j]]--;
	}
	void resume(int c) {
		for (int i=U[c]; i!=c; i=U[i])
			for (int j=L[i]; j!=i; j=L[j])
				U[D[j]]=D[U[j]]=j,S[col[j]]++;
		L[R[c]]=R[L[c]]=c;
	}
	//这里是找可行解; 最优解无法加估价函数剪枝
	char g[maxn];
	bool dance(int pos) {
		if (R[0]==0) {
			int i,j;
			REP(i,pos) g[(ans[i]-1)/16]=(ans[i]-1)%16+'A';
			REP(i,16) {REP(j,16) putchar(g[i*16+j]); puts("");}
			return 1;
		}
		// cnt,pos:选择的个数; ans:选择的值(列)
		// if (pos>=cnt&&cnt!=INF) return;
		// if (R[0]==0) {cnt=min(cnt,pos); return;}
		int c=R[0];
		for (int i=R[0]; i; i=R[i])
			if (S[i]<S[c]) c=i;
		remove(c);
		for (int i=D[c]; i!=c; i=D[i]) {
			ans[pos]=row[i];
			for (int j=R[i]; j!=i; j=R[j]) remove(col[j]);
			if (dance(pos+1)) return 1;
			for (int j=L[i]; j!=i; j=L[j]) resume(col[j]);
		} resume(c);
		return 0;
	}
} dlx;

char g[27][27];
int n,m;
void add(int x,int y,int k) {
	int r=(x*16+y)*16+k;
	dlx.link(r,16*16*0+x*16+y+1);//position
	dlx.link(r,16*16*1+x*16+k);//行
	dlx.link(r,16*16*2+y*16+k);//列
	dlx.link(r,16*16*3+(x/4*4+y/4)*16+k);//块
}
int main() {
	int i,j,k;
	while (~scanf("%s",g[0])) {
		rep(i,1,16) scanf("%s",g[i]);
		dlx.init(16*16*16,16*16*4);
		REP(i,16) REP(j,16) FOR(k,1,16) {
			if (g[i][j]=='-'||g[i][j]=='A'-1+k)
				add(i,j,k);
		}
		static int x=0;
		if (x) puts(""); else x=1;
		dlx.dance(0);
	}
}
/*
*/
