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
const int INF = 0x3f3f3f3f;
const LL INFF = 0x3f3f3f3f3f3f3f3fll;
const LL M = 1e9 + 7;
const LL maxn = 1e6 + 7;
const double eps = 0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0 ? a : -a;}
template<typename T>inline T powMM(T a, T b) {T ret=1; for (; b; b>>=1ll,a=1ll*a*a%M) if (b&1) ret = 1ll * ret * a % M; return ret;}

/*miller_rabin*/
const int times=8;// random_check; 8-12 is OK
LL mul(LL a,LL b,LL M) {
    LL ret=0;
    for (; b; b>>=1,(a+=a)>=M&&(a-=M))
        if (b&1)(ret+=a)>=M&&(ret-=M);
    return ret;
}
LL poww(LL a,LL b,LL M) {
    LL ret=1;
    for (; b; b>>=1,a=mul(a,a,M))
        if (b&1) ret=mul(ret,a,M);
    return ret;
}
bool check(LL a,LL n,LL x,LL t) {
    LL ret=poww(a,x,n);
    LL last=ret;
    for (ret=mul(ret,ret,n); t--; last=ret,ret=mul(ret,ret,n))
        if (ret==1&&last!=1&&last!=n-1) return true;
    if (ret!=1) return true;
    return false;
}
bool miller_rabin(LL n) {
    if (n<2) return false;
    if (!(n&1)) return (n==2);
    LL x=n-1,t=0;
    while (!(x&1)) x>>=1,t++;
    int i;
    REP(i,times)
    if (check(rand()%(n-1)+1,n,x,t)) return false;
    return true;
}
/*pollard_rho*/
LL pollard_rho(LL x,LL c) {
    LL x0=rand()%(x-1)+1;
    LL y=x0; c%=x;
    for (LL i=2,k=2;; i++) {
        ((x0=mul(x0,x0,x)+c)>=x)&&(x0-=x);
        LL d=gcd(y-x0+x,x);
        if (d!=1&&d!=x) return d;
        if (y==x0) return x;
        if (i==k) y=x0,k+=k;
    }
}
LL factor[107]; int tot;
void findfac(LL n,int k) {
    if (n==1) return;
    if (miller_rabin(n)) {factor[tot++]=n; return;}
    LL p=n;
    int c=k;
    while (p>=n) p=pollard_rho(p,c--);
    findfac(p,k);
    findfac(n/p,k);
}
int main() {
    int T;
    srand(time(0));
    scanf("%d",&T);
    while (T--) {
        LL n; int i;
        scanf("%I64d",&n);
        if (miller_rabin(n)) puts("Prime");
        else {
            tot=0;
            findfac(n,107);
            LL ans=factor[0];
            REP(i,tot) ans=min(ans,factor[i]);
            printf("%I64d\n",ans);
        }
    }
}
/*
*/
