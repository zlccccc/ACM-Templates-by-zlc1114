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
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}

struct Tnode {
    int left,right,val;
} T[maxn*80];
int cnt=0;
void build(int &x,int l,int r) {
    if (!x) x=++cnt;
    if (l==r) {T[x].val=l; return;}
    int mid=(l+r)/2;
    build(T[x].left,l,mid);
    build(T[x].right,mid+1,r);
}
void update(int &x,int y,int pos,int val,int l,int r) {
    T[++cnt]=T[y]; x=cnt;
    if (l==r) {T[x].val=val; return;}
    int mid=(l+r)/2;
    if (mid>=pos) update(T[x].left,T[y].left,pos,val,l,mid);
    else update(T[x].right,T[y].right,pos,val,mid+1,r);
}
int query(int x,int pos,int l,int r) {
    if (l==r) return T[x].val;
    int mid=(l+r)/2;
    if (mid>=pos) return query(T[x].left,pos,l,mid);
    else return query(T[x].right,pos,mid+1,r);
}
int root[maxn];
int n,m;
int i,j,k,t;
int a,b,ans;
inline int getfather(int x) {
    int t=query(root[i],x,1,n);
    if (t==x) return x;
    int fa=getfather(t);
    update(root[i],root[i],x,fa,1,n);
    return fa;
}
int main() {
    scanf("%d%d",&n,&m);
    build(root[0],1,n);
    FOR(i,1,m) {
        scanf("%d",&k);
        root[i]=root[i-1];
        if (k==1) {
            scanf("%d%d",&a,&b);
            a^=ans; b^=ans;
            int x=getfather(a),y=getfather(b);
            if (x==y) continue;
            update(root[i],root[i],x,y,1,n);
        } else if (k==2) {
            scanf("%d",&t);
            t^=ans;
            root[i]=root[t];
        } else {
            scanf("%d%d",&a,&b);
            int x=getfather(a),y=getfather(b);
            a^=ans; b^=ans;
            if (x==y) puts("1"),ans=1;
            else puts("0"),ans=0;
        }
    }
    return 0;
}
/*
*/
