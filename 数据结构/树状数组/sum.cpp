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
const LL N=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}


LL a[N];
int n,m;
int i,j,k;
LL lowbit(LL x){
	return x&-x;
}
/*区间和，单点修改*/
LL c[N];
LL presum(LL x){
	LL ret=0;
	for (;x;x-=lowbit(x)) ret+=c[x];
	return ret;
}
LL sum(LL l,LL r){
	return presum(r)-presum(l-1);
}
void add(LL x,int d){//修改不如add有效 
	for (;x<=n;x+=lowbit(x)) c[x]+=d;
}
void init(LL n){
	FOR(i,1,n) c[i]=0; 
	FOR(i,1,n) add(i,a[i]);
}
int T,kk;
char s[10];
int main()
{
	scanf("%d",&T);
	FOR(kk,1,T){
   		printf("Case %d:\n",kk);
   		scanf("%d",&n);
   		FOR(i,1,n) scanf("%d",&a[i]);
		init(n);
   		while (scanf("%s",&s)&&s[0]!='E'){
   			scanf("%d%d",&j,&k);
   			if (s[0]=='Q') printf("%d\n",sum(j,k));
   			if (s[0]=='A') add(j,k);
   			if (s[0]=='S') add(j,-k);
		}
	}
}
/*
*/
