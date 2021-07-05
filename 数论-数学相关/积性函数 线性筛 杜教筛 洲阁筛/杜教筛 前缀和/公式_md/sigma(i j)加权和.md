$\sum_i^n \sum_j^n max(i,j)*\sigma_1(i * j)$

$ = \sum_i^n \sum_j^n max(i,j) * \sum_{a|i} \sum_{b|j} a * \frac{j}{b} [gcd(a,b)=1]$

不妨设j<=i

$= 2*\sum_i^n \sum_j^i i * \sum_{a|i} \sum_{b|j} a * \frac{j}{b} [gcd(a,b)=1] - \sum_i^n i * \sum_{a|i} \sum_{b|i} a * \frac{i}{b} [gcd(a,b)=1]$

先算前半部分

$ \sum_i^n \sum_j^i i * \sum_{a|i} \sum_{b|j} a * \frac{j}{b} [gcd(a,b)=1]$

$ = \sum_{k|gcd(a,b)} \mu(k)  *\sum_i^n \sum_j^i i * \sum_{a|i} \sum_{b|j} a * \frac{j}{b}$

$ = \sum_k \mu(k) * k^2 *\sum_i^{\frac{n}{k}} i * \sum_j^i \sum_{a|i} \sum_{b|j} a * \frac{j}{b}$

$ = \sum_k \mu(k) * k^2 *\sum_i^{\frac{n}{k}} i * \sum_{a|i} a * \sum_j^i \sum_{b|j} * \frac{j}{b}$

只需要线性筛出 $\sigma_1$ 前缀和就行了

然后。。他要求query O(1)

let t=k*i 设后面是f

$ = \sum_k \mu(k) * k^2 *\sum_i^{\frac{n}{k}} f(i)$

$ = \sum_t \sum_{k|t} \mu(k) * k^2 * f(\frac{t}{k})$

算后半部分

$ = \sum_i^n i * \sum_{k|gcd(a,b)} \mu(k) \sum_{a|i} \sum_{b|i} a * \frac{i}{b}$

$ =\sum_t \mu(t) * t^2 * \sum_i^\frac{n}{t} i * \sum_{a|i} \sum_{b|i} a * \frac{i}{b}$

后面俩 $\sigma_1$

let k=t*i 设后面是g

$ =\sum_t \mu(t) * t^2 * \sum_i^\frac{n}{t} g(i)$

$ = \sum_k \sum_{t|k} \mu(t) * t^2 * g(\frac{k}{t})$

