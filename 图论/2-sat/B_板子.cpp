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
const LL maxn=1000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M; return ret;}

struct T_SAT {
    struct enode {
        int to,next;
        enode(int _to=0,int _next=-1):to(_to),next(_next) {};
    } edge[maxn*maxn*2];
    int head[maxn*2],etot;
    void addedge(int u,int v) {
        edge[++etot]=enode(v,head[u]);
        head[u]=etot;
    }
    int dfn[maxn*2],low[maxn*2],belong[maxn*2];
    bool vis[maxn*2];
    int tot,cnt;
    int S[maxn*2],top;
    void dfs(int x) {
        dfn[x]=low[x]=++tot;
        S[++top]=x;
        vis[x]=1;
        for (int i=head[x]; ~i; i=edge[i].next) {
            int v=edge[i].to;
            if (!dfn[v]) {
                dfs(v);
                low[x]=min(low[x],low[v]);
            } else if (vis[v])
                low[x]=min(low[x],dfn[v]);
        }
        if (dfn[x]==low[x]) {
            cnt++;
            while (1) {
                int now=S[top--];
                vis[now]=0;
                belong[now]=cnt;
                if (now==x) break;
            }
        }
    }
    void init(int n) {
        int i;
        REP(i,2*n) head[i]=-1;
        etot=0;
    }
    bool solve(int n) {
        int i;
        tot=cnt=0;
        REP(i,2*n) dfn[i]=vis[i]=0;
        REP(i,2*n) if (!dfn[i]) dfs(i);
        REP(i,n) if (belong[i]==belong[i+n]) return 0;
        return 1;
    }
} two_sat;
int n,m;
int i,j;
int a1,a2,c1,c2;
int main() {
    while (~scanf("%d%d",&n,&m)) {
        two_sat.init(n);
        REP(i,m) {
            scanf("%d%d%d%d",&a1,&a2,&c1,&c2);
            if (c1==1&&c2==1) {
                two_sat.addedge(a1+n,a2);
                two_sat.addedge(a2+n,a1);
            } else if (c1==0&&c2==1) {
                two_sat.addedge(a1,a2);
                two_sat.addedge(a2+n,a1+n);
            } else if (c1==1&&c2==0) {
                two_sat.addedge(a1+n,a2+n);
                two_sat.addedge(a2,a1);
            } else if (c1==0&&c2==0) {
                two_sat.addedge(a1,a2+n);
                two_sat.addedge(a2,a1+n);
            }
        }
        if (two_sat.solve(n)) puts("YES");
        else puts("NO");
    }
}
/*
*/
