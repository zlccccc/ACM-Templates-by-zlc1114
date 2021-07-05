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
#include <iomanip>
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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct node{
    int pos,type;//mouse|hole
    node(){}
    node(int _pos,int _type):pos(_pos),type(_type){}
}a[maxn*2],A[maxn*3];
bool cmp(node A,node B){
    return A.pos<B.pos;
}int n,m;
int i,j,k;
int K[maxn*2],S[maxn],top,cnt;//bigger
int N;
const int MID=maxn*2;
LL F[maxn*4],L,R;int now;//F[i][j]:previous_chosen mouse-hole
int main(){
    scanf("%d%d",&n,&m);
    REP(i,n) scanf("%d",&a[i].pos),a[i].type=0;
    REP(i,m) scanf("%d%d",&a[i+n].pos,&a[i+n].type);
    sort(a,a+n+m,cmp);
    REP(i,n+m){
        if (a[i].type!=K[i]) S[++top]=i; else cnt++;
        while (top&&cnt) {cnt--;int T=S[top];K[T]++;if (K[T]==a[T].type) top--;}
    }top=0;cnt=0;
    rREP(i,n+m){
        if (a[i].type!=K[i]) S[++top]=i; else cnt++;
        while (top&&cnt) {cnt--;int T=S[top];K[T]++;if (K[T]==a[T].type) top--;}
    }top=0;
    REP(i,n+m) {
        if (!a[i].type) A[N++]=a[i];
        else REP(j,K[i]) A[N++]=node(a[i].pos,1);
    }if (N<n+n) return 0*puts("-1");
    now=MID;
    FOR(i,MID-(N-n),MID+(N-n)) F[i]=INFF;F[MID]=0;
    REP(i,N){
        if (!A[i].type){//mouse
            F[now]-=R;now--;F[now]+=L;
            F[now]+=A[i].pos;
            L+=A[i].pos;R-=A[i].pos;
        }else{//hole
            F[now]-=L;now++;F[now]+=R;
            F[now]=min(F[now]+A[i].pos,F[now-1]+L);
            L-=A[i].pos;R+=A[i].pos;
        }
    }printf("%lld\n",F[now]);
}
/*
*/
