#include <iostream>
#include <cstdio>
using namespace std;
int a[1000003];
int b[1000003];
int n,k;
int i;
void fqsort(int l,int r) {//O(n)第k大数
    int le=l,ri=r,m;
    m=a[le];
    while (le<ri) {
        while (le<ri&&a[ri]<=m) ri--; a[le]=a[ri];
        while (le<ri&&a[le]>=m) le++; a[ri]=a[le];
    } if (le==k) printf("%d\n",m);
    else if (le>k) fqsort(l,le-1);
    else fqsort(le+1,r);
}
int main() {
    while (scanf("%d%d",&n,&k)!=EOF) {
        for (i=1; i<=n; i++) {
            scanf("%d",a+i);
            b[i]=i;
        }
        fqsort(1,n);
    }
    return 0;
}
