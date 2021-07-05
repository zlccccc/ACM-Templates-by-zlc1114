#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <stack>
#include <queue>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
const LL INF=1000000000;
const LL INFF=0x1f3f3f3f3f3f3f3fll;
inline LL powMM(LL a,LL b){
    LL ret=1;
    while (b){
        if (b&1) ret=ret*a%M;
        a=a*a%M;
        b>>=1;
    }
    return ret;
}

vector<int> pos[maxn];
struct AC{
	int nxt[maxn][26];
	int len[maxn];
	int cnt;
	int fail[maxn];
	void init(){
		cnt=0;
		memset(nxt,0,sizeof(nxt));
		memset(len,0,sizeof(len));
		memset(fail,0,sizeof(fail));
	}
	void insert(string a,int x){
		int leng=a.length(),now=0,i;
		REP(i,leng){
			int k=a[i]-'a';
			if (!nxt[now][k]) nxt[now][k]=++cnt;
			now=nxt[now][k];
			pos[x][i]=now;
			len[now]=i+1;
		}
	}
	queue<int> Q;
	void buildAC(){
		fail[0]=-1;
		Q.push(0);
		int i;
		while (!Q.empty()){
			int x=Q.front();Q.pop();
			REP(i,26) if (nxt[x][i]){
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
	void clear(){
		int i;
		FOR(i,0,cnt){
			memset(nxt[i],0,sizeof(nxt[i]));
			fail[i]=len[i]=0;
		}
		cnt=0;
	}
}AC;
struct SAM{
	int nxt[maxn][26],pre[maxn],len[maxn];
	int cnt,last;
	void init(){
		cnt=last=0;
		memset(nxt,0,sizeof(nxt));
		memset(pre,0,sizeof(pre));
		memset(len,0,sizeof(len));
	}
	void add(int c){
		int np=++cnt,p=last;
		len[np]=len[p]+1;
		for (;p&&!nxt[p][c];p=pre[p]) nxt[p][c]=np;
		if (!p) pre[np]=1;
		else{
			int q=nxt[p][c];
			if (len[p]+1==len[q]) pre[np]=q;
			else{
				int nq=++cnt;len[nq]=len[p]+1;
				memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
				pre[nq]=pre[q];
				pre[np]=pre[q]=nq;
				for (;p&&nxt[p][c]==q;p=pre[p]) nxt[p][c]=nq;
			}
		}
		last=np;
	}
	void clear(){
		int i;
		FOR(i,0,cnt){
			memset(nxt[i],0,sizeof(nxt[i]));
			pre[i]=len[i]=0;
		}
		cnt=0;last=0;
	}
}SAM;
int n,m;
int i,j,k;
string a[maxn];

int main(){
	int T;
	AC.init();
	SAM.init();
	scanf("%d",&T);
	while (T--){
		scanf("%d",&n);
		FOR(i,1,n){
			cin>>a[i];
			pos[i].resize(a[i].size());
			AC.insert(a[i],i);
		}
		AC.buildAC();
		scanf("%d",&m);
//		FOR(i,1,n){
//			REP(j,a[i].length()){
//				printf("%d:",pos[i][j]);
//				for (k=pos[i][j];k!=0;k=AC.fail[k]) printf("%d,",AC.len[k]);
//				putchar(' ');
//			}
//			puts("");
//		}
		REP(i,m){
			int x,y,i,ans=0;
			scanf("%d%d",&x,&y);
			int len=a[x].length();
			SAM.last=++SAM.cnt;
			REP(i,len) SAM.add(a[x][i]-'a');
			len=a[y].length();
			int now=1,nowlen=0;
			REP(i,len){
				while (now&&!SAM.nxt[now][a[y][i]-'a']) now=SAM.pre[now],nowlen=SAM.len[now];
//				printf("%d %d\n",i,now);
				if (!now) now=1,nowlen=0;
				if (SAM.nxt[now][a[y][i]-'a']){
					now=SAM.nxt[now][a[y][i]-'a'];
					nowlen++;
				}
				for (k=pos[y][i];k!=0;k=AC.fail[k]) if (AC.len[k]<=nowlen) break;
//				printf("%d %d\n",nowlen,AC.len[k]);
				ans=max(ans,AC.len[k]);
			}
			printf("%d\n",ans);
			SAM.clear();
		}
		FOR(i,1,n) vector<int>().swap(pos[i]);
		AC.clear();
	}
}
/*
*/

