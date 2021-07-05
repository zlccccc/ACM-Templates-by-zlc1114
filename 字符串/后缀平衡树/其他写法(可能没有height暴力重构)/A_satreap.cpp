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
const LL maxn=20e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct satreap{
    inline int rand(){
        static unsigned int seed=173;
        return seed=seed*19260817;
    }
    struct node{
        int son[2];unsigned int key;
        node(){son[0]=son[1]=0;}
    }T[maxn];
    LL rank[maxn];int size[maxn],val[maxn];
    int pre[maxn];char c[maxn];
    int cnt,root,last;
    inline bool cmp(int x,int y){
        return c[x]<c[y]||(c[x]==c[y]&&rank[pre[x]]<rank[pre[y]]);
    }
    void rebuild(int &x,LL l,LL r){
        if (!x) return;
        LL mid=(l+r)/2;
        rank[x]=mid;
        rebuild(T[x].son[0],l,mid-1);
        rebuild(T[x].son[1],mid+1,r);
        size[x]=val[x]+size[T[x].son[0]]+size[T[x].son[1]];
    }
    void rotate(int &x,int p,LL l,LL r){
        int y=T[x].son[p];
        T[x].son[p]=T[y].son[p^1];
        T[y].son[p^1]=x;
        x=y;
        rebuild(x,l,r);
    }
    void ins(int &x,LL l,LL r){
        LL mid=(l+r)/2;
        if (!x) {x=cnt;T[x].key=rand();rank[x]=mid;return;}
        size[x]++;
        int p=cmp(x,cnt);
        int &son=T[x].son[p];
        if (p==0) ins(son,l,mid-1);
        else ins(son,mid+1,r);
        if (T[son].key<T[x].key) rotate(x,p,l,r);
    }
    void insert(char s[]){
        int len=strlen(s),i;
        REP(i,len){
            c[++cnt]=s[i];size[cnt]=1;val[cnt]=1;
            pre[cnt]=last;last=cnt;
            ins(root,1ll,1ll<<62);
        }
    }
    bool cmp(int k,char s[],int len){
        int i=0;
        while (i<len&&k&&c[k]==s[i]) i++,k=pre[k];
        if (i==len) return 0;
        if (!k) return 1;
        return c[k]<s[i];
    }
    int query(char s[]){
        int now,len=strlen(s),ret=0;
        reverse(s,s+len);
        for (now=root;now;){
            if (!cmp(now,s,len)) now=T[now].son[0];
            else ret-=size[now]-size[T[now].son[1]],now=T[now].son[1];
        }s[len]='Z'+1;len++;s[len]=0;
        for (now=root;now;){
            if (!cmp(now,s,len)) now=T[now].son[0];
            else ret+=size[now]-size[T[now].son[1]],now=T[now].son[1];
        }
        return ret;
    }
    void del(int k){
        int now,p;
        while (k--){
            for (now=root;now!=last;){
                size[now]--;
                p=rank[last]>rank[now];
                now=T[now].son[p];
            }val[last]=0;size[last]--;
            last=pre[last];
        }
    }
    void Dfs(int x){
        printf("node : %d %d %d; size=%d\n",x,T[x].son[0],T[x].son[1],size[x]);
        if (!x) return;
        if (T[x].son[0]) Dfs(T[x].son[0]);
        if (T[x].son[1]) Dfs(T[x].son[1]);
    }
    void dfs(int x){
        if (!x) return;
        if (T[x].son[0]) dfs(T[x].son[0]);
        printf("%-4d  ",x);int i;if (!val[x]) printf("(deleted)");
        for (i=x;i;i=pre[i]) printf("%c",c[i]);puts("");
        if (T[x].son[1]) dfs(T[x].son[1]);
    }
}SAT;
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
    srand(time(0));
    scanf("%d",&n);
    scanf("%s",a);
    SAT.insert(a);
    while (n--){
        scanf("%s",op);
        if (op[0]=='Q'){
            scanf("%s",a);
            decodeWithMask(a,mask);
            int ans=SAT.query(a);
            printf("%d\n",ans);mask^=ans;
        }else if (op[0]=='D'){
            scanf("%d",&i);
            SAT.del(i);
        }else{
            scanf("%s",a);
            decodeWithMask(a,mask);
            SAT.insert(a);
        }
    }
    return 0;
}
/*
*/
