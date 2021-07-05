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
const LL M=1e9+7;
const LL maxn=207+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int getmin(char a[],int n){//1-start
    int i,j,l;
    FOR(i,1,n) a[i+n]=a[i];
    i=1,j=2;
    while (i<=n&&j<=n){
        REP(l,n) if (a[i+l]!=a[j+l]) break;
        if (l==n) break;
        if (a[i+l]>a[j+l]) swap(i,j);
        j=max(j+l+1,i+1);
    }return i;
}
int n,m;
int i,j,k;
char a[maxn];
set<LL> S;
int main(){
    while (~scanf("%d",&n)){
        S.clear();
        FOR(i,1,n){
            scanf("%s",a+1);
            int i,n;
            n=strlen(a+1);
            int now=getmin(a,n);LL ID=0;
            FOR(i,1,n) ID=ID*37+a[i+now];
//            printf("%s",a+now);puts("");
            S.insert(ID);
        }
        printf("%d\n",S.size());
    }
}
/*
*/
