#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=100007;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

//HDU2896,匹配多串
struct ACM {
    int next[505*140][98],fail[505*140],tot;
    vector<int> have[maxn];
    void init() {tot=0; memset(next[0],0,sizeof(next[0]));}
    void insert(char a[],int id) {
        int i,n=strlen(a),p=0;
        REP(i,n) {
            int c=a[i]-33;
            if (!next[p][c]) {
                next[p][c]=++tot;
                have[tot].clear();
                memset(next[tot],0,sizeof(next[tot]));
            }
            p=next[p][c];
        }
        have[p].push_back(id);
    } int Q[maxn],front,end;
    void buildAC() {
        front=end=0;
        Q[end++]=0;
        while (front!=end) {
            int x=Q[front++],c;
            REP(c,98) if (next[x][c]) {
                if (!x) fail[next[x][c]]=0;
                else {
                    int p=fail[x];
                    while (p&&!next[p][c]) p=fail[p];
                    if (next[p][c])
                        fail[next[x][c]]=next[p][c];
                    else fail[next[x][c]]=0;
                }
                Q[end++]=next[x][c];
            }
            for (int v:have[fail[x]])
                have[x].push_back(v);
        }
    } void query(char a[],int ans[],int &tot) {
        tot=0;
        int p=0;
        int n=strlen(a),i;
        REP(i,n) {
            int c=a[i]-33;
            while (p&&!next[p][c]) p=fail[p];
            p=next[p][c];
            for (int v:have[p]) ans[tot++]=v;
        }
    }
} AC;
int T,i,j,n,m,total;
char s[maxn];
int ans[505],tot;
int main() {
    while (~scanf("%d",&n)) {
        total=0;
        AC.init();
        REP(i,n) {
            scanf("%s",s);
            AC.insert(s,i+1);
        }
        AC.buildAC();
        scanf("%d",&m);
        REP(i,m) {
            scanf("%s",s);
            AC.query(s,ans,tot);
            if (tot==0) continue;
            printf("web %d:",i+1);
            sort(ans,ans+tot);
            ans[tot]=0;
            REP(j,tot) if (ans[j]!=ans[j+1]) printf(" %d",ans[j]);
            puts("");
            total++;
        }
        printf("total: %d\n",total);
    }
}
