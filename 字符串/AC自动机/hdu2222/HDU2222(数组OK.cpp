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

const int maxtot=50*10007;
const int charnum=26;
int nxt[maxtot][charnum],fail[maxtot],num[maxtot];
int cnt;
queue<int> Q;
void init(){
	int i,j;
	while (Q.size()) Q.pop();
	REP(i,maxtot) {
		REP(j,charnum) nxt[i][j]=0;
		num[i]=fail[i]=0;
	}
	cnt=1;
}
inline void insert(char *str){
	int len=strlen(str),now=0,i;
	REP(i,len){
		int k=str[i]-'a';
		if (!nxt[now][k]) nxt[now][k]=cnt++;
		now=nxt[now][k];
	}
	num[now]++;
}
inline void buildAC(){
	fail[0]=-1;
	Q.push(0);
	int i;
	while (Q.size()){
		int x=Q.front();Q.pop();
		REP(i,charnum) if (nxt[x][i]){
			if (x==0) fail[nxt[x][i]]=0;
			else {
				int p=fail[x];
				while (p!=-1&&!nxt[p][i]) p=fail[p];//注意这里是nxt[p][i]
				if (p!=-1) fail[nxt[x][i]]=nxt[p][i];
				else fail[nxt[x][i]]=0;
			}
			Q.push(nxt[x][i]);
		}
	}
}
inline int match(char *str){
	int len=strlen(str),now=0;
	int i,ret=0;
	REP(i,len){
		int k=str[i]-'a';
		while (now&&!nxt[now][k]) now=fail[now];
		now=nxt[now][k];
		if (now==-1) now=0;
		int tmp=now;
		while (tmp){
			if (num[tmp]==-1) break;//vis
			ret+=num[tmp];
			num[tmp]=-1;
			tmp=fail[tmp];
		}
	}
	return ret;
}
int T,i,n;
char s[maxn];
int main(){
	scanf("%d",&T);
	while (T--){
		scanf("%d",&n);
		init();
		REP(i,n){
			scanf("%s",s);
			insert(s);
		}
		buildAC();
//		REP(i,20) printf("%2d ",fail[i]);
//		puts("");
//		REP(i,20) printf("%2d ",num[i]);
//		puts("");
		scanf("%s",s);
		printf("%d\n",match(s));
	}
}
