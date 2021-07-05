#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <ctime>
#include <set>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL N=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}

int n,m;
int i,j;
int l,r,k,o;
int u,v;
int a[8];
int main(){
	int t=5; 
	int MX=1000000;
	int n=5000,m=1000;
	srand(time(0));
	int all;
	printf("%d\n",t);
	while (t--){
		printf("%d %d\n",n,m);
		FOR(i,1,n) printf("%d ",rand()%MX);puts("");
//		FOR(i,1,n) printf("%d ",rand()*10000+rand());puts("");
		REP(i,m){
			int k;
			k=rand()%2;
//			k=1;
			if (k==0){
				printf("C %d %d\n",rand()%n+1,rand()%MX);
//				printf("C 1 %d\n",i);
			}
			if (k==1){
				int l,r;
				l=rand()%n+1;r=rand()%n+1;
				if (l>r) swap(l,r);
				printf("Q %d %d %d\n",l,r,rand()%(r-l+1)+1);
			}
		}
	}
}
/*
*/
