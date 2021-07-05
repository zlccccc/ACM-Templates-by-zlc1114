#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <cstring>
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
const LL M=500+7;
const LL N=500+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a,T b) {return a>0?a:-a;}

LL n,m;
char s[M],a[N];
LL Next[N];
LL i,j,k,t;
void init(char *a,LL *Next){
    Next[0]=-1;
    int len=strlen(a);
    register int i,j;
    FOR(i,1,len-1){
        j=Next[i-1];
        while (j>=0&&a[j+1]!=a[i]) j=Next[j];
        if (a[i]==a[j+1]) Next[i]=j+1;
        else Next[i]=-1;
    }
}
int kmp(char *s,char *a,LL *Next){
    int Len=strlen(s),len=strlen(a);
    register int i,j=-1;
    REP(i,Len){
        while (j>=0&&a[j+1]!=s[i]) j=Next[j];
        if (s[i]==a[j+1]) j++;
        if (j==len-1) return i-len+1;
    }
    return -1;
}
int main(){
	while (~scanf("%s%s",&s,&a)){
        init(a,Next);
        n=strlen(a);
        REP(i,n) printf("%d ",Next[i]);
        t=kmp(s,a,Next);
        if (~t) printf("%d",t+1);
        else printf("Not Found!");
        puts("");
	}
}
/*
*/
