#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <string>
#include <queue>
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> pii;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3f;
const int maxn=1e5+7;
double abs(double x) {return x>0?x:-x;}
//2017-harbin-K
//选出k个区间，使得这k个区间全覆盖，而且sigmaA/sigmaB最小
//俩log dp TLE
//做法：建最短路，玄学过题
struct node {
    int n;
    double d;
    node() {}
    node(int _n,double _d):n(_n),d(_d) {};
    bool operator<(const node &A)const {
        if (d==A.d) return n<A.n;
        return d>A.d;
    }
};
struct node_e {
    int n,A,B;
    double d;
    node_e(int _n,int _A,int _B,double _d):n(_n),A(_A),B(_B),d(_d) {}
};
vector<node_e> edge[maxn];
int dis[maxn];
int preA[maxn],preB[maxn];
void dij(int s,int n) {
    int i;
    FOR(i,1,n) dis[i]=INF;
    dis[s]=0;
    priority_queue<node> Q;
    Q.push(node(s,dis[s]));
    while (Q.size()) {
        node x=Q.top();
        Q.pop();
        for (auto &y:edge[x.n]) {
            if (dis[y.n]>x.d+y.d) {
                dis[y.n]=x.d+y.d;
                Q.push(node(y.n,dis[y.n]));
                preA[y.n]=preA[x.n]+y.A;
                preB[y.n]=preB[x.n]+y.B;
            }
        }
    }
}
int n,t;
int S[maxn],T[maxn],A[maxn],B[maxn];
double check(double x) {
    int i;
    double allA=0,allB=0;
    FOR(i,1,t+1)
    edge[i].clear();
    FOR(i,1,n) {
        if (A[i]-B[i]*x<=0) {
            allA+=A[i];
            allB+=B[i];
            edge[S[i]].emplace_back(node_e(T[i]+1,0,0,0));
        } else edge[S[i]].emplace_back(node_e(T[i]+1,A[i],B[i],A[i]-B[i]*x));
    }
    FOR(i,1,t)
    edge[i+1].emplace_back(node_e(i,0,0,0));
    dij(1,t+1);
    allA+=preA[t+1];
    allB+=preB[t+1];
    return allA/allB;
}
int main() {
    int i,j,m,x,_T;
    scanf("%d",&_T);
    while (_T--) {
        scanf("%d%d",&n,&t);
        FOR(i,1,n)
        scanf("%d%d%d%d",&S[i],&T[i],&A[i],&B[i]);
        double ans=100;
        while (1) {
            double now=check(ans);
            if (abs(now-ans)<0.001) break;
            ans=now;
        }
        printf("%.3lf\n",ans);
    }
    return 0;
}
/*
*/
