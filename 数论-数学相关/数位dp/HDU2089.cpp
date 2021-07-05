#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <cstring>
using namespace std;
#define REP(I,N) for (int I=0;I<N;I++)
#define rREP(I,N) for (int I=N-1;I>=0;I--)
#define rep(I,S,N) for (int I=S;I<N;I++)
#define rrep(I,S,N) for (int I=N-1;I>=S;I--)
#define FOR(I,S,N) for (int I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

LL n,m;
LL dp[20][3];//0:
LL i,j,k;
void init(){
	memset(dp,0,sizeof(dp));
	dp[0][0]=1;
	FOR(i,1,10){
		dp[i][0]=dp[i-1][0]*9-dp[i-1][1];//okay
		dp[i][1]=dp[i-1][0];//2......
		dp[i][2]=dp[i-1][0]+dp[i-1][1]+dp[i-1][2]*10;//not okay
	}
}
int A[20];
int calc(int a){
	int sum=a;
	int m=0;
	int ans=0;
	bool flag=false;
	while(a){
		A[++m]=a%10;
		a/=10;
	}
	A[m+1]=0;
	for (int i=m;i>=1;i--){
		ans+=dp[i-1][2]*A[i];
		if (flag){
			ans+=dp[i-1][0]*A[i];
		}else{
			if (A[i]>4) ans+=dp[i-1][0];
			if (A[i+1]==6&&A[i]>2) ans+=dp[i][1];
			if (A[i]>6) ans+=dp[i-1][1];
			if (A[i]==4||A[i]==2&&A[i+1]==6) flag=1;
		}
	}
	if (flag) ans++;
	return sum-ans;
}
int main(){
	int a,b;
	int l,r;
	init();
	while (~scanf("%d%d",&l,&r)&&(l||r)) printf("%d\n",calc(r)-calc(l-1));
}
/*
*/
