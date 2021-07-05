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
const LL maxn=1<<19|7;
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

void fwt(int *A,int len,int inv) { //对拍对了
    int i,j,k;
    for (i=2; i<=len; i<<=1) {
        for (j=0; j<len; j+=i) {
            for (k=j; k<j+i/2; k++) {
                if (inv==1) {
                    int a=A[k],b=A[k+i/2];
                    A[k]=a+b; (A[k]>=M) &&(A[k]-=M);
                    A[k+i/2]=a-b+M; (A[k+i/2]>=M) &&(A[k+i/2]-=M);
                } else {
                    int a=A[k],b=A[k+i/2];
                    A[k]=a+b; (A[k]>=M) &&(A[k]-=M);
                    A[k+i/2]=a-b+M; (A[k+i/2]>=M) &&(A[k+i/2]-=M);
                }
            }
        }
    }
    int div=powMM((ll)len,M-2);
    if (inv==-1) REP(i,len) mul_(A[i],div);
}
// C[k]=\sum_{i&j=k} A[i^j] B[i|j]
// let i'=i^j, j'=i|j, 这样的i,j对有2^bit(i')个
// C[k]=\sum [j'-i'=k] [i' \subseteq j'] 2^i' * A[i'] * B[j']
// C[k]=\sum [i^j=k] [i&j=i] * 2^i * A[i] * B[j] //这里的意思就是i|k=j, i+k=j
// C[k]=\sum [i^j=k] [bit(j)-bit(i)=bit(k)] 2^i * A[i] * B[j]
// ! 注意这里这个枚举bit要加个新的tmp数组...
int A[20][maxn],B[20][maxn],C[20][maxn];
int bit[maxn],pw1526[maxn],ans[maxn];
int main() {
    int k,i;
    scanf("%d",&m); n=1<<m;
    REP(i,n) bit[i]=bit[i>>1]+(i&1);
    REP(i,n) scanf("%d",&A[bit[i]][i]);
    REP(i,n) scanf("%d",&B[bit[i]][i]);
    pw1526[0]=1;
    rep(i,1,n) pw1526[i]=1526ll*pw1526[i-1]%M;
    REP(i,n) mul_(A[bit[i]][i],powMM(2,bit[i]));
    REP(i,m+1) fwt(A[i],n,1),fwt(B[i],n,1);
    REP(k,m+1) REP(i,m-k+1) {
        int t=0,j=i+k;
        REP(t,n) add_(C[k][t],(ll)A[i][t]*B[j][t]%M);
    } REP(i,m+1) fwt(C[i],n,-1);
    REP(i,n) ans[i]=C[bit[i]][i];
    int Ans=0;
    REP(i,n) add_(Ans,(ll)ans[i]*pw1526[i]%M);
    printf("%d\n",Ans);
}
/*
*/
