#include <bits/stdc++.h>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG1
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef long long LL;
typedef long long ll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=2e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
inline void add(int &A,int B){A+=B;(A>=M)&&(A-=M);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

// 题意:
// 给你个树和数组, 操作 1: 求 A[l] -> A[r] 距离某个点 v 的距离和
// 操作 2: 交换给的数组相邻的两个数字的位置，强制在线
// 然后可持久化树分治的那个链, 可持久化时先加一些点进去

vector<pair<int,ll> > edge[maxn];
int sz[maxn]; bool mark[maxn];
int minweight,root;
void dfs1(int x,int fa,int n){
    int weight=0; sz[x]=1;
    for (auto now:edge[x]) {
        int v=now.first;
        if (v==fa||mark[v]) continue;
        dfs1(v,x,n); sz[x]+=sz[v];
        weight=max(weight,sz[v]);
    }weight=max(weight,n-sz[x]);
    if (weight<minweight) {root=x; minweight=weight;}
}
//get_initial_tree
int fa[maxn*4],way[maxn*4];
struct calculate_node{
    int top,seg; ll len;
    calculate_node(int _top=0,int _seg=0,ll _len=0):top(_top),seg(_seg),len(_len){};
};vector<calculate_node> CAL[maxn];
void dfs2(int x,int fa,int top,int seg,ll len){
    CAL[x].push_back(calculate_node(top,seg,len));
    for (auto now:edge[x]) {
        int v=now.first; ll l=now.second;
        if (v==fa||mark[v]) continue;
        dfs2(v,x,top,seg,len+l);
    }
}
int id[maxn*4]; int itot;
void rebuild(int x,int l,int r){
    int mid=(l+r)/2;
    if (l<mid){
        fa[++itot]=x; way[itot]=0; rebuild(itot,l,mid);
    } else if (l==mid) fa[id[l]]=x,way[id[l]]=0;
    if (mid+1<r){
        fa[++itot]=x; way[itot]=1; rebuild(itot,mid+1,r);
    } else if (mid+1==r) fa[id[r]]=x,way[id[r]]=1;
}
void dfs3(int x){
    mark[x]=1; root=x;
    dfs2(x,0,x,0,0);
    vector<int> subtrees;
    for (auto now:edge[x]){
        int v=now.first;ll len=now.second;
        if (mark[v]) continue;
        minweight=sz[v]; dfs1(v,0,sz[v]);
        dfs2(v,x,root,1,len);
        subtrees.push_back(root);
        dfs3(root);
    }int tot=0;
    for (auto now:subtrees) id[++tot]=now;
    if (tot) rebuild(x,1,tot);
}
struct node{
    int son[2],cnt[2]; ll len[2];
}T[maxn*80]; int tot;//0;add; 1:delete
int Root[maxn];
int P[maxn];
int downway[maxn],downpos[maxn],downtot;//down
int nowid[maxn*4];
void getway(int x){
    downtot=1; downway[1]=0;//no effect
    for (;x;x=fa[x]) downpos[downtot]=x,downway[++downtot]=way[x]; downtot--;
    reverse(downway+1,downway+1+downtot);
    reverse(downpos+1,downpos+1+downtot);
}
ll query(int root,int x){
    getway(x); ll ret=0; int i;
    FOR(i,1,downtot){
        nowid[downpos[i]]=root;
        root=T[root].son[downway[i]];
    } for (auto now:CAL[x]){
        int k=nowid[now.top];ll len=now.len;
        if (!k) continue;
        if (now.seg) ret-=T[k].cnt[1]*len+T[k].len[1];
        else ret+=T[k].cnt[0]*len+T[k].len[0];
    }
    return ret;
}
void change(int &root,int x,int seg){
    getway(x); int i;
    int now=++tot,noww=now; T[tot]=T[root];
    FOR(i,1,downtot) {
        nowid[downpos[i]]=now;
        if (i!=downtot){
            T[now].son[downway[i]]=++tot;
            now=T[now].son[downway[i]];
            root=T[root].son[downway[i]];
            T[now]=T[root];
        }
    } root=noww;
    for (auto now:CAL[x]){
        int k=nowid[now.top];
        T[k].cnt[now.seg]+=seg;
        T[k].len[now.seg]+=seg*now.len;
    }deputs("");
}
int n,m;
ll lastans;
int TaskA(){
    int i;
    FOR(i,1,n) scanf("%d",&P[i]);
    FOR(i,1,n-1){
        int u,v; ll w;
        scanf("%d%d%I64d",&u,&v,&w);
        edge[u].push_back(make_pair(v,w));
        edge[v].push_back(make_pair(u,w));
    }minweight=n; itot=n;
    dfs1(1,0,n); dfs3(root);
    tot=0;
    FOR(i,1,n) Root[i]=Root[i-1],change(Root[i],P[i],1);
    FOR(i,1,m) {
        int op;
        scanf("%d",&op);
        if (op==1){
            int l,r,v;
            scanf("%d%d%d",&l,&r,&v);
            l^=lastans; r^=lastans; v^=lastans;
            lastans=query(Root[r],v);
            lastans-=query(Root[l-1],v);
            printf("%I64d\n",lastans);
            lastans%=1<<30;
        }else{
            int x;
            scanf("%d",&x); x^=lastans;
            change(Root[x],P[x],-1);
            change(Root[x],P[x+1],1);
            swap(P[x],P[x+1]);
        }
    }
    return 0;
}
char S[maxn];
void initialize(){}
void Task_one(){TaskA();}
void Task_T(){int T;scanf("%d",&T);while (T--) TaskA();}
void Task_more_n(){while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m(){while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_string(){while (~scanf("%s",S)) TaskA();}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_more_n_m();
}
/*
*/
