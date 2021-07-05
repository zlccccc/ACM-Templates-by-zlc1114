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

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

//插头dp长这样
//     ______
//____|o|->
template<typename T1,typename T2> struct hashmap {
    const static int seed=199991;//seed最好设置小点=_=! 要clear
    const static int maxn=1e6+7;
    struct node {
        T1 key; T2 val; int next;
        node() {};
        node(T1 k,T2 v,int n):key(k),val(v),next(n) {};
    } T[maxn]; //更好地空间局部性?(雾)
    int head[seed],size;
    void clear() {
        memset(head,-1,sizeof(head));
        size=0;
    }
    void insert(T1 pos,T2 val) {
        int x=pos%seed;
        T[size]=node(pos,val,head[x]);
        head[x]=size++;
    }
    bool find(int x) {
        for (int i=head[x%seed]; ~i; i=T[i].next)
            if (T[i].key==x) return 1;
        return 0;
    }
    T2 &operator [](T1 x) {
        for (int i=head[x%seed]; ~i; i=T[i].next)
            if (T[i].key==x) return T[i].val;
        insert(x,INF);
        return T[size-1].val;
    }
};
typedef hashmap<int,int> HASHMAP;
HASHMAP MP[2];
inline int getBit(int x,int k) {
    return (x>>(k+k))&3;
}
inline int setBit(int x,int k,int v) {//注意这里是返回=_=
    return (x&~(3<<(k+k)))|(v<<(k+k));
}
inline void insert(HASHMAP &nxt,int k,int val) {
    int &nxtval=nxt[k];
    nxtval=min(nxtval,val);//down
}
inline void insert(HASHMAP &nxt,int k,int j,int down,int right,int val) {
    k=setBit(k,j-1,down);
    k=setBit(k,j,right);
    int &nxtval=nxt[k];
    nxtval=min(nxtval,val);//down
}
//题意: 要从上往下划个线,把L和R分开; 不能有环
char str[27][27];
int n,m;
void printstatus(int k,int i,int j,const char str[]=""){
    printf("%s: %d %d; status=",str,i,j);
    REP(i,m+1) printf("%d",getBit(k,i));
    // system("pause");
}
int main() {
    int i,j;
    while (~scanf("%d%d",&n,&m)) {
        FOR(i,1,n) scanf("%s",str[i]+1);
        int now=0,nxt=1;
        MP[now].clear();
        FOR(j,1,m) {
            int x=setBit(0,j,3);
            MP[now].insert(x,0);
        };//top_插头
        FOR(i,1,n) {
            FOR(j,1,m) {//check_position; to_right
                MP[nxt].clear();
                int more=str[i][j]-'0';
                for (int it=0; it<MP[now].size; it++) { //x_left; y:down
                    int k=MP[now].T[it].key,val=MP[now].T[it].val;
                    int L=getBit(k,j-1),U=getBit(k,j);//v=value
                    int z=0;//from left; downval_count
                    {int t; REP(t,j) if (getBit(k,t)) z^=1;}
                    if ((str[i][j]=='#'||str[i][j]=='W'||str[i][j]=='L')&&(L||U)) {
                        continue;//有插头
                    } else if (str[i][j]=='W') {
                        if (z) continue;
                        insert(MP[nxt],k,MP[now][k]);//no way
                    } else if (str[i][j]=='L') {
                        if (!z) continue;//no!
                        insert(MP[nxt],k,MP[now][k]);//no way
                    } else if (str[i][j]=='#') {//all is ok
                        insert(MP[nxt],k,MP[now][k]);//no way
                    } else {
                        if (L&&U) {//value:(left and up)
                            if (L!=U) {
                                if (L==2&&U==1) {// (value= _|)
                                    insert(MP[nxt],k,j,0,0,val+more);
                                } else if (L==3&&U==1) {
                                    int pos,_k=setBit(k,j-1,0);
                                    _k=setBit(_k,j,0);
                                    FOR(pos,j+1,m) if (getBit(k,pos)==2) break;
                                    if (0<=pos&&pos<=m) {
                                        _k=setBit(_k,pos,3);
                                        insert(MP[nxt],_k,val+more);
                                    } else printstatus(k,i,j,"bug1");
                                } else if (L==2&&U==3) {
                                    int pos,_k=setBit(k,j-1,0);
                                    _k=setBit(_k,j,0);
                                    rFOR(pos,0,j-2) if (getBit(k,pos)==1) break;
                                    if (0<=pos&&pos<=m) {
                                        _k=setBit(_k,pos,3);
                                        insert(MP[nxt],_k,val+more);
                                    } else printstatus(k,i,j,"bug2");
                                } else continue;//L=1&&U=2;
                                // merge_circle((i,j)=bottom_right(ex,ey))
                            } else {
                                int pos,_k=setBit(k,j,0); _k=setBit(_k,j-1,0);
                                if (L==1) {
                                    FOR(pos,j+1,m) if (getBit(k,pos)==(L^3)) break;
                                } else {
                                    rFOR(pos,0,j-2) if (getBit(k,pos)==(L^3)) break;
                                } if (0<=pos&&pos<=m) {
                                    _k=setBit(_k,pos,L);
                                    insert(MP[nxt],_k,val+more);
                                } else printstatus(k,i,j,"bug3");
                            }
                        } else if (L||U) {//left or up
                            insert(MP[nxt],k,j,L|U,0,val+more);
                            insert(MP[nxt],k,j,0,L|U,val+more);
                        } else {
                            insert(MP[nxt],k,val);//not_choose
                            insert(MP[nxt],k,j,1,2,val+more);//new
                        }
                    }
                } now^=1; nxt^=1;
            }
            MP[nxt].clear(); //to_next(->)
            for (int it=0; it<MP[now].size; it++) {
                int k=MP[now].T[it].key; int w=MP[now].T[it].val;
                if (!getBit(k,m)) insert(MP[nxt],k<<2,w);
            } now^=1; nxt^=1;
        }
        int ans=INF;
        FOR(j,1,m) {
            int x=setBit(0,j,3);
            ans=min(ans,MP[now][x]);
        }
        if (ans<INF) printf("%d\n",ans);
        else puts("-1");
    }
}
/*
6 8
88W888L811
888#W88811
888888L811
8W8LL#8811
8888888L11
00000W8811

3 6
000888
0L08W8
000888

3 6
000888
000888
000888

3 4
1111
1111
1111

3 4
W88L
88L8
8L8L

6 8
11111111
11111111
11111111
11111111
11111111
11111111
*/