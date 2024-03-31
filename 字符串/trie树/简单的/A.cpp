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
const LL N=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}

LL n,m;
LL a[N][27],f[N],ff[N];//ff[N]:num
LL i,j,k;
int cnt;
LL ans;
string s;
inline void insert(string str){
	int len=str.length(),now=0;
	int i;
	REP(i,len){
		if (!a[now][str[i]-'a']) a[now][str[i]-'a']=++cnt;
		now=a[now][str[i]-'a'];
		++f[now];//表示小于等于这个的有多少
	}
	ff[now]++;//==的
}
int calc(string str){//小于str的
	int len=str.length(),now=0,ans=0;
	int i,j;
	REP(i,len){
		REP(j,str[i]-'a')
			ans+=f[a[now][j]];
        // if (i!=len-1)//等于的也加
            ans+=ff[a[now][str[i]-'a']];
        now=a[now][str[i]-'a'];
        if (now==0) break;
	}
	return ans;//求大的要再加上后面的
}
int findstr(string str){//等于的
    int len=str.length(),now=0,ans=0;
    int i;
    REP(i,len){
        now=a[now][str[i]-'a'];
        if (now==0) return 0;
    }
    ans=ff[now];//可能==0
    return ans;
}
int main(){
	scanf("%d%d",&n,&m);
    REP(i,n) {cin>>s;insert(s);}
    REP(i,m) {cin>>s;cout<<calc(s)<<'\n';}
}
/*
10 10
a ab abc abcd abcde ac acd acde ba ad
a ab abd abc abe ade b bc ba ad
*/
