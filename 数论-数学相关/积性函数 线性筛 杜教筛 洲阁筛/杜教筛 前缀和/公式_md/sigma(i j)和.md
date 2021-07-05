$ \sum_i^n \sum_j^n \sigma(i*j)$

$= \sum_i^n \sum_j^n \sum_{a|i} \sum_{b|j} [gcd(a,b)=1]$

$ = \sum_a^n \sum_b^n \frac{n}{a} \frac{n}{b} [gcd(a,b)=1]$

$ =  \sum_a^n \sum_b^n \sum_{d|gcd(a,b)} \mu(d) \frac{n}{a} \frac{n}{b}$

let i=a/d j=b/d

$= \sum_d^n \mu(d) \sum_i^{\frac{n}{d}} \frac{n}{i*d} \sum_j^{\frac{n}{d}} \frac{n}{j*d}$

前面那个东西可以直接分块算

后面那个东西也可以直接分块算...

$ \sum_i^n \frac{n}{i} = \sum_i^n \sigma(i)$

第一个公式中，

$\sigma(n*m)=\sum_{i|n} \sum_{j|m} [gcd(i,j)=1]$ (原因是枚举约数i*(m/j),gcd(i,j)=1不会算重)

$\mu$ 前缀和杜教筛出来，请看tls博客