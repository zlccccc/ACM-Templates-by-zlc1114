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
const LL maxn=3e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

bool okay[maxn*20];
bool mark[maxn*20];
int nxt[maxn*20][2];
bool rev[21];
int cnt;
void insert(int x,int now,int dep){
    bool mark=x&(1<<dep);
    if (dep==-1) {okay[now]=1; return;}
    if (!nxt[now][mark]) nxt[now][mark]=++cnt;
    insert(x,nxt[now][mark],dep-1);
    okay[now]=okay[nxt[now][0]]&&okay[nxt[now][1]];
}
void reverse(int x,int dep){
    if (dep==-1) return;
    bool mark=x&(1<<dep);
    rev[dep]^=mark;
    reverse(x,dep-1);
}
int query(int x,int now,int dep){
    if (now==0||dep==-1) return x;
    if (rev[dep]^mark[now])
        swap(nxt[now][0],nxt[now][1]),mark[now]^=1;
    if (okay[nxt[now][0]])
        return query(x|(1<<dep),nxt[now][1],dep-1);
    return query(x,nxt[now][0],dep-1);
}
int n,q;
int i;
int val;
int main(){
    scanf("%d%d",&n,&q);
    cnt=1;
    FOR(i,1,n) scanf("%d",&val),insert(val,1,20);
    REP(i,q){
        scanf("%d",&val);
        reverse(val,20);
        printf("%d\n",query(0,1,20));
    }
}
