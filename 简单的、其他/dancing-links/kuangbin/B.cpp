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
const LL maxn=2e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct DLX{
    const static int maxn=1e6+7;
    const static int maxd=1e4+7;
    int n,m,size;
    int U[maxn],D[maxn],R[maxn],L[maxn],col[maxn],row[maxn];
    int H[maxd],S[maxd];//S:cnt
    int ans[maxn];
    void init(int _n,int _m){
        n=_n;m=_m;int i;
        FOR(i,0,m) {
            S[i]=0;
            U[i]=D[i]=i;
            L[i]=i-1,R[i]=i+1;
        }R[m]=0;L[0]=m;
        size=m;
        FOR(i,0,n) H[i]=-1;
    }
    void link(int r,int c){
        S[col[++size]=c]++;row[size]=r;
        D[size]=D[c];U[D[c]]=size;
        D[c]=size;U[size]=c;
        if (H[r]<0) H[r]=L[size]=R[size]=size;
        else{
            R[size]=R[H[r]];
            L[R[H[r]]]=size;
            L[size]=H[r];
            R[H[r]]=size;
        }
    }
    void remove(int c){
        L[R[c]]=L[c];R[L[c]]=R[c];
        for (int i=D[c];i!=c;i=D[i])
            for (int j=R[i];j!=i;j=R[j])
                U[D[j]]=U[j],D[U[j]]=D[j],S[col[j]]--;
    }
    void resume(int c){
        for (int i=U[c];i!=c;i=U[i])
            for (int j=L[i];j!=i;j=L[j])
                U[D[j]]=D[U[j]]=j,S[col[j]]++;
        L[R[c]]=R[L[c]]=c;
    }
    int cnt;
    void dance(int pos){
        if (pos>=cnt&&cnt!=INF) return;
        if (R[0]==0) {cnt=min(cnt,pos);return;}
        int c=R[0];
        for (int i=R[0];i;i=R[i])
            if (S[i]<S[c]) c=i;
        remove(c);
        for (int i=D[c];i!=c;i=D[i]){
            ans[pos]=row[i];
            for (int j=R[i];j!=i;j=R[j]) remove(col[j]);
            dance(pos+1);
            for (int j=L[i];j!=i;j=L[j]) resume(col[j]);
        }resume(c);
    }
}dlx;
int n,m;
inline int getid(int x,int y){
    return (x-1)*m+y;
}
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        int k,i,j;
        scanf("%d%d%d",&n,&m,&k);
        dlx.init(k,getid(n,m));
//        FOR(i,1,n) FOR(j,1,m) printf("%d ",getid(i,j));puts("");
        FOR(i,1,k){
            int x1,y1,x2,y2,x,y;
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            x1++;y1++;
            FOR(x,x1,x2)
                FOR(y,y1,y2)
                    dlx.link(i,getid(x,y));
        }dlx.cnt=INF;
        dlx.dance(0);
        int ans=dlx.cnt;
        if (ans==INF) puts("-1");
        else printf("%d\n",ans);
    }
}
/*
*/
