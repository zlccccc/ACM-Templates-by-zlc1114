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
const LL maxn=5e4+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n;
inline int lowbit(int x){return x&-x;}
int all[maxn];
void add(int x,int val){
    for (;x<=n;x+=lowbit(x)) all[x]+=val;
}int sum(int x){
    int ret=0;
    for (;x;x-=lowbit(x)) ret+=all[x];
    return ret;
}int sum(int l,int r){
    return sum(r)-sum(l-1);
}
struct node{
    int x,y,k,id;//id = 0 : add (abs(y) == 1)
}p[maxn*3],q[maxn*3];
int ans[maxn];
void solve(int l,int r,int L,int R){//time
    if (l>r) return;
    int i;
    if (L==R){
        FOR(i,l,r) ans[p[i].id]=L;
        return;
    }int x=l,xq=0,mid=(L+R)/2;
    FOR(i,l,r){
        if (p[i].id==0){
            if (p[i].k<=mid){
                add(p[i].x,p[i].y);
                p[x++]=p[i];
            }else q[xq++]=p[i];
        }else{
            int k=sum(p[i].x,p[i].y);
            if (k<p[i].k){
                p[i].k-=k;
                q[xq++]=p[i];
            }else p[x++]=p[i];
        }
    }REP(i,xq) p[x+i]=q[i];
    rep(i,l,x) if (p[i].id==0) add(p[i].x,-p[i].y);
    solve(l,x-1,L,mid);
    solve(x,r,mid+1,R);
}
char K[maxn],Q[20];
int a[maxn];
int m;
void solve(){
    scanf("%d%d",&n,&m);
    int i,tot=0;
    FOR(i,1,n){
        scanf("%d",&a[i]);
        p[++tot]={i,1,a[i],0};
    }FOR(i,1,m){
        scanf("%s",Q);
        K[i]=Q[0];
        if (K[i]=='Q'){
            int l,r,k;
            scanf("%d%d%d",&l,&r,&k);
            p[++tot]={l,r,k,i};
        }if (K[i]=='C'){
            int pos,t;
            scanf("%d%d",&pos,&t);
            p[++tot]={pos,-1,a[pos],0};
            p[++tot]={pos,1,t,0};
            a[pos]=t;
        }
    }solve(1,tot,0,1000000000);
    FOR(i,1,m) if (K[i]=='Q') printf("%d\n",ans[i]);//l,r,pos
}
int main(){
    int T_T;
    scanf("%d",&T_T);
    while (T_T--) solve();
}
/*
*/
