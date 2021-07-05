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
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

//注意容斥的时候的length位置不是root~是上个root相连的位置
//也就是说dis得单独计算
int BIT_pool[maxn*40],*BIT[maxn],*SUBBIT[maxn],*st=BIT_pool;
int size[maxn];bool mark[maxn];
int minweight,root;
struct Node{
    int to,next;
    Node(int _to=0,int _next=0):to(_to),next(_next){};
}edge[maxn*2];
int head[maxn],tot;
void addedge(int u,int v){
    edge[++tot]=Node(v,head[u]);head[u]=tot;
}
void dfs1(int x,int fa,int n){
    int weight=0;
    size[x]=1;
    for (int i=head[x];~i;i=edge[i].next){
        int v=edge[i].to;
        if (v==fa||mark[v]) continue;
        dfs1(v,x,n);
        size[x]+=size[v];
        weight=max(weight,size[v]);
    }weight=max(weight,n-size[x]);
    if (weight<minweight) {root=x;minweight=weight;}
}
int length[maxn];
struct node{
    int top,len,next;
    node(){}
    node(int _top,int _len,int _next):top(_top),len(_len),next(_next){};
}nodes[maxn*40];
int addhead[maxn],delhead[maxn],caltot;
int maxdep;
void addadd(int x,int top,int len){
    nodes[++caltot]=node(top,len,addhead[x]);addhead[x]=caltot;
}void adddel(int x,int top,int len){
    nodes[++caltot]=node(top,len,delhead[x]);delhead[x]=caltot;
}
void dfs2(int x,int fa,int top,int dep,bool add){
    if (add) addadd(x,top,dep);
    else adddel(x,top,dep);
    for (int i=head[x];~i;i=edge[i].next){
        int v=edge[i].to;
        if (v==fa||mark[v]) continue;
        dfs2(v,x,top,dep+1,add);
    }if (add) maxdep=max(maxdep,dep);
    else maxdep=max(maxdep,dep);
}
int len[maxn],sublen[maxn];
void dfs3(int x){
    mark[x]=1;root=x;
//    printf("mark:%d\n",x);
    maxdep=0;dfs2(x,0,x,0,1);
    len[x]=maxdep;
    BIT[x]=st;st+=len[x]+1;
    for (int i=head[x];~i;i=edge[i].next){
        int v=edge[i].to;
        if (mark[v]) continue;
        minweight=size[v];
        dfs1(v,0,size[v]);
        maxdep=0;dfs2(v,0,root,1,0);//判重是x,init_dep=1
        sublen[root]=maxdep;
        SUBBIT[root]=st;st+=sublen[root]+1;
        dfs3(root);
    }
}
inline int lowbit(int x){return x&-x;}
void add(int *T,int n,int x,int val){
    x++;T--;n++;
    for (;x<=n;x+=lowbit(x)) T[x]+=val;
}int get(int *T,int x){
    x++;T--;int ret=0;
    for (;x;x-=lowbit(x)) ret+=T[x];
    return ret;
}
void update(int x,int val){
    for (int i=addhead[x];~i;i=nodes[i].next){
        int v=nodes[i].top,length=nodes[i].len;
        add(BIT[v],len[v],length,val);
    }for (int i=delhead[x];~i;i=nodes[i].next){
        int v=nodes[i].top,length=nodes[i].len;
        add(SUBBIT[v],sublen[v],length,val);
    }
}int query(int x,int dis){
    int ret=0;
    for (int i=addhead[x];~i;i=nodes[i].next){
        int v=nodes[i].top,length=nodes[i].len;
        if (dis>=length) ret+=get(BIT[v],min(dis-length,len[v]));
    }for (int i=delhead[x];~i;i=nodes[i].next){
        int v=nodes[i].top,length=nodes[i].len;
        if (dis>=length) ret-=get(SUBBIT[v],min(dis-length,sublen[v]));;
    }return ret;
}
int n,m,T;
int i,j,k;
char op[2];
int a[maxn];
int main(){
    while (~scanf("%d%d",&n,&m)){
        FOR(i,1,n) mark[i]=0,BIT[i]=SUBBIT[i]=nullptr;
        memset(BIT_pool,0,sizeof(int)*(st-BIT_pool));st=BIT_pool;
        FOR(i,1,n) head[i]=delhead[i]=addhead[i]=-1;tot=caltot=0;
        FOR(i,1,n) scanf("%d",&a[i]);
        FOR(i,1,n-1){
            int u,v;
            scanf("%d%d",&u,&v);
            addedge(u,v);addedge(v,u);
        }
        minweight=INF;
        dfs1(1,0,n);
        dfs3(root);
        FOR(i,1,n) update(i,a[i]);
        FOR(i,1,m){
            int u,v;
            scanf("%s%d%d",op,&u,&v);
            if (op[0]=='!') update(u,v-a[u]),a[u]=v;
            else printf("%d\n",query(u,v));
        }
    }
}
/*
*/
