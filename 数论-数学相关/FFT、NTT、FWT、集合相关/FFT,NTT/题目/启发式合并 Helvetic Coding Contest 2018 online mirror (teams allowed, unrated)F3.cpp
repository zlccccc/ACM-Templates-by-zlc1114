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
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=2e5+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

struct complex{
    double a,b;
    complex(double _a=.0,double _b=.0):a(_a),b(_b){}
    complex operator+(const complex &x)const{return complex(a+x.a,b+x.b);}
    complex operator-(const complex &x)const{return complex(a-x.a,b-x.b);}
    complex operator*(const complex &x)const{return complex(a*x.a-b*x.b,a*x.b+b*x.a);}
};
void fft(complex *A,int len,int inv){
    int i,j,k;
    for (i=1,j=len/2;i<len-1;i++){
        if (i<j) swap(A[i],A[j]);
        k=len/2;
        while (j>=k){
            j-=k;k/=2;
        }if (j<k) j+=k;
    }
    for (i=2;i<=len;i<<=1){
        complex wn(cos(-inv*2*pi/i),sin(-inv*2*pi/i));
        for (j=0;j<len;j+=i){
            complex w(1.0,0.0);
            for (k=j;k<(j+i/2);k++){
                complex a=A[k],b=w*A[k+i/2];
                A[k]=a+b;
                A[k+i/2]=a-b;
                w=w*wn;
            }
        }
    }
    if (inv==-1) REP(i,len) A[i].a/=len;
}
complex X[1<<20|7],Y[1<<20|7];
void multi(vector<int> &A,vector<int> &B){
    int len=1,n=A.size(),m=B.size(),i;
    while (len<n+m) len<<=1;
    REP(i,n) X[i]=complex(A[i],0);
    rep(i,n,len) X[i]=complex();
    REP(i,m) Y[i]=complex(B[i],0);
    rep(i,m,len) Y[i]=complex();
    fft(X,len,1);fft(Y,len,1);
    REP(i,len) X[i]=X[i]*Y[i];
    fft(X,len,-1);
    A.resize(n+m-1);
    vector<int>().swap(B);
    REP(i,n+m-1) A[i]=(LL)(X[i].a+0.5)%1009;
}
struct node{
    int pos,length;
    node(int _p,int _l):pos(_p),length(_l){}
    bool operator < (const node &A)const{
        if (length!=A.length) return length>A.length;
        return pos<A.pos;
    }
};
int n,m,k;
vector<int> value[maxn];//resize_max:k
priority_queue<node> Q;
int main() {
    int i,t;
    scanf("%d%d%d",&n,&m,&k);
    REP(i,n) scanf("%d",&t),value[t].push_back(1);
    FOR(i,1,n) if (value[i].size()){
        value[i].push_back(1);
        Q.push(node(i,value[i].size()));
    }
    while (Q.size()>1){
        node A=Q.top();Q.pop();
        node B=Q.top();Q.pop();
//        for (auto now:value[A.pos]) printf("%-3d",now);puts("");
//        for (auto now:value[B.pos]) printf("%-3d",now);puts("");
        multi(value[A.pos],value[B.pos]);
//        for (auto now:value[A.pos]) printf("%-3d",now);puts(" <- ans");
        Q.push(node(A.pos,value[A.pos].size()));
    }node A=Q.top();Q.pop();
    printf("%d",value[A.pos][k]);
    return 0;
}
/*
3 3 2
1 2 3

*/
