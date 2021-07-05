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
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
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

bool gauss(int A[8007][8007],int X[8007],int n,int m,int N) {
    int i,j,k;
    REP(i,n) {
        if (!A[i][i]){
            int id=i;
            rep(j,i+1,m) if (A[j][i]) {id=j;break;}
            if (!A[id][i]) continue;
            if (id!=i)
                {rep(j,i,n) swap(A[i][j],A[id][j]); swap(X[i],X[id]);}
        }if (!A[i][i]) continue;
        int rev=powMM(A[i][i],(int)M-2),las=min(n,i+N+1);
        rep(k,i+1,las) if (A[k][i]) {
            int R=(LL)A[k][i]*rev%M;
            X[k]=(X[k]-(LL)R*X[i])%M;
            rrep(j,i,las)
                A[k][j]=(A[k][j]-(LL)R*A[i][j])%M;
        }
    }
    rREP(i,n){
        X[i]=(LL)X[i]*powMM(A[i][i],(int)M-2)%M;
        REP(j,i)
            X[j]=(X[j]-(LL)A[j][i]*X[i])%M;
        (X[i]<0)&&(X[i]+=M);
    }
    return 1;
}
int f[8007][8007],g[8007];
int id[107][107],tot;
int ax[]={-1,0,1,0};
int ay[]={0,-1,0,1};
int A[4];
const int mid=51;
inline int p2(int x){return x*x;}
int main() {
    int n,i,j,k;
    scanf("%d",&n);int rev=0;
    REP(i,4) scanf("%d",&A[i]),rev+=A[i];
    rev=powMM(rev,(int)M-2);
    REP(i,4) A[i]=(LL)A[i]*rev%M;
    memset(id,0xff,sizeof(id));
    FOR(i,mid-n,mid+n) FOR(j,mid-n,mid+n)
        if (p2(i-mid)+p2(j-mid)<=p2(n)) id[i][j]=tot++;
    FOR(i,mid-n,mid+n) FOR(j,mid-n,mid+n){
        if (id[i][j]!=-1) {
            REP(k,4){
                int x=i+ax[k],y=j+ay[k];
                if (id[x][y]==-1) continue;
//                printf("%d %d\n",id[i][j],id[x][y]);
                f[id[i][j]][id[x][y]]=A[k];
            }g[id[i][j]]=M-1;
            f[id[i][j]][id[i][j]]=M-1;
        }
    }
    gauss(f,g,tot,tot,n*2);
    printf("%d\n",g[id[mid][mid]]);
    return 0;
}
/*
*/
