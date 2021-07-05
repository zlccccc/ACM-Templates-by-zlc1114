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
const LL maxn=2e5+7;
const double eps=0.00000001;
const double pi=acos(-1);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct complex{
    double a,b;
    complex(double _a=.0,double _b=.0):a(_a),b(_b){}
    complex operator+(const complex x)const{return complex(a+x.a,b+x.b);}
    complex operator-(const complex x)const{return complex(a-x.a,b-x.b);}
    complex operator*(const complex x)const{return complex(a*x.a-b*x.b,a*x.b+b*x.a);}
};
void fft(complex *A,int len,int inv){//³­µÄ°å×Ó 
    int i,j,k;
    for (i=1,j=len/2;i<len-1;i++){
        if (i<j) swap(A[i],A[j]);
        k=len/2;
        while(j>=k){
            j-=k;
            k/=2;
        }if (j<k) j+=k;
    }
    for(i=2;i<=len;i<<=1){
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
complex x1[maxn],x2[maxn];
char a[maxn],b[maxn];
int ans[maxn];
int main(){
    int T;
    int i,j,k;
//  printf("%lf\n",pi);
    scanf("%d",&T);
    while (T--){
        scanf("%s%s",a,b);
        bool mark=0;;
        int len1=strlen(a),len2=strlen(b),len=1;
        if (a[0]=='-') {REP(i,len1) a[i]=a[i+1];len1--;mark^=1;}
        if (b[0]=='-') {REP(i,len2) b[i]=b[i+1];len2--;mark^=1;}
        while(len<=len1+len2+1) len<<=1;
        REP(i,len1) x1[i]=complex(a[len1-i-1]-'0',0);
        rep(i,len1,len) x1[i]=complex(0,0);
        REP(i,len2) x2[i]=complex(b[len2-i-1]-'0',0);
        rep(i,len2,len) x2[i]=complex(0,0);
        fft(x1,len,1);fft(x2,len,1);
//      REP(i,len) printf("%lf %lf\n",x1[i].a,x1[i].b);
//      REP(i,len) printf("%lf %lf\n",x2[i].a,x2[i].b);
        REP(i,len) x1[i]=x1[i]*x2[i];
        fft(x1,len,-1);
        REP(i,len) ans[i]=x1[i].a+0.5;
        REP(i,len) ans[i+1]+=ans[i]/10,ans[i]%=10;
        while (ans[len-1]<=0&&len-1>0) len--;
        if (mark) putchar('-');
        rREP(i,len) putchar(ans[i]+'0');
        puts("");
    }
}
/*
*/
