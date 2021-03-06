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
const LL maxn=2e5+7;
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

struct SAM{
    const static int maxn=4e5+7;
    int next[maxn][26],fail[maxn],len[maxn];
    int cnt,last;
    int pos[maxn];
    void init(){
        cnt=last=0; fail[0]=-1; len[0]=0;
        memset(next[0],0,sizeof(next[0]));
    }
    void add(int c,int i){
        int np=++cnt,p=last; pos[np]=i;
        memset(next[np],0,sizeof(next[np]));
        len[np]=len[p]+1;
        for (;p!=-1&&!next[p][c];p=fail[p]) next[p][c]=np;
        if (p==-1) fail[np]=0;
        else{
            int q=next[p][c];
            if (len[p]+1==len[q]) fail[np]=q;
            else{
                int nq=++cnt; len[nq]=len[p]+1; pos[nq]=i;
                memcpy(next[nq],next[q],sizeof(next[q]));
                fail[nq]=fail[q]; fail[np]=fail[q]=nq;
                for (;p!=-1&&next[p][c]==q;p=fail[p]) next[p][c]=nq;
            }
        } last=np;
    }
    struct node{
        int l,r;
        node(){l=r=0;}
    }T[maxn*20];
    int root[maxn],tot;
    void insert(int &x,int pos,int L,int R){
        if (!x) x=++tot,T[x]=node();
        if (L==R) return;
        int mid=(L+R)/2;
        if (pos<=mid) insert(T[x].l,pos,L,mid);
        if (mid<pos) insert(T[x].r,pos,mid+1,R);
    }
    void merge(int &x,int y){
        if (!x||!y) {x|=y; return;}
        T[++tot]=T[x]; x=tot;
        merge(T[x].l,T[y].l);
        merge(T[x].r,T[y].r);
    }
    int query(int x,int l,int r,int L,int R){
        if (!x) return 0;
        if (l<=L&&R<=r) return 1;
        int ret=0,mid=(L+R)/2;
        if (l<=mid) ret|=query(T[x].l,l,r,L,mid);
        if (mid<r) ret|=query(T[x].r,l,r,mid+1,R);
        return ret;
    }
    int S[maxn],K[maxn];
    int sfail[maxn],ans[maxn];
    int solve(){
        int i; tot=0;
        FOR(i,1,cnt) S[i]=0;
        FOR(i,1,cnt) S[len[i]]++;
        FOR(i,1,cnt) S[i]+=S[i-1];
        FOR(i,1,cnt) K[S[len[i]]--]=i;
        FOR(i,1,cnt) root[i]=0;
        rFOR(i,1,cnt){
            int x=K[i]; int pre=fail[x];
            insert(root[x],pos[x],1,cnt);
            merge(root[pre],root[x]);
        }
        int ret=0; sfail[0]=ans[0]=0;
        FOR(i,1,cnt){
            int x=K[i]; int pre=sfail[fail[x]];
            if (!pre||query(root[pre],pos[x]-len[x]+len[pre],pos[x]-1,1,cnt)){
                ans[x]=ans[pre]+1;
                sfail[x]=x;
            }else{
                ans[x]=ans[pre];
                sfail[x]=pre;
            }ret=max(ret,ans[x]);
        }return ret;
    }
}sam;
int TaskA(){
    int i;
    scanf("%s",S);
    sam.init();
    REP(i,n) sam.add(S[i]-'a',i+1);
//    sam.dfs();
    printf("%d\n",sam.solve());
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
	Task_more_n();
}
/*

*/
