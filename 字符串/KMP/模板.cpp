#include <bits/stdc++.h>
using namespace std;

vector<int> getfail(string &str) {  // 返回长度n+1
    int n=str.length();
    vector<int> fail(n+1);
    fail[0]=fail[1]=0;
    int j;
    for (int i=2;i<=n;i++){
        j=fail[i-1];
        while (j&&str[j]!=str[i-1]) j=fail[j];
        if (str[j]==str[i-1]) fail[i]=j+1;
        else fail[i]=0;
    }
    return fail;
}
