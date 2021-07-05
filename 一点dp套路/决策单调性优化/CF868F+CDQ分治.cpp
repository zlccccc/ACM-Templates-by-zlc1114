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
//我的理解:从左往右来看,如果l++,那么切的点只会向右移动,xl,xr是指转折点可能出现的位置;
//CDQ分治,传递下去了解可能存在的区间 
//每次更新的是mid节点 
//bfs,dfs均可,时间均为log(莫队不影响,莫队时间可证明nlogn) 
//CF868F题意:切区间k段,每段数字出现个数sigma{n(n-1)/2}最小的个数 
struct node{int l,r,xl,xr;};
int n,m;
int a[maxn];
LL pre[maxn],dp[maxn],sum;
int cnt[maxn];
int _l,_r;
queue<node> Q;
void solve(){
    int i;
    Q.push(node{1,n,1,n});
    while (Q.size()){
        node F=Q.front();Q.pop();
        int l=F.l,r=F.r,L=F.xl,R=F.xr;
        int m=(l+r)/2,M=L;
//      printf("l,m,r,L,R: %d %d %d %d %d\n",l,m,r,L,R);
        LL &now=dp[m];
        while (_r<m) _r++,sum+=cnt[a[_r]],cnt[a[_r]]++;
        while (_l>L) _l--,sum+=cnt[a[_l]],cnt[a[_l]]++;
        while (_l<L) cnt[a[_l]]--,sum-=cnt[a[_l]],_l++;
        while (_r>m) cnt[a[_r]]--,sum-=cnt[a[_r]],_r--;
        FOR(i,L,min(m,R)){
            while (_l<i) cnt[a[_l]]--,sum-=cnt[a[_l]],_l++;
            if (now>sum+pre[i-1]) now=sum+pre[i-1],M=i;
        }
        if (l<m) Q.push(node{l,m-1,L,M});
        if (r>m) Q.push(node{m+1,r,M,R});
    }
}
int main(){
    int i,k;
    scanf("%d%d",&n,&k);
    FOR(i,1,n) scanf("%d",&a[i]);
    _l=1;_r=0;
    memset(pre,0x3f,sizeof(pre));pre[0]=0;
    while(k--){
        memset(dp,0x3f,sizeof(dp));
        solve();
        memcpy(pre,dp,sizeof(pre));
//      FOR(i,1,n) printf("%d ",dp[i]);puts("");
    }
    printf("%I64d",dp[n]);//最后一次认为在n点切即可 
}
/*
10 2
1 2 1 2 1 2 1 2 1 2
*/
