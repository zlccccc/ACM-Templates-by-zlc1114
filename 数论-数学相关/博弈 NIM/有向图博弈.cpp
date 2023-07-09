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
const LL maxn=10000+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,ull k=64) {ull i; REP(i,k) debug("%d",(int)((x>>i)&1)); putchar(' ');}
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

vector<int> edge[maxn],rev[maxn];//out-edge
int D[10007],Win[10007];
void addedge(int x,int y) {
    D[x]++;
    edge[x].push_back(y);
    rev[y].push_back(x);
}
int getid(int x1,int x2,int y1,int y2) {
    // if (x1>x2) swap(x1,x2);
    // if (y1>y2) swap(y1,y2);
    return x1*1000+x2*100+y1*10+y2;
}
void solve() {
    int i,x1,x2,y1,y2;
    int lose=10000;
    FOR(x1,1,9) FOR(x2,1,9) FOR(y1,1,9) FOR(y2,1,9) {//nxt-status
        int id_a=getid(x1,x2,y1,y2);
        // printf("idx=%d\n",id_a);
        // if (x1==1&&x2==9&&y1==1&&y2==9) {
        //     printf("solve %d\n",id_a);
        // }
        if (x1+x2!=10) addedge(id_a,getid(y1,y2,(x1+x2)%10,x2)); else addedge(id_a,lose);
        if (x1+y1!=10) addedge(id_a,getid(y1,y2,(x1+y1)%10,x2)); else addedge(id_a,lose);
        if (x1+y2!=10) addedge(id_a,getid(y1,y2,(x1+y2)%10,x2)); else addedge(id_a,lose);
        swap(x1,x2);
        if (x1+x2!=10) addedge(id_a,getid(y1,y2,(x1+x2)%10,x2)); else addedge(id_a,lose);
        if (x1+y1!=10) addedge(id_a,getid(y1,y2,(x1+y1)%10,x2)); else addedge(id_a,lose);
        if (x1+y2!=10) addedge(id_a,getid(y1,y2,(x1+y2)%10,x2)); else addedge(id_a,lose);
        swap(x1,x2);
    }
    queue<int> Q;//solve
    FOR(i,1,10000) if (D[i]==0) Win[i]=0,Q.push(i); else Win[i]=2;//i,lose
    while (Q.size()) {
        auto now=Q.front(); Q.pop();
        int pos=now,win=Win[pos];
        // if (pos/100==19) printf("Win %d %d\n",pos,Win[pos]);
        // if (pos==1919) {
        //     printf("Win %d %d\n",pos,Win[pos]);
        //     for (int v:edge[pos]) printf("nxt=%d\n",v);
        //     for (int v:rev[pos]) printf("rev=%d\n",v);
        // }
        // if (win==1) printf("solve %d: %d  %d\n",pos,win,Win[pos]);
        if (win==0) {
            for (int v:rev[pos]) {
                D[v]--;
                if (Win[v]==2) {
                    Win[v]=1,Q.push(v);
                }
            }
        } else {
            for (int v:rev[pos]) {
                D[v]--;
                if (!D[v]&&Win[v]==2) {
                    Win[v]=0,Q.push(v);
                }
            }
        }
    }
}
int main() {
    solve();
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int x1,x2,y1,y2; scanf("%d%d%d%d",&x1,&x2,&y1,&y2);
        int win=Win[getid(x1,x2,y1,y2)];
        if (win==0) puts("Bob");
        else if (win==1) puts("Alice");
        else puts("Tie");
    }
}
/*
*/