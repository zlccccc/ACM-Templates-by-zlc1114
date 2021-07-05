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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

int ans[4],num;
const int maxtot=100007;
struct Aho{
	struct node{
		int next[97];
		int fail,mark;
	}state[maxtot];
	int size,cnt;
	void init(){
		int i;
		REP(i,maxtot){
			memset(state[i].next,0,sizeof(state[i].next));
			state[i].mark=state[i].fail=0;
		}
		cnt=1;
	}
	inline void insert(char *str,int k){
		int len=strlen(str),now=0,i;
		REP(i,len){
			if (!state[now].next[str[i]-33]) state[now].next[str[i]-33]=cnt++;
			now=state[now].next[str[i]-33];
		}
		state[now].mark=k;
	}
	inline void buildAC(){
		state[0].fail=-1;
		queue<int> Q;
		Q.push(0);
		int i,x,p;
		while (!Q.empty()){
			x=Q.front();Q.pop();
			REP(i,97) if (state[x].next[i]){
				if (x==0) state[state[x].next[i]].fail=0;
				else{
					p=state[x].fail;
					while (p!=-1&&state[p].next[i]) p=state[p].fail;
					if (p!=-1) state[state[x].next[i]].fail=state[p].next[i];
					else state[state[x].next[i]].fail=0;
				}
				Q.push(state[x].next[i]);
			}
		}
	}
	inline void match(char* str){
		int len=strlen(str),now=0;
		int i,p;
		REP(i,len){
			if (state[now].next[str[i]-33]) now=state[now].next[str[i]-33];
			else{
				p=state[now].fail;
				while (p!=-1&&!state[p].next[str[i]-33]) p=state[p].fail;
				if (p==-1) now=0;
				else now=state[p].next[str[i]-33];
			}
			if (state[now].mark) {
				if (ans[0]==state[now].mark||ans[1]==state[now].mark||ans[2]==state[now].mark) continue;
				ans[num++]=state[now].mark;
				if (num==3) return;
			}
		}
	}
}AC;
int T,i,j,n,m,total;
char s[10007];
int main(){
	scanf("%d",&n);
	AC.init();
	REP(i,n){
		gets(s);
		AC.insert(s,i+1);
	}
	AC.buildAC();
	scanf("%d",&m);
	REP(i,m){
		scanf("%s",s);
		num=0;ans[0]=ans[1]=ans[2]=-1;
		AC.match(s);
		if (num==0) continue;
		total++;
		printf("web %d:",i+1);
		sort(ans,ans+num);
		REP(j,num) printf(" %d",ans[j]);
		puts("");
	}
	printf("total: %d\n",total);
}
