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


struct Tnode{
	int left,right;
}treeY[maxn*4],treeX[maxn*4];
bool mark[maxn*4][maxn*4];
int locx[maxn],locy[maxn];
void buildY(int x,int y,int yl,int yr){
	treeY[y].left=yl;treeY[y].right=yr;
	mark[x][y]=0;
	if (yl==yr){
		locy[yl]=y;
		return;
	}
	int mid=(yl+yr)/2;
	buildY(x,y<<1,yl,mid);
	buildY(x,y<<1|1,mid+1,yr);
}
void buildX(int x,int n,int xl,int xr){
	treeX[x].left=xl;treeX[x].right=xr;
	if (xl==xr){
		locx[xl]=x;
		buildY(x,1,1,n);
		return;
	}
	int mid=(xl+xr)/2;
	buildX(x<<1,n,xl,mid);
	buildX(x<<1|1,n,mid+1,xr);
	buildY(x,1,1,n);
}
void updateY(int x,int y,int yl,int yr){
	int L=treeY[y].left,R=treeY[y].right;
	if (yl<=L&&R<=yr){
		mark[x][y]^=1;
		return;
	}
	int mid=(L+R)/2;
	if (mid>=yl) updateY(x,y<<1,yl,yr);
	if (yr>mid) updateY(x,y<<1|1,yl,yr); 
}
void updateX(int x,int xl,int xr,int yl,int yr){
	int L=treeX[x].left,R=treeX[x].right;
//	printf("%d  %d %d\n",x,L,R);
	if (xl<=L&&R<=xr){
		updateY(x,1,yl,yr);
		return;
	}
	int mid=(L+R)/2;
	if (mid>=xl) updateX(x<<1,xl,xr,yl,yr);
	if (xr>mid) updateX(x<<1|1,xl,xr,yl,yr);
}
bool findY(int x,int y,int r){
	int L=treeY[y].left,R=treeY[y].right;
	if (L==R) return mark[x][y];
	int mid=(L+R)/2;
	if (mid>=r) return mark[x][y]^findY(x,y<<1,r);
	else return mark[x][y]^findY(x,y<<1,r);
}
bool findX(int x,int l,int r){
	int L=treeX[x].left,R=treeX[x].right;
	if (L==R){
		return findY(x,1,r);
	}
	int mid=(L+R)/2;
	if (mid>=l) return findX(x<<1,l,r);
	else return findX(x<<1|1,l,r);
}
bool calc(int x,int y){
	int ret=0,i,j;
	for (i=locx[x];i;i>>=1)
		for (j=locy[y];j;j>>=1) ret^=mark[i][j];
	return ret;
}
int n,m;
int a[maxn];
char s;
int T;
int i,j,k;
int x_1,x_2,y_1,y_2;
int main()
{
	scanf("%d",&T);
	while (T--){
	   	scanf("%d%d",&n,&m);
		buildX(1,n,1,n);
	   	REP(i,m){
	   		cin>>s;
	   		if (s=='Q'){
				scanf("%d%d",&j,&k);
				printf("%d\n",findX(1,j,k));
			}
			if (s=='C'){
				scanf("%d%d%d%d",&x_1,&y_1,&x_2,&y_2);
				updateX(1,x_1,x_2,y_1,y_2);
			}
		}
		puts("");
	}
}
/*
*/
