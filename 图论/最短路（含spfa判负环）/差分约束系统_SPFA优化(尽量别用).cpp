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

// dijkһ�㶼���spfa��ܶ�~
// ����u->v,len����val(v)-val(u)<=len
// ���ӣ�https://ac.nowcoder.com/acm/contest/71/E
// ��һ����Ϊ n ������ A�������� m ���������������������֣�
// 1���������� [l,r]��������Ԫ�ذ�λ��͵��� x
// 2���������� [l,r]��������Ԫ�ذ�λ��͵��� x
// ���һ������ A��ʹ����������� m ����������֤�н⡣
// �Ȱ�λ��һ��, Ȼ��ǰ׺�ͽ��в��Լ��; Լ���Ļ�����ÿһλ��1�ȵ�
struct SPFA {
    vector<vector<pii>> edge;
    vector<int> dis;
    vector<bool> vis;
    vector<int> cnt;  // bfs���˼���
    SPFA(int n): edge(n+1),dis(n+1,INF),vis(n+1),cnt(n+1) {}
    void addedge(int x,int y,int w) {
        edge[x].push_back({y,w});
    }
    void clear() {
        edge.assign(edge.size(),vector<pii>());
        dis.assign(dis.size(),INFF);
        vis.assign(vis.size(),false);
        cnt.assign(cnt.size(),0);
    }
    bool spfa(int x,bool slf=true,bool lll=false) {
        deque<int> Q;
        Q.push_back(x); dis[x]=0;
	    int sum=0; //lll
        while (!Q.empty()){
            int u=Q.front();Q.pop_front();
            if (lll) {
                if (!Q.empty()&&sum/Q.size()<dis[u]) Q.push_back(u); //lll
                else {vis[u]=0; sum-=dis[u];} //lll
            } else vis[u]=0; //not lll
            for (auto [v,d]:edge[u]) {
                if (dis[u]+d<dis[v]) {
                    dis[v]=dis[u]+d;
                    if (!vis[v]) {
                        vis[v]=1;
                        if (slf) {
                            if (Q.empty()||dis[Q.front()]<dis[v]) Q.push_back(v); //slf
                            else Q.push_front(v); //slf
                        } else {
    					    Q.push_back(v); //not slf
                        }
    					cnt[v]++; //judge negative ring; ���id�����˼���
    					if (cnt[v]>=edge.size()-1) return 1; //judge negative ring
    					sum+=dis[v]; //lll
                    }
                }
            }
        }
        return 0; // judge negative ring
    }
    bool solve(int x) {
        dis[x]=0;
        return spfa(x);  // 0: �и���
    }
};
int ans[maxn];
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    vector<ar4> limits(m+1);
    FOR_(i,1,m) REP_(k,4) scanf("%d",&limits[i][k]);
    SPFA spfa(n);
    REP_(k,20) {
        spfa.clear();
        FOR_(i,1,n) {  // ÿ��λ��ֻ����0����1
            spfa.addedge(i,i-1,0);
            spfa.addedge(i-1,i,1);
        }
        FOR_(i,1,m){
            auto [op,l,r,x]=limits[i];
            if (op==1) {  // or
                if ((x>>k)&1) spfa.addedge(r,l-1,-1);  // sum[r]-sum[l-1]>=1
                else spfa.addedge(l-1,r,0);  // sum[r]-sum[l-1]=0
            } else {  // and
                if ((x>>k)&1) spfa.addedge(r,l-1,-(r-l+1));  // sum[r]-sum[l-1]>=r-l+1
                else spfa.addedge(l-1,r,r-l);  // sum[r]-sum[l-1]<=r-l
            }
        }
        spfa.solve(0);
        FOR_(i,1,n) ans[i]|=(spfa.dis[i]-spfa.dis[i-1])<<k;
    }
    FOR_(i,1,n) printf("%d ",ans[i]);
}
/*
2 3 5 8 13 6
1 1 2 3 4 5
*/
