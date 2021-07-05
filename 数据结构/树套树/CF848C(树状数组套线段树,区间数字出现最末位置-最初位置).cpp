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
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

const LL MAX=10000007;
struct node{
    int l,r;
    LL sum;
}T[MAX];
int cnt;
void Update(int &x,int pos,int val,int l,int r){
    if (!x) x=++cnt;
    T[x].sum+=val;
    if (l==r) return;
    int mid=(l+r)/2;
    if (mid>=pos) Update(T[x].l,pos,val,l,mid);
    else Update(T[x].r,pos,val,mid+1,r);
}
LL Query(int x,int l,int r,int L,int R){
    if (!x||(l<=L&&R<=r)) return T[x].sum;
    int mid=(L+R)/2;
    LL ret=0; 
    if (mid>=l) ret+=Query(T[x].l,l,r,L,mid);
    if (r>mid) ret+=Query(T[x].r,l,r,mid+1,R);
    return ret;
}
int n,m;
int root[maxn];
inline int lowbit(int x){
    return x&-x;
}
void update(int x,int pos,int val){
    for (;x<=n;x+=lowbit(x)) Update(root[x],pos,val,1,n);
}
LL query(int x,int l,int r){
    LL ret=0;
    for (;x;x-=lowbit(x))
        ret+=Query(root[x],l,r,1,n);//其实还是应该是r-(l-1)的 
    return ret;
}
int a[maxn];
set<int> S[maxn];
void ins(int pos,int val){//固定R (L用前缀和)
    S[val].insert(pos);
    set<int>::iterator it=S[val].lower_bound(pos),itt=it;itt++;
    int pre=0,suf=0;
    if (it!=S[val].begin()) it--,pre=*it;
    if (itt!=S[val].end()) suf=*itt;
    if (pre) update(pos,pre,pos-pre);
    if (suf) update(suf,pos,suf-pos);
    if (pre&&suf) update(suf,pre,pre-suf);
}
void del(int pos,int val){
    set<int>::iterator it=S[val].lower_bound(pos),itt=it;itt++;
    int pre=0,suf=0;
    if (it!=S[val].begin()) it--,pre=*it;
    if (itt!=S[val].end()) suf=*itt;
    if (pre) update(pos,pre,-(pos-pre));
    if (suf) update(suf,pos,-(suf-pos));
    if (pre&&suf) update(suf,pre,-(pre-suf));
    S[val].erase(pos);
}
int i;
int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n){
        scanf("%d",&a[i]);
        ins(i,a[i]);
    }
    REP(i,m){
        int k;
        scanf("%d",&k);
        if (k==1){
            int p,x;
            scanf("%d%d",&p,&x);
            del(p,a[p]);
            a[p]=x;
            ins(p,a[p]);
        }else if (k==2){
            int l,r;
            scanf("%d%d",&l,&r);
            printf("%I64d\n",query(r,l,r));
        }
    }
}
/*
*/
