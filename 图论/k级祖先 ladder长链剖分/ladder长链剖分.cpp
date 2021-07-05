#include <sstream>
#include <fstream>
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

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

namespace ladder {
    vector<int> edge[maxn];
    int id[maxn]; int tot;
    int fa[maxn][21],son[maxn],top[maxn],len[maxn],dep[maxn];
    vector<int> ladder[maxn];
    int upp[maxn];
    void dfs(int x,int father=0) {
        fa[x][0]=father; id[++tot]=x;
        for (int v:edge[x]) if (v!=father) dfs(v,x);
    }
    void buildfa() {
        int i,j; dep[id[1]]=0;
        FOR(i,1,tot) rep(j,1,21) fa[i][j]=fa[fa[i][j-1]][j-1],dep[i]=dep[fa[i][0]]+1;
        rFOR(i,1,tot) {
            int o=0,x=id[i]; top[x]=x;
            ladder[x].clear();
            for (int v:edge[x]) if (v!=fa[x][0]){
                if (!o||len[o]<len[v]) o=v;
            } if (o) len[x]=len[o]+1; else o=0;
            son[x]=o; top[x]=x;
        } FOR(i,1,tot) if (son[id[i]]) top[son[id[i]]]=top[id[i]];
        rFOR(i,1,tot) ladder[top[id[i]]].push_back(id[i]);
        FOR(i,2,tot) {
            int x=id[i];
            if (top[x]==x) {
                for (int y=fa[x][0],c=len[x]; y&&c; y=fa[y][0],c--)
                    ladder[x].push_back(y);
            }
        } upp[0]=-1;
        FOR(i,1,tot) upp[i]=upp[i-1]+(i==(i&-i));
    }
    int prev(int x,int k) {
        if (!k) return x;
        if (dep[x]<=k) return 0;
        x=fa[x][upp[k]]; k-=1<<upp[k];
        k-=dep[x]-dep[top[x]]; x=top[x];
        return ladder[x][len[x]+k];
    }
}
using namespace ladder;
int main() {
    int i;
    scanf("%d%d",&n,&m);
    FOR(i,1,n-1){
        int u,v;
        scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        // edge[v].push_back(u);
    } dfs(1,0); buildfa();
    FOR(i,1,m){
        int x,k;
        scanf("%d%d",&x,&k);
        printf("%d\n",prev(x,k));
    }
}
/*
*/
