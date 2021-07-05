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
const LL maxn=100+7;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M; return ret;}

//求行列式的值
//%m,m为质数的积
//从0开始
template<typename T>inline T poww(T a,T b,T M) {
    T ret=1;
    for (; b; b>>=1ll,a=1ll*a*a%M)
        if (b&1) ret=1ll*ret*a%M;
    return ret;
}
LL guass(LL A[107][107],int n,LL M) {
    LL ret=1; int i,j,k;
    REP(i,n) {
        int id=i;
        if (!A[i][i]) rep(j,i+1,n) if (A[j][i]) id=j;
        if (!A[id][i]) continue;
        if (id!=i) {rep(j,i,n) swap(A[i][j],A[id][j]); ret*=-1;}
        A[i][i]%=M; (A[i][i]<0) &&(A[i][i]+=M);
        LL rev=poww(A[i][i],M-2,M);
        rep(k,i+1,n)
        rrep(j,i,n)(A[k][j]-=(LL)A[k][i]*rev%M*A[i][j])%=M;
    } REP(i,n)(ret*=A[i][i])%=M;
    (ret<0) &&(ret+=M);
    return ret;
}
LL A[107][107],B[107][107];
void exgcd(LL a,LL b,LL &d,LL &x,LL &y) {
    if (!b) {d=a; x=1; y=0;}
    else {exgcd(b,a%b,d,y,x); y-=a/b*x;}
}
vector<LL> P;
vector<LL> Ans;
LL ans;
LL chinese_remainder(vector<LL> &m,vector<LL> &r) {
    int i; LL M=m[0],R=r[0];
    rep(i,1,P.size()) {
        LL x,y,d;
        exgcd(M,m[i],d,x,y);
        if ((r[i]-R)%d) return -1;
        x=(r[i]-R)/d*x%(m[i]/d);
        R+=x*M; M=M/d*m[i];
        R%=M; (R<0) &&(R+=M);
    } return R;
}
int n,m;
int i,j,k;
int main() {
    while (~scanf("%d%d",&n,&m)) {
        P.clear(); Ans.clear();
        REP(i,n)
        REP(j,n) scanf("%lld",&A[i][j]);
        for (i=2; i*i<=m; i++) if (m%i==0) {
            P.push_back(i);
            while (m%i==0) m/=i;
        } if (m!=1) P.push_back(m);
        for (int v:P) {
            REP(i,n) REP(j,n) B[i][j]=A[i][j];
            Ans.push_back((LL)guass(B,n,v));
        }
        ans=chinese_remainder(P,Ans);
        printf("%lld\n",ans);
    }
}
/*
3 1011
1 2 5
3 4 4
4 5 6
*/
