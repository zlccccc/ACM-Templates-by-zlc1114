#include <bits/stdc++.h>
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
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
inline void add(int &A,int B){A+=B;(A>=M)&&(A-=M);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int n,m;
char S[maxn];

int mask[maxn];
int cnt[67];
int TaskA(){
    int i,j,k,q;
    n=strlen(S);
    const int MAX=(1<<6)-1;
    REP(i,n) mask[i]=MAX;
    scanf("%d",&m);
    REP(i,m){
        int pos;
        char s[20];
        scanf("%d",&pos); pos--; mask[pos]=0;
        scanf("%s",s); int l=strlen(s);
        REP(j,l) mask[pos]|=1<<(s[j]-'a');
    }REP(i,n) REP(k,MAX){
        if ((k>>(S[i]-'a'))&1) cnt[k]--;
        if (mask[i]&k) cnt[k]++;
    }REP(i,n){
        REP(k,MAX) if (mask[i]&k) cnt[k]--;
        REP(j,7) if ((mask[i]>>j)&1){
            bool okay=true;
            REP(k,MAX){
                if (cnt[k]+((k>>j)&1)<0) okay=false;
                if (!okay) break;
            }if (okay) break;
        }//printf("%d: %d\n",i,j);
        if (j==7) return 0*puts("Impossible");
        S[i]=j+'a'; mask[i]=1<<j;
        REP(k,MAX) if (mask[i]&k) cnt[k]++;
    }puts(S);
    return 0;
}
void initialize(){}
void Task_one(){TaskA();}
void Task_T(){int T;scanf("%d",&T);while (T--) TaskA();}
void Task_more_n(){while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m(){while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_string(){while (~scanf("%s",S)) TaskA();}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_more_string();
}
/*

*/
