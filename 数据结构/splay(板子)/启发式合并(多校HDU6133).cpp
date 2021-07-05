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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline LL powMM(LL a,LL b) {
    LL ret=1;
    while (b) {
        if (b&1) ret=ret*a%M;
        a=a*a%M;
        b>>=1;
    }
    return ret;
}

struct splaytree {
    struct node {
        LL val,sum;
        int son[2],size;
        void init(LL _val) {
            val=sum=_val; size=1;
            son[0]=son[1]=0;
        }
    } T[maxn]; //编号是对应的
    int fa[maxn];
    int root;
    inline void pushup(int x) {
        T[x].sum=T[x].val;
        T[x].size=1;
        if (T[x].son[0]) {
            T[x].sum+=T[T[x].son[0]].sum;
            T[x].size+=T[T[x].son[0]].size;
        }
        if (T[x].son[1]) {
            T[x].sum+=T[T[x].son[1]].sum;
            T[x].size+=T[T[x].son[1]].size;
        }
    }
    void rotate(int x,int kind) {
        int y=fa[x],z=fa[y];
        T[y].son[!kind]=T[x].son[kind],fa[T[x].son[kind]]=y;
        T[x].son[kind]=y,fa[y]=x;
        T[z].son[T[z].son[1]==y]=x,fa[x]=z;
        pushup(y);
    }
    void splay(int x,int goal) {
        if (x==goal) return;
        while (fa[x]!=goal) {
            int y=fa[x],z=fa[y];
            int rx=T[y].son[0]==x,ry=T[z].son[0]==y;
            if (z==goal) rotate(x,rx);
            else {
                if (rx==ry) rotate(y,ry);
                else rotate(x,rx);
                rotate(x,ry);
            }
        }
        pushup(x);
        if (goal==0) root=x;
    }
    LL insert(int x) { //x为原先位置
        int u=root,f=0;
        while (u) {
            f=u;
            if (T[x].val<T[u].val) u=T[u].son[0];
            else u=T[u].son[1];
        }
        if (T[x].val<T[f].val) T[f].son[0]=x;
        else T[f].son[1]=x;
        fa[x]=f;
        splay(x,0);
        return T[T[x].son[0]].sum+T[x].val*(T[T[x].son[1]].size+1);
    }
    LL dfs(int x) {
        int l=T[x].son[0],r=T[x].son[1];
        LL ret=0;
        T[x].init(T[x].val);
        if (l) ret+=dfs(l);
        ret+=insert(x);
        if (r) ret+=dfs(r);
        return ret;
    }
    LL merge(int x,int y,LL tmp,LL ret) {
        if (x==y) return tmp;
        splay(x,0); splay(y,0);
        if (T[x].size>T[y].size) swap(x,y),swap(tmp,ret);
        root=y;
        ret+=dfs(x);
        return ret;
    }
    int getkth(int x,int k) { //未验证,抄的前面那个板子
        int u=root;
        while (T[T[u].son[0]].size!=k) {
            if (k<T[T[u].son[0]].size) u=T[u].son[0];
            else {
                k-=T[T[u].son[0]].size+1;
                u=T[u].son[1];
            }
        }
        return T[x].val;
    }
} T;
int n,m;
vector<int> edge[maxn];
LL ans[maxn];
int val[maxn];
void dfs(int x,int fa) {
    ans[x]=val[x];
    for (int v:edge[x]) {
        if (v==fa) continue;
        dfs(v,x);
        ans[x]=T.merge(x,v,ans[x],ans[v]);
    }
}
int i,j,k;
int main() {
    int TT;
    scanf("%d",&TT);
    while (TT--) {
        scanf("%d",&n);
        FOR(i,1,n) scanf("%d",&val[i]);
        REP(i,n-1) {
            int u,v;
            scanf("%d%d",&u,&v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        FOR(i,1,n) T.T[i].init(val[i]);
        dfs(1,0);
        FOR(i,1,n) printf("%lld ",ans[i]);
        puts("");
        FOR(i,1,n) T.fa[i]=0;
        FOR(i,1,n) ans[i]=0,vector<int>().swap(edge[i]);
    }
}
/*
*/

