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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}
//注意Q里放的东西
//用一个log换来了一个通用性更强的方式
//这道题实测和斜率优化时间差不多了(后者常数大) 
int n,m,s;
int i,j,k;
struct node{int l,r,xl,xr;};
queue<node> Q;
LL A[maxn],X[maxn];
LL dp[maxn],pre[maxn];
LL SIZE[maxn];
int fa[maxn];
int tot;
void solve(){
    int i;
    Q.push(node{1,tot,1,tot-1});
    while (Q.size()){
        auto F=Q.front();Q.pop();
        int l=F.l,r=F.r,L=F.xl,R=F.xr;//l,r,check_l,check_r
        int m=(l+r)/2,M=L;
        LL &now=dp[m];
        FOR(i,L,min(m-1,R)){
            if (now>pre[i]+2*(X[m-1]-X[i])-2*(m-1-i)*A[i]-(m-i-1)+1)
                now=pre[i]+2*(X[m-1]-X[i])-2*(m-1-i)*A[i]-(m-i-1)+1,M=i;
        }
        if (l<m) Q.push(node{l,m-1,L,M});
        if (r>m) Q.push(node{m+1,r,M,R});
    }
}
int main(){
    scanf("%d%d%d",&n,&m,&s);
    FOR(i,2,n) scanf("%d",&fa[i]);
    rFOR(i,1,n) SIZE[i]++,SIZE[fa[i]]+=SIZE[i];
    for (;s;s=fa[s]) A[++tot]=SIZE[s];
    FOR(i,1,tot) X[i]+=A[i]+X[i-1];
//  FOR(i,1,tot) printf("%lld ",A[i]);puts("");
//  FOR(i,1,tot) printf("%lld ",X[i]);puts("");puts("");
    FOR(i,1,tot) dp[i]=INFF;
    FOR(i,1,tot) dp[i]=2*X[i-1]-i+1;
//  dp[1]=0;m++;
//  FOR(i,1,tot) printf("%lld ",dp[i]);puts("");
//  while (m--){
//      rFOR(i,1,tot)//update X'(j+1->i)
//          FOR(j,1,i-1) dp[i]=min(dp[i],dp[j]+2*(X[i-1]-X[j])-2*(i-1-j)*A[j]-(i-1-j)+1);
//      FOR(i,1,tot) printf("%lld ",dp[i]);puts("");
//  }
    while (m--){
        FOR(i,1,tot) pre[i]=dp[i];
        solve();
//      FOR(i,1,tot) printf("%lld ",dp[i]);puts("");
    }
    printf("%lld\n",dp[tot]);
}
