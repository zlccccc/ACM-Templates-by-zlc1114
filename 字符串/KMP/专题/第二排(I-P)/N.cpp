#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
#include <cassert>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e4+7;
const LL maxn=3e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int fail[maxn];
int cnt[maxn];
int kmp(char a[],char b[]){
    int i,j;
    int n=strlen(a+1),m=strlen(b+1);
    fail[0]=fail[1]=0;
    FOR(i,2,n){
        j=fail[i-1];
        while (j&&a[j+1]!=a[i]) j=fail[j];
        if (a[j+1]==a[i]) fail[i]=j+1;
        else fail[i]=0;
    }j=0;
    int ret=0;
    FOR(i,1,m){
        while (j&&a[j+1]!=b[i]) j=fail[j];
        if (a[j+1]==b[i]) j++;
        ret=max(ret,j);
    }
//    printf("%s %s   ret=%d\n",a+1,b+1,ret);
//    FOR(i,1,n) printf("%d ",fail[i]);puts("");
    return ret;
}
int T;
int n,m;
int i,j,k;
char a[4007][207];
int main(){
    while (~scanf("%d",&n)&&n){
        FOR(i,1,n) scanf("%s",a[i]+1);
        m=strlen(a[1]+1);
        int ans=0,pos=1;
        FOR(i,1,m) {
            int now=m-i+1;
            FOR(j,2,n) now=min(now,kmp(a[1]+i-1,a[j]));
//            printf("%d : %d\n",i,now);
            if (now>ans) ans=now,pos=i;
            else if (now==ans&&strcmp(a[1]+pos,a[1]+i)==1) ans=now,pos=i;
        }FOR(i,pos,pos+ans-1) putchar(a[1][i]);
        if (!ans) puts("IDENTITY LOST");
        else puts("");
    }
}
/*
*/
