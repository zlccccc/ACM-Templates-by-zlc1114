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

vector<int> V;
LL f[27][2];
int value[27];
LL calc(int x,int is4,int flag){
//    printf("%d %x %d %d; lca=%d\n",x,used,remain,flag,V[lca[used]]);
    if (x==0) return 1;
    if (!flag&&f[x][is4]!=-1) return f[x][is4];
    LL ret=0;int i,maxi=10;
    if (flag) maxi=min(maxi,value[x]);
    REP(i,maxi){
        if (i==9&&is4) continue;
        else if (i==4) ret+=calc(x-1,1,0);
        else ret+=calc(x-1,0,0);
    }if (flag){
        if (maxi==9&&is4);
        else if (maxi==4) ret+=calc(x-1,1,1);
        else ret+=calc(x-1,0,1);
        return ret;
    }else return f[x][is4]=ret;
}int k;
LL calc(LL x){
    int length=0;
    while (x) value[++length]=x%10,x/=10;
    return calc(length,0,1);
}LL calc(LL l,LL r){
    return calc(r)-calc(l-1);
}
int n,m;
int i,j;
int T;
int main(){
    memset(f,0xff,sizeof(f));
//    FOR(i,1,1000) if (!calc(i,i)) printf("%d ",i);
    scanf("%d",&T);
    while (T--){
        LL x;scanf("%lld",&x);
        printf("%lld\n",x-calc(1,x));
    }
}
/*
10
1 10 2
*/
