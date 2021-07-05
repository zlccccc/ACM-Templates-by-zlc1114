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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=4e5+7;
const double eps=0.00000001;
const double pi=acos(-1);
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M; return ret;}

const LL MOD=2281701377;
const LL g=3;
LL mul(LL x,LL y) {
    return x*y%MOD;
//    return ( x * y - ( long long ) ( x / ( long double ) MOD * y + 1e-3 ) * MOD + MOD ) % MOD ;
}
LL poww(LL a,LL b) {
    LL ret=1;
    for (; b; b>>=1ll,a=mul(a,a))
        if (b&1) ret=mul(ret,a);
    return ret;
}
void ntt(LL *A,int len,int inv) { //抄的板子
    int i,j,k;
    for (i=1,j=len/2; i<len-1; i++) {
        if (i<j) swap(A[i],A[j]);
        k=len/2;
        while (j>=k) {
            j-=k;
            k/=2;
        }
        if (j<k) j+=k;
    }
    for (i=2; i<=len; i<<=1) {
        LL wn=poww(g,(MOD-1)/i);
        if (inv==-1) wn=poww(wn,MOD-2);
        for (j=0; j<len; j+=i) {
            LL w=1;
            for (k=j; k<(j+i/2); k++) {
                LL a=A[k],b=mul(w,A[k+i/2]);
                A[k]=(a+b)%MOD;
                A[k+i/2]=(a-b+MOD)%MOD;
                w=mul(w,wn);
            }
        }
    }
    if (inv==-1) {
        LL vn=poww(len,MOD-2);
        REP(i,len) A[i]=mul(A[i],vn);
    }
}
LL x1[maxn];
LL ans[maxn];
int main() {
    int n,q;
    int i,j,k;
    int T;
    scanf("%d",&T);
    int len=1;
    while (len<=200000) len<<=1;
    while (T--) {
        scanf("%d%d",&n,&q);
        REP(i,len) ans[i]=x1[i]=0;
        REP(i,n) scanf("%d",&k),x1[k]++,ans[k*2]--;
        ntt(x1,len,1);
        REP(i,len) x1[i]=mul(x1[i],x1[i]);
        ntt(x1,len,-1);
        REP(i,len) ans[i]+=x1[i];
        REP(i,len) ans[i]/=2;
        REP(i,len-1) ans[i+1]+=ans[i];
        REP(i,q) scanf("%d",&k),printf("%lld\n",ans[k-1]);
    }
}
/*
    http://m.blog.csdn.net/naipp/article/details/52738840
    全是抄的QAQ
    //常用费马素数和原根的表
    是这样的，这几天在写 FFT，由于是在模意义下的，需要各种素数……
    然后就打了个表方便以后查了、
    如果 r*2^k+1 是个素数，那么在mod r*2^k+1意义下，可以处理 2^k 以内规模的数据，
    2281701377=17*2^27+1  是一个挺好的数，平方刚好不会爆 long long
    1004535809=479*2^21+1 加起来刚好不会爆 int 也不错
    下面是刚刚打出来的表格（gg 是mod(r*2^k+1)的原根）
    素数                rr  kk  gg
    3                   1   1   2
    5                   1   2   2
    17                  1   4   3
    97                  3   5   5
    193                 3   6   5
    257                 1   8   3
    7681                15  9   17
    12289               3   12  11
    40961               5   13  3
    65537               1   16  3
    786433              3   18  10
    5767169             11  19  3
    7340033             7   20  3
    23068673            11  21  3
    104857601           25  22  3
    167772161           5   25  3
    469762049           7   26  3
    1004535809          479 21  3
    2013265921          15  27  31
    2281701377          17  27  3
    3221225473          3   30  5
    75161927681         35  31  3
    77309411329         9   33  7
    206158430209        3   36  22
    2061584302081       15  37  7
    2748779069441       5   39  3
    6597069766657       3   41  5
    39582418599937      9   42  5
    79164837199873      9   43  5
    263882790666241     15  44  7
    1231453023109121    35  45  3
    1337006139375617    19  46  3
    3799912185593857    27  47  5
    4222124650659841    15  48  19
    7881299347898369    7   50  6
    31525197391593473   7   52  3
    180143985094819841  5   55  6
    1945555039024054273 27  56  5
    4179340454199820289 29  57  3
*/
