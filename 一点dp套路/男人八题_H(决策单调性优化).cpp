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
#include <cstdlib>
#include <iomanip>
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
const LL M=998244353;
const LL maxn=1e6+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M; return ret;}

//这个是男人八题的H
//题意:sum{A[l]->A[k],{1<=l<r<=n,k是l->r的路径上最近的标记点}}
//做法:DP; 注意有时DP[0]甚至DP[1]都要预处理的
//注意先写好DP方程
//注意DP方程上代表的意义!
//注意不能转移的地方!一定continue,否则可能破坏可以优化的性质
//我的理解:从左往右来看,如果l++,那么切的点只会向右移动,xl,xr是指转折点可能出现的位置;
//CDQ分治,传递下去了解可能存在的区间 
//每次更新的是mid节点 
//bfs,dfs均可,时间均为log(莫队不影响,莫队时间可证明nlogn) 
//CF868F题意:切区间k段,每段数字出现个数sigma{n(n-1)/2}最小的
LL L1[maxn],L2[maxn],R1[maxn],R2[maxn];//前缀和之和,小技巧
LL getL(int l,int r) { //一个求l->r的点到l的sum和
    return (L2[r]-L2[l])-L1[l]*(r-l);
}
LL getR(int l,int r) {
    return (R2[l]-R2[r])-R1[r]*(r-l);
}

LL pre[maxn],dp[maxn];
struct node {int l,r,xl,xr;};
LL cnt,sum,sum_sum;
queue<node> Q;
void changel(LL val,int seg) {
    sum_sum+=sum*seg*2;
    sum_sum-=cnt*val*seg*2;
    cnt+=seg; sum+=val*seg;
}
void changer(LL val,int seg) {
    sum_sum-=sum*seg*2;
    sum_sum+=cnt*val*seg*2;
    cnt+=seg; sum+=val*seg;
}
int _l,_r;
LL A[maxn];
void changeto(int l,int r) {
    while (_r<r) _r++,changer(A[_r],1);
    while (_l>l) _l--,changel(A[_l],1);
    while (_l<l) changel(A[_l],-1),_l++;
    while (_r>r) changer(A[_r],-1),_r--;
}
void solve(int n) {
    int i;
    Q.push(node{1,n,0,n-1});
    while (Q.size()) {
        auto F=Q.front(); Q.pop();
        int l=F.l,r=F.r,L=F.xl,R=F.xr;//l,r,check_l,check_r
        int m=(l+r)/2,M=L;
        LL &now=dp[m];
        FOR(i,L,min(m-1,R)) {
            //这里changeto不会改变复杂度
            LL msum=(m-i)*getL(m,n);
            LL rsum=(n-m+1)*(getR(i+1,m)+i*(A[m]-A[i]));
            if (now>pre[i]-msum-rsum)
                now=pre[i]-msum-rsum,M=i;
        }
        if (l<m) Q.push(node{l,m-1,L,M});
        if (r>m) Q.push(node{m+1,r,M,R});
    }
}
//DP[i]:i_chosen; contains [i]->[i]; [i]->R(i+1->n)
//update:m [i-m]->[i], [i-m]->[m-n] [i-m]->[i-m]
int T;
int n,m,k;
int i,j;
int main() {
    while (~scanf("%d%d",&n,&k)) {
        FOR(i,1,n) scanf("%lld",&A[i]);
        A[0]=A[1]; A[n+1]=A[n];
        FOR(i,1,n) L1[i]=A[i]-A[i-1]+L1[i-1];
        FOR(i,1,n) L2[i]=L2[i-1]+L1[i];

        rFOR(i,1,n) R1[i]=A[i+1]-A[i]+R1[i+1];
        rFOR(i,1,n) R2[i]=R2[i+1]+R1[i];

        _l=1; _r=0; sum=sum_sum=cnt=0;
        changeto(1,n);
        FOR(i,0,n) dp[i]=sum_sum;
//        FOR(i,1,n) printf("%lld ",dp[i]);puts(" <- start_DP");
        FOR(i,1,k) {
            int i;
            FOR(i,0,n) pre[i]=dp[i];
            solve(n);
//            FOR(m,1,n) FOR(i,0,m-1){
////                changeto(i+1,m);
////                cal:-=[m,n]->[i](differ)+[i+1-m](to m)
////                cal:-=[i+1,m]->[m,n](to m)
//                LL msum=(m-i)*getL(m,n);
//                LL rsum=(n-m+1)*(getR(i+1,m)+i*(A[m]-A[i]));
//                dp[m]=min(dp[m],pre[i]-msum-rsum);
//            }
//            FOR(i,1,n) printf("%lld ",dp[i]);puts(" <- DP");
        }
        LL ans=dp[0];
        FOR(i,1,n) ans=min(ans,dp[i]);
        printf("%lld\n",ans);
    }
}
/*
*/
