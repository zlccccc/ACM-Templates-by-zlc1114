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

#define DEBUG1
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
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
template<typename T>inline void print2(T x,int k=64) {ll i; rREP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B) {A+=B; (A>=M) &&(A-=M);}
template<typename T>inline void mul_(T &A,ll B) {(A*=B)%=M;}
template<typename T>inline void mod_(T &A,ll B=M) {A%=M;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int n,m;
char S[maxn];
int TaskA();
void Task_one() {TaskA();}
void Task_T() {int T; scanf("%d",&T); while (T--) TaskA();}
void Task_more_n() {while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m() {while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_string() {while (~scanf("%s",S)) TaskA();}

// 斯坦纳树, 求min_length很简单.. min_cnt会重复计算, 所以从小到大计算
// len=1, 求方案数
struct info {
    int min,cnt;
    info(int _min=INF,int _cnt=0):min(_min),cnt(_cnt) {};
} f[1<<12|7][57],g[1<<12|7][57];
inline void add(info &A,info B) {
    if (A.min>B.min) A=info(B.min,0);
    if (A.min==B.min) add_(A.cnt,B.cnt);
}
inline info merge(info A,info B) {
    info ret(A.min+B.min,(ll)A.cnt*B.cnt%M);
    if (ret.min>n) ret.min=n,ret.cnt=0;
    return ret;
}
vector<int> edge[maxn];
vector<int> have[maxn];
int now[maxn],dep[maxn],vis[maxn];
int TaskA() {
    int i,j,_,maxs;
    scanf("%d",&_); maxs=1<<_;
    REP(i,n) edge[i].clear();
    REP(i,m) {
        int u,v;
        scanf("%d%d",&u,&v);
        u--; v--;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    REP(i,maxs) REP(j,n) f[i][j]=g[i][j]=info(n,0);
    REP(i,n) {
        int cur=i<_?1<<i:0; vis[i]=-1;
        f[cur][i]=g[cur][i]=info(0,1);
    }
    int sta;
    REP(sta,maxs) {
        REP(i,n) {//f:last_op:addedge; g:no_limit
            if (i<_&&!((sta>>i)&1)) continue;
            int remove=i<_?1<<i:0; int remain=sta^remove;
            int lowbit=remain&-remain; // 防止重复计算, 一定注意这里是remain!
            if (remain)
                for (int pre=remain&(remain-1); pre; pre=remain&(pre-1)) if (pre&lowbit)
                        add(g[sta][i],merge(f[pre|remove][i],g[(sta^pre)|remove][i]));
            dep[i]=g[sta][i].min;
            if (dep[i]<n) have[dep[i]].push_back(i);
        } //?被卡常了?
        vector<int> Q;
        REP(i,n) {
            for (auto x:have[i]) {
                if (vis[x]==sta) continue;
                Q.push_back(x); vis[x]=sta;
            } for (auto x:Q) {
                info now=info(g[sta][x].min+1,g[sta][x].cnt);
                for (auto v:edge[x]) {
                    if (!(v<_&&!((sta>>v)&1))) {
                        if (dep[v]>dep[x]+1) {
                            dep[v]=dep[x]+1;
                            have[dep[v]].push_back(v);
                        }
                    } int nxtsta=v<_?sta|(1<<v):sta;
                    add(g[nxtsta][v],now); add(f[nxtsta][v],now);
                }
            } Q.clear(); have[i].clear();
        }
    } // printf("%d %d\n",g[maxs-1][1].min,g[maxs-1][1].cnt);
    printf("%d\n",g[maxs-1][1].cnt);
    return 0;
}
void initialize() {}
int main() {
    int startTime=clock();
    //initialize
    initialize();
    debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
    Task_more_n_m();
}
/*
*/
