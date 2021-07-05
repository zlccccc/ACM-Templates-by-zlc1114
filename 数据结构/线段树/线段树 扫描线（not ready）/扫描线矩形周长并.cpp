#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const int eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a) {return a>0?a:-a;}

int size;
int len[maxn*2];
int n,m;
int i,j,k;
struct Seg {
    struct node {
        int left,right;
        int len,num;
        bool cl,cr;//iff
        int lazy;
        void update(int x) {
            lazy+=x;
        }
    } tree[maxn*4];
    void pushup(int x) {
        if (tree[x].lazy) {
            tree[x].len=len[tree[x].right+1]-len[tree[x].left];
            tree[x].cl=tree[x].cr=1; tree[x].num=2;
        } else if (tree[x].left==tree[x].right) {
            tree[x].len=0;
            tree[x].cl=tree[x].cr=0; tree[x].num=0;
        } else {
            tree[x].len=tree[x<<1].len+tree[x<<1|1].len;
            tree[x].num=tree[x<<1].num+tree[x<<1|1].num;
            if (tree[x<<1].cr&&tree[x<<1|1].cl) tree[x].num-=2;
            tree[x].cl=tree[x<<1].cl;
            tree[x].cr=tree[x<<1|1].cr;
        }
    };
    void build(int x,int l,int r) {
        tree[x].left=l; tree[x].right=r;
        tree[x].len=tree[x].lazy=0;
        if (l==r) {
        } else {
            int mid=(l+r)/2;
            build(x<<1,l,mid);
            build(x<<1|1,mid+1,r);
            pushup(x);
        }
    }
    void update(int x,int l,int r,LL val) {
        int L=tree[x].left,R=tree[x].right;
        if (l<=L&&R<=r) {
            tree[x].update(val);
            pushup(x);
        } else {
            int mid=(L+R)/2;
            if (mid>=l) update(x<<1,l,r,val);
            if (r>mid) update(x<<1|1,l,r,val);
            pushup(x);
        }
    }
    int query(int x,int l,int r) { //num
        int L=tree[x].left,R=tree[x].right;
        if (l<=L&&R<=r) {
            return tree[x].len;
        } else {
            int mid=(L+R)/2;
            int ans;
            if (mid>=l) ans+=query(x<<1,l,r);
            if (r>mid) ans+=query(x<<1|1,l,r);
            pushup(x);
            return ans;
        }
    }
} T;
struct point {
    int x1,x2,h;
    int n;
    bool operator <(const point &a)const {
        if (h!=a.h) return h<a.h;
        return n>a.n;
    }
} a[maxn];
map<int,int> Hash;
int x1,x2,y1,y2;
int ans;
int len1,len2,num;
int main() {
    while (~scanf("%d",&n)) {
        if (n==0) break;
        FOR(i,1,n) {
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            len[i*2-1]=x1; len[i*2]=x2;
            a[i*2-1].x1=x1; a[i*2-1].x2=x2;
            a[i*2-1].n=1;  a[i*2-1].h=y1;
            a[i*2].x1=x1; a[i*2].x2=x2;
            a[i*2].n=-1; a[i*2].h=y2;
        }
        sort(a+1,a+n*2+1);
        sort(len+1,len+n*2+1);
        Hash.clear();
        FOR(i,1,2*n) Hash[len[i]]=i;
        T.build(1,1,n*2);
        ans=0;
        FOR(i,1,2*n) {
            len1=T.tree[1].len; num=T.tree[1].num;
            T.update(1,Hash[a[i].x1],Hash[a[i].x2]-1,a[i].n);
            len2=T.tree[1].len;
            ans+=abs(len2-len1);
            ans+=num*(a[i].h-a[i-1].h);
        }
        printf("%d\n",ans);
    }
}
/*
*/
