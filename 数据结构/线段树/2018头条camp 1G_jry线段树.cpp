#include<bits/stdc++.h>
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define REP(I,N) for (I=0;I<N;I++)
using namespace std;
typedef long long ll;
const int INF=0x3f3f3f3f;
const int mod=1e9+9;
const int maxn=1e5+7;

// 区间取max min, 维护其他值
// 直接维护max,min,第二小即可, 暴力改就行了, 一个log
struct node{
    int MIN,MINCNT,IMIN;
    ll SUM;
    node(){MIN=MINCNT=SUM=0; IMIN=INF;}
}T[maxn*4];
void min_(int &A,int B){(A>B)&&(A=B);}
char op[2]; ll ans;
void build(int x,int l,int r){
    T[x]=node(); T[x].MINCNT=r-l+1;
    if (l==r) return;
    int mid=(l+r)/2;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
}
inline void update(int x,int l,int r,int val,int L,int R,int tag=1) {
//    printf("%d : %d %d %d l-r=%d %d; inisum=%d\n",x,l,r,val,L,R,T[x].SUM);
    if (l<=L&&R<=r){
        if (T[x].IMIN>val){
            if (T[x].MIN<val) {
                T[x].SUM+=(ll)(val-T[x].MIN)*T[x].MINCNT;
                T[x].MIN=val;
            } if (tag) ans+=T[x].SUM;
            return;
        }
    } int mid=(L+R)/2;
    update(x<<1,L,mid,T[x].MIN,L,mid,0);
    update(x<<1|1,mid+1,R,T[x].MIN,mid+1,R,0);
    if (l<=mid) update(x<<1,l,r,val,L,mid);
    if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
    T[x].SUM=T[x<<1].SUM+T[x<<1|1].SUM;
    T[x].MIN=T[x].IMIN=INF;
    T[x].MIN=min(T[x<<1].MIN,T[x<<1|1].MIN);
    T[x].MINCNT=0;

    if (T[x<<1].MIN==T[x].MIN) {
        min_(T[x].IMIN,T[x<<1].IMIN);
        T[x].MINCNT+=T[x<<1].MINCNT;
    } else min_(T[x].IMIN,T[x<<1].MIN);
    if (T[x<<1|1].MIN==T[x].MIN) {
        min_(T[x].IMIN,T[x<<1|1].IMIN);
        T[x].MINCNT+=T[x<<1|1].MINCNT;
    } else min_(T[x].IMIN,T[x<<1|1].MIN);
}
inline ll gcd(ll a,ll b){return !b?a:gcd(b,a%b);}
int main() {
    int _=0,n,m,i;
    while (~scanf("%d%d",&n,&m)) {
        if (!n&&!m) break;
        build(1,1,n);
        FOR(i,1,m) {
            scanf("%s",op);
            int l,r; scanf("%d%d",&l,&r);
            if (op[0]=='^') {
                int x; scanf("%d",&x);
                update(1,l,r,x,1,n);
            } else {
                ans=0;
                update(1,l,r,0,1,n);
                ll g=gcd(r-l+1,ans);
                if (ans==0) puts("0");
                else if (r-l+1==g) printf("%lld\n",ans/g);
                else printf("%lld/%lld\n",ans/g,(r-l+1)/g);
            }
        }
    }
    return 0;
}