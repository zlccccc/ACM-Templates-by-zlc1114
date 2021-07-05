#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=3e5+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;

LL K;
LL MUL[37];
LL getSum(LL x,LL y){
    LL ret=0,i;
    REP(i,K) ret=ret+(x/MUL[i]%3+y/MUL[i]%3)%3*MUL[i];
    return ret;
}
LL getDiv(LL x){
    LL ret=0,i;
    REP(i,K) ret=ret+(3-x/MUL[i]%3)%3*MUL[i];
    return ret;
}
LL color[maxn];
vector<int> edge[maxn];
LL ans;
int size[maxn];
bool mark[maxn];
int minweight,root;
void dfs1(int x,int fa,int n){
    int weight=0;
    size[x]=1;
    for (int v:edge[x]){
        if (v==fa||mark[v]) continue;
        dfs1(v,x,n);
        size[x]+=size[v];
        weight=max(weight,size[v]);
    }
    weight=max(weight,n-size[x]);
    if (weight<minweight) {root=x;minweight=weight;}
}
map<LL,int> now;
map<LL,int> MP;
void dfs2(int x,int fa,LL num){
    now[getSum(color[x],num)]++;
    for (int v:edge[x]){
        if (v==fa||mark[v]) continue;
        dfs2(v,x,getSum(num,color[x]));
    }
}
void calc(int x){
    MP.clear();
    MP[color[x]]++;
    for (int u:edge[x]){
        if (mark[u]) continue;
        now.clear();
        dfs2(u,0,0);
        for(pair<LL,int> P:now) ans+=MP[getDiv(P.first)]*P.second;
        for(pair<LL,int> P:now) MP[getSum(color[x],P.first)]+=P.second;
    }
    MP.clear();
}
void dfs3(int x){
    mark[x]=1;
    calc(x);
    for (int v:edge[x]){
        if (mark[v]) continue;
        minweight=size[v];
        dfs1(v,0,size[v]);
        dfs3(root);
    }
}
int n,m;
LL C[maxn];
LL P;
int main(){
    int i,j;
    MUL[0]=1;
    FOR(i,1,33) MUL[i]=MUL[i-1]*3;
    while (~scanf("%d",&n)){
        ans=0;
        scanf("%d",&K);
        REP(i,K) scanf("%lld",&C[i]);
        FOR(i,1,n){
            scanf("%lld",&P);
            REP(j,K){
                int t=0;
                while (P%C[j]==0){
                    P/=C[j];
                    t++;
                    if (t==3) t=0;
                }
                color[i]+=MUL[j]*t;
            }
            if (color[i]==0) ans++;
        }
        REP(i,n-1){
            int u,v;
            scanf("%d%d",&u,&v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        minweight=n;
        dfs1(1,0,n);
        dfs3(root);
        printf("%lld\n",ans);
        FOR(i,1,n) mark[i]=0;
        FOR(i,1,n) color[i]=0;
        FOR(i,1,n) vector<int>().swap(edge[i]);
    }
}
/*
*/
