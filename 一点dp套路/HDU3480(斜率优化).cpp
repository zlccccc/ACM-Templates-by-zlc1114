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
//HDU 3480//斜率优化
//题意:一堆数字,切成k份,每块的代价为(max-min)^2
//dp方程:dp[i][j]=min{dp[k][j-1]+(a[i]-a[k+1])^2};
//dp方程:dp[i][j]=min{dp[k][j-1]+a[k+1]^2-2*a[i]*a[k+1]}+a[i]^2
//k=(dp[k][j-1](pre)+a[k+1]^2)/(a[k+1]),常数2*a[i]
//斜率优化本质是维护一个下凸壳
int n,m,i,j,k,t;
int a[maxn],pre[maxn],dp[maxn];
int head,tail;
int Q[maxn];//id
inline int getY(int id){
    return pre[id]+a[id+1]*a[id+1];
}
inline int getX(int id){
    return a[id+1];
}
int main(){
    int T,X=0;
    scanf("%d",&T);
    while (T--){
        scanf("%d%d",&n,&m);
        FOR(i,1,n) scanf("%d",&a[i]);
        sort(a+1,a+1+n);
        int qi,qj,qk;
        FOR(i,1,n) dp[i]=(a[i]-a[1])*(a[i]-a[1]);
        FOR(j,2,m){
            FOR(i,1,n) pre[i]=dp[i];
            head=tail=0;
            dp[0]=0;Q[tail++]=0;
            FOR(i,1,n){
                while (head+1<tail){
                    qi=Q[head],qj=Q[head+1];
                    if (getY(qj)-getY(qi)<=2*a[i]*(getX(qj)-getX(qi))) head++;
                    else break;
                }qi=Q[head];
                dp[i]=pre[qi]+(a[i]-a[qi+1])*(a[i]-a[qi+1]);
                while (head+1<tail){
                    qi=Q[tail-2];qj=Q[tail-1];qk=i;
                    int y1=getY(qj)-getY(qi),x1=getX(qj)-getX(qi);
                    int y2=getY(qk)-getY(qj),x2=getX(qk)-getX(qj);
                    if (y2*x1<=y1*x2) tail--;//y2/x2>y1/x1
                    else break;
                }Q[tail++]=i;
            }
        }
        printf("Case %d: %d\n",++X,dp[n]);
    }
}
/*
*/
