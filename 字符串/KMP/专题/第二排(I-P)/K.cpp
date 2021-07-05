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
char a[maxn];
int fail[maxn];
int cnt[maxn];
int main(){
    scanf("%d",&T);
    while (T--){
        scanf("%d",&n);
        scanf("%s",a+1);
        fail[0]=fail[1]=0;
        FOR(i,2,n){
            j=fail[i-1];
            while (j&&a[j+1]!=a[i]) j=fail[j];
            if (a[j+1]==a[i]) fail[i]=j+1;
            else fail[i]=0;
        }
        int ans=0;
        FOR(i,1,n) cnt[i]=1;
        rFOR(i,1,n){
            (ans+=cnt[i])%=M;
            (cnt[fail[i]]+=cnt[i])%=M;
        }
//        FOR(i,1,n) printf("%d ",cnt[i]);puts("");
        printf("%d\n",ans);
    }
}
/*
*/
