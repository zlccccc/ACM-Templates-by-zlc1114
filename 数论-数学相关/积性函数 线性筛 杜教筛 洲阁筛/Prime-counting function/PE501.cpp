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
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
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

//这道题题意:小于n有多少个数字有4个因子
//(两个质数积,一个质数三次方)
//注意容斥减去多算的
//http://codeforces.com/blog/entry/44466?#comment-290036/
//考虑S(v,m):2...v,质因子全都>=m;那么考虑容斥:
//容斥掉的至少有一个p,而且没有小于p的因子
//很明显的,p=min(p,sqrt(v));
//S(v,p)=S(v,p-1)-(S(v/p,p-1)-S(p-1,p-1));(DP)
//那么反过来算即可;pi(n)=S(n,n);
//H[i]:pi(n/i);L[i]:pi(i)
//计算过程中,L[i]表示S(i,p),最终S(i,i)
//简单的这样DP,时间复杂度O(n^3/4),如果预处理n^2/3则最终n^2/3
LL H[maxn],L[maxn];
void calc(LL n) {
    LL p,k,m;
    for (m=1; m*m<=n; ++m) H[m]=n/m-1;
    FOR(p,1,m) L[p]=p-1;
    FOR(p,2,m) {//在这里,如果前方限制了P的最大值,是min(P,m)
        if (L[p]==L[p-1]) continue;//not_prime
        FOR(k,1,min(m-1,n/p/p)) {
            if (p*k<m) H[k]-=H[p*k]-L[p-1];
            else H[k]-=L[n/p/k]-L[p-1];
        }
        rFOR(k,p*p,m) L[k]-=L[k/p]-L[p-1];
    }
}
LL solve(LL n){
    calc(n);
    LL ans=0,i,j;
    LL m=cbrt(n-1),q=sqrt(n-1);
    while (q*q<=n) q++;
    q--;
    while (m*m*m<=n) m++;
    m--;
//    FOR(i,2,q) dbgln(L[i]);
    //i*j*k
    for (i=2;i*i*i<=n;i++) if (L[i]!=L[i-1]){
        for (j=i+1;i*j*j<=n;j++) if (L[j]!=L[j-1]){
            if (n/i/j>j){
                if (n/j/i<=q){
                    ans+=L[n/j/i]-L[j];
//                    dbg(i);dbg(j);printf("(L1)ans+= %lld  %lld\n",L[n/j/i],L[j]);
                }else{
                    ans+=H[j*i]-L[j];
//                    dbg(i);dbg(j);printf("(H1)ans+= %lld  %lld\n",H[j*i],L[j]);
                }
            }
        }
    }
    //i*j
    FOR(i,2,m) if (L[i]!=L[i-1]){
        if (n/i/i/i<=q){
            ans+=L[n/i/i/i];
//            dbg(i);printf("(L2)ans+= %lld\n",L[n/i/i/i]);
        }else{
            ans+=H[i*i*i];
//            dbg(i);printf("(H2)ans+= %lld\n",H[i*i*i]);
        }if (i*i*i*i<=n){
            ans--;
//            dbg(i);puts("(H2) DEL");
        }
    }m=1;
    while (m*m*m*m*m*m*m<=n) m++;
    m--;
//    printf("  (F3)ans+= %lld\n",m);
    ans+=L[m];
    printf("%I64d\n",ans);
    return ans;
}
LL getcheck(LL x){
    int cnt=0,i;
    FOR(i,1,x) if (x%i==0) {
        cnt++;
        if (cnt>8) return 0;
    }return (cnt==8);
}
int main() {
    LL i;
//    printf("%lld\n",solve(3));
//    rFOR(i,2,100) if (getcheck(i)) printf("%d ",i);puts("");
//    rFOR(i,2,1000) if (getcheck(i)!=solve(i)-solve(i-1)) printf("not: %lld; %lld\n",i,solve(i));
    solve(100);
    solve(1000);
    solve(1000000);
    solve(1000000000000ll);
}
/*
100
1000
1000000
1000000000000
*/
