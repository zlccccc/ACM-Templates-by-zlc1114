#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=100007;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}
 
int wa[maxn],wb[maxn],wv[maxn],ws1[maxn];
int cmp(int *r,int a,int b,int l){
	return r[a]==r[b]&&r[a+l]==r[b+l];
}
//sa->pos(后缀排名->pos)
void da(int *r,int *sa,int n,int m){
	r[n++]=0;//使rnk从1开始(sa[0]=n)
	int i,j,p,*x=wa,*y=wb,*t;
	REP(i,m) ws1[i]=0;//pre-cmp
	REP(i,n) ws1[x[i]=r[i]]++;//r->x
	rep(i,1,m) ws1[i]+=ws1[i-1];
	rREP(i,n) sa[--ws1[x[i]]]=i;//sort(计数排序)
	for (j=1,p=1;p<n;j<<=1,m=p){//j->2^x
		p=0;rep(i,n-j,n) y[p++]=i;//最后j个是不用加(显然) 
		REP(i,n) if (sa[i]>=j) y[p++]=sa[i]-j;//后缀顺序
		REP(i,n) wv[i]=x[y[i]];//x+y->wv(由于后缀顺序)
		REP(i,m) ws1[i]=0;
		REP(i,n) ws1[wv[i]]++;
		rep(i,1,m) ws1[i]+=ws1[i-1];
		rREP(i,n) sa[--ws1[wv[i]]]=y[i];//sort(计数排序)
		t=x,x=y,y=t;
		p=1;x[sa[0]]=0;
		rep(i,1,n) x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
}
int rnk[maxn],height[maxn];
void calheight(int *r,int *sa,int n){
	int i,j,k=0;
	FOR(i,1,n) rnk[sa[i]]=i;
	REP(i,n){//线性按照从前往后找,充分利用性质 
		if (k) k--;
		j=sa[rnk[i]-1];
		while (r[i+k]==r[j+k]) k++;
		height[rnk[i]]=k;
	}
}
char a[maxn],b[maxn],c[maxn],d[maxn];
int sa[maxn],r[maxn];
int limit[maxn];
int i,j,k;
int n,m,tt,t,ans;
int main()
{
	while (~scanf("%s%s%s",&a,&b,&d)){
		n=strlen(a);
		m=strlen(b);
		tt=strlen(d);
		t=0;
		REP(i,n) c[t++]=a[i];
		c[t++]='z'+1;
		REP(i,tt) c[t++]=d[i];
		REP(i,t) r[i]=c[i];
		da(r,sa,t,200);
		calheight(r,sa,t);
		REP(i,n+m+1) limit[i]=INF;
	//	FOR(i,1,n+tt+1) printf("%s    %d %d\n",&c[sa[i]],sa[i],height[i]);
		k=rnk[n+1];
		while (k>=0&&height[k]>=tt) {limit[sa[k]]=tt-1;k--;}
		k=rnk[n+1]+1;
		while (k<t&&height[k]>=tt) {limit[sa[k]]=tt-1;k++;}
	//	puts("");
	//	REP(i,n+tt+1) printf("%d ",rnk[i]); puts("");
	//	REP(i,n+tt+1) printf("%d ",limit[i]);
		rep(i,n+1,n+m+1) limit[i]=INF;
		
		t=0;
		REP(i,n) c[t++]=a[i];
		c[t++]='z'+1;
		REP(i,m) c[t++]=b[i];
		REP(i,t) r[i]=c[i];
	//REP(i,t) printf("%c",r[i]+'a'-1);
		da(r,sa,t,150);
		calheight(r,sa,n+m+1);
	//	FOR(i,1,n) printf("%d\n",sa[i]);
		ans=0;
		rep(i,1,n+m+1)
			if ((sa[i]<n)^(sa[i-1]<n)) ans=max(ans,min(min(limit[sa[i]],limit[sa[i-1]]),height[i])); 
	//	FOR(i,1,n+m+1) printf("%s    %d %d\n",&c[sa[i]],sa[i],height[i]);
		printf("%d\n",ans);
	}
}
