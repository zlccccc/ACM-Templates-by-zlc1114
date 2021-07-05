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
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+9;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

bool deleted[maxn],vis[maxn];
vector<pair<int,int> > edge[maxn];
priority_queue<pair<int,int> > Q;
int weight[maxn];
int fa[maxn];
inline int getfa(int x){
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa[x]);
}
int getst(int &s,int &t,int n){
    int i;t=1;
    while (Q.size()) Q.pop();
    REP(i,n-1){
        vis[s=t]=1;
        for (auto &e:edge[s]) {
            int v=getfa(e.second);
            e.second=v;
            if (!vis[v])
                Q.push(make_pair(weight[v]+=e.first,v));
        }t=0;
        while (!t&&Q.size()){
            auto now=Q.top();Q.pop();
            int v=now.second;
            if (!vis[v]) t=v;
        }if (!weight[t]) return 0;
    }return weight[t];
}
int mincut(int n){
    int ret=INF;
    int s,t,i,j,k;
    FOR(i,1,n) deleted[i]=0,fa[i]=i;
    rFOR(i,2,n){
        FOR(j,1,n) weight[j]=0,vis[j]=0;
        ret=min(ret,getst(s,t,i));
        if (!ret) return 0;
        for (auto v:edge[t]) edge[s].push_back(v);
        int x=getfa(s),y=getfa(t);fa[y]=x;
        vector<pair<int,int> >().swap(edge[t]);
    }return ret;
}
int n,m;
int main() {
    int i,j;
    int T;
    while (~scanf("%d%d",&n,&m)){
        FOR(i,1,n) edge[i].clear();
        FOR(i,1,m){
            int u,v,val;
            scanf("%d%d%d",&u,&v,&val);
            edge[u].push_back(make_pair(val,v));
            edge[v].push_back(make_pair(val,u));
        }printf("%d\n",mincut(n));
    }
    return 0;
}
/*
*/
