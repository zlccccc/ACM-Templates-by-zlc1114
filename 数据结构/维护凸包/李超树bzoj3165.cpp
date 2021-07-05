#include <sstream>
#include <fstream>
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
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG1
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef long long LL;
typedef long long ll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

//李超树最主要的作用在于维护线段,而不是直线!
//维护l<=x<=r时下放线段,时间复杂度两个log!
//这里是最大值
double cross(double k1,double b1,double k2,double b2) {
    if (abs(k1-k2)<eps) return INF;
    return (b2-b1)/(k1-k2);
}
int flag[maxn*4];
double tagk[maxn*4],tagb[maxn*4];
void ins(int x,double k,double b,int l,int r,int id,int L,int R) {
    if (l<=L&&R<=r) {
        if (!flag[x]) tagk[x]=k,tagb[x]=b,flag[x]=id;
        else {
            int mid=(L+R)/2;
            double ini_l=tagk[x]*L+tagb[x],now_l=k*L+b;
            double ini_r=tagk[x]*R+tagb[x],now_r=k*R+b;
            if (ini_l>=now_l&&ini_r>=now_r) return;
            if (ini_l<=now_l&&ini_r<=now_r) tagk[x]=k,tagb[x]=b,flag[x]=id;
            else {
                double pos=cross(k,b,tagk[x],tagb[x]);//交点x坐标
                if ((pos<=mid&&ini_l>=now_l)||(pos>mid&&ini_r>=now_r)) { //坐标低的下放,平的直接留下就行
                    swap(tagk[x],k);
                    swap(tagb[x],b);
                    swap(flag[x],id);
                } if (pos<=mid) ins(x<<1,k,b,l,r,id,L,mid);
                else ins(x<<1|1,k,b,l,r,id,mid+1,R);
            }
        }
    } else {
        int mid=(L+R)/2;
        if (l<=mid) ins(x<<1,k,b,l,r,id,L,mid);
        if (mid<r) ins(x<<1|1,k,b,l,r,id,mid+1,R);
    }
}
double ans; int id;
void que(int x,int pos,int L,int R) {
    if (flag[x]) {
        double now=tagk[x]*pos+tagb[x];
        if (now-ans>eps||(now-ans>-eps&&id>flag[x])) {
            ans=now,id=flag[x];
        }
    }
    if (L==R) return;
    int mid=(L+R)/2;
    if (pos<=mid) que(x<<1,pos,L,mid);
    else que(x<<1|1,pos,mid+1,R);
}
char A[20];
int main() {
    int n=40000,q,i=0;
    scanf("%d",&q);
    while (q--) {
        int op;
        scanf("%d",&op);
        if (op==0) {
            int x;
            scanf("%d",&x);
            x=(x+id-1)%39989+1;
            ans=0; id=0; que(1,x,1,n);
            // printf("query: %d %f %d\n",x,ans,id);
            printf("%d\n",id);
        } else {
            int x0,x1,y0,y1;
            scanf("%d%d%d%d",&x0,&y0,&x1,&y1);
            x0=(x0+id-1)%39989+1;
            y0=(y0+id-1)%1000000000+1;
            x1=(x1+id-1)%39989+1;
            y1=(y1+id-1)%1000000000+1;
            if (x1<x0) swap(x1,x0),swap(y1,y0);
            double k,b;
            if (x0!=x1) k=(double)(y1-y0)/(x1-x0),b=-x0*k+y0;
            else k=0,b=max(y0,y1);
            // printf("%d - %d : %d %d   %f %f\n",x0,x1,y0,y1,k,b);
            ins(1,k,b,x0,x1,++i,1,n);
        }
    }
}
/*
*/
