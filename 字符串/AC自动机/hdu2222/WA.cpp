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
int next[maxtot][26],fail[maxtot],cnt[maxtot];
int size,cnt;
void init(){
	int i;
	REP(i,maxtot){
		memset(next[i],0,sizeof(next[i]));
		cnt[i]=fail[i]=0;
	}
	cnt=1;
}
inline void insert(char* str){
	int len=strlen(str),now=0;
	int i,k;
	REP(i,len){
		k=str[i]-'a';
		if (!next[now][k]) next[now][k]=cnt++;
		now=next[now][k];
	}
	cnt[now]++;
}
inline void buildAC(){
	queue<int> Q;
	Q.push(0);
	int i,u,v;
	while (!Q.empty()){
		u=Q.front();Q.pop();
		cnt[u]+=cnt[fail[u]];
		REP(i,26){
			v=next[u][i];
			if (!v) next[u][i]=next[fail[u]][i];//link一下末尾节点,这样破坏了原有图形,但是time-- 
			else Q.push(v);
			if (u&&v){
				fail[v]=next[fail[u]][i];//由于上面的relink,这里fail[u][i]!=0
			}
		}
	}
}
inline void remark(int u){
	while (u){
		state[u].cnt=0;
		u=state[u].fail;
	}
}
inline int match(char* str){//找子串
	int len=strlen(str),now=0,res=0;
	int i,p,k;
	REP(i,len){
		k=str[i]-'a';
		if (next[now][k]) now=next[now][k];//恒成立? 
		else{
			p=state[now].fail;
			while (p!=-1&&!state[p].next[str[i]-'a']) p=state[p].fail;
			if (p==-1) now=0;
			else now=state[p].next[str[i]-'a'];
		}
		res+=state[now].cnt;
		if (state[now].cnt)	remark(now);
	}
	return res;
}
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
