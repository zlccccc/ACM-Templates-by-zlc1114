// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define REP_(I,N) for (int I=0,END=(N);I<END;I++)
#define rREP_(I,N) for (int I=(N)-1;I>=0;I--)
#define rep_(I,S,N) for (int I=(S),END=(N);I<END;I++)
#define rrep_(I,S,N) for (int I=(N)-1,START=(S);I>=START;I--)
#define FOR_(I,S,N) for (int I=(S),END=(N);I<=END;I++)
#define rFOR_(I,S,N) for (int I=(N),START=(S);I>=START;I--)

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
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=1e-10;
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
inline ll fastgcd(ll a, ll b) {  // __gcd()
    if (!b) return a;
    ll az=__builtin_ctzll(a),bz=__builtin_ctzll(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az, diff=b-a, az=__builtin_ctzll(diff);
        (b>a)&&(b=a), a=abs(diff);
    }
    return b<<z;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));
vector<pii> direction4 = {{-1,0},{0,-1},{0,1},{1,0}};
vector<pii> direction8 = {{-1,-1},{-1,0},{1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

// https://codeforces.com/contest/1388/problem/E
// 题意是到x轴的distance-max;
// init_direct为直接投影的排序; init_rotate为投影到坐标上的排序
// 用的时候自己试一下
// 用的ll, 估计没有太多精度问题
// 测试无误; init_direct后 'print'可以递增;
// init_direct后, x*k.x-y*k.y递增
struct frac{
    ll x,y;
    frac(ll _x,ll _y) {
        if (_y<0) _x=-_x,_y=-_y;
        else if (_y==0) _x=abs(_x);
        x=_x; y=_y;
        // norm();
    }
    void norm() {
        ll d=__gcd(abs(x),abs(y));
        x/=d; y/=d;
    }
    bool operator<(const frac &k) const {
        return x*k.y<k.x*y;
    }
    bool operator<=(const frac &k) const {
        return x*k.y<=k.x*y;
    }
    bool operator!=(const frac &k) const {
        return x*k.y!=k.x*y;
    }
    double value(){
        return 1.0*x/y;
    }
};
struct point_rotate{//n^2
    struct point{
        int x,y; int id;
    }T[maxn];
    int start;
    vector<pair<frac,pii> > changes;
    int pos_id[maxn],n;
    void init_direct(int _n) {
        n=_n;
        start=0; changes.clear();
        FOR_(i,1,n) T[i].id=i;
        sort(T+1,T+1+n,[](point &a,point &b){//k=-inf=1/-eps
            if (a.x!=b.x) return a.x>b.x;
            return a.y>b.y;
        });
        FOR_(i,1,n) pos_id[T[i].id]=i;
        FOR_(i,1,n) FOR_(j,i+1,n) if (T[i].x!=T[j].x) {//change position
            // printf("to be change: %f %d %d(pos=%d %d)\n",frac(T[i].y-T[j].y,T[i].x-T[j].x).value(),T[i].id,T[j].id,pos_id[T[i].id],pos_id[T[j].id]);
            changes.push_back(make_pair(frac(T[i].y-T[j].y,T[i].x-T[j].x),make_pair(i,j)));//rotate id
        }
        sort(changes.begin(),changes.end());//low to high
        for (auto &now:changes) {
            pii id=now.second;
            now.second=make_pair(T[id.first].id,T[id.second].id);
        }
    }
    void init_rotate(int n) {
        //k' should be 1/k (y=kx)
        FOR_(i,1,n) swap(T[i].x,T[i].y);//swap
        init_direct(n);
    }
    void change(frac k) {//y=kx;作为法向量的直线
        for (;start<(int)changes.size()&&changes[start].first<=k;start++) {
            pii pos=changes[start].second;
            int x=pos.first,y=pos.second;
            // assert(pos_id[y]-pos_id[x]==1);
            swap(T[pos_id[y]],T[pos_id[x]]);
            swap(pos_id[y],pos_id[x]);
            // printf("swap: %d %d\n",x,y);
            // print(k);
        } 
    }
    void print(frac k) {
        //direct; /sqrt(x^2+y^2)=>length
        FOR_(i,1,n) printf("%lld(%d) ",T[i].x*k.x-T[i].y*k.y,T[i].id); printf(" <- position_direct; x*y=%lld;, k=%f\n",k.x*k.y,k.value());//(/=xy)
    }
}P;
int Y[maxn],L[maxn],R[maxn];
int cnt;//count; change leftid
vector<pair<frac,int> > ks;//double p; change_x_y
double getpos(int x,int y,frac p) {
    // printf("%d %d\n",x,y);
    if (!p.y) return x;
    return 1.0*(x*p.y-y*p.x)/p.y;
}
int inter[maxn];
int id[maxn],ini[maxn];
int main() {
    int n; scanf("%d",&n);
    FOR_(i,1,n) {
        scanf("%d%d%d",&L[i],&R[i],&Y[i]);
        P.T[i].x=L[i]; P.T[i].y=Y[i];
        // P.T[i+n].x=R[i]; P.T[i+n].y=Y[i];
    }
    P.init_rotate(n);
    // P.init_rotate(n*2);
    FOR_(i,1,n) FOR_(j,i+1,n) {
        if (Y[i]==Y[j]) continue;
        {//find ans
            frac l(L[i]-R[j],Y[i]-Y[j]);//reverse
            frac r(R[i]-L[j],Y[i]-Y[j]);
            if (Y[i]>Y[j]) swap(l,r);
            ks.push_back(make_pair(l,-1));//swap_position
            ks.push_back(make_pair(r,1));//swap_position
        }
    }
    // P.print(frac(100,-1));
    if (!(ks.size())) ks.push_back(make_pair(frac(1,0),0));
    sort(ks.begin(), ks.end());
    double ans=INFF;
    for (auto now:ks) {
        P.change(now.first);
        // printf("%f: change %d\n",now.first.value(),now.second);
        bool ok=0;
        ok|=cnt==0;
        cnt+=now.second;
        ok|=cnt==0;
        if (ok) {
            // P.print(now.first);
            int pl=P.T[1].id,pr=P.T[n].id;
            double l=getpos(R[pl],Y[pl],now.first);
            double r=getpos(L[pr],Y[pr],now.first);
            // double l=getpos(P.T[1].y,P.T[1].x,now.first);
            // double r=getpos(P.T[n*2].y,P.T[n*2].x,now.first);
            // printf("%f %f %f\n",l,r,r-l);
            min_(ans,abs(r-l));
        }
    }
    printf("%.12f\n",ans);
}
/*
题意: 直线投影到x轴上不相交, 问minlength是多少
做法就是单纯把不合法情况全搞出来, 然后随便判一判(set二分or n^2log)
*/