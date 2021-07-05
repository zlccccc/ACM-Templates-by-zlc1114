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

const int maxtot=5e5+7;
struct Aho{
	struct node{
		int next[26];
		int fail,cnt;
	}state[maxtot];
	int size,cnt;
	void init(){
		int i;
		REP(i,maxtot){
			memset(state[i].next,0,sizeof(state[i].next));
			state[i].cnt=state[i].fail=0;
		}
		cnt=1;
	}
	inline void insert(char* str){
		int len=strlen(str),now=0;
		int i;
		REP(i,len){
			if (!state[now].next[str[i]-'a']) state[now].next[str[i]-'a']=cnt++;
			now=state[now].next[str[i]-'a'];
		}
		state[now].cnt++;
	}
	inline void buildAC(){
		state[0].fail=-1;//root
		queue<int> Q;
		Q.push(0);
		int i,x,p;
		while (!Q.empty()){
			x=Q.front();Q.pop();
			REP(i,26) if (state[x].next[i]){
				if (x==0) state[state[x].next[i]].fail=0;
				else {
					p=state[x].fail;
					while (p!=-1&&!state[p].next[i]) p=state[p].fail;
					if (p!=-1) state[state[x].next[i]].fail=state[p].next[i];
					else state[state[x].next[i]].fail=0;
				}
				Q.push(state[x].next[i]);
			}
		}
	}
	inline int cal(int u){
		int res=0;
		while (u!=-1){
			res=res+state[u].cnt;
			state[u].cnt=0;
			u=state[u].fail;
		}
		return res;
	}
	inline int match(char* str){//ÕÒ×Ó´®
		int len=strlen(str),now=0,res=0;
		int i,p;
		REP(i,len){
			if (state[now].next[str[i]-'a']) now=state[now].next[str[i]-'a'];
			else {
				p=state[now].fail;
				while (p!=-1&&!state[p].next[str[i]-'a']) p=state[p].fail; 
				if (p==-1) now=0;
				else now=state[p].next[str[i]-'a'];
			}
//			printf("%3d,",now);
			if (state[now].cnt)	res+=cal(now);
		}
		return res;
	}
}AC;
int T,i,n;
char s[maxn];
int main(){
	scanf("%d",&T);
	while (T--){
		scanf("%d",&n);
		AC.init();
		REP(i,n){
			scanf("%s",s);
			AC.insert(s);
		}
		AC.buildAC();
//		REP(i,20) printf("%2d ",AC.state[i].fail);
//		puts("");
//		REP(i,20) printf("%2d ",AC.state[i].cnt);
//		puts("");
		scanf("%s",s);
		printf("%d\n",AC.match(s));
	}
}
