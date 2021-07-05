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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a*=a) ret=1ll*ret*a%M; return ret;}

// 拆点后可以S向入连边, 出向T连边, 然后入和出就可以保持动态平衡!
// 连边是为了将"获取的"和"使用的"联系起来! 大概意思就是, 使用的流量确定...
// 注意观察特殊性质
struct node {
    LL to,cap,cost,rev;
    node(int t=0,int c=0,int n=0,int r=0):
        to(t),cap(c),cost(n),rev(r) {}
};
vector<node> edge[maxn];
void addedge(int from,int to,LL cap,LL cost) {
    edge[from].push_back(node(to,cap,cost,edge[to].size()));
    edge[to].push_back(node(from,0,-cost,edge[from].size()-1));
}
int n,m,V;
LL dis[maxn];
bool mark[maxn];
int pre_v[maxn],pre_e[maxn];
deque<int> Q;
pair<LL,LL> mincostflow(int s,int t,LL f) {
    LL ret=0,d;
    int i,v;
    while (f) {
        memset(dis,0x3f,sizeof(dis));
        memset(mark,0,sizeof(mark));
        while (Q.size()) Q.pop_front();
        dis[s]=0;
        Q.push_back(s);
        while (Q.size()) {
            v=Q.front();
            mark[v]=0;
            Q.pop_front();
            REP(i,edge[v].size()) {
                node &e=edge[v][i];
                if (e.cap>0&&dis[e.to]>dis[v]+e.cost) {
                    dis[e.to]=dis[v]+e.cost;
                    pre_v[e.to]=v;
                    pre_e[e.to]=i;
                    if (!mark[e.to]) {
                        if (Q.empty()||dis[Q.front()]<dis[e.to])
                            Q.push_back(e.to);
                        else Q.push_front(e.to);
                        mark[e.to]=1;
                    }
                }
            }
        }
        if (dis[t]==INFF) break;
        d=f;
        for (v=t; v!=s; v=pre_v[v])
            d=min(d,edge[pre_v[v]][pre_e[v]].cap);
        f-=d;
        ret+=d*dis[t];
        for (v=t; v!=s; v=pre_v[v]) {
            node &e=edge[pre_v[v]][pre_e[v]];
            e.cap-=d;
            edge[v][e.rev].cap+=d;
        }
        if (d==0) break;
    }
    return make_pair(INFF-f,ret);
}
int i,j,k;
int main() {
    scanf("%d%d",&n,&m);
    FOR(i,1,m) {
        LL u,v,c,w;
        scanf("%lld%lld%lld%lld",&u,&v,&c,&w);
        addedge(u,v,c,w);
    }
    V=n;
    pair<LL,LL> ans=mincostflow(1,n,INFF);
    printf("%lld %lld",ans.first,ans.second);
}
