#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
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
const LL maxn=3e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

//p是每个点为中心的延伸最长回文子串长度，-1就是原串以这个点为中心的长度
//看到题先去想这种方法，再说其他方法
int n,m;
char s[maxn],str[maxn];
int len1,len2,p[maxn],ans;
void init() {
    ans=0; int i;
    str[0]='+'; str[1]='%';
    REP(i,len1+1) {
        str[i*2+2]=s[i];
        str[i*2+3]='%';
    } len2=len1*2+2;
}
// 主要是说已经对称匹配过的不用再进行
void manacher() {
    int id=0,mx=0; int i;
    FOR(i,1,len2-1) {
        if (mx>i) p[i]=min(p[2*id-i],mx-i);
        else p[i]=1;
        while (str[i+p[i]]==str[i-p[i]]) p[i]++;
        if (p[i]+i>mx) {
            mx=p[i]+i; id=i;
        }
    }
}
int main() {
    int i;
    while (~scanf("%s",s)) {
        len1=strlen(s);
        init();
        manacher();
        REP(i,len2) ans=max(ans,p[i]);
        printf("%d\n",ans-1);
    }
}
