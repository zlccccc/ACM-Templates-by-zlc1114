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
const LL maxn=4e5+7;
const double eps=0.00000001;
const double pi=acos(-1);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}
//or/and的理解:这里的变换是利用dp时分治来压位(写成非递归形式)实现的，时间nlogn
//进行组合可以将二元运算的东西都组合出来 
//实际上or都没用 
//从底向上merge也可以直接使用(底层已经solve完成,merge单层)
void fwt(LL *A,int len,int inv)//对拍对了 
{
    int i,j,k;
    int div=powMM(2ll,M-2);
    for(i=2;i<=len;i<<=1){
        for(j=0;j<len;j+=i){
            for(k=j;k<j+i/2;k++){
                if (inv==1){
                    LL a=A[k],b=A[k+i/2];
                    A[k]=(a+b)%M;
                    A[k+i/2]=(a-b+M)%M;
                //xor:a[k]=x+y,a[k+i/2]=(x-y+mod)%mod;
                //and:a[k]=x+y;
                //or:a[k+i/2]=x+y;
                }else{
                    LL a=A[k],b=A[k+i/2];
                    A[k]=(a+b)*div%M;
                    A[k+i/2]=(a-b+M)%M*div%M;
                //xor:a[k]=(x+y)/2,a[k+i/2]=(x-y)/2;
                //and:a[k]=x-y;
                //or:a[k+i/2]=y-x;
                }
            }
        }
    }
}
LL a[maxn],b[maxn];
int ans[maxn];
int main(){
    int T,n;
    int i,j,k;
    while (~scanf("%d",&n)){
        int len=1;
        while(len<=200000) len<<=1;
        REP(i,len) a[i]=b[i]=0;
        REP(i,n) scanf("%d",&k),a[k]++;
        REP(i,n) scanf("%d",&k),b[k]++;
        fwt(a,len,1);fwt(b,len,1);
        REP(i,len) a[i]=a[i]*b[i]%M;
        fwt(a,len,-1);
        REP(i,len) while (a[i]--) printf("%d ",i);
        puts("");
    }
}
/*
5
1 2 3 4 5
*/
