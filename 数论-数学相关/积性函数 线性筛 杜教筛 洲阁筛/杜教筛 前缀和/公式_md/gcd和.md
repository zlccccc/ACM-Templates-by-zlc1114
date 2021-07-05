$ \sum_i \sum_j gcd(i,j)$ 

$= \sum_d d * \sum_i \sum_j [gcd(i,j)=1]$

$= \sum_{d} d * \sum_{k} * \sum_{k|i} * \sum_{k|j} \mu{(k)}$

$= \sum_{d} d * \sum_{k} * \frac{n}{d*k} ^2 * \mu{(k)}$

$ = \sum_{d|t} * \sum_{t} * \frac{n}{t} ^ 2 * d * \mu{(\frac{t}{d})}$

$ = \sum_{t} * \frac{n}{t} ^ 2 * \sum_{d|t} * d * \mu{(\frac{t}{d})}$

$ = \sum_{t} * \frac{n}{t} ^ 2 * \varphi{(t)}$

按照n/t分块

