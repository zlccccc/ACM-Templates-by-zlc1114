$d(i*j)=\sum_{a|i} \sum_{b|j} [gcd(a,b)=1] * a * \frac{j}{b}$ (原因是枚举约数i*(m/j),gcd(i,j)=1不会算重)

$ \sum_i^n \sum_j^n d(i*j)$

$ = \sum_i^n \sum_j^n \sum_{a|i} \sum_{b|j} [gcd(a,b)=1] a * \frac{j}{b}$

let i'=i/a, j'=j/b

$ = \sum_{i'}^{\frac{n}{a}} \sum_{j'}^{\frac{n}{b}} \sum_a \sum_b [gcd(a,b)=1] a * j'$

$ = \sum_a^n \sum_b^n \frac{n}{a} * \frac{\frac{n}{b}*(\frac{n}{b}+1)}{2} * a * [gcd(a,b)=1]$

$ = \sum_{d|gcd(a,b)} \mu(d) \sum_a^n \frac{n}{a} * a * \sum_b^n \frac{\frac{n}{b}*(\frac{n}{b}+1)}{2}$

let i=a/d, j=b/d

$ = \sum_d d * \mu(d) * \sum_i^{\frac{n}{d}} \frac{n}{i * d} * i * \sum_j^{\frac{n}{d}} \frac{\frac{n}{d * j}*(\frac{n}{d * j}+1)}{2}$

结果后面这俩东西是一样的

$ \sum_i^n \frac{\frac{n}{i}*(\frac{n}{i}+1)}2 = \sum_i^n \sum_j^{\frac{n}{i}} j = \sum_j^n \sum_i^{\frac{n}{j}} j = \sum_j^n j*\frac{n}{j}$

$ \sum_i^n i * \frac{n}{i} = \sum_i^n \sigma_1(i)$

