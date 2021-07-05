$ \sum_i \sum_j [lcm(i,j) \leq n]$

$ = \sum_i \sum_j \sum_t [\frac{i*j}{t} \leq n] [gcd(i,j)=t]$   

$ = \sum_i \sum_j \sum_{t|gcd(i,j)} [\frac{i*j}{t} \leq n] [gcd(\frac{i}{t},\frac{j}{t})=1]$

let i'=i/t, j'=j/t

$ = \sum_t \sum_{i'} \sum_{j'} [i' * j' * t\leq n] [gcd(i',j')=1]$

$ = \sum_t \sum_{i'} \sum_{j'} \sum_{p|gcd(i,j)} \mu(p) *[i' * j' \leq \frac{n}{t}]$

let i=i'/p, j=j'/p

$ = \sum_t \sum_p \mu(p) \sum_i \sum_j *[i * j * p ^2\leq \frac{n}{t}]$

$ = \sum_p \mu(p) * \sum_t \sum_i \sum_j [i * j * t \leq \frac{n}{p^2}]$

i*j<=n/t可以直接筛出来，前面是个mu前缀和(tle)

直接考虑i<=j<=t，分开计算即可