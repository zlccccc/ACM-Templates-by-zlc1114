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

//cnt,sum1,sum2
struct node{
    LL cnt,sum1,sum2;
    node(){cnt=sum1=sum2=0;};
    node(int _cnt,int _sum1,int _sum2):cnt(_cnt),sum1(_sum1),sum2(_sum2){};
}f[27][17][17];
int value[27];LL pow10[107];
node calc(int x,int add,int val,int flag){
//    printf("%d %x %d %d; lca=%d\n",x,used,remain,flag,V[lca[used]]);
    if (x==0) return node((add&&val),0,0);
    if (!flag&&f[x][add][val].cnt!=-1) return f[x][add][val];
    node ret;int i,maxi=9;
    if (flag) maxi=min(maxi,value[x]);
    FOR(i,0,maxi){
        if (i==7) continue;
        node now=calc(x-1,(add+i)%7,(val*10+i)%7,flag&&(i==maxi));
        (ret.cnt+=now.cnt)%=M;
        (ret.sum1+=now.sum1+now.cnt*i%M*pow10[x-1])%=M;
        (ret.sum2+=now.sum2+now.sum1*i*2%M*pow10[x-1]+now.cnt*i*i%M*pow10[2*x-2])%=M;
    }if (!flag) f[x][add][val]=ret;
    return ret;
}int k;
LL calc(LL x){
    int length=0;
    while (x) value[++length]=x%10,x/=10;
    return calc(length,0,0,1).sum2;
}LL calc(LL l,LL r){
    return (calc(r)-calc(l-1)+M)%M;
}
int n,m;
int i,j;
int T;
int main(){
    REP(i,27) REP(j,10) REP(k,10) f[i][j][k]=node(-1,-1,-1);
    pow10[0]=1;
    FOR(i,1,100) pow10[i]=pow10[i-1]*10%M;
//    rFOR(i,1,1000) if (!calc(i,i)) printf("%d:%d\n",i,calc(i,i));puts("");
    scanf("%d",&T);
    while (T--){
        LL l,r;
        scanf("%lld%lld",&l,&r);
        printf("%lld\n",calc(l,r));
    }
}
/*
10
1000000000000000000 1000000000000000000
*/
