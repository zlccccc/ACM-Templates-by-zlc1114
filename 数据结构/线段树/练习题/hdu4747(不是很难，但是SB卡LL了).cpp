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
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3f;
const LL M=1e9+7;
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a) {return a>0?a:-a;}

int a[maxn];
LL sum[maxn<<2],lazy[maxn<<2],len[maxn<<2],mx[maxn<<2],mn[maxn<<2];
int lef[maxn<<2],rig[maxn<<2];
void change(int x,LL val){
    sum[x]=len[x]*val;
    mx[x]=mn[x]=val;
    lazy[x]=val;
}
void pushdown(int x){
    if (lazy[x]!=-1){
        change(x<<1,lazy[x]);
        change(x<<1|1,lazy[x]);
        lazy[x]=-1;
    }
}
void pushup(int x){
    sum[x]=sum[x<<1]+sum[x<<1|1];
    len[x]=len[x<<1]+len[x<<1|1];
    mx[x]=max(mx[x<<1],mx[x<<1|1]);
    mn[x]=min(mn[x<<1],mn[x<<1|1]);
}
void build(int x,int l,int r){
    lef[x]=l;rig[x]=r;
    sum[x]=len[x]=0;lazy[x]=-1;
    if (l==r){
        sum[x]=mx[x]=mn[x]=a[l];
        len[x]=1;
        return;
    }
    int mid=(l+r)/2;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
    pushup(x);
}
void update(int x,int l,int r,int L,int R,LL val){
    if (mx[x]<val) return;
    if (l<=L&&R<=r&&mn[x]>=val){
        change(x,val);
        return;
    }
    if (L==R) return;
    pushdown(x);
    int mid=(L+R)/2;
    if (mid>=l) update(x<<1,l,r,L,mid,val);
    if (r>mid) update(x<<1|1,l,r,mid+1,R,val);
    pushup(x);
}
LL query(int x,int l,int r,int L,int R){
    if (l<=L&&R<=r) return sum[x];
    pushdown(x);
    int mid=(L+R)/2;
	LL ret=0;
    if (mid>=l) ret+=query(x<<1,l,r,L,mid);
    if (r>mid) ret+=query(x<<1|1,l,r,mid+1,R);
    pushup(x);
    return ret;
}
int n;
int i,j;
int num[maxn],b[maxn],now;
LL ans;
vector<int> pos[maxn];
int main()
{
    while (~scanf("%d",&n)&&n){
        FOR(i,0,n) pos[i].clear(),a[i]=num[i]=0;
        now=0;
        FOR(i,1,n){
            scanf("%d",&b[i]);
            j=b[i];
            if (j<=n) pos[j].push_back(i);
            while (pos[now].size()) now++;
            a[i]=now;
        }
        FOR(i,0,now) pos[i].push_back(n+1);
        FOR(i,1,n) printf("%d ",a[i]);
        puts("");
        build(1,1,n);
        ans=0;
        FOR(i,1,n){
            ans+=query(1,i,n,1,n);
//            printf("%lld    %d %d\n",query(1,i,n,1,n),i,n);
//            printf("lef:  ");FOR(j,1,20) printf("%3d",lef[j]);puts("");
//            printf("rig:  ");FOR(j,1,20) printf("%3d",rig[j]);puts("");
//            printf("lazy: ");FOR(j,1,20) printf("%3d",lazy[j]);puts("");
//            printf("sum:  ");FOR(j,1,20) printf("%3d",sum[j]);puts("");
//            printf("max:  ");FOR(j,1,20) printf("%3d",mx[j]);puts("");
//            printf("min:  ");FOR(j,1,20) printf("%3d",mn[j]);puts("");
//            printf("len:  ");FOR(j,1,20) printf("%3d",len[j]);puts("");
            j=b[i];
            if (j<=n){
                update(1,pos[j][num[j]],pos[j][num[j]+1]-1,1,n,j);
//                printf("j=%d %d->pos[j][num[j]+1]=%d\n",j,pos[j][num[j]],pos[j][num[j]+1]-1);
                num[j]++;
            }
        }
        printf("%lld\n",ans);
    }
}
/*
3
0 1 3
  0 0
    0
5
1 0 2 0 1
0

0 2 3 3 3
  1 1 1 3
    0 1 3
      1 2
        0
*/
