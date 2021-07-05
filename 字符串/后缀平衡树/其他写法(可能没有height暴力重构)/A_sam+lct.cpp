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
#include <bitset>
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
const LL M=998244353;
const LL maxn=12e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct lct{
    struct node{
        int son[2],val,add,size;
        bool rev;
        void init(int _val){
            son[0]=son[1]=rev=add=0;
            size=1;
        }
    }T[maxn];
    bool root[maxn];
    int fa[maxn];
    void Reverse(int x){
        T[x].rev^=1;
        swap(T[x].son[0],T[x].son[1]);
    }
    void Add(int x,int val){
        T[x].val+=val;
        T[x].add+=val;
    }
    void pushup(int x){
        T[x].size=1;
        if (T[x].son[0]) T[x].size+=T[T[x].son[0]].size;
        if (T[x].son[1]) T[x].size+=T[T[x].son[1]].size;
    }
    void pushdown(int x){
        if (T[x].rev){
            if (T[x].son[0]) Reverse(T[x].son[0]);
            if (T[x].son[1]) Reverse(T[x].son[1]);
            T[x].rev=0;
        }
        if (T[x].add){
            if (T[x].son[0]) Add(T[x].son[0],T[x].add);
            if (T[x].son[1]) Add(T[x].son[1],T[x].add);
            T[x].add=0;
        }
    }
    void rotate(int x,int kind){
        int y=fa[x],z=fa[y];
        T[y].son[!kind]=T[x].son[kind],fa[T[x].son[kind]]=y;
        T[x].son[kind]=y,fa[y]=x;
        if(root[y]) {root[x]=true;root[y]=false;}
        else T[z].son[T[z].son[1]==y]=x;
        fa[x]=z;
        pushup(y);
    }
    void Prechange(int x){
        if (!root[x]) Prechange(fa[x]);
        pushdown(x);
    }
    void splay(int x){
        Prechange(x);
        while (!root[x]){
            int y=fa[x],z=fa[y];
            int rx=T[y].son[0]==x,ry=T[z].son[0]==y;
            if (root[y]) rotate(x,rx);
            else{
                if (rx==ry) rotate(y,ry);
                else rotate(x,rx);
                rotate(x,ry);
            }
        }
        pushup(x);
    }
    int access(int x){
        int y=0;
        for (;x;x=fa[x]){
            splay(x);
            root[T[x].son[1]]=true;
            T[x].son[1]=y;
            root[y]=false;
            y=x;
            pushup(x);
        }
        return y;
    }
    void makeroot(int x){
        access(x);
        splay(x);
        Reverse(x);
    }
    void link(int u,int v){
        makeroot(u);
        fa[u]=v;
    }
    void cut(int u,int v){
         makeroot(u);
         splay(v);
         fa[T[v].son[0]]=fa[v];
         fa[v]=0;
         root[T[v].son[0]]=true;
         T[v].son[0]=0;
         pushup(v);
    }
    void update(int u,int val){
        makeroot(1);
        access(u);
        splay(u);
        Add(u,val);
    }
    int ask(int x){
        splay(x);//splay Ò²¿É
        return T[x].val;
    }
}LCT;
struct sam{
    int cnt,last;
    int len[maxn],pre[maxn],nxt[maxn][26];//size[maxn];
    int id[maxn],length;
    inline void ins(int c){
        int np=++cnt,p=last;
        len[np]=len[p]+1;
        for (;p&&!nxt[p][c];p=pre[p]) nxt[p][c]=np;
        if (!p) pre[np]=1,LCT.link(np,1);
        else{
            int q=nxt[p][c];
            if (len[p]+1==len[q]) pre[np]=q,LCT.link(np,q);
            else{
                int nq=++cnt;len[nq]=len[p]+1;
                memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
//                size[nq]=size[q];
                LCT.T[nq].val=LCT.ask(q);
                LCT.link(nq,pre[q]);
                pre[nq]=pre[q];
                LCT.cut(q,pre[q]);
                LCT.link(nq,np);
                LCT.link(nq,q);
                pre[np]=pre[q]=nq;
                for (;p&&nxt[p][c]==q;p=pre[p]) nxt[p][c]=nq;
            }
        }
        last=np;
        id[++length]=np;
        LCT.update(np,1);
//        for (;np;np=pre[np]) size[np]++;
    }
    void insert(char s[]){
        int len=strlen(s),i;
        REP(i,len) ins(s[i]-'A');
    }
    int query(char *s){
        int p;
        for (p=1;p;p=nxt[p][(*s++)-'A'])
            if ((*s)=='\0')
                return LCT.ask(p);
//                return size[p];
        return 0;
    }
    void del(int k){
        while (k--)
            LCT.update(id[length--],-1);
//            for (int np=id[length--];np;np=pre[np])
//                size[np]--;
        last=id[length];
    }
    void init(){
        memset(nxt,0,sizeof(nxt));
        memset(len,0,sizeof(len));
        memset(pre,0,sizeof(pre));
//        memset(size,0,sizeof(size));
        cnt=0;last=++cnt;length=0;
        id[length]=last;
    }
}SAM;
int mask;
void decodeWithMask(char s[],int mask){
    int len=strlen(s),j;
    REP(j,len){
        mask=(mask*131+j)%len;
        char t=s[j];
        s[j]=s[mask];
        s[mask]=t;
    }
}
int n,m,i;
char a[3000007],op[20];
int main(){
    scanf("%d",&n);
    scanf("%s",a);
    REP(i,maxn) LCT.T[i].init(0),LCT.root[i]=1,LCT.fa[i]=0;
    SAM.init();
    SAM.insert(a);
    while (n--){
        scanf("%s",op);
        if (op[0]=='Q'){
            scanf("%s",a);
            decodeWithMask(a,mask);
            int ans=SAM.query(a);
            printf("%d\n",ans);mask^=ans;
        }else if (op[0]=='D'){
            scanf("%d",&i);
            SAM.del(i);
        }else{
            scanf("%s",a);
            decodeWithMask(a,mask);
            SAM.insert(a);
        }
    }
    return 0;
}
/*
*/
