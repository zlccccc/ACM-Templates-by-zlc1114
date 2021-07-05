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
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

int n,m;
double a[maxn];
double hash[maxn];
int b[maxn];
int ans;
int i,j,k;
int size;
int main(){
	while (~scanf("%d",&n)){
		REP(i,n) scanf("%lf",&a[i]);
		REP(i,n) hash[i]=a[i];
		sort(hash,hash+n);
		size=unique(hash,hash+n)-hash;
		REP(i,n) b[i]=lower_bound(hash,hash+size,a[i])-hash+1;//0,1...n
		REP(i,size) printf("%.2lf ",hash[i]);
		puts("");
		REP(i,n) printf("%d ",b[i]);
		puts("");
	}
}
