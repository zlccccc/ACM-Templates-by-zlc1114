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
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(int)(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

struct BITSET {
    vector<ULL> V;
    void set(int x,int k) {
        assert((int)V.size()>x/64);
        if (k) V[x/64]|=1ull<<(x&63);
        else V[x/64]&=~(1ull<<(x&63));
    }
    void resize(int x) {
        V.resize((x-1)/64+1,0);
    }
    int get(int x) {
        return (V[x/64]>>(x&63))&1;
    }
    bool operator < (const BITSET &B) const {
        int i;
        REP(i,(int)V.size()) if (V[i]!=B.V[i]) return V[i]<B.V[i];
        return 0;
    }
    BITSET const doit(int size,int F[65536]) const {//相邻两位合并
        BITSET ret; int i;
        ret.resize(size/2);
        REP(i,(int)V.size()) {
            if (i&1) {
                ret.V[i/2]|=((ULL)F[V[i]&65535]<<32)
                            |((ULL)F[(V[i]>>16)&65535]<<40)
                            |((ULL)F[(V[i]>>32)&65535]<<48)
                            |((ULL)F[(V[i]>>48)]<<56);
            } else {
                ret.V[i/2]|=((ULL)F[V[i]&65535])
                            |((ULL)F[(V[i]>>16)&65535]<<8)
                            |((ULL)F[(V[i]>>32)&65535]<<16)
                            |((ULL)F[(V[i]>>48)]<<24);
            }
        } return ret;
    }
    void print() {
        int i;
        REP(i,(int)V.size()) pr2(V[i],64);
    }
};
int ORB[maxn],ANDB[maxn],XORB[maxn];
map<BITSET,int> MP[20];
int main() {
    int i,k;
    REP(k,65536) {
        int now=0;
        REP(i,8) now|=(((k>>(i*2))&1)|((k>>(i*2+1))&1))<<i; ORB[k]=now;
        now=0;
        REP(i,8) now|=(((k>>(i*2))&1)&((k>>(i*2+1))&1))<<i; ANDB[k]=now;
        now=0;
        REP(i,8) now|=(((k>>(i*2))&1)^((k>>(i*2+1))&1))<<i; XORB[k]=now;
    }
    scanf("%d%s",&n,str);
    // n=18;
    m=1<<n;
    // REP(i,m) str[i]=rand()%2+'0';
    BITSET now;
    now.resize(1<<n);
    REP(i,m) {
        now.set(i,str[i]-'0');
    } MP[0][now]++;
    // now.print();puts("");
    REP(k,n) {
        // printf("%d: %d\n",k,(int)MP[k].size());
        for (auto now:MP[k]) {
            auto &V=now.first;
            // V.print(); printf(" %lld\n",now.second);
            // REP(i,(1<<(n-k))) printf("%c",V[i]+'0');printf("  %lld\n",now->second);
            BITSET nxt;
            nxt.resize(1<<(n-k-1));
            nxt=V.doit(1<<(n-k),ORB);
            // REP(i,(1<<(n-k-1))) nxt.set(i,V.get(i*2)|V.get(i*2+1));
            MP[k+1][nxt]+=now.second;
            nxt=V.doit(1<<(n-k),ANDB);
            // REP(i,(1<<(n-k-1))) nxt.set(i,V.get(i*2)&V.get(i*2+1));
            MP[k+1][nxt]+=now.second;
            nxt=V.doit(1<<(n-k),XORB);
            // REP(i,(1<<(n-k-1))) nxt.set(i,V.get(i*2)^V.get(i*2+1));
            MP[k+1][nxt]+=now.second;
        }
    } now.resize(1); now.V[0]=1;
    MP[n][now]+=0;
    for (auto now:MP[n]) {
        if ((now.first).V[0]==1) {
            printf("%d",now.second);
        }
    }
    // printf("%lld\n",ans);
}
/*
5
00000000000000000000000000000000
5
10010101010110001001010101011000
5
11111111111111111111111111111111
*/