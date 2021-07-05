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
const LL maxn=4e5+7;
const double eps=0.00000001;
const double pi=acos(-1);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

const LL MOD=2281701377;
const LL g=3;
inline LL mul(LL x ,LL y ) {
	return x*y%MOD;
//    return ( x * y - ( long long ) ( x / ( long double ) MOD * y + 1e-3 ) * MOD + MOD ) % MOD ;
}
LL poww(LL a,LL b){
	LL ret=1;
	for (;b;b>>=1ll,a=mul(a,a))
		if (b&1) ret=mul(ret,a);
	return ret;
}
void ntt(LL *A,int len,int inv){//³­µÄ°å×Ó 
	int i,j,k;
	for (i=1,j=len/2;i<len-1;i++){
		if (i<j) swap(A[i],A[j]);
		k=len/2;
		while(j>=k){
			j-=k;
			k/=2;
		}if (j<k) j+=k;
	}
	for(i=2;i<=len;i<<=1){
		LL wn=poww(g,(MOD-1)/i);
		if (inv==-1) wn=poww(wn,MOD-2);
		for (j=0;j<len;j+=i){
			LL w=1;
			for (k=j;k<(j+i/2);k++){
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
LL x1[maxn],x2[maxn];
char a[maxn],b[maxn];
LL ans[maxn];
int main(){
	int n,q;
	int i,j,k;
	while (~scanf("%s%s",a,b)){
		int len1=strlen(a),len2=strlen(b),len=1;
		while(len<=len1+len2+1) len<<=1;
		REP(i,len1) x1[i]=a[len1-i-1]-'0';
		rep(i,len1,len) x1[i]=0;
		REP(i,len2) x2[i]=b[len2-i-1]-'0';
		rep(i,len2,len) x2[i]=0;
		ntt(x1,len,1);ntt(x2,len,1);
		REP(i,len) x1[i]=mul(x1[i],x2[i]);
		ntt(x1,len,-1);
		REP(i,len) ans[i]=x1[i];
		REP(i,len) ans[i+1]+=ans[i]/8,ans[i]%=8;
		while (ans[len-1]<=0&&len-1>0) len--;
		rREP(i,len) putchar(ans[i]+'0');
		puts("");
	}
}
/*
*/
