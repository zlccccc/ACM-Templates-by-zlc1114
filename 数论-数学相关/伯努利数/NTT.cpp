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
const LL maxn=1e6+107;
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

const int N=300020;

//const LL P = 50000000001507329LL; //190734863287 * 2 ^ 18 + 1 G = 3 常数巨大
// const int P = 1004535809; //479 * 2 ^ 21 + 1 G = 3
const int P = 998244353; // 119 * 2 ^ 23 + 1 G = 3
//const int P = 104857601;  // 25 * 2 ^ 22 + 1 G = 3
//const int P = 167772161; // 5 * 2 ^ 25 + 1 G = 3   
const int G = 3;    
 
int wn[25]; 
int n;
 
LL mul(LL x, LL y) {  
    return (x * y - (LL)(x / (long double)P * y + 1e-3) * P + P) % P;  
}  
  
  
int qpow(int x, int k, int p) {    
    int ret = 1;    
    while(k) {    
        if(k & 1) ret = 1LL * ret * x % p;    
        k >>= 1;    
        x = 1LL * x * x % p;    
    }    
    return ret;    
}    
    
void getwn() {    
    for(int i = 1; i <= 21; ++i) {    
        int t = 1 << i;    
        wn[i] = qpow(G, (P - 1) / t, P);    
    }    
}    
    
void change(int *y, int len) {    
    for(int i = 1, j = len / 2; i < len - 1; ++i) {    
        if(i < j) swap(y[i], y[j]);    
        int k = len / 2;    
        while(j >= k) {    
            j -= k;    
            k /= 2;    
        }    
        j += k;    
    }    
}    
    
void NTT(int *y, int len, int on) {    
    change(y, len);    
    int id = 0;    
    
    for(int h = 2; h <= len; h <<= 1) {    
        ++id;    
        for(int j = 0; j < len; j += h) {    
            int w = 1;    
            for(int k = j; k < j + h / 2; ++k) {    
                int u = y[k];    
                int t = 1LL * y[k+h/2] * w % P;    
                y[k] = u + t;    
                if(y[k] >= P) y[k] -= P;    
                y[k+h/2] = u - t + P;    
                if(y[k+h/2] >= P) y[k+h/2] -= P;    
                w = 1LL * w * wn[id] % P;    
            }    
        }    
    }    
    if(on == -1) {    
        for(int i = 1; i < len / 2; ++i) swap(y[i], y[len-i]);    
        int inv = qpow(len, P - 2, P);    
        for(int i = 0; i < len; ++i)    
            y[i] = 1LL * y[i] * inv % P;    
    }    
}  
 
int B[N];
int f[N], nf[N];
int a[N];
int tmp[N];
 
void get_inv(int A[], int A0[], int t) {
    if(t == 1) {
        A0[0] = qpow(A[0], P - 2, P);
        return;
    }
    get_inv(A, A0, t / 2);
    for(int i = 0; i < t; ++i) tmp[i] = A[i];
    for(int i = t; i < 2 * t; ++i) tmp[i] = 0;
    for(int i = t / 2; i < 2 * t; ++i) A0[i] = 0;
    NTT(tmp, 2 * t, 1);
    NTT(A0, 2 * t, 1);
    for(int i = 0; i < 2 * t; ++i) {
        tmp[i] = (2 - 1LL * tmp[i] * A0[i] % P) % P;
        if(tmp[i] < 0) tmp[i] += P;
        A0[i] = 1LL * A0[i] * tmp[i] % P;
    }
    NTT(A0, 2 * t, -1);
}
void init() {
    f[0] = 1;
    for(int i = 1; i < N; ++i) f[i] = 1LL * f[i-1] * i % P;
    nf[N-1] = qpow(f[N-1], P - 2, P);
    for(int i = N - 2; i >= 0; --i) {
        nf[i] = 1LL * nf[i+1] * (i + 1) % P;
    }
    for(int i = 0; i < N - 1; ++i) a[i] = nf[i+1];
    int len = 1 << 17;
    get_inv(a, B, len);
    for(int i = 0; i < len; ++i)
        B[i] = 1LL * B[i] * f[i] % P;
}

ll INV[1000007];
LL inv[1000002];//inverse
LL fac[1000002];//Factorial
LL C(int n,int m) {
    return fac[n]*inv[m]%M*inv[n-m]%M;
} 
ll SUM_N_K(ll n,ll k) {
    if (k==0) return n;
    ll pw=1,now=0; int i;
    FOR(i,1,k+1) {
        pw=pw*((n+1)%M)%M;
        add_(now,INV[k+1]*C(k+1,i)%M*B[k+1-i]%M*pw%M);
    }
    return now;
}
void INIT() {
    int i;
    fac[0]=1;
    FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1; INV[0]=INV[1]=1;
    FOR(i,2,1000000) INV[i]=inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
}

int main() {
    ll n,m,i;
    int ans=0;
    scanf("%lld%lld",&n,&m);
    if (n>100000) {
        FOR(i,1,m) add_(ans,n%M*powMM(i,n-1)%M);
    } else {
        getwn(); init(); INIT();
        // printf("%lld\n",SUM_N_K(m,n-1));
        ans=n%M*SUM_N_K(m,n-1)%M;
    }
    printf("%d\n",ans);
    // printf("%lld\n",ans[1]);
}
/*
*/