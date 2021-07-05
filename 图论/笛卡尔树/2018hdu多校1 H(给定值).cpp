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
const LL maxn=1e6+7;
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

// 按照A从大到小建笛卡尔树
int A[maxn],fa[maxn],id[maxn];//id: topo
void buildtree(int n){
    static int S[maxn],top,tot,i;
    tot=top=0;
    FOR(i,1,n){
        int now=0;
        while (top&&A[S[top]]<A[i]){
            if (now) fa[now]=S[top],id[++tot]=now;//pop
            now=S[top];  top--;
        } S[++top]=i;
        if (now) fa[now]=S[top],id[++tot]=now;//pop
    } int now=0;
    while (top){
        if (now) fa[now]=S[top],id[++tot]=now;
        now=S[top]; top--;
    } fa[now]=0; id[++tot]=now;
    reverse(id+1,id+1+n);// 变成正的
    // FOR(i,1,n) printf("%d ",fa[i]);puts("");
    // FOR(i,1,n) printf("%d ",id[i]);puts("");
    // printf("tot=%d\n",tot);
}
int inv[maxn];
int sz[maxn];//求树的size
int main() {
    int T,_t;
    int i;
    FOR(i,1,1000000) inv[i]=powMM((ll)i,M-2);
    scanf("%d",&T);
    FOR(_t,1,T){
        scanf("%d",&n);
        FOR(i,1,n) scanf("%d",&A[i]);
        buildtree(n);
        int ans=(ll)n*inv[2]%M;
        FOR(i,1,n) sz[i]=1;
        rFOR(i,2,n) sz[fa[id[i]]]+=sz[id[i]];
        FOR(i,1,n) mul_(ans,inv[sz[i]]);
        printf("%d\n",ans);
    }
}
/*
*/
