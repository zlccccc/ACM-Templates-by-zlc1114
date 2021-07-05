$ \sum_i^n \sum_j^m lcm(i,j)$

$ = \sum_i^n \sum_j^m \sum_d \frac{i * j}{d} [gcd(i,j)=d]$

$ = \sum_{d} \sum_i^{\frac{n}{d}} \sum_j^{\frac{m}{d}} i * j * d [gcd(i,j)=1]$

$ = \sum_d d * \sum_i^{\frac{n}{d}} \sum_j^{\frac{m}{d}} \sum_{k|gcd(i,j)} i * j * \mu(k)$

$ = \sum_d d * \sum_k *  \sum_i^{\frac{n}{d * k}} \sum_j^{\frac{m}{d * k}} i * j * \mu(k) * k^2$ 

let d'=d*k

$ = \sum_{d'} * d' * \sum_{k|d'} k * \mu(k) * \sum_i^{\frac{n}{d'}} \sum_j^{\frac{m}{d'}} i * j$

$ = \sum_d * d * \frac{\frac{n}{d} * (\frac{n}{d}+1) * \frac{m}{d} * (\frac{m}{d}+1)}{4} * \sum_{k|d'} k * \mu(k)$

let t=d/k

$ = \sum_t^{\frac{min(n,m)}{k}} * \frac{\frac{n}{t * k} * (\frac{n}{t * k}+1) * \frac{m}{t * k} * (\frac{m}{t * k}+1)}{4} * \sum_k k * \mu(k)$

