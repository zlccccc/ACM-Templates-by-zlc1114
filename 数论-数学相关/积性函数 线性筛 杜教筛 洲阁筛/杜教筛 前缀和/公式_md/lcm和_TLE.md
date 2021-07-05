$  \sum_{i} \sum_{j} lcm(i,j)$
$= \sum_{d} \sum_{i}^{n/d} \sum_{j}^{n/d} [gcd(i,j)=1] * i * j * d$

$ = \sum_{d} * \sum_{k} \sum_{i}^{\frac{n}{d*k}} \sum_{j}^{\frac{n}{d*k}} \mu{(k)} * i * j * k^2 * d$

let t=d*k

$ = \sum_{d|t} * \sum_t * {(\frac{n}{t} *  (\frac{n}{t} +1))}^2 / 4 * \mu(k) * k * t$

$ = \sum_t * {(\frac{n}{t} *  (\frac{n}{t} +1))}^2 / 4 * t * \sum_{k|t} * \mu(k) * k$

$ = \sum_{d}^{\frac{n}{k}} * {(\frac{n}{k * d} *  (\frac{n}{k * d} +1))}^2 / 4 * d * \sum_{k} * \mu(k) * k^2$

枚举d，对前半部分分块计算

考虑后半部分计算

$F(t)=\sum_{k|t} * \mu(k) * k^2$

$1 = \sum_{n} \sum_{k|n} \mu(k) * k^2 * \frac{n}{k}^2$

let i=n/k

$= \sum_{i} i^2 \sum_{k}^{\frac{n}{i}} \mu{(k)} * k^2$

$ F(n) = 1 - \sum{i^2*F(n/i)}$


