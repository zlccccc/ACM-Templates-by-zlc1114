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
int n;
int i,j,k;
LL lowbit(LL x){
	return x&-x;
}
/*区间最大值*/
LL m[N];
void change(LL r){
	m[r]=a[r];
	LL i,t=lowbit(r);
	for (i=1;i<t;i<<=1)
		m[r]=max(m[r],m[r-i]);
}
void init(LL n){
	LL i;
	FOR(i,1,n) change(i);
}
void update(LL x){
	LL i;
	change(x);
	for (i=x;i<=n;i+=lowbit(i)) change(i);
}
LL getmax(LL l,LL r){
	LL ret=a[r];
	while (l!=r){
		for (r--;r-lowbit(r)>=l;r-=lowbit(r)){
			ret=max(ret,m[r]);
		}ret=max(ret,a[r]);
	}
	return ret;
}
int main()
{
	cin>>n;
	FOR(i,1,n) cin>>a[i];
	init(n);
	FOR(i,1,n) cout<<m[i]<<' ';
	cin>>n;
	FOR(i,1,n){
		cin>>j>>k;
		printf("%lld\n",getmax(j,k));
	}
}
/*
10
1 2 1 1 0 6 4 7 9 1
5
1 5
4 5
1 4
5 6
7 9
*/
