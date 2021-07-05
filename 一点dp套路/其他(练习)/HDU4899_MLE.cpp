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

char A[20];int len;
int encode(int f[]){
    int ret=0,i;
    rREP(i,len) ret=ret<<4|f[i];
    return ret;
}void decode(int e,int f[]){
    int i;
    REP(i,len) f[i]=e&15,e>>=4;
}
int getnextstatus(int val,int k){
    int f[20],i;f[0]=0;
    decode(val,f+1);
    rREP(i,len) f[i+1]=max(f[i+1],f[i]+(k==A[i]));
    REP(i,len) f[i+1]=max(f[i+1],f[i]);
    val=encode(f+1);
    return val;
}
void printstatus(int x){
    int i;
    REP(i,len) printf("%d ",(x>>(i*4))&15);
}
int nxt[1<<20|7][4];
int id[1<<20|7];
int val[maxn],tot;
queue<int> Q;
void initDP(){
    int i,k;
    REP(i,1<<(len+4)) id[i]=0;
    Q.push(0);tot=0;
    id[0]=++tot;val[tot]=0;
    while (Q.size()){
        int x=Q.front();Q.pop();
        REP(k,4){
            int nxtstatus=getnextstatus(x,k);
            if (!id[nxtstatus]) {
                id[nxtstatus]=++tot;
                val[tot]=nxtstatus;
                Q.push(nxtstatus);
            }
            nxt[id[x]][k]=id[nxtstatus];
//            printstatus(x);printf("  -- %d ->  ",k);printstatus(nxtstatus);puts("");
        }
    }
//    printf("tot=%d\n",tot);
}
int dp[2][maxn];
inline void update(int &x,int y){
    ((x+=y)>=M)&&(x-=M);
}
void solve(int n){
    initDP();
    int i,j,k,t;
    int f[20];
    int now=0;
    REP(i,len) f[i]=0;
    FOR(i,1,tot) dp[now][i]=0;
    dp[now][id[encode(f)]]=1;
//    printf("encode_f=%d\n",id[encode(f)]);
    REP(i,n){
        FOR(t,1,tot) dp[now^1][t]=0;
        FOR(t,1,tot){
            REP(k,4){
                update(dp[now^1][nxt[t][k]],dp[now][t]);
            }
        }now^=1;
    }int ans[20];
    REP(i,len+1) ans[i]=0;
    FOR(i,1,tot){
        int maxlen=0;
        decode(val[i],f);
        REP(j,len) maxlen=max(maxlen,f[j]);
        update(ans[maxlen],dp[now][i]);
        printf("%d : ",dp[now][i]);printstatus(val[i]);puts("");
    }REP(i,len+1) printf("%d\n",ans[i]);
}
int main() {
    int T,i;
    scanf("%d",&T);
    while (T--){
        int n,m;
        static int x=0;
        scanf("%s%d",A,&n);
        len=strlen(A);
        REP(i,len) if (A[i]=='A') A[i]=0;
        REP(i,len) if (A[i]=='T') A[i]=1;
        REP(i,len) if (A[i]=='C') A[i]=2;
        REP(i,len) if (A[i]=='G') A[i]=3;
        solve(n);
    }
    return 0;
}
/*
10
1 : 0 0 0
5120 : 0 1 1
1023 : 0 0 1
16640 : 1 1 1
52905 : 0 1 2
295245 : 1 2 2
180190 : 1 1 2
497452 : 1 2 3


10
AAAAAAAAAA
1000
*/
