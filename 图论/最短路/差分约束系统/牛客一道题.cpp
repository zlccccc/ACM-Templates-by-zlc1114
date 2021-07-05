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
const LL M=998244353;
const LL M1=998244353;
const LL M2=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}
//https://www.nowcoder.net/acm/contest/71/E
//前缀和进行差分约束
const int len=20;
int n,m,i,j,k;
struct node{
    int n,d,next;
    node(){}
    node(int _n,int _d,int _next):n(_n),d(_d),next(_next){}
}edge[maxn*4];
int head[maxn],cnt;
inline void addedge(int u,int v,int len){
//    printf("addedge : %2d->%2d %3d\n",u,v,len);
    edge[cnt]=node(v,len,head[u]);
    head[u]=cnt++;
};
int dis[maxn];
bool vis[maxn];
void spfa(int s,int n){
    int i;
    FOR(i,0,n) dis[i]=INF,vis[i]=0;
    dis[s]=0;
    deque<int> Q;//slf need
    Q.push_back(s);
    while (!Q.empty()){
        int u=Q.front();Q.pop_front();
        vis[u]=0;//not lll
        for(i=head[u];i!=-1;i=edge[i].next){
            node &v=edge[i];
            if (dis[u]+v.d<dis[v.n]){
                dis[v.n]=dis[u]+v.d;
                if (!vis[v.n]){
                    vis[v.n]=1;
                    if (Q.empty()||dis[Q.front()]<dis[v.n]) Q.push_back(v.n);//slf
                    else Q.push_front(v.n);//slf
                }
            }
        }
//        FOR(i,0,n) printf("%d ",dis[i]);puts(" <-  dis");
    }
}
int op[maxn],l[maxn],r[maxn],v[maxn];
int ans[maxn];
int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m) scanf("%d%d%d%d",&op[i],&l[i],&r[i],&v[i]);
    REP(j,len){
        cnt=0;
        FOR(i,0,n) head[i]=-1;
        FOR(i,1,n){
            addedge(i,i-1,0);
            addedge(i-1,i,1);
        }FOR(i,1,m){
            if (op[i]==1){
                if ((v[i]>>j)&1) addedge(r[i],l[i]-1,-1);
                else addedge(l[i]-1,r[i],0);
            }else{
                if ((v[i]>>j)&1) addedge(r[i],l[i]-1,-(r[i]-l[i]+1));
                else addedge(l[i]-1,r[i],r[i]-l[i]);
            }
        }spfa(0,n);
        FOR(i,1,n) ans[i]|=(dis[i]-dis[i-1])<<j;
    }
    FOR(i,1,n) printf("%d\n",ans[i]);
}
/*
2 3 5 8 13 6
1 1 2 3 4 5
*/
