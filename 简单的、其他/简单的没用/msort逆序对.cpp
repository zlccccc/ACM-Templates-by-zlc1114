#include <iostream>
#include <cstdio>
using namespace std;
typedef long long LL;
int a[1000003];
int b[1000003];
int n,i,j,k;
LL ans;
void msort(int le,int ri) {//逆序对
    if (le==ri) return;
    int mid=(le+ri)>>1,i=le,j=mid+1,k=i;
    msort(le,mid); msort(j,ri);
    while (i<=mid||j<=ri) {
        if (i==mid+1) {b[k++]=a[j++]; ans+=mid-i+1;}
        else if (j==ri+1) b[k++]=a[i++];
        else if (a[i]<=a[j]) b[k++]=a[i++];
        else {b[k++]=a[j++]; ans+=mid-i+1;}
    }
    for (i=le; i<=ri; i++) a[i]=b[i];
}
int main() {
    while (~scanf("%d",&n)&&n) {
        ans=0;
        for (i=0; i<n; i++) scanf("%d",a+i);
        msort(0,n-1);
        printf("%I64d\n",ans);
    }
    return 0;
}
