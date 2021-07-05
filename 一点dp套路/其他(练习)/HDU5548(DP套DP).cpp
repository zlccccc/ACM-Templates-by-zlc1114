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
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

//题意:麻将胡牌的可能种数
//为了不数漏,方法是这样的:
//首先考虑每个可能情况选择的个数,只可能有3*3*2=18种
//然后我们把状态压一下,每种牌型可能的1<<18的状态!
//对这个1<<18的状态进行转移
void print2(int x) {
    int i;
    rREP(i,18) putchar(((x>>i)&1)+'0');
} int encode(int n_2,int n_1,int have2) { //start from n-2 | n-1
    int ret=0;
    ret=ret*3+n_2;
    ret=ret*3+n_1;
    ret=ret*2+have2;
    return ret;
} void decode(int e,int &n_2,int &n_1,int &have2) {
    have2=e%2; e/=2;
    n_1=e%3; e/=3;
    n_2=e%3; e/=3;
}
void printstatus(int e) {
    int n_2,n_1,have2;
    decode(e,n_2,n_1,have2);
    printf(" %d %d %d ",n_2,n_1,have2);
}
int getnextstatus(int status,int k) {
    int nxtstatus=0,n;
    int n_2,n_1,have2;
    int x_2,x_1,xave2;
    REP(n,18) if ((status>>n)&1) {
        decode(n,n_2,n_1,have2);
        x_2=n_1; x_1=k-n_2-n_1; xave2=have2;
        if (x_1>=0) {
            int x=encode(x_2,x_1%3,xave2);
            nxtstatus|=(1<<x);
//            printstatus(n);printf("->");printstatus(x);printf("(+%d)",k);puts("");
        } if (!have2&&x_1-2>=0) {
            int x=encode(x_2,x_1-2,1);
            nxtstatus|=(1<<x);
//            printstatus(n);printf("->");printstatus(x);printf("(+%d)",k);puts("");
        }
    }
//    printf("get:%d->%d (k=%d)\n",status,nxtstatus,k);
    return nxtstatus;
}
queue<int> Q;
int id[1<<18|7],val[1007];
int tot;
int nxt[1007][7];
void initDP() {
    int i,j; tot=0;
    int k;//this_number
    Q.push(1); id[0]=++tot;
    while (Q.size()) {
        int status=Q.front(); Q.pop();
        FOR(k,0,4) { //只考虑这里产生2~
            int nxtstatus=getnextstatus(status,k);
            if (!id[nxtstatus]) id[nxtstatus]=++tot,val[tot]=nxtstatus,Q.push(nxtstatus);
            nxt[id[status]][k]=id[nxtstatus];
        }
    }
//    printf("%d\n",tot);
//    REP(i,(1<<18)) if (id[i]){
//        printf("(%-2d): ",id[i]);
//        print2(i);puts("");
//        REP(j,18) if ((i>>j)&1) printstatus(j);puts("");
//    }
//    FOR(i,1,tot){
//        printf(" %-2d : ",i);
//        print2(val[i]);puts("");
//        REP(j,18) if ((val[i]>>j)&1) printstatus(j);puts("");
//    }
}
int dp[207][207][78];
inline void update(int &x,int y) {
    ((x+=y)>M)&&(x-=M);
}
int solve(int n,int m) {
    int i,j,k,t;
    FOR(i,0,n+3) FOR(j,0,m) FOR(t,0,68) dp[i][j][t]=0;
    dp[0][0][1<<id[encode(0,0,0)]]=1;
    FOR(i,0,n+3) {
        int MAX;
        if (i<n) MAX=4; else MAX=0;
        FOR(j,0,m) {
            FOR(t,1,tot) if (dp[i][j][t]) {
                FOR(k,0,MAX) {
                    int nxtpos=nxt[t][k];
//                    printf("%d->%d; k=%d\n",t,id[nxtstauts],k);
                    update(dp[i+1][j+k][nxtpos],dp[i][j][t]);
                }
            }
        }
    } int ret=0;
//    FOR(t,1,tot) printf("%d: %d\n",t,dp[n+3][m][t]);
    FOR(t,1,tot) {
        if ((val[t]>>encode(0,0,1))&1) {
            update(ret,dp[n+3][m][t]);
//            printf("t=%d\n",t);
        }
    }
    return ret;
}
int main() {
    int T;
    initDP();
    scanf("%d",&T);
    while (T--) {
        int n,m;
        static int x=0;
        scanf("%d%d",&n,&m);
        printf("Case #%d: %d\n",++x,solve(n,m));
    }
    return 0;
}
/*
4
1 2
3 5
4 5
9 14
*/
