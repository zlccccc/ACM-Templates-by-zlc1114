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
const LL maxn=8e5+7;
const double eps=0.00000001;
const double pi=acos(-1);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

const LL MOD=2281701377;
const LL g=3;
LL mul(LL x,LL y){
	return x*y%MOD;
}
LL poww(LL a,LL b){
	LL ret=1;
	for (;b;b>>=1,a=mul(a,a))
		if (b&1) ret=mul(ret,a);
	return ret;
}
void ntt(LL *A,int len,int inv){
	int i,j,k;
	for (i=1,j=len/2;i<len-1;i++){
		if (i<j) swap(A[i],A[j]);
		k=len/2;
		while (j>=k){
			j-=k;
			k/=2;
		}if (j<k) j+=k;
	}
	for (i=2;i<=len;i<<=1){
		LL wn=poww(g,(MOD-1)/i);
		if (inv==-1) wn=poww(wn,MOD-2);
		for (j=0;j<len;j+=i){
			LL w=1;
			for (k=j;k<j+i/2;k++){
				LL a=A[k],b=mul(w,A[k+i/2]);
				A[k]=(a+b)%MOD;
				A[k+i/2]=(a-b+MOD)%MOD;
				w=mul(w,wn);
			}
		}
	}
	if (inv==-1){
		LL vn=poww(len,MOD-2);
		REP(i,len) A[i]=mul(A[i],vn);
	}
}
int n,m,k;
LL sum[maxn];
LL A[maxn],B[maxn];
char a[maxn],b[maxn];
LL all[maxn];
void solve(char c,int len){
	int i,j;
	REP(i,len) A[i]=B[i]=0;
	REP(i,len) sum[i+1]=(a[i]==c);
	REP(i,len) sum[i+1]+=sum[i];
	REP(i,n) A[i]=(sum[min(n,i+k+1)]-sum[max(0,i-k)]>0);
	REP(i,m) B[i]=(b[m-i-1]==c);
//	REP(i,len) printf("%d",A[i]);puts("");
//	REP(i,len) printf("%d",sum[i]);puts("");
//	REP(i,len) printf("%d",B[i]);puts("");
	ntt(A,len,1);ntt(B,len,1);
	REP(i,len) A[i]=A[i]*B[i]%MOD;
	ntt(A,len,-1);
//	REP(i,len) printf("%d",A[i]);puts("");puts("");
	REP(i,len) all[i]+=A[i];
}
int ans;
int main(){
	scanf("%d%d%d",&n,&m,&k);
	scanf("%s%s",a,b);
	int len=1;
	while (len<=n+m) len<<=1;
	solve('A',len);
	solve('T',len);
	solve('C',len);
	solve('G',len);
	int i;
//	REP(i,len) printf("%d",all[i]);puts("");puts("");
	REP(i,len) ans+=(all[i]==m);
	printf("%d\n",ans);
}
/*
10 4 10
AGCAATTCAT
ACAT
*/
