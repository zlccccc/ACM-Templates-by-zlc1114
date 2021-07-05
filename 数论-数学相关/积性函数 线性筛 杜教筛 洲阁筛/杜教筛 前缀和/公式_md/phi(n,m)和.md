$ \sum_i^n \sum_j^m \varphi(i * j)$         $n \leq 1e5 ; m \leq 1e9$ 

由于$\varphi(n)=n * \prod_{p|n,p是质数} (1-\frac{1}{p})$ 看网上思路得到假设 $t 是 n 的有用的因子乘积$

$ = \sum_i^n \frac{n}{t} * \sum_j^m \varphi(t * j)$

$ = \sum_i^n \frac{n}{t} * \sum_j^m \frac{\varphi(t) * \varphi(j)}{\varphi(gcd(t,j))}$

$ = \sum_i^n \frac{n}{t} * \sum_j^m \varphi(\frac{t}{gcd(t,j)}) * \varphi(j) * gcd(t,j)$

$ = \sum_i^n \frac{n}{t} * \sum_j^m \varphi(\frac{t}{gcd(t,j)}) * \varphi(j) * \sum_{k|gcd(t,j)} \varphi(k)$

接下来有个从网上抄的极其厉害的东西

$ = \sum_i^n \frac{n}{t} * \sum_j^m \varphi(j) * \sum_{k|gcd(t,j)} \varphi(\frac{t * k}{gcd(t,j)})$

直接合并是因为前面和后面是互质的。。这谁能想到

也就是: 当 $\mu(n)^2=1$ 存在 $\varphi(n*k) = \sum_{d|gcd(n,k)} \varphi(d) \varphi(k)$

$ = \sum_i^n \frac{n}{t} * \sum_j^m \varphi(j) * \sum_{k|t, k|j} \varphi(\frac{t}{k})$

let j'=j/k

$ = \sum_i^n \frac{n}{t} * \sum_{k|t} \varphi(\frac{t}{k}) \sum_j^\frac{m}{k} \varphi(k * j)$

定义 $S(t,m) = \sum_j^m \varphi(t * j)$

$S(t,m) =  \sum_{k|t} \varphi(\frac{t}{k}) S(k,\frac{m}{k})$

