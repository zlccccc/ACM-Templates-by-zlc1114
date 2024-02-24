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
const LL maxn=3e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M; return ret;}

int fa[maxn][21];
int n,i,j;
int dep[maxn];
vector<int> edge[maxn];
void dfs(int x,int depth) {
    dep[x]=depth;
    for (int v:edge[x]) dfs(v,depth+1);
}
int lca(int x,int y) {
    int i;
    if (dep[x]<dep[y]) swap(x,y);
    rREP(i,20) if (dep[x]-dep[y]>=1<<i) x=fa[x][i];
    if (x==y) return x;
    rREP(i,20) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
int dis(int x,int y) {
    return dep[x]+dep[y]-2*dep[lca(x,y)];
}
int kthfa(int x,int k) {
    int i;
    rREP(i,20) if ((k>>i)&1) x=fa[x][i];
    return x;
}
int walk(int x,int y,int d) {
    int f=lca(x,y);
    if (dep[x]-dep[f]>=d) return kthfa(x,d);
    return kthfa(y,dep[x]+dep[y]-2*dep[f]-d);
}
vector<int> S1,S2;
int dis1,dis2,maxdis;
int main() {
    scanf("%d",&n); n++;
    FOR(i,2,n) {
        scanf("%d",&fa[i][0]);
        edge[fa[i][0]].push_back(i);
    }
    FOR(i,2,n) rep(j,1,20) fa[i][j]=fa[fa[i][j-1]][j-1];
    dfs(1,0);
    maxdis=0;
//  printf("dis=%d\n",dis(2,3));
    S1.push_back(1);
    FOR(i,2,n) {
        dis1=dis2=0;
        if (S1.size()) dis1=dis(S1[0],i);
        if (S2.size()) dis2=dis(S2[0],i);
        if (max(dis1,dis2)>maxdis) {
            maxdis=max(dis1,dis2);
            if (dis1>=dis2) {
                for (int v:S2) if (dis(i,v)==maxdis) S1.push_back(v);
                S2.clear();
                S2.push_back(i);
            } else {
                for (int v:S1) if (dis(i,v)==maxdis) S2.push_back(v);
                S1.clear();
                S1.push_back(i);
            }
        } else if (dis1==maxdis) S2.push_back(i);
        else if (dis2==maxdis) S1.push_back(i);
//      printf("%d %d\n",dis1,dis2);
        printf("%d\n",S1.size()+S2.size());
    }
}
/*
*/
