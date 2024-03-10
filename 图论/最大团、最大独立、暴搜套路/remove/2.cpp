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
const LL maxn=50+7;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M; return ret;}

int n;
int ans;
int edge[maxn][maxn],cnt[maxn],vis[maxn];//vis:ÔªËØ
bool dfs(int u,int pos) {
    int i,j;
    FOR(i,u+1,n) {
        if (cnt[i]+pos<=ans) return 0;
        if (edge[u][i]) {
            REP(j,pos) if (!edge[i][vis[j]]) break;
            if (j==pos) {
                vis[pos]=i;
                if (dfs(i,pos+1)) return 1;
            }
        }
    }
    if (pos>ans) {ans=pos;return 1;}
    return 0;
}
int maxclique() {
    int i; ans=-1;
    rFOR(i,1,n) {
        vis[0]=i;
        dfs(i,1);
        cnt[i]=ans;
    } return ans;
}
int main() {
    int k;
    int i,j;
    scanf("%d%d",&n,&k);
    FOR(i,1,n)FOR(j,1,n) scanf("%d",&edge[i][j]);
    maxclique();
    printf("%.16lf",0.5*k*k*(ans-1)/ans);
}
/*
4 4
0 1 0 1
1 0 1 0
0 1 0 1
1 0 1 0
*/
