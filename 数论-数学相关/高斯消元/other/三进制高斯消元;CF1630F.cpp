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
typedef array<int,3> ar3;
typedef array<int,4> ar4;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
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

struct Equation{
    bitset<256> bit[3]; // [3]: %3==x
};
vector<Equation> Bit;
int n;
int edge[65][65];
int A[maxn],B[maxn],C[maxn];
vector<int> val;
Equation add(const Equation &A, const Equation &B) { //相加
    Equation ret; int i,j;
    REP(i,3) REP(j,3) ret.bit[(i+j)%3]^=A.bit[i]&B.bit[j];
    return ret;
}
int ans[257];
void solve() {
    int n,m;
    int i,j,k;
    scanf("%d%d",&n,&m);
    memset(edge,0xff,sizeof(edge));
    Bit.clear(); val.clear();
    bitset<256> all;
    REP(i,m) all.set(i);
    REP(i,m) {
        scanf("%d%d%d",&A[i],&B[i],&C[i]);
        edge[A[i]][B[i]]=edge[B[i]][A[i]]=i;
        if (C[i]==-1) continue;
        Bit.push_back({all,0,0}); val.push_back(C[i]-1);
        Bit.back().bit[0].set(i,0);
        Bit.back().bit[1].set(i,1);
    }
    FOR(i,1,n) FOR(j,i+1,n) FOR(k,j+1,n) {
        if (edge[i][j]!=-1&&edge[j][k]!=-1&&edge[k][i]!=-1) {
            Bit.push_back({all,0,0}); val.push_back(0);
            for (auto e:{edge[i][j],edge[j][k],edge[k][i]}){
                Bit.back().bit[0].set(e,0);
                Bit.back().bit[1].set(e,1);
            }
        }
    }
    // solve; add
    REP(i,(int)Bit.size()) {
        int pos=-1;
        REP(j,m) if (!(Bit[i].bit[0][j])) {pos=j; break;}
        // REP(j,m) {
        //     if (Bit[i].bit[0][j]) putchar('0');
        //     if (Bit[i].bit[1][j]) putchar('1');
        //     if (Bit[i].bit[2][j]) putchar('2');
        // } printf("   %d; pos=%d\n",val[i],pos);
        if (pos==-1) {
            if (!val[i]) continue;
            else {puts("-1"); return;}
        }
        if (Bit[i].bit[2][j]) Bit[i]=add(Bit[i],Bit[i]),val[i]=(val[i]+val[i])%3;
        REP(j,(int)Bit.size()) if (j!=i) {
            if (Bit[j].bit[1][pos]) Bit[j]=add(Bit[j],Bit[i]),val[j]=(val[i]+val[j])%3;
            if (Bit[j].bit[2][pos]) Bit[j]=add(Bit[j],Bit[i]),val[j]=(val[i]+val[j])%3;
        }
    }
    REP(i,m) ans[i]=0;
    REP(i,(int)Bit.size()) {
        int pos=-1;
        REP(j,m) if (!(Bit[i].bit[0][j])) {pos=j; break;}
        if (pos==-1) continue;
        ans[pos]=val[i];
    }
    REP(i,m) printf("%d%c",ans[i]+1," \n"[i==m-1]);
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        solve();
    }
}
/*
10
4 5
1 2 -1
1 3 -1
2 3 2
2 4 -1
3 4 -1
5 5
2 4 2
2 5 1
3 4 -1
1 3 -1
4 5 -1
5 5
1 5 3
2 3 -1
2 4 1
1 2 -1
2 5 -1
*/