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
const LL maxn=3e5+7;
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
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

vector<int> edge[maxn],vt[maxn],kp;
bool key[maxn];
int build(int x,int fa){
    vector<int> ch;
    for (auto v:edge[x]){
        if (v==fa) continue;
        int w=build(v,x);
        if (w) ch.push_back(w);
    } if (ch.size()>=2) key[x]=1;
    if (key[x]){
        kp.push_back(x);
        for (auto v:ch) {
            vt[x].push_back(v);
            vt[v].push_back(x);
        } return x;
    } if (ch.size()) return ch[0];
    return 0;
}
int ans; bool vis[maxn];
void dfs(int u,int s,int dep){
    int cnt=0;
    for (auto v:vt[u]) {
        if (v==s) ++cnt;
        if (v<s&&!vis[v]){
            vis[v]=1; dfs(v,s,dep+1); vis[v]=0;
        }
    } if (cnt>1||(cnt==1&&dep>2)) ans++;
}
int fa[maxn];
inline int getfa(int x){
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa[x]);
}
int main(){
    int i;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) fa[i]=i;
    FOR(i,1,m) {
        int u,v;
        scanf("%d%d",&u,&v);
        int x=getfa(u),y=getfa(v);
        if (x==y) {
            key[u]=key[v]=1;
            vt[u].push_back(v);
            vt[v].push_back(u);
        }else {
            fa[x]=y;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
    } key[1]=1;
    build(1,0);
    for(auto s:kp) {
        // printf("%d ",s);
        vis[s]=1; dfs(s,s,1); vis[s]=0;
    } printf("%d\n",ans/2);
}