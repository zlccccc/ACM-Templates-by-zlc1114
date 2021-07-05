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

//当板子了
//这道题是连续的差最大是1
//需要注意时间空间限制,有时需要hash
//注意取模时底下calc也要取-_-
LL f[27][27][3];
int value[27];
LL calc(int x,int prev,int is13,int flag){
//    printf("%d %x %d %d; lca=%d\n",x,used,remain,flag,V[lca[used]]);
    if (x==0) return (prev==0&&is13==2);
    if (!flag&&f[x][prev][is13]!=-1) return f[x][prev][is13];
    LL ret=0;int i,maxi=9;
    if (flag) maxi=min(maxi,value[x]);
    FOR(i,0,maxi){
//        if (not_0||i)//这是与lead_0有关的写法
        if (is13==2) ret+=calc(x-1,(prev*10+i)%13,2,flag&&(i==maxi));
        else if (i==1) ret+=calc(x-1,(prev*10+i)%13,1,flag&&(i==maxi));
        else if (i==3&&is13) ret+=calc(x-1,(prev*10+i)%13,2,flag&&(i==maxi));
        else ret+=calc(x-1,(prev*10+i)%13,0,flag&&(i==maxi));
    }if (!flag) f[x][prev][is13]=ret;
    return ret;
}int k;
LL calc(LL x){
    int length=0;
    while (x) value[++length]=x%10,x/=10;
    return calc(length,0,0,1);
}LL calc(LL l,LL r){
    return calc(r)-calc(l-1);
}
int n,m;
int i,j;
int T;
int main(){
    memset(f,0xff,sizeof(f));
//    FOR(i,1,10000) if (calc(i,i)) printf("%d ",i);puts("");
//    scanf("%d",&T);
    LL l,r;l=1;
    while (~scanf("%lld",&r)){
        printf("%lld\n",calc(l,r));
    }
}
/*
10
1 10
*/
