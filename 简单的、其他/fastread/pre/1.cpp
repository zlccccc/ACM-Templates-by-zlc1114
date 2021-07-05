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

int n,m;
char s[maxn],str[maxn];
int len1,len2,p[maxn],ans;
template<class T>
bool read_d(T &num) {
    char in; bool IsN=false;
    in=getchar();
    if (in==EOF) return false;
    while (in!= '-'&&(in<'0'||in>'9')) in=getchar();
    if (in=='-') {IsN=1; num=0;}
    else num=in-'0';
    while (in=getchar(),in>='0'&&in<='9')
        num=num*10+in-'0';
    if (IsN) num=-num;
    return 1;
}
template<class T>
bool read_f(T &num) {
    char in; bool IsN=false,IsD=false;
    T Dec=0.1;
    in=getchar();
    if (in==EOF) return false;
    while (in!='-'&&in!='.'&&(in<'0'||in>'9'))
        in=getchar();
    if (in=='-') {IsN=1; num=0;}
    else if (in=='.') {IsD=1; num=0;}
    else num=in-'0';
    if (!IsD) while (in=getchar(),in>='0'&&in<='9')
            num=num*10+in-'0';
    if (in=='.') while (in=getchar(),in>='0'&&in<='9')
        {num+=Dec*(in-'0'); Dec*=0.1;}
    if (IsN) num=-num;
    return 1;
}
LL d;
double c;
int main() {
    int i;
    while (read_f(c)) {
        printf("%lf\n",c);
    }
}
/*
54623.654
*/
