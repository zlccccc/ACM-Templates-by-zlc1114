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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

template<typename T1,typename T2> struct hashmap{
    const static int seed=999991;
    const static int maxn=1e6+7;
    struct node{
        T1 key;T2 val;int next;
        node(){};
        node(T1 k,T2 v,int n):key(k),val(v),next(n){};
    }T[maxn];//更好地空间局部性?(雾)
    int head[seed],size;
    void clear(){
        memset(head,-1,sizeof(head));
        size=0;
    }
    void insert(T1 pos,T2 val){
        int x=pos%seed;
        T[size]=node(pos,val,head[x]);
        head[x]=size++;
    }
    T2 &operator [](T1 x){
        for (int i=head[x%seed];~i;i=T[i].next)
            if (T[i].key==x) return T[i].val;
        insert(x,0);
        return T[size-1].val;
    }
};
hashmap<int,LL> MP[2];
int T;
inline int getpos(int x,int k){
    return (x>>(k+k))&3;
}inline int setpos(int x,int k,int v){
    return (x&~(3<<(k+k)))|(v<<(k+k));
}char A[27][27];
int ex,ey;//012:#()
int main(){
//    scanf("%d",&T);
    T=1;
    while (T--){
        int n,m;
        int i,j,k;
        scanf("%d%d",&n,&m);
        FOR(i,1,n) scanf("%s",A[i]+1);
        FOR(i,1,n) FOR(j,1,m) if (A[i][j]=='.') ex=i,ey=j;
        int now=0,nxt=1;
        MP[now].clear();MP[now].insert(0,1);
        FOR(i,1,n){
            FOR(j,1,m){
//                printf("%d %d\n",i,j);
                MP[nxt].clear();
                for(int it=0;it<MP[now].size;it++){
                    int k=MP[now].T[it].key;LL w=MP[now].T[it].val;
                    int L=getpos(k,j-1),U=getpos(k,j);
                    if (A[i][j]=='*') {//update0
                        if (!L&&!U) MP[nxt][k]+=w;
                    }else if (A[i][j]) {//update1
                        if (!L&&!U){
                            int K=setpos(k,j-1,1);
                            K=setpos(K,j,2);
                            MP[nxt][K]+=w;
                        }else if ((!L)^(!U)){
                            int K=setpos(k,j-1,U);
                            K=setpos(K,j,L);
                            MP[nxt][K]+=w;
                            MP[nxt][k]+=w;
                        }else if (L&&U){
                            int K=setpos(k,j-1,0);
                            K=setpos(K,j,0);
                            if (L!=U){
                                if (L==2||(i==ex&&j==ey))//L=1,U=2时,代表的是已经连接
                                    MP[nxt][K]+=w;
                            }else{
                                if (L==1){
                                    int cnt=1;
                                    for (int l=j+1;l<=m;l++){
                                        int x=getpos(K,l);
                                        if (x==1) cnt++;
                                        if (x==2) cnt--;
                                        if (!cnt) {K=setpos(K,l,1);break;}//连接后,会改变一个插头的value
                                    }MP[nxt][K]+=w;
                                }else if (L==2){
                                    int cnt=-1;
                                    for (int l=j-2;l>=0;l--){
                                        int x=getpos(K,l);
                                        if (x==1) cnt++;
                                        if (x==2) cnt--;
                                        if (!cnt) {K=setpos(K,l,2);break;}
                                    }MP[nxt][K]+=w;
                                }
                            }
                        }
                    }
                }now^=1;nxt^=1;
//                for(int it=0;it<MP[now].size;it++){
//                    int k=MP[now].T[it].key;LL w=MP[now].T[it].val;
//                        printf("%d  ",it);
//                        for (int i=0;i<=m;i++) putchar('0'+getpos(k,i));
//                        printf("  %lld",w);puts("");
//                }
            }//shift
            MP[nxt].clear();
            for(int it=0;it<MP[now].size;it++){
                int k=MP[now].T[it].key;LL w=MP[now].T[it].val;
                if (!getpos(k,m)) MP[nxt][k<<2]+=w;
            }
            now^=1;nxt^=1;
//                puts("");
//                for(int it=0;it<MP[now].size;it++){
//                    int k=MP[now].T[it].key;LL w=MP[now].T[it].val;
//                        printf("%d  ",it);
//                        for (int i=0;i<=m;i++) putchar('0'+getpos(k,i));
//                        printf("  %lld",w);puts("");
//                }
        }static int x;
        printf("%lld",MP[now][0]);
    }
}
/*
*/
