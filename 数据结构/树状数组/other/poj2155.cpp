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
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3f;
const LL M=1e9+7;
const LL maxn=1007;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a) {return a>0?a:-a;}


int n,m;
int c[maxn][maxn];
int lowbit(int x){return x&-x;}
void update(int x1,int y1){
	int x=x1;
	while (x<=n){
		int y=y1;
		while (y<=n){
			c[x][y]^=1;
			y+=lowbit(y);
		}
		x+=lowbit(x);
	}
}
int sum(int x1,int y1){
	int ret=0;
	int x=x1;
	while (x){
		int y=y1;
		while (y){
			ret^=c[x][y];
			y^=lowbit(y);
		}
		x^=lowbit(x);
	}
	return ret;
}
void init(){
	int i,j;
	FOR(i,1,n)
		FOR(j,1,n) c[i][j]=0;
}
int T;
char s[10];
int i,j,k;
int x1,x2,y1,y2;
int main()
{
	scanf("%d",&T);
	while (T--){
		scanf("%d%d",&n,&m);
		init();
		REP(i,m){
			scanf("%s",s);
			if (s[0]=='C'){
				scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
				update(x1,y1);
				update(x1,y2+1);
				update(x2+1,y1);
				update(x2+1,y2+1);
			}
			else {
				scanf("%d%d",&x1,&y1);
				printf("%d\n",sum(x1,y1));
			}
		}
		puts("");
	}
}
/*
*/
