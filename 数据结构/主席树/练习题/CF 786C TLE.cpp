#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}

int n;
int a[maxn];
int num[maxn];
int ask(int i){
	int s=1,t=1,ret=0,cnt;
	while (t<=n){
		ret++;
		cnt=0;
		while (cnt<=i&&t<=n){
			if (!num[a[t]]){
				cnt++;
				num[a[t]]=1;
			}
			if (cnt<=i) t++;
//			printf("%d->%d(%d) ",t,num[a[t]],cnt);
		}
		while (s<t){
			num[a[s]]=0;
			s++;
		}
		num[a[t]]=0;
//		printf("%d %d\n",s,t);
	}
	return ret;
}
int i;
int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&a[i]);
	FOR(i,1,n) printf("%d ",ask(i));
}
/*
*/
