
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
const LL maxn=1e5+107;
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

//复杂度n^2*m^3/4(不一定确定); 速度非常快, 常数极小可以水过题
struct query{
    int x1,x2,y1,y2,id;
}Q[maxn];
int ans[maxn];
vector<int> v;
int fin[60000007];
int p[5000000],tot;
int BID[90];//BLOCKID
const int BLOCK=11;
int cnt[90*90],val[90*90];
int nowans=0;
int A[90][90];
void ADD(int v,int c) {
    // printf("add %d %d\n",v,c);
    if (cnt[v]) add_(nowans,val[v]);
    cnt[v]+=c;
    if (cnt[v]) add_(nowans,M-val[v]);
}
int main() {
    int n,limit,i,j;
    scanf("%d%d",&n,&limit);
    // read(n); read(limit);
    //筛下看看能不能过...
    nowans=1;
    // float t_ss=clock();
    FOR(i,2,limit) {
        if (!fin[i]) p[tot++]=i,fin[i]=powMM(i,limit);
        REP(j,tot){
            if (i*p[j]>limit) break;
            fin[i*p[j]]=(ll)fin[i]*fin[p[j]]%M;
        }
        add_(nowans,fin[i]);
    }
    // printf("tot=%d\n",tot);
    // printf("fir %f\n",clock()-t_ss);

    FOR(i,1,n) FOR(j,1,n) {
        scanf("%d",&A[i][j]);
        // A[i][j]=rand()%limit+1;
        v.push_back(A[i][j]);
    } sort(v.begin(), v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    REP(i,(int)v.size()) {
        val[i]=powMM(v[i],limit);
    }
    FOR(i,1,n) FOR(j,1,n)
        A[i][j]=lower_bound(v.begin(),v.end(),A[i][j])-v.begin();
    // FOR(i,1,n) FOR(j,1,n) printf("%d%c",A[i][j]," \n"[j==n]);
    int m;
    // read(m);
    scanf("%d",&m);
    // float t_st=clock();
    FOR(i,1,m) {
        scanf("%d%d%d%d",&Q[i].x1,&Q[i].y1,&Q[i].x2,&Q[i].y2);
        // Q[i].x1=rand()%n+1; Q[i].x2=rand()%n+1;
        // Q[i].y1=rand()%n+1; Q[i].y2=rand()%n+1;
        Q[i].id=i;
        if (Q[i].x1>Q[i].x2) swap(Q[i].x1,Q[i].x2);
        if (Q[i].y1>Q[i].y2) swap(Q[i].y1,Q[i].y2);
    }
    FOR(i,1,n) BID[i]=i/BLOCK;
    sort(Q+1,Q+1+m,[](const query &A,const query &B){
        if (BID[A.x1]!=BID[B.x1]) return A.x1<B.x1;
        if (BID[A.y1]!=BID[B.y1]) return A.y1<B.y1;
        if (BID[A.x2]!=BID[B.x2]) return A.x2<B.x2;
        if (A.y2!=B.y2) return A.y2<B.y2;
        return false;
    });
    int x1=1,x2=0,y1=1,y2=0,o;
    FOR(o,1,m) {
        query p=Q[o];
        // printf("query: %d %d %d %d\n",p.x1,p.x2,p.y1,p.y2);
        //add
        while (x1>p.x1) {x1--; FOR(i,y1,y2) ADD(A[x1][i],1);}
        while (x2<p.x2) {x2++; FOR(i,y1,y2) ADD(A[x2][i],1);}
        while (y1>p.y1) {y1--; FOR(i,x1,x2) ADD(A[i][y1],1);}
        while (y2<p.y2) {y2++; FOR(i,x1,x2) ADD(A[i][y2],1);}
        //del
        while (x1<p.x1) {FOR(i,y1,y2) ADD(A[x1][i],-1); x1++;}
        while (x2>p.x2) {FOR(i,y1,y2) ADD(A[x2][i],-1); x2--;}
        while (y1<p.y1) {FOR(i,x1,x2) ADD(A[i][y1],-1); y1++;}
        while (y2>p.y2) {FOR(i,x1,x2) ADD(A[i][y2],-1); y2--;}
        ans[p.id]=nowans;
    }
    FOR(i,1,m) printf("%d\n",ans[i]);
    // printf("%f\n",clock()-t_st);
}
/*
88 60000000 100000
*/