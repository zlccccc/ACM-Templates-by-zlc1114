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
const LL maxn=2e6+107;
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

namespace NTT {
    const int maxn=1<<21|7;
    const ll MOD=998244353;
    const ll g=3;
    int wn[maxn],invwn[maxn];
    ll mul(ll x,ll y) {
        return x*y%MOD;
    }
    ll poww(ll a,ll b) {
        ll ret=1;
        for (; b; b>>=1ll,a=mul(a,a))
            if (b&1) ret=mul(ret,a);
        return ret;
    }
    void initwn(int l) {
        static int len=0;
        if (len==l) return; len=l;
        ll w=poww(g,(MOD-1)/len); int i;
        ll invw=poww(w,MOD-2); wn[0]=invwn[0]=1;
        rep(i,1,len) {
            wn[i]=mul(wn[i-1],w);
            invwn[i]=mul(invw,invwn[i-1]);
        }
    }
    void ntt(ll *A,int len,int inv) {
        int i,j,k; initwn(len);
        for (i=1,j=len/2; i<len-1; i++) {
            if (i<j) swap(A[i],A[j]);
            k=len/2;
            while (j>=k) j-=k,k/=2;
            if (j<k) j+=k;
        } for (i=2; i<=len; i<<=1) {
            for (j=0; j<len; j+=i) {
                for (k=j; k<(j+i/2); k++) {
                    ll a,b; a=A[k];
                    if (inv==-1) b=mul(A[k+i/2],invwn[(ll)(k-j)*len/i]);
                    else b=mul(A[k+i/2],wn[(ll)(k-j)*len/i]);
                    A[k]=(a+b); (A[k]>=MOD) &&(A[k]-=MOD);
                    A[k+i/2]=(a-b+MOD); (A[k+i/2]>=MOD) &&(A[k+i/2]-=MOD);
                }
            }
        } if (inv==-1) {
            ll vn=poww(len,MOD-2);
            REP(i,len) A[i]=mul(A[i],vn);
        }
    }
    void mul(ll *A,ll *B,ll *C,int len) { //C=A*B
        int i;
        ntt(A,len,1); ntt(B,len,1);
        REP(i,len) C[i]=mul(A[i],B[i]);
        ntt(C,len,-1);
    }
    static ll A[maxn],B[maxn];
    void multiply(ll *a,ll *b,ll *ans,int n,int m) {//C=A*B(actual)
        int len=1,i;
        while (len<n+m-1) len<<=1; 
        REP(i,n) A[i]=a[i]; rep(i,n,len) A[i]=0;
        REP(i,m) B[i]=b[i]; rep(i,m,len) B[i]=0;
        mul(A,B,ans,len);
    }
}
// 分治fft
// C[i+j] = \sum A[i]*B[j] {i<j}
int Size=8,n,k;
ll A[maxn],B[maxn];
ll Ans[maxn],tmpA[maxn],tmpB[maxn],tmpC[maxn];
void solve(int l,int r) {
    if (l+l+1>k) return;//min:l+l
    if (r-l+1<=Size) {
        int i,j;
        FOR(i,l,r) FOR(j,i+1,r) add_(Ans[i+j],A[i]*B[j]*2%M);
        return;
    }
    int mid=(l+r)/2,i;
    solve(l,mid);
    if (l+mid+1<=k) {
        FOR(i,l,mid) tmpA[i-l]=A[i]; // C:tmp
        FOR(i,mid+1,r) tmpB[i-mid-1]=B[i]; // C:tmp
        NTT::multiply(tmpA,tmpB,tmpC,mid-l+1,r-mid);
        FOR(i,0,r-l-1) add_(Ans[i+mid+1+l],tmpC[i]*2%M);
    }
    solve(mid+1,r);
}
//mex(x)<mex(y):
//mex(x)==mex(y): only if A[mex+1]=0
ll pw2[3][maxn],C[maxn];
// ll Ans[maxn];
int main() {
    int i,j;
    scanf("%d%d",&n,&k);
    FOR(i,0,n) scanf("%lld",&C[i]);
    //mx from 1 to n-1
    FOR(i,0,n+1) {
        pw2[0][i]=powMM(2,C[i]);
        pw2[1][i]=(powMM(2,C[i])+M-1)%M;
        pw2[2][i]=(powMM(2,C[i])+M-2)%M;
    }
    FOR(i,1,n+1) REP(j,3) mul_(pw2[j][i],pw2[j][i-1]);
    FOR(i,0,n+1) {
        if (i&&C[i-1]<1) break;//have
        A[i]=B[i]=1;
        if (i) mul_(A[i],pw2[2][i-1]);
        mul_(A[i],powMM(pw2[1][i],M-2));
        if (i) mul_(B[i],pw2[1][i-1]);
        mul_(B[i],powMM(pw2[0][i],M-2));
        mul_(B[i],pw2[0][n]);
    } int last=n+1; //not zero
    if (C[i-1]<1) last=i-1;
    // printf("last=%d\n",last);
    // FOR(i,0,n+1) {//A[i+1] is true?
    //     if (i&&C[i-1]==0) break;//have
    //     //f(mx,my)[mx<my]=\mul[0->x-1]{a[i]-1}*{a[i+1]!=0}(inside)*\mul[x+2->y]{a[i]}*pow(2,\sum{y+2->n})
    //     // FOR(j,i+1,n+1) {
    //     // add_(Ans[i+i],M-(ll)A[i]*A[i]%M);
    //     FOR(j,i+1,n+1) {
    //         // if (j&&C[j-1]==0) break;//have
    //         int k;
    //         ll nowans=1;
    //         // printf("i,j=%d %d; A,B=%lld,%lld\n",i,j,A[i],B[j]);
    //         mul_(nowans,A[i]);
    //         mul_(nowans,B[j]);
    //         // if (i) nowans=nowans*pw2[2][i-1];
    //         // mul_(nowans,pw2[1][j-1]);
    //         // mul_(nowans,powMM(pw2[1][i],M-2));
    //         // mul_(nowans,pw2[0][n]);
    //         // mul_(nowans,powMM(pw2[0][j],M-2));
    //         // FOR(k,0,i-1) mul_(nowans,powMM(2,C[k])-2);//all have
    //         // FOR(k,i+1,j-1) mul_(nowans,powMM(2,C[k])-1);
    //         // FOR(k,j+1,n) mul_(nowans,powMM(2,C[k]));
    //         add_(Ans[i+j],nowans*2);
    //         // printf("i,j=%d %d: %lld\n",i,j,nowans*2);
    //     }
    // }
    // printf("last=%d; %d %d/%d\n",last,pw2[2][last-1],pw2[0][n],pw2[0][last]);
    solve(0,n+1);
    if (last==0) add_(Ans[0],pw2[0][n]);
    else if (A[last-1]>=2) add_(Ans[last+last],pw2[2][last-1]*pw2[0][n]%M*powMM(pw2[0][last],M-2)%M);
    // FOR(i,0,k) printf("%lld ",Ans[i]%M);
    FOR(i,0,k) printf("%lld ",Ans[i]%M);
}
/*
0 2
2
*/