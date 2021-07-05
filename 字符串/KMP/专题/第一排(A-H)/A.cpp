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
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int T;
int n,m;
int i,j,k;
int a[maxn],b[maxn];
int fail[maxn];
int main(){
	scanf("%d",&T);
	while (T--){
		scanf("%d%d",&n,&m);
		FOR(i,1,n) scanf("%d",&a[i]);
		FOR(i,1,m) scanf("%d",&b[i]);
		fail[0]=fail[1]=0;
		FOR(i,2,m){
			j=fail[i-1];
			while (j&&b[j+1]!=b[i]) j=fail[j];
			if (b[j+1]==b[i]) fail[i]=j+1;
			else fail[i]=j;
		}
		j=0;bool mark=0;
		FOR(i,1,n){
			while (j&&a[i]!=b[j+1]) j=fail[j];
			if (a[i]==b[j+1]) j++;
			if (j==m) {
				printf("%d\n",i-m+1);
				mark=1;break;
			}
		}if (j!=m) puts("-1");
	}
}
/*
*/
