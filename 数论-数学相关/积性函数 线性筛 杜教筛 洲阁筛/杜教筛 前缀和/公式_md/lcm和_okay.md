$  \sum_{i} \sum_{j} lcm(i,j)$

$= 2* \sum_{i} \sum_{j}^{i} \frac{i * j}{gcd(i,j)} - \frac{n * (n+1)}{2}$

$= 2 * \sum_{i} i* \sum_{j}^{i} \sum_{d|gcd(i,j)} [gcd(\frac{i}{d},\frac{j}{d})=1] * \frac{j}{d} - \frac{n * (n+1)}{2}$

$ = 2 * \sum_{i} i* \sum_{d|i} \sum_{j}^{\frac{i}{d}}  [gcd(\frac{i}{d},j)=1] * j - \frac{n * (n+1)}{2}$

let d=i/d

$ = 2 * \sum_{i} i * \sum_{d|i} \frac{d * \varphi(d) + [d==1]}{2} - \frac{n * (n+1)}{2} $

$ = \sum_{i} i * \sum_{d|i} d * \varphi(d)$

let i'=i/d

$ = \sum_{i'} i' * \sum_{t}^{\frac{n}{i}} * t * t * \varphi(t) $

考虑后半部分计算

$F(t)=\sum_{k|t} * \varphi(k) * k^2$

$ \frac{n * (n+1) * n * (n+1)}{4} = \sum_{n} \sum_{k|n} \varphi(k) * k^2 * \frac{n}{k}^2$

let i=n/k

$= \sum_{i} i^2 \sum_{k}^{\frac{n}{i}} \varphi{(k)} * k^2$

$ F(n) = \frac{n * (n+1) * n * (n+1)}{4} - \sum{i^2 * F(n/i)}$

