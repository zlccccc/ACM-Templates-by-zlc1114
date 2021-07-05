#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=12e5+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;

// 查询某串部分在串l->r的最大出现次数及位置
// SAM(这个套路)
// 做法:求出后缀树然后直接找到对应位置merge
// 这里可以看出, fail的含义就是说
// 某个位置往前len差长度的所有子串
// 然后对后缀树来建树然后对len倍增
// 就能求出对应的最短对应点来
int nxt[maxn][27],pre[maxn],len[maxn];
int CNT,last;
void add(int c) {
    int np=++CNT,p=last;
    len[np]=len[p]+1;
    for (; p&&!nxt[p][c]; p=pre[p]) nxt[p][c]=np;
    if (!p) pre[np]=1;
    else {
        int q=nxt[p][c];
        if (len[p]+1==len[q]) pre[np]=q;
        else {
            int nq=++CNT; len[nq]=len[p]+1;
            memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
            pre[nq]=pre[q];
            pre[np]=pre[q]=nq;
            for (; p&&nxt[p][c]==q; p=pre[p]) nxt[p][c]=nq;
        }
    }
    last=np;
}
//segtree
int cnt;
struct node {
    pair<int,int> val;//bigger
    int l,r;
} tree[maxn*25];
int root[maxn];
inline pair<int,int> add(pair<int,int> A,pair<int,int> B) {
    return make_pair(A.first+B.first,A.second);
}
inline pair<int,int> better(pair<int,int> A,pair<int,int> B) {
    if (A.first==B.first) return A.second<B.second?A:B;
    return A.first>B.first?A:B;
}
inline void insert(int &x,int val,int l,int r) {
    if (!x) x=++cnt;
    if (l==r) {
        tree[x].val.first++;
        tree[x].val.second=l;
        return;
    }
    int mid=(l+r)/2;
    if (val<=mid) insert(tree[x].l,val,l,mid);
    else insert(tree[x].r,val,mid+1,r);
    tree[x].val=better(tree[tree[x].l].val,
                       tree[tree[x].r].val);
}
inline int Merge(int x,int y,int l,int r) {
    if (!x||!y) return x|y;
    int z=++cnt;
    if (l==r) {
        tree[z].val=add(tree[x].val,tree[y].val);
        return z;
    }
    int mid=(l+r)/2;
    tree[z].l=Merge(tree[x].l,tree[y].l,l,mid);
    tree[z].r=Merge(tree[x].r,tree[y].r,mid+1,r);
    tree[z].val=better(tree[tree[z].l].val,
                       tree[tree[z].r].val);
    return z;
}
inline pair<int,int> query(int x,int l,int r,int L,int R) {
    if (!x) return make_pair(0,0);
    if (l<=L&&R<=r) return tree[x].val;
    int mid=(L+R)/2;
    pair<int,int> ret=make_pair(0,0);
    if (mid>=l)
        ret=better(ret,query(tree[x].l,l,r,L,mid));
    if (r>mid)
        ret=better(ret,query(tree[x].r,l,r,mid+1,R));
    return ret;
}
int father[21][maxn],pos[maxn];//倍增求father
inline int getfather(int l,int r) {
    int L=(r-l+1),ret=pos[r],i;
    rFOR(i,0,20) if (len[father[i][ret]]>=L)
        ret=father[i][ret];
    return ret;
}
int n,m,q;
int i,j,k;
char s[maxn];
int S[maxn],K[maxn];
int main() {
    scanf("%s",s);
    last=++CNT;
    n=strlen(s);
    REP(i,n) add(s[i]-'a'),pos[i+1]=last;
    add(26);
    scanf("%d",&m);
    FOR(k,1,m) {
        scanf("%s",s);
        n=strlen(s);
        REP(i,n) add(s[i]-'a'),insert(root[last],k,1,m);
        add(26);
    }
    FOR(i,1,CNT) S[len[i]]++;
    FOR(i,1,CNT) S[i]+=S[i-1];
    FOR(i,1,CNT) K[S[len[i]]--]=i;
    rFOR(i,1,CNT) {
        if (pre[K[i]]) root[pre[K[i]]]=
                Merge(root[pre[K[i]]],root[K[i]],1,m);
    }
    FOR(i,1,CNT) father[0][i]=pre[i];
    FOR(j,1,20) FOR(i,1,CNT)
    father[j][i]=father[j-1][father[j-1][i]];//倍增
    scanf("%d",&q);
    while (q--) {
        int l,r,pl,pr;
        scanf("%d%d%d%d",&l,&r,&pl,&pr);
        int x=getfather(pl,pr);
        pair<int,int> ans=query(root[x],l,r,1,m);
        if (ans.first==0) printf("%d 0\n",l);
        else printf("%d %d\n",ans.second,ans.first);
    }
}
