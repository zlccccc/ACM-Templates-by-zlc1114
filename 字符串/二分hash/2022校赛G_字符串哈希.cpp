// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
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
#include <functional>
#include <random>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define REP_(I,N) for (int I=0;I<N;I++)
#define rREP_(I,N) for (int I=N-1;I>=0;I--)
#define rep_(I,S,N) for (int I=S;I<N;I++)
#define rrep_(I,S,N) for (int I=N-1;I>=S;I--)
#define FOR_(I,S,N) for (int I=S;I<=N;I++)
#define rFOR_(I,S,N) for (int I=N;I>=S;I--)

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
// const LL M=1e9+7;
const LL M=998244353;
// ll M=1;
const LL maxn=3e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T fastgcd(T a, T b) {
    int az=__builtin_ctz(a),bz=__builtin_ctz(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctz(diff);
        min_(b,a); a=abs(diff);
    }
    return b<<z;
}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
typedef array<int,2> ar2;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

// 字符串哈希
// 题意是n,m的二维矩阵,顺时针旋转90度和原始相同的正方形
// 答案最大n*m*min(n,m); 哈希一下判断一下就完事
struct Hash{
    vector<int> px,val; int MOD,P;
    Hash(int n=1,int p=37,int mod=M) {
        // printf("hash %d %d %d\n",n,p,mod);
        px.resize(n+1); val.resize(n+1);
        P=p; MOD=mod; px[0]=1;
        FOR_(i,1,n) px[i]=(LL)px[i-1]*p%MOD;
    }
    void set(char a[]){ // id start from 0
        val[0]=0; int n=val.size()-1;
        FOR_(i,1,n) val[i]=((LL)val[i-1]*P+a[i-1])%MOD;
    }
    int get(int l,int r){
        l++; r++;
        // printf("get %d %d\n",l,r);
        int ret=val[r]-(LL)val[l-1]*px[r-l+1]%M;
        (ret<0)&&(ret+=M); return ret;
    }
};

vector<Hash> L,R,U,D;
int n,m;
char s[maxn];
int main() {
    int n,m;
    cin>>n>>m;
    vector<string> str(n); // upper?
    L=vector<Hash>(n,Hash(m));
    R=vector<Hash>(n,Hash(m));
    U=vector<Hash>(m,Hash(n));
    D=vector<Hash>(m,Hash(n));
    REP_(i,n) cin>>str[i];
    REP_(i,n) {
        REP_(j,m) s[j]=str[i][j]; R[i].set(s);
        REP_(j,m) s[m-j-1]=str[i][j]; L[i].set(s);
    }
    REP_(j,m) {
        REP_(i,n) s[i]=str[i][j]; D[j].set(s);
        REP_(i,n) s[n-i-1]=str[i][j]; U[j].set(s);
    }
    int ans=0;
    vector<vector<array<int,2>>> dp(n+1,vector<array<int,2>>(m+1));
    FOR_(k,0,min(n,m)) {
        REP_(i,n-k+1) REP_(j,m-k+1) {
            int &x=dp[i][j][k&1]; x=0;
            if (k==0) x=1;
            else if (k==1) x=1,ans++;
            else if (dp[i+1][j+1][k&1]) {
                int ri=i+k-1,rj=j+k-1;
                int r=R[i].get(j,rj);
                int l=L[ri].get(m-1-rj,m-1-j);
                int u=U[j].get(n-1-ri,n-1-i);
                int d=D[rj].get(i,ri);
                // printf("%d->%d; %d->%d: %d %d %d %d\n",i+1,ri+1,j+1,rj+1,l,r,u,d);
                if (r==l&&l==d&&d==u) x=1,ans++;
            }
        }
    }
    cout<<ans;
}
/*
3 3
aba
baa
aba


*/