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
const LL maxn=3e6+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M; return ret;}

// 做法: 按位分治, insert left; calculate right
int nxt[maxn][2];
int tot;
void ins(int x) {
    int now=0,i;
    rREP(i,31) {
        int mark=(x>>i)&1;
        if (!nxt[now][mark]) nxt[now][mark]=++tot;
        now=nxt[now][mark];
    }
}
int calc(int x) {
    int now=0,i,ret=0;
    rREP(i,31) {
        int mark=(x>>i)&1;
        if (nxt[now][mark]) now=nxt[now][mark];
        else now=nxt[now][!mark],ret|=(1<<i);
    } return ret;
}
int a[maxn],q[maxn];
LL ans;
void solve(int x,int l,int r) {
    if (x<0||l>=r) return;
    //  printf("%d %d %d\n",x,l,r);
    int L=l,R=r,i;
    FOR(i,l,r) if ((a[i]>>x)&1) q[L++]=a[i]; else q[R--]=a[i];
    FOR(i,l,r) a[i]=q[i];
    //  FOR(i,l,r) printf("%d ",a[i]);puts("");
    L--; R++;
    solve(x-1,l,L); solve(x-1,R,r);
    if (l>L||R>r) return;
    FOR(i,l,L) ins(a[i]);
    int add=INF;
    FOR(i,R,r) add=min(add,calc(a[i]));
    ans+=add;
    FOR(i,0,tot) nxt[i][0]=nxt[i][1]=0;
    tot=0;
}
int n,m;
int main() {
    int i,k;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&a[i]);
    solve(30,1,n);
    printf("%I64d\n",ans);
}
/*
*/