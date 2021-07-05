#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL N=1e4;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a,double b) {return a>0?a:-a;}

// 计数题的时候, "选择"和"方案"分开算是一个不错的选择~

// 注意n>M时要用lucas!
LL inv[1000002];//inverse
LL fac[1000002];//Factorial
// 求出的是ax+by=1的解(a,b正负不限,而且挺小的);
// d(gcd)==1时存在逆元;(d!=1)&&(num|d)时,num*a/d可认为逆元
// (x+p)%p为逆元
// DP:C[i][j]=(C[i-1][j-1]+C[i][j-1])%M
void exgcd(LL a,LL b,LL &d,LL &x,LL &y) {
    if (!b) {d=a; x=1; y=0;}
    else {exgcd(b,a%b,d,y,x); y-=a/b*x;}
}
// 前面那个线性求逆元的log版2333
int getinv(int n) {
    if (n==1) return 1;
    return (M-M/n)*(getinv(M%n))%M;
}
LL C(int n,int m) {
    return fac[n]*inv[m]%M*inv[n-m]%M;
}
//Lucas扩展：Kummer定理：
//C(n,k)中的p的幂次的为p进制下n-k借位次数
//e.g.求C(n,0)...C(n,n)的lcm%(1e9+7)
//做法:考虑每个素因子,n转化为p进制后,除了最后的为p-1的都可以借位
//ans=pow(p,k)的乘积
LL lucas(LL n,LL m) { //注意MOD不能太大=_=! Mlogn
    return m==0?1:1ll*C(n%M,m%M)*lucas(n/M,m/M)%M;
}
int main() {
    int i;
    fac[0]=1;
    FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
    printf("%I64d",C(10,3));
}
/*
*/
