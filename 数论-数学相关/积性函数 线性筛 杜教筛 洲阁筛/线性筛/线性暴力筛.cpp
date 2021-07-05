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
const LL maxn=1e7+107;
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

const int MAX=1e7+7;
int P[maxn/10],tot;
bitset<MAX> mark;
int nowq[maxn],nowp[maxn];
int base[maxn],tmp[maxn],fin[maxn];//base:not mul; tmp: p^k; fin:final-ans
void solve(int p,int q) {
    int i;
    base[1]=tmp[1]=fin[1]=1;
    nowp[1]=nowq[1]=1;
    rep(i,2,MAX) mark[i]=0; tot=0;//clear
    rep(i,2,MAX) {
        // get i^k
        if (!mark[i]) {
            int pwp=powMM(i,p),pwq=powMM(i,q);
            for (ll j=i;j<MAX;j*=i) {
                nowp[j]=((ll)nowp[j/i]*pwp+1)%M;
                nowq[j]=((ll)nowq[j/i]*pwq+1)%M;
                fin[j]=nowq[j];
                for (ll k=1;k<j;k*=i) {//same as p-tot
                    // printf("%lld -> %lld\n",j,k*i);
                    add_(fin[j],M-((ll)fin[k]*nowp[j/k])%M);
                }
            }
            P[tot++]=i,base[i]=1,tmp[i]=i;
        } int j;
        // get not i^k
        REP(j,tot){//base: not multi
            int k=i*P[j];
            if (k>=MAX) break;
            mark[k]=1;
            if (i%P[j]==0) {
                base[k]=base[i]; tmp[k]=tmp[i]*P[j];
                fin[k]=((ll)base[k]*fin[tmp[k]])%M;
                break;
            } else {//new
                base[k]=fin[i]; tmp[k]=P[j];
                fin[k]=((ll)base[k]*fin[tmp[k]])%M;
            }
            // printf("get %d: %d  %d\n",k,tmp[k],P[j]);
        }
    }
    // printf("tot=%d\n",tot);
}
int main() {
    int n,p,q; scanf("%d%d%d",&n,&p,&q);
    // double t=clock();
    solve(p,q);
    // printf("%f\n",clock()-t);
    int i; int ans=0;
    FOR(i,1,n) ans^=fin[i];
    printf("%d\n",ans);
    // FOR(i,1,n) printf("%d ",fin[i]);
}
/*
20 0 3
10000000 0 3
*/