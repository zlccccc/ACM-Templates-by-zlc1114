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
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
int n,m,q;
char str[maxn];

struct node{
    int l,r,val,len;
    node(int _val=0){l=r=len=0; val=_val;}
}T[maxn]; int tot;
int merge(int x,int y){//不能直接swap x和儿子, 否则可能不满足堆性质
    if (!x||!y) return x|y;
    if (T[x].val>T[y].val) swap(x,y);
    T[x].r=merge(T[x].r,y);
    if (T[T[x].l].len<T[T[x].r].len) swap(T[x].l,T[x].r);
    T[x].len=T[T[x].r].len+1;
    return x;
}
int pop(int x) {
    T[x].val=-1;
    return merge(T[x].l,T[x].r);
}
int fa[maxn],root[maxn];
inline int getfa(int x){
    if (x==fa[x]) return x;
    return fa[x]=getfa(fa[x]);
}
int main() {
    int i;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) {
        int x;scanf("%d",&x);
        T[i]=node(x);
        fa[i]=root[i]=i;
    } FOR(i,1,m){
        int op;
        scanf("%d",&op);
        if (op==1) {
            int x,y; scanf("%d%d",&x,&y);
            if (T[x].val==-1||T[y].val==-1) continue;
            x=getfa(x); y=getfa(y);
            if (x==y) continue;
            root[y]=merge(root[x],root[y]);
            fa[x]=y;
        } else {
            int x; scanf("%d",&x);
            if (T[x].val==-1) {puts("-1"); continue;}
            x=getfa(x);
            if (!root[x]) puts("-1");
            else {
                printf("%d\n",T[root[x]].val);
                root[x]=pop(root[x]);
            }
        }
    }
}
/*
acdefg
10
1 3

*/