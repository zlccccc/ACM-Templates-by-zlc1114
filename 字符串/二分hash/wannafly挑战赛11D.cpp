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
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

// 题意:求上下拼接后的最长回文串长度(很坑)
struct hashset{
    const static int seed=1e7+7;
    const static int maxn=2e6+7;
    struct node{
        int x,y;int next;
        node(){};
        node(int _x,int _y,int n):x(_x),y(_y),next(n){};
    }T[maxn];//更好地空间局部性?(雾)
    int head[seed],size;
    void clear(){
        memset(head,-1,sizeof(head));
        size=0;
    }
    void insert(int x,int y){
        int& h=head[x%seed];
        for (int i=h;~i;i=T[i].next)
            if (T[i].x==x&&T[i].y==y) return;
        T[size]=node(x,y,h);h=size++;
    }
    bool count(int x,int y){
        for (int i=head[x%seed];~i;i=T[i].next)
            if (T[i].x==x&&T[i].y==y) return 1;
        return 0;
    }
}have;
struct hash{
    int px[maxn],val[maxn],p;
    void setp(int P,int n=200000){
        int i;px[0]=1;p=P;
        FOR(i,1,n) px[i]=(LL)px[i-1]*p%M;
    }
    void set(char a[],int n){
        int i;val[0]=0;
        FOR(i,1,n) val[i]=((LL)val[i-1]*p+a[i-1])%M;
    }
    int get(int l,int r){
        l++;r++;
        int ret=val[r]-(LL)val[l-1]*px[r-l+1]%M;
        (ret<0)&&(ret+=M);return ret;
    }
}HA,RB;
void manacher(char A[],int p[],int len){
    int id=0,mx=0,i;
    rep(i,1,len){
        if (mx>i) p[i]=min(p[2*id-i],mx-i);
        else p[i]=1;
        while (A[i+p[i]]==A[i-p[i]]) p[i]++;
        if (p[i]+i>mx) mx=p[i]+i,id=i;
    }
}
int n,i;
int s[maxn];
char a[maxn],b[maxn],A[maxn*2],B[maxn*2];
int PA[maxn*2],PB[maxn*2];//id
int len,ans;
int main(){
    scanf("%d",&n);
    scanf("%s%s",a,b+1);
    a[n]='(';b[0]=')';n++;
    A[len]='+';B[len]='-';len++;
    A[len]='%';B[len]='%';len++;
    REP(i,n){
        A[len]=a[i];B[len]=b[i];len++;
        A[len]='%'; B[len]='%'; len++;
    }A[len]='*';B[len]='/';len++;
    n=len;
    manacher(A,PA,len);
    manacher(B,PB,len);
    HA.setp(19);RB.setp(19);
    HA.set(A,n);reverse(B,B+n);RB.set(B,n);
    reverse(B,B+n);
    rep(i,1,n){
        //min(i-1-PA[i]+1,n-1-i-PA[i]+1)+1
        //PA和PB的判断相同 (只需一个最大即可)
        PA[i]=max(PA[i],PB[i]);
        int l=0,r=min(i-PA[i],n-1-i-PA[i])+1;//r:not
        while (l+1<r){
            int mid=(l+r)/2;
            int hash_A=HA.get(i-PA[i]-mid+1,i-PA[i]);
            int hash_B=RB.get(n-(i+PA[i]+mid),n-1-(i+PA[i]));
            if (hash_A==hash_B) l=mid;
            else r=mid;
        }ans=max(ans,PA[i]+l);
    }printf("%d\n",ans-1);
}
/*
8
aaaaaaaa
bbbaabaa
*/
