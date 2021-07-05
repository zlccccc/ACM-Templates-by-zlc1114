#include <sstream>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
#include <cassert>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG
#ifdef DEBUG
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#define dbg(x)
#define dbgln(x)
#endif // DEBUG
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=25*25*16+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

// 题意:n%1,n%2...异或, 做法是BSGS然后类欧几里得
// 每块是n-n/l*l ^ ... ^ n-n/r*r
// 也就是n-(n/l)*k,(等价于n%r+(n/l)*k) k是0->r-l
// 按位计算, 就变成了个类欧几里得
// 玄学卡常,n<=某值直接暴力, 这里tls说是一个log的
LL f(LL a,LL b,LL c,LL n) {
    if (a==0) return b/c*(n+1);
    if (a>=c||b>=c) return (a/c)*n*(n+1)/2+(b/c)*(n+1)+f(a%c,b%c,c,n);
    LL m=(a*n+b)/c;
    return n*m-f(c,c-b-1,a,m-1);
}
LL solve(LL l,LL c,LL n) {
    LL ret=0,i;
    if (n<=10000) REP(i,n+1) ret^=l,l+=c;
    else REP(i,40) ret^=(f(c,l,(1ll<<i),n)&1)<<i;
    return ret;
}
LL getans(LL n) {
    LL ans=0;
    for (LL l=1,r; l<=n;) {
        r=n/(n/l);
        ans^=solve(n%r,n/l,r-l);
        l=r+1;
    } return ans;
}
int main() {
    int T;
    int i,j,k;
    scanf("%d",&T);
    while (T--) {
        LL n;
        scanf("%lld",&n);
        printf("%lld\n",getans(n));
    }
    return 0;
}
/*
*/
