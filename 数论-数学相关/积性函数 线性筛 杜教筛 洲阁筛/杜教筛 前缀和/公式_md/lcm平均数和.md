$ \sum_k \sum_i \frac{i}{gcd(i,k)}$ 

$ = \sum_{k} \sum_{d|gcd(i,k)} \sum_{i} \frac{i}{d} [gcd(i,k)=d]$

let i'=i/d

$ = \sum_{k} \sum_{d|k} \sum_{i'}^{\frac{k}{d}} i' [gcd(i',\frac{k}{d})=1]$

let d'=k/d

$ = \sum_{k} \sum_{d'|k} \frac{d'*\varphi(d')+[d'==1]}{2}$

$ = \frac{n + \sum_{k} \sum_{d|k} d * \varphi(d)}{2}$

$ = \frac{n + \sum_{k} \sum_{d|k} \frac{k}{d} * \varphi(\frac{k}{d})}{2}$

let d'=k/d

$ = \frac{n + \sum_{k} \sum_{d'}^{\frac{n}{k}} d' * \varphi(d')}{2}$

