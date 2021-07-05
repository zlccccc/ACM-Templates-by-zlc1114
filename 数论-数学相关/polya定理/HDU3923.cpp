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
#include <cmath>
#include <ctime>
#include <utility>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b) {T ret=1; for (; b; b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M; return ret;}

//HDU3923; ��ɫm, ����n, ��ת�����û�����һ��
//ans=1/|G|*sigma{pow(k(color),m(not move point ��������))}
//ע��������ʽ
//Burnside����:�ȼ������l=sum{ci(ai)},ci���û��µĲ�������
//���pow�ǿ��Ա仯��������ʽ��
//ע��,polya�����൱���ֶ�����һ��Burnside�����в�����ĸ���!
int n,m;
bool mark[maxn];
int phi[maxn];
int p[maxn],tot;
int main() {
    int i,j;
    phi[1]=1;
    FOR(i,2,1000000) {
        if (!mark[i]) p[tot++]=i,phi[i]=i-1;
        REP(j,tot) {
            if (i*p[j]>1000000) break;
            //�о��ϲ��ᱬ,��Ϊ�Ǵ�С��ɸ��
            mark[i*p[j]]=1;
            if (i%p[j]==0) {phi[i*p[j]]=phi[i]*p[j]; break;}
            else phi[i*p[j]]=phi[i]*(p[j]-1);
        }
    }
    int t,T;
    scanf("%d",&T);
    FOR(t,1,T) {
        scanf("%d%d",&m,&n);
        LL all=0,cnt=0;
        // FOR(i,1,n){
        //     (all+=powMM((LL)m,gcd(n,i)))%=M;
        //     (all<0)&&(all+=M);
        // }cnt=n;
        //�û�
        FOR(i,1,n) if (n%i==0) {
            (all+=(LL)powMM(m,i)*phi[n/i])%=M;
            (all<0) &&(all+=M);
        }
        cnt=n;
        //��ת
        if (n&1) {
            (all+=(LL)n*powMM(m,(n+1)/2))%=M;
            cnt+=n;
        } else {
            (all+=(LL)n/2*powMM(m,n/2))%=M;
            (all+=(LL)n/2*powMM(m,n/2+1))%=M;
            cnt+=n;
        }
//        printf("%lld %lld\n",cnt,all);
        all=all*powMM(cnt,M-2)%M;
        printf("Case #%d: %lld\n",t,all);
    }
}
/*
    100
    3 4
    100 56
    2 3
    4 6
    8 9
    1 2
*/
