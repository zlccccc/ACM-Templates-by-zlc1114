#include <cmath>
#include <cstdio>
typedef long long LL;
const int maxn = 1000001, mod = 1000000009, inv2 = 500000005;
int f[maxn];
int s(LL n)
{
    int res = 0;
    for(LL i = 1, j; i <= n; i = j + 1)
    {
        j = n / (n / i);
        res = (res + n / i % mod * ((j - i + 1) % mod) % mod * ((i + j) % mod)) % mod;
    }
    res = (LL)res * inv2 % mod;
    return res;
}
int main()
{
    f[1] = 1;
    for(int i = 1; i < maxn; ++i)
    {
        for(int j = i + i; j < maxn; j += i)
            f[j] -= f[i];
        f[i] *= i;
    }
    for(LL n; scanf("%lld", &n) == 1; )
    {
        int ans = 0, lim = (int)ceil(sqrt(n));
        for(int i = 1; i <= lim; ++i)
            if(f[i])
                ans = (ans + (LL)f[i] * s(n / i / i)) % mod;
        if(ans < 0)
            ans += mod;
        printf("%d\n", ans);
    }
    return 0;
}