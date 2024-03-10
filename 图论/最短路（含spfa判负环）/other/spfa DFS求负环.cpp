#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <deque>
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
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
struct node{
    int n,d;
    node(){}
    node(int a,int b):n(a),d(b){}
    bool operator<(const node&a)const{
        if (d==a.d) return n<a.n;
        return d>a.d;
    }
};
vector<node> edge[maxn];
int dis[maxn],n,m;
bool vis[maxn];
bool spfa(int u){
    int i;
    vis[u]=1;
    REP(i,edge[u].size()){
        node v=edge[u][i];
        if (dis[u]+v.d<dis[v.n]){
            dis[v.n]=dis[u]+v.d;
            if (vis[v.n]) return 1;
            else {
                dis[v.n]=dis[u]+v.d;
                if (spfa(v.n)) return 1;
            }
        }
    }
    vis[u]=0;
    return 0;//judge negative ring
}
int s,t;
int u,v,len;
int main(){
    int i,j,k;
    while (~scanf("%d%d",&n,&m)){
        FOR(i,1,n) edge[i].clear();
        REP(i,m){
            scanf("%d%d%d",&u,&v,&len);
            edge[u].push_back(node(v,len));
            edge[v].push_back(node(u,len));
        }
        FOR(i,1,n) dis[i]=INF;dis[1]=0;
        FOR(i,1,n) vis[i]=0;
        spfa(1);
        FOR(i,2,n) printf("%d ",dis[i]==INF?-1:dis[i]);
        puts("");
    }
    return 0;
}
/*
*/
