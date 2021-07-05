#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
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
const LL maxn=507;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a*=a) ret=1ll*ret*a%M;return ret;}

#define x x_x
#define y y_y
struct node{
    int from,to,cap;
    node(int f=0,int t=0,int c=0):from(f),to(t),cap(c){}
};
vector<node> E;
vector<int> edge[maxn];
int tot;
void addflow(int from,int to,int cap){
    E.push_back(node(from,to,cap));edge[from].push_back(tot++);
    E.push_back(node(to,from,0));  edge[to].push_back(tot++);
}
queue<int> Q;
bool vis[maxn];
int d[maxn];
bool bfs(int s,int t){
    memset(vis,0,sizeof(vis));
    while (Q.size()) Q.pop();
    Q.push(s);
    d[s]=0;vis[s]=1;
    int i;
    while (!Q.empty()){
        int x=Q.front();Q.pop();
        REP(i,edge[x].size()){
            node &e=E[edge[x][i]];
            if (!vis[e.to]&&e.cap){
                vis[e.to]=1;
                d[e.to]=d[x]+1;
                Q.push(e.to);
            }
        }
    }
    return vis[t];
}
int dfs(int x,int t,int flow){
    if (x==t||flow==0) return flow;
    int i,ret=0,f;
    REP(i,edge[x].size()){
        node &e=E[edge[x][i]];
        if (d[x]+1==d[e.to]&&((f=dfs(e.to,t,min(flow,e.cap)))>0)){
            e.cap-=f;
            E[edge[x][i]^1].cap+=f;
            ret+=f;
            flow-=f;
            if (flow==0) break;
        }
    }
    return ret;
}
int n,m,i;
int u,v,len,ans;
int main(){
    while (~scanf("%d%d",&m,&n)){
        E.clear();
        FOR(i,1,n) edge[i].clear();
        ans=0;tot=0;
        FOR(i,1,m){
            scanf("%d%d%d",&u,&v,&len);
            addflow(u,v,len);
        }
        while (bfs(1,n)) ans+=dfs(1,n,INF);
        printf("%d\n",ans);
    }
}
