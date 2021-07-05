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
#include <bitset>
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
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

struct Edge {
    int u,v,val;
} edge[maxn];
int head[maxn];
bool cmp(Edge &A,Edge &B){
    return A.val<B.val;
};
int fa[maxn];
ULL sum[maxn],cnt[maxn];
inline int getfa(int x){
    if (fa[x]==x) return x;
    int y=getfa(fa[x]);
    if (fa[x]!=y) sum[x]+=sum[fa[x]];
    fa[x]=y;
    return y;
}
int solve(){
    int n,m;
    scanf("%d%d",&n,&m);
    int i;
    REP(i,m)
        scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].val);
    sort(edge,edge+m,cmp);
    FOR(i,1,n) fa[i]=i,sum[i]=0,cnt[i]=1;
    REP(i,m){
        int x=getfa(edge[i].u),y=getfa(edge[i].v);
        if (x==y) continue;
        if (cnt[x]>cnt[y]) swap(x,y);
        sum[y]+=cnt[x]*edge[i].val;
        sum[x]+=cnt[y]*edge[i].val;
        sum[x]-=sum[y];fa[x]=y;
        cnt[y]+=cnt[x];
//      printf("link: %d(%I64d,%I64d)-%d(%I64d,%I64d); %d\n",x,cnt[x],sum[x],y,cnt[y],sum[y],edge[i].val);
//      int j;
//      FOR(j,1,n){
//          int x=getfa(j);
//          LL val=sum[j];
//          if (x!=j) val+=sum[x];
//          printf("%d:%I64d ",j,val);
//      }puts("");
    }ULL ans=0;
    FOR(i,1,n){
        int x=getfa(i);
        ULL val=sum[i];
        if (x!=i) val+=sum[x];
        // printf("%d:%I64d ",i,val);
        ans^=(ULL)i*val;
    }static int x=0;;
    printf("Case #%d: %llu\n",++x,ans);
    return 0;
}
int main() {
    int T;
    scanf("%d",&T);
    while (T--) solve();
    return 0;
}
/*
*/
