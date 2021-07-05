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
const LL maxn=20000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M; return ret;}

namespace maxflow {
    typedef int type;
    const type INF=0x3f3f3f3f3f3f3f3f;
    struct node {
        int to; type cap; int next;
        node(int t=0,type c=0,int n=0):to(t),cap(c),next(n) {};
    } edge[maxn*50];
    int head[maxn],tot;
    void addedge(int from,int to,type cap,type rcap=0) {
        edge[tot]=node(to,cap,head[from]); head[from]=tot++;
        edge[tot]=node(from,rcap,head[to]); head[to]=tot++;
    }
    int gap[maxn],dep[maxn],cur[maxn];
    void bfs(int s,int t,int n) {//t好像没啥用啊=_=
        static int Q[maxn],ST,ED;
        memset(dep+1,0xff,n*sizeof(int));
        memset(gap+1,0,n*sizeof(int));
        gap[0]=1; dep[t]=0;
        ST=0; ED=-1; Q[++ED]=t;
        while (ST<=ED) {
            int u=Q[ST++];
            for (int i=head[u]; ~i; i=edge[i].next) {
                int v=edge[i].to;
                if (dep[v]!=-1) continue;
                Q[++ED]=v; dep[v]=dep[u]+1;
                gap[dep[v]]++;
            }
        }
    }
    int S[maxn];
    type sap(int s,int t,int n) {
        bfs(s,t,n);
        memcpy(cur+1,head+1,n*sizeof(int));
        int top=0,u=s; type ret=0;
        while (dep[s]<n) {
            if (u==t) {
                type MIN=INF,inser=0,i;
                REP(i,top) if (MIN>edge[S[i]].cap)
                    MIN=edge[S[i]].cap,inser=i;
                REP(i,top) {
                    edge[S[i]].cap-=MIN,edge[S[i]^1].cap+=MIN;
                } ret+=MIN; top=inser; u=edge[S[top]^1].to;
                continue;
            } bool flag=0; int v;
            for (int i=cur[u]; ~i; i=edge[i].next) {
                v=edge[i].to;
                if (edge[i].cap&&dep[v]+1==dep[u]) {
                    flag=1; cur[u]=i; break;
                }
            } if (flag) {
                S[top++]=cur[u]; u=v; continue;
            } int MIN=n;
            for (int i=head[u]; ~i; i=edge[i].next) {
                v=edge[i].to;
                if (edge[i].cap&&dep[v]<MIN)
                    MIN=min(MIN,dep[v]),cur[u]=i;
            } gap[dep[u]]--;
            if (ret>INF) return ret;//not okay
            if (!gap[dep[u]]) return ret;
            dep[u]=MIN+1; gap[dep[u]]++;
            if (u!=s) u=edge[S[--top]^1].to;
        } return ret;
    }
    void init(int n) {
        memset(head+1,0xff,n*sizeof(int)); tot=0;
    }
}
int n,m,s,t;
int main() {
    while (~scanf("%d%d",&n,&m)) {
        maxflow::init(n+2);
        s=n+1; t=n+2;
        int i;
        FOR(i,1,n) {
            int a,b;
            scanf("%d%d",&a,&b);
            maxflow::addedge(s,i,a);
            maxflow::addedge(i,t,b);
        }
        FOR(i,1,m) {
            int u,v,len;
            scanf("%d%d%d",&u,&v,&len);
            maxflow::addedge(u,v,len,len);
        }
        printf("%d\n",maxflow::sap(s,t,n+2));
    }
}
/*
*/
