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
const LL maxn=1.2e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,ull k=64) {ull i; REP(i,k) debug("%d",(int)((x>>i)&1)); putchar(' ');}
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

const int K_K=16+1;
namespace ST {
    const int maxn=1<<K_K;
    int ST[maxn][K_K],t_t[maxn];//only L
    inline void initST(int n,const int id[],const int A[]) { //0 to n-1
        int i,j; assert(n<=maxn);
        rep(i,1,n) t_t[i]=t_t[i>>1]+1;
        REP(i,n) {
            ST[i][0]=id[i];
            rep(j,1,t_t[i+1]) {
                int u=ST[i-(1<<(j-1))][j-1],v=ST[i][j-1];
                ST[i][j]=A[u]>=A[v]?u:v;
            }
        }
    }
    inline int RMQ(int x,int y,const int A[]) {
        int t=t_t[y-x+1]-1;
        x=ST[x+(1<<t)-1][t]; y=ST[y][t];
        return A[x]>=A[y]?x:y;
    }
}
namespace RMQ01 {//start from 0; return the First Maximize Value Position
    const int maxn=1<<K_K;
    inline int B(int x) {return x>>4;}
    int BLOCK[maxn],MAXP[maxn],BMAX[maxn];
    inline int value(int l,int r) {//0000xxxx1111  // & mid | right
        int mid=((1<<((r&15)+1))-1)^((1<<((l&15)+1))-1);
        int right=((1<<16)-1)^((1<<((r&15)+1))-1);
        // printf(" get value %d %d ",l,r); pr2(mid,16); pr2(right,16); 
        // pr2((BLOCK[B(l)]&mid)|right,16); printf("<- final pos=%d\n",MAXP[(BLOCK[B(l)]&mid)|right]);
        return MAXP[(BLOCK[B(l)]&mid)|right]+(l&~15);
    }
    void dfs_value(int x=0,int depth=15,int maxval=0,int maxpos=0) {
        if (maxval<=0) maxpos=0,maxval=0;
        if (depth==0) {MAXP[x<<1]=MAXP[x<<1|1]=maxpos; return;}
        dfs_value(x<<1,depth-1,maxval+1,maxpos+1);
        dfs_value(x<<1|1,depth-1,maxval-1,maxpos+1);
    }
    void build(int n, int A[]) {//0:+1; 1:-1 //start from (1-15); g[i]=A[i]-A[i-1]
        int i; dfs_value(); while (n&15) A[n]=A[n-1]-1,n++;
        // { // get the max position (left + k)
        //     rrep(i,65500,65536) { //MAXV: A[k]-A[i]
        //         // MAXV[i]=MAXV[i>>1]; MAXP[i]=MAXP[i>>1]+1;
        //         // if (MAXV[i]<=0) MAXV[i]=0,MAXP[i]=0;
        //         // MAXV[i]-=(1-((i&1)<<1));
        //         int k,maxpos=0,maxval=0,nowval=0;
        //         rep(k,1,16) {
        //             int now=(i>>k)&1;
        //             if (now==0) nowval++;
        //             else nowval--;
        //             if (nowval>maxval) maxpos=k,maxval=nowval;
        //         }
        //         pr2(i,16);
        //         printf("Test  %d: %d(%d) %d(%d)\n",i,MAXP[i],MAXV[i],maxpos,maxval);
        //     }
        // }
        //build
        memset(BLOCK,0,sizeof(BLOCK));
        rrep(i,1,n) BLOCK[B(i)]=BLOCK[B(i)]<<1|(1-((A[i]-A[i-1]+1)>>1));
        BLOCK[0]<<=1;
        REP(i,B(n-1)+1) BMAX[i]=MAXP[BLOCK[i]]+(i<<4);
        ST::initST(B(n-1)+1,BMAX,A);
    }
    int RMQ01(int x,int y,const int A[]) {
        int rx=B(x)<<4|15,ly=B(y)<<4;
        // printf("value=%d ",value(x,y)); pr2(BLOCK[B(x)],16); printf(" <- value %d %d; block\n",x,y);
        if (y<=rx) return value(x,y);
        int u=value(x,rx),v;
        if (rx+1!=ly) v=ST::RMQ(B(x)+1,B(y)-1,A),u=A[u]>=A[v]?u:v;
        v=value(ly,y); u=A[u]>=A[v]?u:v;
        // printf("rx,ly=%d %d\n",rx,ly);
        return u;
    }
}
int A[1000007];
int MAX(int x,int y) {
    int k,ans=-INF,pos=0;
    FOR(k,x,y) if (A[k]>ans) pos=k,ans=A[k];
    return pos;
}
int main() {
    srand(time(0));
    int i,n=100;
    rep(i,1,n) A[i]=((rand()&1)*2-1)+A[i-1];
    // REP(i,30) printf("%d ",A[i]); puts("");
    RMQ01::build(n,A);
    FOR(i,1,n) {
        int l,r; l=rand()%n,r=rand()%n;
        if (l>r) swap(l,r);
        assert(MAX(l,r)==RMQ01::RMQ01(l,r,A));
        // printf("(%d-%d): %d %d\n",l,r,MAX(l,r),RMQ01::RMQ01(l,r,A));
        // printf("(%d-%d): (%d)%d (%d)%d\n",l,r,MAX(l,r),A[MAX(l,r)],RMQ01::RMQ01(l,r,A),A[RMQ01::RMQ01(l,r,A)]);
    }
}
/*
*/