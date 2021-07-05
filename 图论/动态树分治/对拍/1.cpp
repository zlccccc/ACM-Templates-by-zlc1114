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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}

int n,m;
int i,j;
int l,r,k,o;
int u,v;
int a[8];
int Ti,Si;
bool mark[maxn],Mark[maxn];
int A[maxn];
int main(){
    int now=clock();
	int t=1,n,m,q;
	n=m=5;q=10000;
//	printf("%d\n",t);
	srand(time(0));
//	printf("%d\n",t);
	while (t--){
        printf("%d %d\n",n,m);
        FOR(i,1,n) A[i]=i;
        random_shuffle(A+1,A+1+n);
        FOR(i,1,n) printf("%d ",A[i]);puts("");
        FOR(i,2,n) printf("%d %d %d\n",rand()%(i-1)+1,i,rand()%20+1);
        FOR(i,1,m){
            if (rand()&1==2){
                printf("! %d %d\n",rand()%n+1,rand()%10);
            }else{
                int l,r; l=rand()%n+1,r=rand()%n+1;
                if (l>r) swap(l,r);
                printf("1\n%d %d %d\n",l,r,rand()%n+1);
            }
        }
	}
}
/*
*/
