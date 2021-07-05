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

//板子调了半天
//mod数字中的所有数字=0
//做法:lca最大2520,而且这样的lca数字不多，压位直接DP
vector<int> V;
LL f[27][57][2527];
int value[27];
int lca[1<<10|7];
LL calc(int x,int used,int remain,int limit){
//    printf("%d %x %d %d; lca=%d\n",x,used,remain,limit,V[lca[used]]);
    if (x==0) return (remain%V[lca[used]]==0);
    if (!limit&&f[x][lca[used]][remain]!=-1) return f[x][lca[used]][remain];
    LL ret=0;int i,k=10;
    if (limit) k=min(k,value[x]);
    REP(i,k){
        ret+=calc(x-1,used|(1<<i),(remain*10+i)%2520,0);
    }if (limit) return ret+calc(x-1,used|(1<<k),(remain*10+k)%2520,1);
    else return f[x][lca[used]][remain]=ret;
}LL calc(LL x){
    int length=0;
    while (x) value[++length]=x%10,x/=10;
    return calc(length,0,0,1);
}LL calc(LL l,LL r){
    return calc(r)-calc(l-1);
}
int n,m;
int i,j,k;
int T;
int main(){
    lca[0]=1;
    REP(i,(1<<10)) REP(j,10) {
        int value;
        if (j!=0) value=lca[i]*j/gcd(j,lca[i]);else value=lca[i];
        lca[i|(1<<j)]=value;
    }REP(i,(1<<10)) V.push_back(lca[i]);
    sort(V.begin(),V.end());
    V.erase(unique(V.begin(),V.end()),V.end());
    REP(i,(1<<10)) lca[i]=lower_bound(V.begin(),V.end(),lca[i])-V.begin();
//    REP(i,10000) if (calc(i,i)) printf("%d ",i);
    memset(f,0xff,sizeof(f));
    scanf("%d",&T);
    while (T--){
        LL l,r;
        scanf("%I64d%I64d",&l,&r);
        printf("%I64d\n",calc(l,r));
    }
}
/*
10
1 1000000000000000000
*/
