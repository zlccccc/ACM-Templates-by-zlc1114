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
const LL maxn=1000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct DLX{
    const static int maxn=1e5+7;
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
//        printf("link:%d %d\n",r,c);
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
        for (int i=D[c];i!=c;i=D[i])
            L[R[i]]=L[i],R[L[i]]=R[i];
    }
    void resume(int c){
        for (int i=U[c];i!=c;i=U[i])
            L[R[i]]=R[L[i]]=i;
    }
    bool v[maxd];
    int f(){
        int ret=0;
        for (int c=R[0];c;c=R[c]) v[c]=1;
        for (int c=R[0];c;c=R[c]) if (v[c]){
            ret++;v[c]=0;
            for (int i=D[c];i!=c;i=D[i])
                for (int j=R[i];j!=i;j=R[j])
                    v[col[j]]=0;
        }
        return ret;
    }
    int cnt;
    bool dance(int pos){
        if (pos+f()>cnt) return 0;
        if (R[0]==0) return pos<=cnt;
        int c=R[0];
        for (int i=R[0];i;i=R[i])
            if (S[i]<S[c]) c=i;
        for (int i=D[c];i!=c;i=D[i]){
            ans[pos]=row[i];
            remove(i);
            for (int j=R[i];j!=i;j=R[j]) remove(j);
            if (dance(pos+1)) return 1;
            for (int j=L[i];j!=i;j=L[j]) resume(j);
            resume(i);
        }return 0;
    }
}dlx;
int n,m;
LL X[maxn],Y[maxn];
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        int k,i,j;
        scanf("%d%d",&n,&k);
        FOR(i,1,n) scanf("%lld%lld",&X[i],&Y[i]);
        LL l=0,r=4e9+7;
        while (l<r){//0!
            LL mid=(l+r)/2;
            dlx.init(n,n);
            dlx.cnt=k;
            FOR(i,1,n)
                FOR(j,1,n)
                    if (abs(X[i]-X[j])+abs(Y[i]-Y[j])<=mid)
                        dlx.link(i,j);
            if (!dlx.dance(0)) l=mid+1;
            else r=mid;
//            printf("%lld : %d\n",mid,dlx.cnt);
        }
        static int x=0;
        printf("Case #%d: %lld\n",++x,l);
    }
}
/*
*/
