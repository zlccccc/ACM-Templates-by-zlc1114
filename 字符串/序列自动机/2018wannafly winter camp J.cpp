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
const LL maxn=2e5+107;
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
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
int n,m,q;
char str[maxn];//倒着的

//序列自动机: 假设y之后第一次出现位置为nxt[x][y]
//f[x]=f[x]+f[nxt[x][y]]; 所以只与head是几有关
//trans[head][last(nextvalue)]
//保存的是第一个head处的值(转移)
//多加一个节点保存到结尾位置的ans是多少
//题意: 给个字符串, 每次在原串的每两个字符中间加个字符, 问你最后的子序列个数
//做法: 倒着发现是个复制后中间加个字符, 用子序列自动机来做
int fa[maxn];
ll val[maxn];
struct mat{
    int trans[27][27]; bool have[27];
    mat(){memset(trans,0,sizeof(trans)); memset(have,0,sizeof(have));}
};
mat mul(mat A,mat B){
    mat ret; int i,j,k;
    REP(i,27) {
        if (A.have[i]) {
            REP(j,27) {
                if (B.have[j])
                    REP(k,27) add_(ret.trans[i][k],(ll)A.trans[i][j]*B.trans[j][k]%M);
                else add_(ret.trans[i][j],A.trans[i][j]);
            }
        } else REP(j,27) add_(ret.trans[i][j],B.trans[i][j]);
    }
    REP(i,27) ret.have[i]=A.have[i]|B.have[i];
    return ret;
}
mat getMat(int c){
    c-='a'; mat ret; int i; ret.have[c]=1;
    REP(i,27) ret.trans[c][i]=1;
    return ret;
}
int main() {
    int i;
    scanf("%d",&n);
    scanf("%s",str);
    mat ans=getMat(str[n-1]); int Ans=0;
    rREP(i,n-1) {
        // int j,k;;
        // mat mat1=mul(getMat(str[i]),ans);
        // REP(j,27) {
        //  REP(k,27){
        //      printf("%2d ",mat1.trans[j][k]);
        //  } puts("<-mul");
        // }
        ans=mul(ans,mul(getMat(str[i]),ans));
        // REP(j,27) {
        //  REP(k,27){
        //      printf("%2d ",ans.trans[j][k]);
        //  } puts("<-ans");
        // }
    }
    REP(i,26) add_(Ans,ans.trans[i][26]);
    printf("%d\n",Ans);
}
/*
3 5
2 1
1 2 1
2 1
1 2 3
2 1
*/