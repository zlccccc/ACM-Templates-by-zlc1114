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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a=a*a%M) ret=1ll*ret*a%M; return ret;}

//主要在于建图
//连边u->v,len <=> val(v)-val(u)<=len
//其他的都要化成这种形式
int n,m;
int i,j;
struct node {
    int n,d,next;
    node() {}
    node(int a,int b):n(a),d(b) {}
    bool operator<(const node &a)const {
        if (d==a.d) return n<a.n;
        return d>a.d;
    }
} edge[150007];
int cnt=0;
int head[maxn];
void addedge(int u,int v,int len) {
    edge[cnt].n=v;
    edge[cnt].d=len;
    edge[cnt].next=head[u];
    head[u]=cnt++;
};
int dis[maxn];
void dij(int s) {
    int i;
    FOR(i,1,n) dis[i]=INF;
    dis[s]=0;
    priority_queue<node> Q;
    Q.push(node(s,dis[s]));
    while (!Q.empty()) {
        node x=Q.top();
        Q.pop();
        for (i=head[x.n]; i!=-1; i=edge[i].next) {
            node &y=edge[i];
            if (dis[y.n]>x.d+y.d) {
                dis[y.n]=x.d+y.d;
                Q.push(node(y.n,dis[y.n]));
            }
        }
    }
}
int u,v,len;
int main() {
    while (~scanf("%d%d\n",&n,&m)) {
        memset(head,0xff,sizeof(head));
        cnt=0;
        REP(i,m) {
            scanf("%d%d%d",&u,&v,&len);
            //val(v)-val(u)<=len
            addedge(u,v,len);
        }
        dij(1);
        printf("%d\n",dis[n]);
    }
}
/*
*/
