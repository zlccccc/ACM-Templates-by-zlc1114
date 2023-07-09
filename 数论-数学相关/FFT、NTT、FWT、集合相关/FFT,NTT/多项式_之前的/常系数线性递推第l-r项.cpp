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

// Cayley-Hamilton定理
// F(A)=0; A是个矩阵, F是特征多项式
// 特征多项式=1/生成函数(即分母)
// 求出x^k % A即可, 这个就是贡献的k
namespace NTT {
    const int maxn=1<<20|7;
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
    void inv(ll *A,ll *B,int l) { //B=inv(A)
        static ll C[maxn];
        B[0]=poww(A[0],MOD-2); B[1]=0;
        for (int len=2; len<=l; len<<=1) {
            int i; fill(B+len,B+len+len,0);
            copy(A,A+len,C); fill(C+len,C+len+len,0);
            ntt(C,len*2,1); ntt(B,len*2,1);
            REP(i,len*2) B[i]=mul(B[i],(MOD+2-mul(C[i],B[i])));
            ntt(B,len*2,-1); fill(B+len,B+len+len,0);
        }
    }
    static ll A[maxn],B[maxn];
    void multiply(ll *a,ll *b,ll *ans,int n,int m) {//C=A*B(actual)
        int len=1,i;
        while (len<n+m-1) len<<=1;
        REP(i,n) A[i]=a[i]; rep(i,n,len) A[i]=0;
        REP(i,m) B[i]=b[i]; rep(i,m,len) B[i]=0;
        mul(A,B,ans,len);
    }
    void inverse(ll *a,ll *ans,int n) {
        int len=1,i;
        while (len<n) len<<=1;
        REP(i,n) A[i]=a[i]; rep(i,n,len) A[i]=0;
        inv(A,ans,len);
    }
    void divide(ll *a,ll *b,ll *ans,int n,int m,int &l) {
        if (n<m) {l=1; ans[0]=0; return;}
        int len=1,i; l=n-m+1;
        while (len<n-m+1) len<<=1;
        REP(i,n) A[i]=a[i]; reverse(A,A+n); min_(n,l);
        REP(i,m) B[i]=b[i]; reverse(B,B+m); min_(m,l);
        rep(i,m,len) B[i]=0;
        inv(B,ans,len);
        multiply(A,ans,ans,len,n);
        reverse(ans,ans+l);
    }
    //ans1:答案; ans2:余数
    void delivery(ll *a,ll *b,ll *ans1,ll *ans2,int n,int m,int &l1,int &l2) {
        divide(a,b,ans1,n,m,l1); l2=min(n,m-1);
        static ll tmp[maxn];
        multiply(b,ans1,tmp,m,l1);
        int i; REP(i,l2) ans2[i]=(a[i]-tmp[i]+M)%M;
        while (l2!=1&&ans2[l2-1]==0) l2--;
    }
}
ll A[maxn],B[maxn];
ll C[maxn],D[maxn],E[maxn];
int main() {
    ll l,r;
    scanf("%d%lld%lld",&n,&l,&r); int i;
    FOR(i,1,n) scanf("%lld",&A[i]),A[i]=B[i]=(M-A[i]%M);
    A[0]=1; while (A[n]==0) n--; m=n;
    n+=r-l; n++;
    NTT::inverse(A,A,n*2);
    m++; B[0]=1; reverse(B,B+m);//no!
    C[1]=1; D[0]=1; int lC=2,lD=1;
    for (ll x=l; x; x>>=1) {
        if (x&1) {
            NTT::multiply(C,D,D,lC,lD); int l1;
            NTT::delivery(D,B,E,D,lC+lD-1,m,l1,lD);
        } NTT::multiply(C,C,C,lC,lC); int l1;
        NTT::delivery(C,B,E,C,lC+lC-1,m,l1,lC);
    } reverse(D,D+lD);
    NTT::multiply(D,A,E,lD,n);
    FOR(i,lD-1,r-l+lD-1) printf("%lld\n",E[i]);
    return 0;
}
/*
4 100 200 
1 2 3 4
*/
