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

const int tot=505;
const int maxtot=505*140;
const int charnum=98;
int nxt[maxtot][charnum],fail[maxtot],mark[maxtot];
int cnt;
queue<int> Q;
void init(){
	int i,j;
	while (Q.size()) Q.pop();
	REP(i,maxtot){
		REP(j,charnum) nxt[i][j]=0;
		mark[i]=fail[i]=0;
	}
	cnt=1;
}
inline void insert(char *str,int id){
	int len=strlen(str),now=0,i;
	REP(i,len){
		int k=str[i]-33;
		if (!nxt[now][k]) nxt[now][k]=cnt++;
		now=nxt[now][k];
	}
	mark[now]=id;
}
inline void buildAC(){
	fail[0]=-1;
	Q.push(0);
	int i;
	while (!Q.empty()){
		int x=Q.front();Q.pop();
		REP(i,charnum) if (nxt[x][i]){
			if (x==0) fail[nxt[x][i]]=0;
			else{
				int p=fail[x];
				while (p!=-1&&!nxt[p][i]) p=fail[p];
				if (p!=-1) fail[nxt[x][i]]=nxt[p][i];
				else fail[nxt[x][i]]=0;
			}
			Q.push(nxt[x][i]);
		}
	}
}
inline void match(char *str){
	int len=strlen(str),now=0;
	int i;
	num=0;
	REP(i,tot) ans[i]=0;
	REP(i,len){
		int k=str[i]-33;
		while (now&&!nxt[now][k]) now=fail[now];
		now=nxt[now][k];
		if (now==-1) now=0;
		int tmp=now;
		while (tmp&&!ans[mark[tmp]]){
			if (mark[tmp]){
				ans[mark[tmp]]=1;
				num++;
			}
			tmp=fail[tmp];
			if (num>=3) return;
		}
	}
} 
int T,i,j,n,m,total;
char s[maxn];
int main(){
	while (~scanf("%d",&n)){
		total=0;
		init();
		REP(i,n){
			scanf("%s",s);
			insert(s,i+1);
		}
		buildAC();
		scanf("%d",&m);
		REP(i,m){
			scanf("%s",s);
			match(s);
			if (num==0) continue;
			total++;
			printf("web %d:",i+1);
			REP(j,tot) if (ans[j]) printf(" %d",j);
			puts("");
		}
		printf("total: %d\n",total);
	}
}
