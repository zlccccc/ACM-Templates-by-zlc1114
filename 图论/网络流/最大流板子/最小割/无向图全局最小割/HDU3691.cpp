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
const LL M=1e9+9;
const LL maxn=1e6+7;
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

LL edge[507][507];
bool deleted[maxn],vis[maxn];
vector<int> id;
LL weight[maxn];
LL getst(int &s,int &t,int n){
    int i;t=1;
    for (int v:id) weight[v]=0,vis[v]=0;
    REP(i,n-1){
        vis[s=t]=1;
        for (int v:id) if (!vis[v])
            weight[v]+=edge[s][v],t=v;
        for (int v:id) if (!vis[v])
            if (weight[v]>=weight[t]) t=v;
        if (!weight[t]) return 0;
    }return weight[t];
}
LL mincut(int n){
    LL ret=INFF;
    int s,t,i,j,k;
    FOR(i,1,n) deleted[i]=0;
    rFOR(i,2,n){
        j=0;id.clear();
        FOR(k,1,n) if (!deleted[k]) id.push_back(k);
        ret=min(ret,getst(s,t,id.size()));
        if (!ret) return 0;
        for (int v:id) if (v!=s&&v!=t){
            edge[s][v]+=edge[t][v];
            edge[v][s]+=edge[v][t];
        }deleted[t]=1;
    }return ret;
}
int n,m;
int main() {
    int i,j;
    int T;
    while (~scanf("%d%d%*d",&n,&m)&&(n||m)){
        FOR(i,1,n) FOR(j,1,n) edge[i][j]=0;
        FOR(i,1,m){
            int u,v,val;
            scanf("%d%d%d",&u,&v,&val);
            edge[u][v]+=val;
            edge[v][u]+=val;
        }printf("%lld\n",mincut(n));
    }
    return 0;
}
/*
5 5 1
1 2 5
2 4 6
1 3 7
3 4 3
5 1 10
0 0 0
*/
