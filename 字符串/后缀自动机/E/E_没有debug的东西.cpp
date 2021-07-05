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
const LL maxn=3e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

//SPOJ COT4
struct SAM{
    const static int maxn=2e5+7;
    int next[maxn][26],fail[maxn],len[maxn],cnt,pos[maxn],Pos[maxn];
    void init(){
        cnt=0;fail[0]=-1;len[0]=0;pos[0]=0;
        memset(next[0],0,sizeof(next[0]));
    }
    int add(int p,int c,int id){
        int np=++cnt;pos[np]=Pos[np]=id;
        memset(next[np],0,sizeof(next[np]));
        len[np]=len[p]+1;
        for (;p!=-1&&!next[p][c];p=fail[p]) next[p][c]=np;
        if (p==-1) fail[np]=0;
        else {
            int q=next[p][c];
            if (len[p]+1==len[q]) fail[np]=q;
            else{
                int nq=++cnt;len[nq]=len[p]+1;
                memcpy(next[nq],next[q],sizeof(next[q]));
                fail[nq]=fail[q];pos[nq]=pos[q];Pos[nq]=0;
                fail[np]=fail[q]=nq;
                for (;p!=-1&&next[p][c]==q;p=fail[p]) next[p][c]=nq;
            }
        }
        return np;
    }
    int failnext[maxn][26];
};
struct TRIE{
    SAM sam;
    const static int maxn=1e5+26+7;
    void init(){
        sam.init();
        tot=0;ToT=1;id[ToT]=0;val[0]=-1;//1:空
        memset(next[0],0,sizeof(next[0]));
    }
    //1:trie上建树
    int id[maxn],ToT;//queries
    int next[maxn][26],last[maxn],tot;//on the trie
    int val[maxn];
    void Add(int i,int c){
        int p=id[i];ToT++;
        if (!next[p][c]) {
            next[p][c]=++tot;val[tot]=c;
            memset(next[tot],0,sizeof(next[tot]));
            fa[tot][0]=p;
        }id[ToT]=next[p][c];
    }
    int Q[maxn],st,ed;
    void buildSAM(){
        st=ed=0;Q[ed++]=0;
        while (st!=ed){
            int p=Q[st++];char c;
            REP(c,26) if (next[p][c]){
                int nxt=next[p][c];
                last[nxt]=sam.add(last[p],c,nxt);
                Q[ed++]=nxt;
            }
        }
    }
    //2:get L-R
    int failtot;
    int rank[maxn],sa[maxn];
    void dfsrank(int x){
        if (sam.Pos[x]) rank[sam.Pos[x]]=++failtot,sa[failtot]=sam.Pos[x];
        char c;
        REP(c,26) if (sam.failnext[x][c]) dfsrank(sam.failnext[x][c]);
    }
    void linkfail(){
        int i;
        memset(sam.failnext,0,sizeof(sam.failnext[0])*(sam.cnt+1));
        FOR(i,1,sam.cnt)
            sam.failnext[sam.fail[i]][val[prev(sam.pos[i],sam.len[sam.fail[i]])]]=i;
        dfsrank(0);
    }
    //3:build_fa; ladder长链剖分
    int fa[maxn][21],son[maxn],top[maxn],len[maxn],dep[maxn];
    vector<int> ladder[maxn],upper[maxn];
    int upp[maxn];
    void buildfa(){
        int i,j,c;
        dep[0]=0;
        FOR(i,1,tot) rep(j,1,21)
            fa[i][j]=fa[fa[i][j-1]][j-1],dep[i]=dep[fa[i][0]]+1;
        rFOR(i,0,tot){
            int o=0;top[i]=i;
            ladder[i].clear();
            REP(c,26) if (next[i][c]){
                int p=next[i][c];
                if (!o||len[o]<len[p]) o=p;
            }if (o) len[i]=len[o]+1;else o=0;
            son[i]=o;top[i]=i;
        }FOR(i,0,tot) if (son[i]) top[son[i]]=top[i];
        rFOR(i,0,tot) ladder[top[i]].push_back(i);
        FOR(i,1,tot) if (top[i]==i){
            int u=i;
            REP(j,len[i]){
                u=fa[u][0];
                ladder[i].push_back(u);
                if (!u) break;
            }
        }upp[0]=-1;
        FOR(i,1,tot) upp[i]=upp[i-1]+(i==(i&-i));
    }
    int prev(int x,int k){;
        if (!k) return x;
        x=fa[x][upp[k]];k-=1<<upp[k];
        k-=dep[x]-dep[top[x]];x=top[x];
        return ladder[x][len[x]+k];
    }
}trie;
struct queries{
    int op,i,j;char c;
}q[maxn];
//3:get Ans_L-R
int QAQ;
struct node{
    int l,r,len,next;
    node(){l=r=len=0;}
    node(int _l,int _r,int _len):l(_l),r(_r),len(_len){};
}A[maxn],C[27];
node merge(node A,node B){//反着来的,B在后
    if (A.len==0) return B;
    if (B.len==0) return A;
    if (B.l>B.r||A.l>A.r) return node(0,-1,A.len+B.len);
    int l,r,L,R;
    l=B.r+1;r=B.l-1;
    for(L=B.l,R=B.r;L<=R;){
        int mid=(L+R)/2;
        if (trie.rank[trie.prev(trie.sa[mid],B.len)]<A.l) L=mid+1;
        else R=mid-1,l=mid;
    }
    for(L=B.l,R=B.r;L<=R;){
        int mid=(L+R)/2;
        if (trie.rank[trie.prev(trie.sa[mid],B.len)]>A.r) R=mid-1;
        else L=mid+1,r=mid;
    }
    return node(l,r,A.len+B.len);
}
//4:solve
int F[maxn];
inline int lowbit(int x){return x&-x;}
void update(int x,int val){
    for (;x<=trie.failtot;x+=lowbit(x)) F[x]+=val;
}int query(int x){
    int ret=0;
    for (;x;x-=lowbit(x)) ret+=F[x];
    return ret;
}int query(int l,int r){
    if (l>r) return 0;
    return query(r)-query(l-1);
}
node B[maxn];
int Ans[maxn],head[maxn];
void addnode(int x,int pos,int i){
    x=trie.id[x];B[i]=A[pos];
    B[i].next=head[x];head[x]=i;
}
void getans(int x){
    int i;
    if (x) update(trie.rank[x],1);
    for (i=head[x];~i;i=B[i].next){
        if (B[i].len&&B[i].l<=B[i].r) Ans[i]=query(B[i].l,B[i].r);
        else Ans[i]=0;
    }
    REP(i,26) if (trie.next[x][i]) getans(trie.next[x][i]);
    if (x) update(trie.rank[x],-1);
}
int n,m,Q;
int i,j,k;
char c;
int main(){
    scanf("%d",&Q);
    trie.init();
    FOR(i,1,Q){
        scanf("%d",&q[i].op);
        if (q[i].op==1){
            scanf("%d %c",&q[i].i,&c);q[i].c=c-'a';
            trie.Add(q[i].i,q[i].c);
        }else if (q[i].op==2){
            scanf("%d%d %c",&q[i].i,&q[i].j,&c);q[i].c=c-'a';
        }else scanf("%d%d",&q[i].i,&q[i].j);
    }
    trie.buildfa();
    trie.buildSAM();
    trie.linkfail();
    REP(i,26){
        int l,r,L,R;
        l=trie.failtot+1;r=0;
        for(L=1,R=trie.failtot;L<=R;){
            int mid=(L+R)/2;
            if (trie.val[trie.sa[mid]]<i) L=mid+1;
            else R=mid-1,l=mid;
        }
        for(L=1,R=trie.failtot;L<=R;){
            int mid=(L+R)/2;
            if (trie.val[trie.sa[mid]]>i) R=mid-1;
            else L=mid+1,r=mid;
        }
        C[i]=node(l,r,1);
    }
    FOR(i,0,trie.tot) head[i]=-1;QAQ=1;
    FOR(i,1,Q){
        if (q[i].op==1){
            head[i]=-1;
        }else if (q[i].op==2){
            if (q[i].i==0) A[++QAQ]=merge(C[q[i].c],A[q[i].j]);
            if (q[i].i==1) A[++QAQ]=merge(A[q[i].j],C[q[i].c]);
        }else if (q[i].op==3)
            A[++QAQ]=merge(A[q[i].i],A[q[i].j]);
        else addnode(q[i].j,q[i].i,i);
    }
    getans(0);
    FOR(i,1,Q) if (q[i].op==4) printf("%d\n",Ans[i]);
    return 0;
}
/*
*/
