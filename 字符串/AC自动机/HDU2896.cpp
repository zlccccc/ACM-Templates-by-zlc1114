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
namespace ACM {
    const int maxn=505*140;
    int next[maxn][98],fail[maxn],len[maxn],tot;
    vector<int> have[maxn];
    void init() {
        tot=0; len[0]=0; fail[0]=0;
        memset(next[0],0,sizeof(next[0]));
    }
    void insert(char s[],int id) {
        int i,n=strlen(s),p=0;
        REP(i,n) {
            int c=s[i]-33;
            if (!next[p][c]) {
                next[p][c]=++tot; len[tot]=len[p]+1;
                have[tot].clear(); fail[tot]=0;
                memset(next[tot],0,sizeof(next[tot]));
            } p=next[p][c];
        } have[p].push_back(id);
    }
    int Q[maxn],ST,ED;
    void buildAC() {
        ST=0; ED=-1; Q[++ED]=0;
        while (ST<=ED) {
            int p=Q[ST++],c;
            REP(c,98) {
                if (next[p][c]) {
                    fail[next[p][c]]=p?next[fail[p]][c]:0;
                    Q[++ED]=next[p][c];
                } else next[p][c]=p?next[fail[p]][c]:0;//否则可能fail=self
            }
            for (int v:have[fail[p]])
                have[p].push_back(v);
        }
    }
    void query(char a[],vector<int> &ans) {
        int p=0;
        int n=strlen(a),i;
        REP(i,n) {
            int c=a[i]-33; p=next[p][c];
            for (int v:have[p]) ans.push_back(v);
        }
    }
}
int T,i,j,n,m,total;
char s[maxn];
vector<int> ans;
int main() {
    while (~scanf("%d",&n)) {
        total=0;
        ACM::init();
        FOR(i,1,n) {
            scanf("%s",s);
            ACM::insert(s,i);
        } ACM::buildAC();
        scanf("%d",&m);
        FOR(i,1,m) {
            scanf("%s",s);
            ACM::query(s,ans);
            if (ans.size()==0) continue;
            printf("web %d:",i);
            sort(ans.begin(),ans.end());
            ans.erase(unique(ans.begin(), ans.end()),ans.end());
            for (auto now:ans) printf(" %d",now); puts("");
            total++; ans.clear();
        }
        printf("total: %d\n",total);
    }
}
/*
*/
