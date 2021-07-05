#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const LL maxm=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

// tuple:
// priority_queue<tuple<ll, bool, short, short>, vector<tuple<ll, bool, short, short>>, greater<>> pq;
// pq.push({0, 0, 0, 0});
//woc板子错了
struct node {
    int n; LL d;
    node(int _n=0,LL _d=0):n(_n),d(_d) {};
    const bool operator <(const node &A)const {
        if (d!=A.d) return d>A.d;//注意!!! 否则为未优化的bellmanford
        return n>A.n;
    }
};
vector<node> edge[maxn];
priority_queue<node> Q;
LL dis[maxn];
int n,m;
void dij(int s,int n) {
    int i;
    FOR(i,1,n) dis[i]=INFF;
    dis[s]=0;
    Q.push(node(s,0));
    while (Q.size()) {
        node x=Q.top(); Q.pop();
        if (dis[x.n]!=x.d) continue;//!
        for (node y:edge[x.n]) {
            if (dis[y.n]>x.d+y.d) {
                dis[y.n]=x.d+y.d;
                Q.push(node(y.n,dis[y.n]));
            }
        }
    }
}
int s,t;
int u,v,len;
int main() {
    int i,j,k;
    while (~scanf("%d%d",&n,&m)) {
        FOR(i,1,n) edge[i].clear();
        REP(i,m) {
            scanf("%d%d%d",&u,&v,&len);
            edge[u].push_back(node(v,len));
            edge[v].push_back(node(u,len));
        }
        dij(1);
        FOR(i,2,n) printf("%d ",dis[i]==INF?-1:dis[i]);
        puts("");
    }
    return 0;
}
/*
*/
