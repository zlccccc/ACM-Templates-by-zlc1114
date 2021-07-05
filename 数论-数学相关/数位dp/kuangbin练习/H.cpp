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

//这道题满足条件的"支点"只有一个~
LL f[27][27][2007];
int value[27];
LL calc(int mid,int x,int prev,int flag){
    if (x==0) return (prev==0);
    if (prev<0) return 0;
//    printf("%d %d %d %d;F=%d\n",mid,x,prev,flag,f[mid][x][prev]);
    if (!flag&&f[mid][x][prev]!=-1) return f[mid][x][prev];
    LL ret=0;int i,maxi=9;
    if (flag) maxi=min(maxi,value[x]);
    FOR(i,0,maxi){
        ret+=calc(mid,x-1,prev+i*(x-mid),flag&&(i==maxi));
    }if (!flag) f[mid][x][prev]=ret;
    return ret;
}int k;
LL calc(LL x){
    int length=0;
    while (x) value[++length]=x%10,x/=10;
    LL ret=0;int i;
    REP(i,20) ret+=calc(i,length,0,1)-1;//0
    return ret;
}LL calc(LL l,LL r){
    return calc(r)-calc(l-1);
}
int n,m;
int i,j;
int T;
int main(){
    memset(f,0xff,sizeof(f));
//    FOR(i,1,10000) if (calc(i,i)) printf("%d ",i);puts("");
    scanf("%d",&T);
    while (T--){
        LL l,r;
        scanf("%lld%lld",&l,&r);
        LL ans=0;
        if (!l) ans++,l++;
        ans+=calc(l,r);
        printf("%lld\n",ans);
    }
}
/*
10
1 10
*/
