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
const LL maxn=2e6+7;
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

//题意:
//给一堆边, 每个生成树上的边贡献w[i]*max(dep[u],dep[v])
//问你生成树总贡献
//做法: 枚举生成树, 然后直接dp 两边cnt和len得到答案
//f:\sum{dep} g:\sum{cnt}
int e[17][17]; int ew[17][17];
int f[17][1<<12|7],g[17][1<<12|7];
int F[17][1<<12|7],G[17][1<<12|7];//F,G:link
int bit[1<<12|7];
int main() {
    int i,j;
    scanf("%d%d",&n,&m);
    REP(i,m) {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        u--; v--; e[u][v]++; e[v][u]++;
        ew[u][v]+=w; ew[v][u]+=w;
    } int sta;
    REP(i,n) g[i][1<<i]=1;
    REP(sta,(1<<n)) bit[sta]=bit[sta>>1]+(sta&1);
    REP(sta,(1<<n)) {
        REP(i,n) if ((sta>>i)&1) { //this_root
            int remain=sta^(1<<i);
            if (remain){
                int low=remain&-remain;//low写错了 =_=
                for (int now=remain; now ; now=(now-1)&remain) if (now&low){
                    int sta1=now,sta2=sta^sta1;
                    add_(f[i][sta],(ll)F[i][sta1]*g[i][sta2]%M);
                    add_(f[i][sta],(ll)G[i][sta1]*f[i][sta2]%M);
                    add_(g[i][sta],(ll)G[i][sta1]*g[i][sta2]%M);
                }
            } else g[i][sta]=1;
            REP(j,n) if (!((sta>>j)&1)&&e[i][j]){
                add_(F[j][sta],e[i][j]*(f[i][sta]+(ll)g[i][sta]*bit[sta]%M)%M);
                add_(G[j][sta],(ll)e[i][j]*g[i][sta]%M);
            }
        }
    } sta=(1<<n)-1; int ans=0;
    REP(i,n) REP(j,n) if (ew[i][j]&&i!=j){
        int s=sta^(1<<j);
        for (int now=s; now; now=(now-1)&s) if ((now>>i)&1){
            int sta1=now,sta2=sta^sta1;
            int cnt=(f[i][sta1]+(ll)bit[sta1]*g[i][sta1]%M)%M*g[j][sta2]%M;
            add_(ans,(ll)ew[i][j]*cnt%M);
        }
    } printf("%d\n",ans);
}
/*
*/