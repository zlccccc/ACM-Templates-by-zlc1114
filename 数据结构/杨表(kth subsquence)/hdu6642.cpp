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

//题意: 选5个subsquence和最大
//杨表: 单调**子序列个数最大多少个
//杨表做法: 直接替换原数列中比这个大的位置,
//    然后直接将多出来的往下放即可
//正确性: 可以将这个点后面连的所有东西放下边,
//    相当于连个边,相当于最优选择
ll ans;
map<int,ll> MP[5];//pos,cnts
void update(int x,int y,int dep) {//x,cnt
    if (dep==5) return;
    while (y) {
        map<int,ll>::iterator it=MP[dep].upper_bound(x);
        if (it==MP[dep].end()) {
            ans+=y;
            MP[dep][x]+=y; break;
        } pair<int,int> now=*it;
        MP[dep].erase(it);
        ll down=min(now.second,y);
        y-=down; now.second-=down;
        if (now.second) MP[dep][now.first]+=now.second;
        MP[dep][x]+=down;
        update(now.first,down,dep+1);
    }
}
int main(){
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int i,n;
        scanf("%d",&n); ans=0;
        REP(i,5) MP[i].clear();
        FOR(i,1,n) {
            int k; scanf("%d",&k);
            update(k,k,0);
            printf("%lld%c",ans," \n"[i==n]);
        }
    }
}