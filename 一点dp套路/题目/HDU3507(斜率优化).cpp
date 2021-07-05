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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}
//HDU 3507//斜率优化
//题意:一堆数字,写到一行的cost=sum^2+m,求个min
//dp方程:dp[i]=min{dp[j]+(sum[i]-sum[j])^2+m};
//dp[i]=min{(dp[j]+sum[j]*sum[j]+m)-2*sum[i]*sum[j]}+sum[i];
//k=d(dp[j]+sum[j]*sum[j]+m)/d(sum[j]);常数2*sum[i]
//斜率优化本质是维护一个下凸壳
int n,m,i,j,k,t;
LL a[maxn],dp[maxn];
int head,tail;
int Q[maxn];//id
inline LL getY(int id){
    return dp[id]+a[id]*a[id]+m;
}
inline LL getX(int id){
    return a[id];
}
int main(){
    while (~scanf("%d%d",&n,&m)){
        FOR(i,1,n) scanf("%lld",&a[i]);
        FOR(i,1,n) a[i]+=a[i-1];
        head=tail=0;
        dp[0]=0;Q[tail++]=0;
        int qi,qj,qk;
        FOR(i,1,n){
            while (head+1<tail){
                qi=Q[head],qj=Q[head+1];
                if (getY(qj)-getY(qi)<=2*a[i]*(getX(qj)-getX(qi))) head++;
                else break;
            }qi=Q[head];
            dp[i]=dp[qi]+(a[i]-a[qi])*(a[i]-a[qi])+m;
            while (head+1<tail){
                qi=Q[tail-2];qj=Q[tail-1];qk=i;
                LL y1=getY(qj)-getY(qi),x1=getX(qj)-getX(qi);
                LL y2=getY(qk)-getY(qj),x2=getX(qk)-getX(qj);
                if (y2*x1<=y1*x2) tail--;//y2/x2>y1/x1
                else break;
            }Q[tail++]=i;
            rep(j,head,tail) printf("%lld-%lld  ",getX(Q[j]),getY(Q[j]));puts("");
        }
        printf("%lld\n",dp[n]);
    }
}
/*
*/
