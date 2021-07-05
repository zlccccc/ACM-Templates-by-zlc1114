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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

//change常数大时size可以增大
//sort时先block,改变顺序可以降低常数
//n^2/3,注意常数
//注意change时间时排的顺序
const int SIZE=2500;
struct queries{
    int l,r,t;//pre
    queries(){};
    queries(int _l,int _r,int _t):l(_l),r(_r),t(_t){};
}Q[maxn],S[maxn];
int n,m,q;
int i,j,k;
int a[maxn];
int BLOCK[maxn];
bool cmp(queries &A,queries &B){
    if (BLOCK[A.l]!=BLOCK[B.l]) return BLOCK[A.l]<BLOCK[B.l];
    if (BLOCK[A.r]!=BLOCK[B.r]) return BLOCK[A.r]<BLOCK[B.r];
    return (A.t<B.t)^((BLOCK[A.l]^BLOCK[A.r])&1);
}vector<int> V;
inline int getid(int x){return lower_bound(V.begin(),V.end(),x)-V.begin()+1;}
int L,R,T;
int num[maxn],cnt[maxn];
inline void add(int pos){
    int &T=num[a[pos]];
    cnt[T]--;T++;cnt[T]++;
}inline void del(int pos){
    int &T=num[a[pos]];
    cnt[T]--;T--;cnt[T]++;
}inline void change(int pos,int val){
    if (L<=pos&&pos<=R){del(pos),a[pos]=val,add(pos);}
    else a[pos]=val;
}
int ans[maxn];
int main(){
    scanf("%d%d",&n,&q);
    FOR(i,1,n) scanf("%d",&a[i]),V.push_back(a[i]);
    FOR(i,1,q){
        int op,l,r;
        scanf("%d%d%d",&op,&l,&r);
        if (op==1){
            Q[i]=queries(l,r,i);
        }if (op==2) {
            S[i]=queries(l,r,a[l]);a[l]=r;
            V.push_back(a[l]);
        }
    }sort(V.begin(),V.end());
    V.erase(unique(V.begin(),V.end()),V.end());
    FOR(i,1,n) a[i]=getid(a[i]);
    FOR(i,1,q) if (S[i].t) S[i].r=getid(S[i].r),S[i].t=getid(S[i].t);
    FOR(i,1,max(n,q)) BLOCK[i]=i/SIZE;
    sort(Q+1,Q+q+1,cmp);
    L=1;R=0;T=q;cnt[0]=INF;
    FOR(i,1,q) if (Q[i].t){
        while (T<Q[i].t){T++;if (S[T].t) change(S[T].l,S[T].r);}
        while (T>Q[i].t){if (S[T].t) change(S[T].l,S[T].t);T--;}
        while (L<Q[i].l){del(L);L++;}
        while (R>Q[i].r){del(R);R--;}
        while (L>Q[i].l){L--;add(L);}
        while (R<Q[i].r){R++;add(R);}
        int now=0;
        while (cnt[now]) now++;
        ans[Q[i].t]=now;
    }FOR(i,1,q) if (ans[i]) printf("%d\n",ans[i]);
}
/*
*/
