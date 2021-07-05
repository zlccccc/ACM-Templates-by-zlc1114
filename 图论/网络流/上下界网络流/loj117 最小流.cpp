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
const LL maxn=5e4+17;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a*=a) ret=1ll*ret*a%M; return ret;}

namespace maxflow {
    typedef int type;
    const type INF=0x3f3f3f3f;
    struct node {
        int to; type cap; int next;
        node(int t=0,type c=0,int n=0):to(t),cap(c),next(n) {};
    } edge[maxn*50];
    int head[maxn],tot;
    int addedge(int from,int to,type cap,type rcap=0) {
        edge[tot]=node(to,cap,head[from]); head[from]=tot++;
        edge[tot]=node(from,rcap,head[to]); head[to]=tot++;
        return tot-2;
    }
    int dep[maxn],cur[maxn];//当前弧优化
    bool bfs(int s,int t,int n) {
        static int Q[maxn],ST,ED;
        memset(dep+1,0,n*sizeof(int));
        ST=0; ED=-1;
        Q[++ED]=s; dep[s]=1;
        while (ST<=ED) {
            int u=Q[ST++];
            for (int i=head[u]; i!=-1; i=edge[i].next) {
                int v=edge[i].to;
                if (!dep[v]&&edge[i].cap) {
                    Q[++ED]=v; dep[v]=dep[u]+1;
                }
            }
        } return (dep[t]!=0);
    }
    type dfs(int x,const int &t,type flow=INF) {
        if (x==t||flow==0) return flow;
        type ret=0;
        for (int i=cur[x]; i!=-1; i=edge[i].next) {
            if (dep[x]+1==dep[edge[i].to]&&edge[i].cap) {
                type f=dfs(edge[i].to,t,min(flow,edge[i].cap));
                edge[i].cap-=f; edge[i^1].cap+=f;
                ret+=f; flow-=f; cur[x]=i;
                if (flow==0) break;
            }
        } if (!ret) dep[x]=0;
        return ret;
    }
    type maxflow(int s,int t,int n) {
        type ret=0;
        while (bfs(s,t,n)) {
            type f;
            memcpy(cur+1,head+1,n*sizeof(int));
            while ((f=dfs(s,t))>0) ret+=f;
        } return ret;
    }
    void init(int n) {
        memset(head+1,0xff,n*sizeof(int)); tot=0;
    }
}
//可二分t->s边的下/上界,即可达到最大最小流
//最大流:t->s连边, ss->tt流, s->t正向最大流,会流掉反向建的边的流量, 流量就是ans
//最小流:ss->tt流, t->s连边, ss->tt流, s->t的就是最大流
//带权值的直接加权即可, in和out加的边val=0(只是为了限制流出可以等于流入而已)
namespace pipeflow {
    typedef int type;
    int eid[maxn*10],etot;
    type in[maxn],out[maxn],flow[maxn*10];
    int s_s,t_t;//S,T
    int addedge(int u,int v,int low,int high) {
        eid[etot]=maxflow::addedge(u,v,high-low);
        out[u]+=low; in[v]+=low; flow[etot++]=low;
        return etot-1;
    }
    void init(int n) {
        s_s=n+1,t_t=n+2; etot=0;
        memset(in+1,0,n*sizeof(type));
        memset(out+1,0,n*sizeof(type));
        maxflow::init(n+2);
    }
    type solve(int n,int s,int t) {
        int sum=0; int i;
        FOR(i,1,n) {
            sum+=max(0,in[i]-out[i]);
            if (in[i]>out[i]) maxflow::addedge(s_s,i,in[i]-out[i]);
            if (in[i]<out[i]) maxflow::addedge(i,t_t,out[i]-in[i]);
        }
        // // maxflow:
        // maxflow::addedge(t,s,INF);
        // if (maxflow::maxflow(s_s,t_t,n+2)!=sum) return -1;
        // return maxflow::maxflow(s,t,n+2);//maxflow

        // // minflow:
        // type first=maxflow::maxflow(s_s,t_t,n+2);
        // int retpos=maxflow::addedge(t,s,INF);
        // if (first+maxflow::maxflow(s_s,t_t,n+2)!=sum) return -1;
        // return maxflow::edge[retpos^1].cap;//minflow

        // okay flow:
        // if (maxflow::maxflow(s_s,t_t,n+2)!=sum) return 0;
        REP(i,etot) flow[i]+=maxflow::edge[eid[i]^1].cap;//edges
        //return 1;
    }
}
int E[maxn*10];
int main() {
    int n,m,s,t,i;
    scanf("%d%d%d%d",&n,&m,&s,&t);
    pipeflow::init(n);
    FOR(i,1,m) {
        int u,v,low,high;
        scanf("%d%d%d%d",&u,&v,&low,&high);
        E[i]=pipeflow::addedge(u,v,low,high);
    } int ans=pipeflow::solve(n,s,t);
    if (ans==-1) puts("please go home to sleep");
    else printf("%d\n",ans);
}
