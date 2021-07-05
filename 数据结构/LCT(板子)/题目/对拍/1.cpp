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
pair<int,int> edge[1000000];
int main(){
	int t=1; 
	int MX=40;
	int n=1000,m=2000;
	srand(time(0));
	int all;
	printf("%d\n",t);
	while (t--){
		printf("%d %d\n",n,m);
		FOR(i,1,n) printf("%d ",rand()%MX-20);puts("");
		FOR(i,2,n) edge[i]=make_pair(rand()%(i-1)+1,i);
		FOR(i,2,n) printf("%d %d\n",edge[i].first,edge[i].second);
		REP(i,m){
			int k;
			k=rand()%4+1;
			if (k==5){
//				printf("1 2 1 2 1\n");
//				printf("1 %d %d\n",k,rand()%n+1,rand()%n+1);
			}else if (k==2){
				int t=rand()%n+1;
				printf("2 %d %d %d\n",rand()%n+1,rand()%n+1,rand()%MX-20);
			}else if (k==3){
				printf("3 %d %d %d\n",rand()%n+1,rand()%n+1,rand()%MX-20);
			}else{
				printf("4 %d %d\n",rand()%n+1,rand()%n+1);
			}
		}
		puts("");
	}
}
/*
*/
