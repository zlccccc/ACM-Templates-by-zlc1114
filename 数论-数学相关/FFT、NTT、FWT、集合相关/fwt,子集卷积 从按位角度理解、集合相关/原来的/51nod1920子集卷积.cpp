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
#include <bitset>
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
const LL M=1e9+7;//206158430209;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}
/*
F0=(a+b+c+d)*(a+b+c+d)
F1=(a-b+c-d)*(a-b+c-d)
F2=(a+d)*(a+d)
F3=(a-d)*(a-d)
F4=b*b
F5=c*c
*/
int A[10][maxn];
LL S[10][7][28];//同时存在的每层最多6个 
void solve(int depth,int X[],LL T[]){//pos
	if (!depth) {T[0]=1ll*X[0]*X[0];return;}
	int t=1<<(2*(depth-1)),p=depth;
	int *X0=X,*X1=X+t,*X2=X+t*2,*X3=X+t*3;
	int *P=A[depth-1];
	int *S0=P,*S1=P+t,*S2=P+t*2,*S3=P+t*3,*S4=P+t*4,*S5=P+t*5;
	int i,j,k;
	REP(i,t){
		S0[i]=X0[i]+X1[i]+X2[i]+X3[i];
		S1[i]=X0[i]-X1[i]+X2[i]-X3[i];
		S2[i]=X0[i]+X3[i];
		S3[i]=X0[i]-X3[i];
		S4[i]=X1[i];
		S5[i]=X2[i];
	}
	LL *T0=S[depth-1][0],*T1=S[depth-1][1],*T2=S[depth-1][2],*T3=S[depth-1][3],*T4=S[depth-1][4],*T5=S[depth-1][5];
	solve(depth-1,S0,T0);
	solve(depth-1,S1,T1);
	solve(depth-1,S2,T2);
	solve(depth-1,S3,T3);
	solve(depth-1,S4,T4);
	solve(depth-1,S5,T5);
	FOR(i,0,depth*3) T[i]=0;
	LL H0,H1,H2,H3;
	FOR(i,0,depth*3-3){
		H0=(T2[i]+T3[i])/2+T4[i]+T5[i];
		H1=(T0[i]-T1[i]-T2[i]+T3[i])/2;
		H2=(T0[i]+T1[i])/2-H0;
		H3=(T2[i]-T3[i])/2;
		T[i]+=H0;T[i+1]+=H1;T[i+2]+=H2;T[i+3]+=H3;
	}
}
LL ans[28];
int main(){
	int n,m;
	int i,j,k;
	scanf("%d%d",&n,&m);
	REP(i,n){
		int now=0;
		REP(j,m) scanf("%d",&k),now=now<<2|k;
		A[9][now]++;
	}
	solve(9,A[9],ans);
	FOR(i,0,m*3) printf("%lld ",ans[i]);
}
/*
*/
