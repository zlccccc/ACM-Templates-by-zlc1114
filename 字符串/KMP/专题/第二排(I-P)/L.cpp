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

int T;
int n,m;
int i,j,k;
char a[maxn],b[maxn],K[27],R[255];
int fail[maxn];
int cnt[maxn];
int main(){
    scanf("%d",&T);
    while (T--){
        scanf("%s%s",K,a+1);
        n=strlen(a+1);
        FOR(i,1,n) b[i]=K[a[i]-'a'];
        REP(i,26) R[K[i]]=i+'a';
        fail[0]=fail[1]=0;
        FOR(i,2,n){
            j=fail[i-1];
            while (j&&a[j+1]!=a[i]) j=fail[j];
            if (a[j+1]==a[i]) fail[i]=j+1;
            else fail[i]=0;
        }j=0;
        FOR(i,1,n){
            while (j&&a[j+1]!=b[i]) j=fail[j];
            if (a[j+1]==b[i]) j++;
        }while (j*2>n) j=fail[j];
//        FOR(i,1,n) printf("%d ",fail[i]);
//        printf("j=%d\n",j);
        printf("%s",a+1);
        FOR(i,j+1,n-j) putchar(R[a[i]]);
        puts("");
    }
}
/*
5
abcdefghijklmnopqrstuvwxyz
ababab
abcdefghijklmnopqrstuvwxyz
aba
abcdefghijklmnopqrstuvwxyz
absab
qwertyuiopasdfghjklzxcvbnm
qwertabcde
*/
