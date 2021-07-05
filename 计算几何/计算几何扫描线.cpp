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
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=1e7+3;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=2e5+107;
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

// CEOI 2020 day1B 线段扫描线; 动态维护y=eps*x的扫描线
// 题意是给线段, 连线让所有线段在平面连起来
// 做法是维护每个点up or down的最近邻加入or删除线段端点(一个区间只能维护一种), 连起来即可
int x3;
const ll MOD=1e9;
struct int128 {//getbigint
    ll fin;
    ll x0,x1; // get
    int128(ll x) {
        x0=0; x1=x;
        fin=x;
        reset();
    }
    void reset() {
        ll mor=x1/MOD; x1-=mor*MOD;
        while (x1>0) x1-=MOD,mor++;
        while (x1<0) x1+=MOD,mor--;
        x0+=mor;
    }
    void operator*=(ll x) {
        x0*=x; x1*=x;
        // fin=fin*(__int128)x;
        reset();
        // assert(fin-(__int128)x0*MOD-x1==0);
    }
    bool operator<(const int128 &o) const {
        if (x0!=o.x0) return x0<o.x0;
        else return x1<o.x1;
    }
};
struct Point {
    ll x,y;
    bool operator<(const Point &o) const {
        if (x!=o.x) return x<o.x;
        else return y<o.y;
    }
};
struct Line {
    mutable Point p1,p2; int id,mask;//id:
    bool operator<(const Line &o)const {
        int128 left(1),right(1); // __int128
        if (p1.x!=p2.x) left*=(x3-p1.x)*(p2.y-p1.y)+p1.y*(p2.x-p1.x);//div
        if (o.p1.x!=o.p2.x) right*=(x3-o.p1.x)*(o.p2.y-o.p1.y)+o.p1.y*(o.p2.x-o.p1.x);
 
        if (p1.x!=p2.x) right*=p2.x-p1.x;
        else left*=p1.y;
        if (o.p1.x!=o.p2.x) left*=o.p2.x-o.p1.x;
        else right*=o.p1.y;
        return left<right;
        //we should first add then remove
    }
} A[maxn*2];

//downid(0): inside; upid(1): outside; more
set<Line> S;
void outputlines(vector<Line> V) {
    printf("%d\n",(int)V.size());
    for (auto line:V) {
        printf("%d %d %d %d\n",(int)line.p1.x,(int)line.p1.y,(int)line.p2.x,(int)line.p2.y);
    }
}
Point last[maxn],uplast[maxn];//fa;merge-it
int main() {
    int n,i;
    scanf("%d",&n);
    FOR(i,1,n) {
        int x1,x2,y1,y2;
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        // swap(x1,y1); swap(x2,y2);
        A[i].p1.x=x1; A[i].p2.x=x2;
        A[i].p1.y=y1; A[i].p2.y=y2;
        if (A[i].p2<A[i].p1) swap(A[i].p1,A[i].p2);
        A[i+n]=A[i];
        A[i].mask=1; A[i+n].mask=-1;
        A[i].id=A[i+n].id=i;
    }
    //we should first add then remove
    FOR(i,1,n) last[i]=uplast[i]=A[i].p1;//initial
    sort(A+1,A+1+n+n,[](const Line &x,const Line &y) {
        Point px,py;
        if (x.mask==1) px=x.p1; else px=x.p2;
        if (y.mask==1) py=y.p1; else py=y.p2;
        return px<py;
    });
    Line tmp; tmp.p1.x=tmp.p1.y=tmp.p2.y=-INF; tmp.p2.x=INF; tmp.id=0;
    S.insert(tmp);
    vector<Line> ans,V;
    FOR(i,1,n+n) {
        debug("A&Q %d %d %d %d; id=%d\n",(int)A[i].p1.x,(int)A[i].p1.y,(int)A[i].p2.x,(int)A[i].p2.y,A[i].id);
        if (A[i].mask==1) {
            { // DOIT before insert line
                int mask=0;
                x3=A[i].p1.x;
                auto it=S.lower_bound(A[i]);
                if (it==S.end()) it--,mask=1;
                int id=it->id;//previous
                // printf("id=%d; rid=%d; last=%d; mask=%d\n",id,rid,lastid[id][mask],mask);
                if (i!=1) {//just link it
                    debug(" ACT QUERY %d(%d %d %d %d); mask=%d; finid=%d\n",id,(int)it->p1.x,(int)it->p1.y,(int)it->p2.x,(int)it->p2.y,mask,fin_id);
                    Line now;
                    if (mask==0) now.p1=last[id];
                    else now.p1=uplast[id];
                    now.p2=A[i].p1;
                    ans.push_back(now);
                    if (mask==1) V.push_back(now);
                    if (mask==1) V.push_back(A[i]);
                    // printf("upd %d %d %d\n",rid,mask,p);
                    if (mask==0) last[id]=A[i].p1;
                    else uplast[id]=A[i].p1;
                }
                debug("insert %d\n",A[i].id);
            }
            // insert line
            x3=A[i].p1.x;
            S.insert(A[i]);
        } else {//remove; should merge it into its link
            // remove line
            x3=A[i].p2.x; int p=A[i].id;
            auto it=S.lower_bound(A[i]);
            assert(p==it->id); // removed id
            S.erase(it);
            { // DOIT after remove line
                int mask=0;
                it=S.lower_bound(A[i]);
                if (it==S.end()) it--,mask=1;
                int id=it->id;//previous
                if (mask==0) last[id]=A[i].p2;
                else uplast[id]=A[i].p2;
            }
        }
        // for (auto line:S) {
        //     printf("   line in S %d %d %d %d\n",(int)line.p1.x,(int)line.p1.y,(int)line.p2.x,(int)line.p2.y);
        // }
    }
    // V.resize(1000);
    // outputlines(V);
    assert((int)ans.size()==n-1);
    for (auto line:ans) {
        printf("%d %d %d %d\n",(int)line.p1.x,(int)line.p1.y,(int)line.p2.x,(int)line.p2.y);
    }
}
/*
*/