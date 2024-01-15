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
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M; return ret;}

template<typename T>inline T poww(T a,T b,T M) {
    T ret=1;
    for (; b; b>>=1ll,a=1ll*a*a%M)
        if (b&1) ret=1ll*ret*a%M;
    return ret;
}

// CF459(DIV1)D
// 题意:求生成树中含k条给定树边的生成树个数
// 做法:为给定边加不同权值,然后矩阵树定理
// 具体来说, 假设ans(x)是用了x条边的结果,那么ans(x)*{i^x}=g(i)是可以算的
// 相当于问你ans(x)这个多项式的系数; 拉格朗日插值就好了

// 矩阵树定理:生成树数量=|基尔霍夫矩阵C=D-A|;
// D为度数矩阵,A为边矩阵
// 然后拉格朗日插值求出系数即可
LL guass(LL A[107][107],int n,LL M) {
    LL ret=1; int i,j,k;
    REP(i,n) {
        int id=i;
        if (!A[i][i]) rep(j,i+1,n) if (A[j][i]) id=j;
        if (!A[id][i]) continue;
        if (id!=i) {rep(j,i,n) swap(A[i][j],A[id][j]); ret*=-1;}
        A[i][i]%=M; (A[i][i]<0) &&(A[i][i]+=M);
        LL rev=poww(A[i][i],M-2,M);
        rep(k,i+1,n) rrep(j,i,n)
            (A[k][j]-=(LL)A[k][i]*rev%M*A[i][j])%=M;
    } REP(i,n)(ret*=A[i][i])%=M;
    (ret<0) &&(ret+=M);
    return ret;
}
int n,m;
int i,j,k;
int a[107][107]; LL A[107][107];
LL val[107],v_v[107];
LL f[107],g[107],ans[107];
int main() {
    scanf("%d",&n);
    FOR(i,1,n-1) {
        int u,v;
        scanf("%d%d",&u,&v); u--; v--;
        a[u][v]=a[v][u]=1;
    } REP(i,n) v_v[i]=i;
    REP(k,n) {
        REP(i,n) REP(j,n) A[i][j]=0;
        REP(i,n) REP(j,n) if (i!=j) {
            if (a[i][j]) A[i][j]=M-v_v[k],A[i][i]+=v_v[k];
            else A[i][j]=M-1,A[i][i]++;
        } val[k]=guass(A,n-1,M);
    }
    g[0]=1; REP(i,n) rFOR(j,0,i)(g[j+1]+=g[j])%=M,(g[j]*=(M-v_v[i]))%=M;
    REP(k,n) {
        LL rev=1;
        rFOR(i,0,n) f[i]=(g[i+1]+f[i+1]*v_v[k]%M+M)%M;
        REP(j,n) if (j!=k)(rev*=(v_v[k]-v_v[j]))%=M;
        (rev<0) &&(rev+=M); rev=powMM(rev,M-2);
        rev=(rev*val[k])%M;
        FOR(i,0,n)(ans[i]+=(LL)f[i]*rev%M)%=M;
    } FOR(i,0,n-1) printf("%lld ",ans[i]);
}
/*
9
6 2
2 3
5 1
1 2
5 7
9 3
2 8
4 8
*/
