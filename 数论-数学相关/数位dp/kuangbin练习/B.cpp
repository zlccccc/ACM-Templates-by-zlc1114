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

//我真是石乐志不会做
//数字中严格LIS=k的数量
//用单调队列优化的方法,然后压位数位DP
vector<int> V;
LL f[27][1<<10|7][17][2];
int num[1<<10|7];
inline int get(int x,int i){
    int j=i;
    while (j<10&&!((x>>j)&1)) j++;
    x^=1<<i;if (j<10) x^=1<<j;
    return x;
}int value[27];
LL calc(int x,int used,int k,int not_0,int flag){
//    printf("%d %x %d %d; lca=%d\n",x,used,remain,flag,V[lca[used]]);
    if (x==0) return (num[used]==k);
    if (num[used]>k) return 0;
    if (!flag&&f[x][used][k][not_0]!=-1) return f[x][used][k][not_0];
    LL ret=0;int i,maxi=10;
    if (flag) maxi=min(maxi,value[x]);
    REP(i,maxi){
        if (not_0||i) ret+=calc(x-1,get(used,i),k,not_0||i,0);
        else ret+=calc(x-1,used,k,not_0||i,0);
    }if (flag) return ret+calc(x-1,get(used,maxi),k,not_0||maxi,1);
    else return f[x][used][k][not_0]=ret;
}int k;
LL calc(LL x){
    int length=0;
    while (x) value[++length]=x%10,x/=10;
    return calc(length,0,k,0,1);
}LL calc(LL l,LL r){
    return calc(r)-calc(l-1);
}
int n,m;
int i,j;
int T;
int main(){
    REP(i,(1<<10)) num[i]=num[i>>1]+(i&1);
    memset(f,0xff,sizeof(f));
//    k=2;FOR(i,1,10000) if (calc(i,i)) printf("%d ",i);
    scanf("%d",&T);
    while (T--){
        LL l,r;static int x;
        scanf("%lld%lld%d",&l,&r,&k);
        printf("Case #%d: %lld\n",++x,calc(l,r));
    }
}
/*
10
1 10 2
*/
