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
const LL maxn=1000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}
//HDU 3516//四边形不等式优化 
//题意:给定一个从左上往右下的图，只能往下往右连，求一个构造使得所有的边长度总和最小 
//dp方程:dp[i][j]=max{dp[i][k]+dp[k+1][j]+x[k+1]-x[i]+y[k]-y[j]}; 
//能用：满足:
//w[i][j]+w[i'][j']<=w[i][j']+w[i'][j];
//w[i'][j']<=w[i][j],那么决策区间包含 
struct node{
    int x,y;
}a[maxn];
int n,m,i,j,k,t;
int dp[maxn][maxn],pos[maxn][maxn];
int main(){
    while (~scanf("%d",&n)){
        FOR(i,1,n) scanf("%d%d",&a[i].x,&a[i].y),pos[i][i]=i;
        FOR(i,1,n) FOR(j,i+1,n) dp[i][j]=INF;
        FOR(t,1,n-1){
            FOR(i,1,n-t){
                j=i+t;
                FOR(k,pos[i][j-1],min(j-1,pos[i+1][j])){
                    int now=dp[i][k]+dp[k+1][j]+a[k+1].x-a[i].x+a[k].y-a[j].y;
                    if (dp[i][j]>now){
                        dp[i][j]=now;
                        pos[i][j]=k;
                    }
                }
            }
        }
        printf("%d\n",dp[1][n]);
    }
}
/*
*/
