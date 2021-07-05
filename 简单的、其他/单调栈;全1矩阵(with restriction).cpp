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
const LL M=998244353;
const LL maxn=1e5+107;
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
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

// jisuanke
// https://www.jisuanke.com/contest/11347/challenges E
// 题意: x和y有倍数关系的全1矩阵
// 做法就单纯是个预处理下单调栈前缀和
ll C[1007][1007];
int U[1007][1007];
char str[1007][1007];
int S[1007];//stack
int main() {
    int i,j,k,n;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%s",str[i]+1);
    FOR(i,1,n) FOR(j,1,n) {
        if (str[i][j]=='1') U[i][j]=U[i-1][j]+1;
        else U[i][j]=0;
    }
    // FOR(i,1,n) FOR(j,1,n) printf("%d%c",U[i][j]," \n"[j==n]); puts("<- U");
    FOR(i,1,n) FOR(j,1,n) {
        if (i%j==0||j%i==0) {
        // if (1) {
            FOR(k,i,n) C[k][j]+=k-i+1;
        }
    }
    // FOR(i,1,n) FOR(j,1,n) printf("%d%c",C[i][j]," \n"[j==n]);
    FOR(i,1,n) FOR(j,1,n) {//sum
        C[i][j]+=C[i][j-1];
    }
    // FOR(i,1,n) FOR(j,1,n) printf("%d%c",C[i][j]," \n"[j==n]);
    ll ans=0;
    FOR(i,1,n) {
        // printf("i=%d\n",i);
        int top=0;
        FOR(j,1,n+1) {
            while (top&&U[i][S[top]]>U[i][j]) {
                int r=S[top],l=S[top-1]; top--;
                int H=U[i][r],h=max(U[i][l],U[i][j]);
                int w=j-l-1;
                ll now=C[w][H]-C[w][h];
                // printf("j=%d : add %d (%d-%d) = %d\n",j,w,h,H,now);
                ans+=now;
            } S[++top]=j;
            // int k; FOR(k,1,top) printf("%d ",S[k]); puts("<S");
        }
    }
    printf("%lld\n",ans);
}
/*
*/