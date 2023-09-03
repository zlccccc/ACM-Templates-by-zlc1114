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
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

// ax+by=1; a和b已知
int n,m;
int i,j,k;
void exgcd(LL a,LL b,LL &d,LL &x,LL &y){//d==0时存在逆元 //(x+p)%p为逆元
    if (!b) {d=a;x=1;y=0;}
    else {exgcd(b,a%b,d,y,x);y-=a/b*x;}
}
bool check(LL a,LL b,LL x){
    LL A,B,d;exgcd(a,b,d,A,B);
    A*=x;B*=x;
    LL T=A/b+B/a;
    A%=b;B%=a;
    if (A<0) A+=b,T--;
    if (B<0) B+=a,T--;
    return T>=0;
}
int solve(){
    int a,b,x,y;
    scanf("%lld%lld%lld%lld",&a,&b,&x,&y);
    int g=gcd(a,b);
    if (x%g||y%g) return 0*puts("NO");
    x/=g;y/=g;a/=g;b/=g;
    if (!(x%a)&&!(y%b)) return 0*puts("YES");
    if (!(y%a)&&!(x%b)) return 0*puts("YES");
    if (!(x%(a*b))&&check(a,b,y)) return 0*puts("YES");
    if (!(y%(a*b))&&check(a,b,x)) return 0*puts("YES");
    return 0*puts("NO");
}
int main(){
//    printf("check: %d\n",check(2ll,3ll,5ll));
    int T;
    scanf("%d",&T);
    while(T--) solve();
}
/*
*/
