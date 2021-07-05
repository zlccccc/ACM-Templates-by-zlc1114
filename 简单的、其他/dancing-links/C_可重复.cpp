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
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M; return ret;}

//dlx:求解精确覆盖
//link的意思是,r覆盖了c
//暴力枚举,n个点覆盖m个格子; 注意一定要init
struct DLX {
    const static int maxn=1e5+7;
    const static int maxd=1e4+7;
    int n,m,size;
    int U[maxn],D[maxn],R[maxn],L[maxn],col[maxn],row[maxn];
    int H[maxd],S[maxd];//S:cnt
    int ans[maxn];
    void init(int _n,int _m) {
        n=_n; m=_m; int i;
        FOR(i,0,m) {
            S[i]=0;
            U[i]=D[i]=i;
            L[i]=i-1,R[i]=i+1;
        } R[m]=0; L[0]=m;
        size=m;
        FOR(i,0,n) H[i]=-1;
    }
    void link(int r,int c) {
        S[col[++size]=c]++; row[size]=r;
        D[size]=D[c]; U[D[c]]=size;
        D[c]=size; U[size]=c;
        if (H[r]<0) H[r]=L[size]=R[size]=size;
        else {
            R[size]=R[H[r]];
            L[R[H[r]]]=size;
            L[size]=H[r];
            R[H[r]]=size;
        }
    }
    void remove(int c) {
        for (int i=D[c]; i!=c; i=D[i])
            L[R[i]]=L[i],R[L[i]]=R[i];
    }
    void resume(int c) {
        for (int i=U[c]; i!=c; i=U[i])
            L[R[i]]=R[L[i]]=i;
    }
    bool v[maxd];
    //估价函数,函数返回的是至少还需要多少行才能完成重复覆盖
    //如果max的话可以直接cnt{R[]},也就是最多个数
    int f() {
        int ret=0;
        for (int c=R[0]; c; c=R[c]) v[c]=1;
        for (int c=R[0]; c; c=R[c]) {
            if (v[c]) {
                ret++; v[c]=0;
                for (int i=D[c]; i!=c; i=D[i])
                    for (int j=R[i]; j!=i; j=R[j])
                        v[col[j]]=0;
            }
        }
        return ret;
    }
    int cnt;
    void dance(int pos) {
        if (R[0]==0) {cnt=min(cnt,pos); return;}
        if (pos+f()>=cnt) return;
        int c=R[0];
        for (int i=R[0]; i; i=R[i])
            if (S[i]<S[c]) c=i;
        for (int i=D[c]; i!=c; i=D[i]) {
            ans[pos]=row[i];
            remove(i);
            for (int j=R[i]; j!=i; j=R[j]) remove(j);
            dance(pos+1);
            for (int j=L[i]; j!=i; j=L[j]) resume(j);
            resume(i);
        }
    }
} dlx;
int n,m;
int check(int x,int y,int a,int b,double d) {
    return (x-a)*(x-a)+(y-b)*(y-b)<d*d;
}
int x1[maxn],x2[maxn],y1[maxn],y2[maxn];
int main() {
    int T;
    scanf("%d",&T);
    while (T--) {
        int k,i;
        scanf("%d%d%d",&n,&m,&k);
        FOR(i,1,n) scanf("%d%d",&x1[i],&y1[i]);
        FOR(i,1,m) scanf("%d%d",&x2[i],&y2[i]);
        double l=0,r=1500;
        while (r-l>1e-7) {
            int i,j;
            double mid=(l+r)/2;
//            printf("%f %f %f\n",l,mid,r);
            dlx.init(m,n);
            FOR(i,1,n) FOR(j,1,m) {
                if (check(x1[i],y1[i],x2[j],y2[j],mid))
                    dlx.link(j,i);
            }
            dlx.cnt=k+1;
            dlx.dance(0);
            if (dlx.cnt>k) l=mid;
            else r=mid;
        } printf("%.6f\n",l);
    }
}
/*
*/
