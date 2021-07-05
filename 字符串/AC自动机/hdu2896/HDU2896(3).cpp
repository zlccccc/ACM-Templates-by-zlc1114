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
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

int ans[505],num;
const int maxtot=505*140;
struct Aho{
    struct node{
        int next[98];
        int fail,mark;
    }stateTable[maxtot];
    int cnt;
    queue<int> Q;
    void init(){
        int i;
        while (Q.size()) Q.pop();
        REP(i,maxtot){
            memset(stateTable[i].next,0,sizeof(stateTable[i].next));
            stateTable[i].mark=stateTable[i].fail=0;
        }
        cnt=1;
    }
    inline void insert(char *str,int id){
        int len=strlen(str),now=0,i;
        REP(i,len){
            if (!stateTable[now].next[str[i]-33]) stateTable[now].next[str[i]-33]=cnt++;
            now=stateTable[now].next[str[i]-33];
        }
        stateTable[now].mark=id;
    }
    inline void buildAC(){
        stateTable[0].fail=-1;
        Q.push(0);
        int i;
        while (!Q.empty()){
            int x=Q.front();Q.pop();
            REP(i,98) if (stateTable[x].next[i]){
                if (x==0) stateTable[stateTable[x].next[i]].fail=0;
                else{
                    int p=stateTable[x].fail;
					while (p!=-1&&!stateTable[x].next[i]) p=stateTable[p].fail;
					if (p!=-1) stateTable[stateTable[x].next[i]].fail=stateTable[p].next[i];
					else stateTable[stateTable[x].next[i]].fail=0;
                }
                Q.push(stateTable[x].next[i]);
            }
        }
    }
    inline void match(char* str){
        int len=strlen(str),now=0;
        int i,p;
	    num=0;
		REP(i,505) ans[i]=0;
        REP(i,len){
            while (now&&!stateTable[now].next[str[i]-33]) now=stateTable[now].fail;
        	now=stateTable[now].next[str[i]-33];
        	if (now==-1) now=0;
        	int tmp=now;
        	while (tmp&&!ans[stateTable[now].mark]){
        		if (stateTable[tmp].mark){
					ans[stateTable[tmp].mark]=1;
					num++;
				}
				tmp=stateTable[tmp].fail;
				if (num>=3) return;
			}
        }
    }
}AC;
int T,i,j,n,m,total;
char s[maxn];
int main(){
    while (~scanf("%d",&n)){
    	total=0;
	    AC.init();
	    REP(i,n){
	    	scanf("%s",s);
	        AC.insert(s,i+1);
	    }
	    AC.buildAC();
	    scanf("%d",&m);
	    REP(i,m){
	    	scanf("%s",s);
	        AC.match(s);
	        if (num==0) continue;
	        total++;
	        printf("web %d:",i+1);
	        REP(j,505) if (ans[j]) printf(" %d",j);
	        puts("");
	    }
	    printf("total: %d\n",total);
	}
}
