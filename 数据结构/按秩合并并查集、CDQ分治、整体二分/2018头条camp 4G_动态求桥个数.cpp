#include<bits/stdc++.h>
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
using namespace std;
const int maxn=1e5+7;

// 题意: 动态求桥的个数
// 做法: 按时间分治, 然后缩边, tarjan找桥
int m;
struct E {
    int v,w;
    E() {}
    E(int _v,int _w) {v=_v; w=_w;}
};
struct node {
    int u,v,w,l,r;
    node(int _u,int _v,int _w,int _l,int _r) {
        u=_u; v=_v; w=_w; l=_l; r=_r;
    }
};
vector<E> edge[maxn];
typedef long long ll;
vector<node> remain;
int key[maxn],dfn[maxn];
E build(int x,int fa) {//build vt
    vector<E> ch; dfn[x]=1;
    for (auto now:edge[x]) {
        if (now.v==fa) continue;
        E w=build(now.v,x); w.w+=now.w;
        if (w.v) ch.push_back(w);
    } if (ch.size()>=2) key[x]=1;
    // printf("build: %d fa=%d; key=%d; ch.size=%d\n",x,fa,key[x],(int)ch.size());
    // if (ch.size()) printf("(%d-%d)\n",ch[0].v,ch[0].w);
    if (key[x]) {
        for (auto v:ch)
            remain.push_back(node(x,v.v,v.w,1,m));//exist!
        return E(x,0);
    } if (ch.size()) return ch[0];
    return E(0,0);
}
int low[maxn],vis[maxn],id[maxn];
int S[maxn],top,tot;
//first:  more;
void tarjan(int x,int fa) { //先缩这个, 再建虚树
    dfn[x]=low[x]=++tot;
    S[++top]=x; vis[x]=1;
    int cntfa=0;
    for (auto now:edge[x]) {
        if (now.v==fa&&!cntfa) {
            cntfa=1; continue;
        }
        if (!dfn[now.v]) {
            tarjan(now.v,x);
            low[x]=min(low[x],low[now.v]);
        } else if (vis[now.v])
            low[x]=min(low[x],dfn[now.v]);
    } if (dfn[x]==low[x]) {
        while (1) {
            int now=S[top--];
            vis[now]=0; id[now]=x;
            if (now==x) break;
        }
    }
    // printf("tarjan: %d: id=%d; low=%d,vis=%d\n",x,id[x],dfn[x],low[x]);
}
void clear_and_set(int l,int r,const vector<node> &nodes) {
    for (auto x:nodes) {
        edge[x.u].clear();
        edge[x.v].clear();
        dfn[x.u]=dfn[x.v]=0;
    } tot=0;//clear
    for (auto x:nodes) {
        if (x.l<=l&&r<=x.r) {
            // printf("set: %d-%d: w=%d time=%d to %d\n",x.u,x.v,x.w,x.l,x.r);
            edge[x.u].push_back(E(x.v,x.w));
            edge[x.v].push_back(E(x.u,x.w));
        }
    }//all_have
}
int ans[maxn];
void solve(int l,int r,vector<node> nodes,int base) { //m:边数
    // printf("solve: %d-%d; base=%d\n",l,r,base);
    clear_and_set(l,r,nodes);
    for (auto x:nodes) {
        if (!dfn[x.u]) tarjan(x.u,0);
        if (!dfn[x.v]) tarjan(x.v,0);
    }//tarjan
    vector<node> tmp;
    int all=0;
    for (auto x:nodes) {
        if (id[x.u]!=id[x.v]) {
            node nxt=x;
            nxt.u=id[x.u]; nxt.v=id[x.v];
            tmp.push_back(nxt);
            if (x.l<=l&&r<=x.r) all+=x.w;
        }
    }//init
    // puts("tarjan done");
    nodes.swap(tmp);
    if (l==r) {
        ans[l]=base+all;
        return;
    } int mid=(l+r)/2,div;

    tmp.clear();
    clear_and_set(l,r,nodes);
    for (auto x:nodes) key[x.u]=key[x.v]=0;
    for (auto x:nodes) {
        if (x.l<=mid&&!(x.l<=l&&r<=x.r)) {
            key[x.u]=key[x.v]=1;
            tmp.push_back(x);
        }
    } div=0; remain.clear();
    for (auto x:nodes) {
        if (x.l<=mid&&!(x.l<=l&&r<=x.r)) {
            if (!dfn[x.u]) build(x.u,0);
            if (!dfn[x.v]) build(x.v,0);
        }
    }//tarjan
    // for (auto x:remain) printf("    remain %d-%d: %d\n",x.u,x.v,x.w);
    // for (auto x:tmp)    printf("tmp-remain %d-%d: %d; time=%d-%d\n",x.u,x.v,x.w,x.l,x.r); puts("");
    for (auto x:remain) tmp.push_back(x),div+=x.w;;
    solve(l,mid,tmp,all-div+base);

    tmp.clear();
    clear_and_set(l,r,nodes);
    for (auto x:nodes) key[x.u]=key[x.v]=0;
    for (auto x:nodes) {
        if (mid<x.r&&!(x.l<=l&&r<=x.r)) {
            key[x.u]=key[x.v]=1;
            tmp.push_back(x);
        }
    } div=0; remain.clear();
    for (auto x:nodes) {
        if (mid<x.r&&!(x.l<=l&&r<=x.r)) {
            if (!dfn[x.u]) build(x.u,0);
            if (!dfn[x.v]) build(x.v,0);
        }
    }//tarjan
    // for (auto x:remain) printf("    remain %d-%d: %d\n",x.u,x.v,x.w);
    // for (auto x:tmp)    printf("tmp-remain %d-%d: %d; time=%d-%d\n",x.u,x.v,x.w,x.l,x.r); puts("");
    for (auto x:remain) tmp.push_back(x),div+=x.w;;
    solve(mid+1,r,tmp,all-div+base);
}
int main() {
    int i;
    int n;
    scanf("%d%d",&n,&m);
    map<pair<int,int>,int> MP;
    vector<node> init;
    FOR(i,1,m) {
        char op[4]; int u,v;
        scanf("%s%d%d",op,&u,&v);
        if (u>v) swap(u,v);
        if (op[0]=='A') {
            MP[make_pair(u,v)]=i;
        } else {
            init.push_back(node(u,v,1,MP[make_pair(u,v)],i-1));
            MP.erase(make_pair(u,v));
        }
    } for (auto now:MP)
        init.push_back(node(now.first.first,now.first.second,1,now.second,m));
    // for (auto now:init)
    //     printf("edge %d-%d: from %d to %d\n",now.u,now.v,now.l,now.r);
    solve(1,m,init,0);
    FOR(i,1,m) printf("%d\n",ans[i]);
    return 0;
}
/*
4 8
ADD 1 2
ADD 2 3
ADD 1 3
DEL 2 3
DEL 1 2
ADD 2 4
ADD 1 4
ADD 2 3
*/