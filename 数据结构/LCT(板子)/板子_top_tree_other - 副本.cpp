#include<bits/stdc++.h>
using namespace std;
#define inline inline
#define gc getchar()
#define pc putchar
inline int in(){
	int x = 0,y = 0,c = gc;
	while(!isdigit(c)) y = c,c = gc;
	while(isdigit(c)) x = (x << 1) + (x << 3) + (c ^ '0'),c = gc;
	return y == '-' ? -x : x;
}
inline void out(int q){
	if(q < 0) pc('-'),q = -q;
	if(q >= 10) out(q / 10);
	pc(q % 10 + '0');
}
int n,m,rt,val[100010];
struct ed{
	int f,t;
}e[200010];
struct info{
	int mx,mn,sm,sz;
	info(int _mx = 0,int _mn = 0,int _sm = 0,int _sz = 0){
		mx = _mx;mn = _mn;sm = _sm;sz = _sz;
	}
};
struct tag{
	int mul,add;
	tag(int _mul = 1,int _add = 0){
		mul = _mul;add = _add;
	}
	bool emp(){return mul == 1 && add == 0;}
};
info operator + (info u,tag v){
	return !u.sz ? u : info(u.mx * v.mul + v.add,u.mn * v.mul + v.add,u.sm * v.mul + v.add * u.sz,u.sz);
}
info operator + (info u,info v){
	return info(max(u.mx,v.mx),min(u.mn,v.mn),u.sm + v.sm,u.sz + v.sz);
}
tag operator + (tag u,tag v){
	return tag(u.mul * v.mul,u.add * v.mul + v.add);
}
#define l(x) t[x].c[0]
#define r(x) t[x].c[1]
#define xl(x) t[x].c[2]
#define xr(x) t[x].c[3]
#define f(x) t[x].f
#define s(x,y) t[x].c[y]
#define ll(x) t[x].c[tp]
#define rr(x) t[x].c[tp + 1]
struct node{
	int f,c[4],val;
	tag stag,xtag;
	info shi,xu,all;
	bool rev,isx;
}t[2000010];
int cnt,ft,bin[2000010];
inline void rv(int q){
	t[q].rev ^= 1;swap(l(q),r(q));
}
inline void tagshi(int q,tag w){
	t[q].stag = t[q].stag + w;t[q].shi = t[q].shi + w;t[q].val = t[q].val * w.mul + w.add;
	t[q].all = t[q].shi + t[q].xu;
}
inline void tagxu(int q,tag w,bool fg = 1){
	t[q].xtag = t[q].xtag + w;t[q].all = t[q].all + w;t[q].xu = t[q].xu + w;
	if(fg) tagshi(q,w);
}
inline void pushup(int q){
	t[q].shi = t[q].xu = t[q].all = info(-(1 << 30),1 << 30,0,0);
	if(!t[q].isx) t[q].all = t[q].shi = info(t[q].val,t[q].val,t[q].val,1);
	for(int i = 0;i < 2;++i) if(s(q,i)) t[q].shi = t[q].shi + t[s(q,i)].shi,t[q].xu = t[q].xu + t[s(q,i)].xu;
	for(int i = 0;i < 4;++i) if(s(q,i)) t[q].all = t[q].all + t[s(q,i)].all;
	for(int i = 2;i < 4;++i) if(s(q,i)) t[q].xu = t[q].xu + t[s(q,i)].all;
}
inline void pushdown(int q){
	if(t[q].rev){
		if(l(q)) rv(l(q));
		if(r(q)) rv(r(q));
		t[q].rev = 0;
	}
	if(!t[q].xtag.emp()){
		for(int i = 0;i < 4;++i) if(s(q,i)) tagxu(s(q,i),t[q].xtag,i >= 2);
		t[q].xtag = tag(1,0);
	}
	if(!t[q].stag.emp()){
		for(int i = 0;i < 2;++i) if(s(q,i)) tagshi(s(q,i),t[q].stag);
		t[q].stag = tag(1,0);
	}
}
inline int son(int q,int x){
	if(s(q,x)) pushdown(s(q,x));
	return s(q,x);
}
inline int fd(int q){
	for(int i = 0;i < 4;++i) if(s(f(q),i) == q) return i;
	return -1;
}
inline void sets(int q,int w,int tp){
	if(w) f(w) = q;
	s(q,tp) = w;
}
inline bool is(int q,int tp = 0){
	if(!tp) return !f(q) || (l(f(q)) != q && r(f(q)) != q);
	return !f(q) || !t[q].isx || !t[f(q)].isx;
}
void ro(int q,int tp){
	if(is(q,tp)) return;
	int p = f(q);
	if(f(p)) sets(f(p),q,fd(p));
	else f(q) = 0;
	f(p) = q;
	if(ll(p) == q){
		ll(p) = rr(q);
		rr(q) = p;
		if(ll(p)) f(ll(p)) = p;
	}
	else{
		rr(p) = ll(q);
		ll(q) = p;
		if(rr(p)) f(rr(p)) = p;
	}
	pushup(p);pushup(q);
}
inline void gx(int q){
	if(f(q)) gx(f(q));
	pushdown(q); 
}
void sp(int q,int tp = 0){
	pushup(q);
	while(!is(q,tp)){
		int p = f(q);
		if(is(p,tp)) ro(q,tp);
		else{
			if((ll(f(p)) == p) ^ (ll(p) == q)) ro(q,tp);
			else ro(p,tp);
			ro(q,tp);
		}
	}
}
inline int newd(){
	int q = ft ? bin[ft--] : ++cnt;
	for(int i = 0;i < 4;++i) s(q,i) = 0;f(q) = 0;
	t[q].stag = t[q].xtag = tag(1,0);
	t[q].shi = t[q].xu = t[q].all = info(-(1 << 30),1 << 30,0,0);
	t[q].isx = 1;t[q].rev = t[q].val = 0;
	return q;
}
inline void deld(int q){bin[++ft] = q;}
void ad(int q,int w){
	for(int i = 2;i < 4;++i) if(!s(w,i)){
		sets(w,q,i);return;
	}
	int p = newd(),u;
	for(u = w;t[xl(u)].isx;u = son(u,2));
	sets(p,xl(u),2);sets(p,q,3);sets(u,p,2);sp(p,2);
}
void del(int q){
	if(t[f(q)].isx){
		sets(f(f(q)),s(f(q),5 - fd(q)),fd(f(q)));
		deld(f(q));sp(f(f(q)),2);
	}
	else sets(f(q),0,fd(q));
	f(q) = 0;
}
void ac(int q){
	int u;
	gx(q);sp(q);
	if(r(q)){
		u = r(q);r(q) = 0;ad(u,q);pushup(q);
	} 
	while(f(q)){
		for(u = f(q);t[u].isx;u = f(u));
		sp(u);
		if(r(u)){
			sets(f(q),r(u),fd(q));sp(f(q),2);
		}
		else del(q);
		sets(u,q,1);
		pushup(u);q = u;
	}
}
inline void mk(int q){
	ac(q);sp(q);rv(q);
}
inline int getf(int q){
	ac(q);sp(q);q = son(q,0);
	while(q && r(q)) q = son(q,1);
	return q;
}
inline int getr(int q){
	while(f(q)) q = f(q);
	return q;
}
int ct(int q){
	int p = getf(q);
	if(p){
		ac(p);sp(p);del(q);pushup(p);
	}
	return p;
}
void lk(int q,int w){
	int p = ct(q);	
	if(getr(q) != getr(w)) p = w;
	if(p){
		ac(p);sp(p);ad(q,p);pushup(p);
	}
}
int main(){
	int i,j,op,u,v,w;
	n = in();m = in();rt = 1;
	for(i = 1;i < n;++i){
		e[i].f = in();e[i].t = in();
	}
	for(i = 1;i <= n;++i){
		t[++cnt].val = in();pushup(cnt);
	}
	for(i = 1;i < n;++i){
		mk(e[i].f);mk(e[i].t);lk(e[i].f,e[i].t);
	}
	rt = in();mk(rt);
	for(i = 1;i <= m;++i){
		op = in();u = in();
		if(op == 1){
			mk(u);rt = u;
		}
		else if(op == 9){
			v = in();
			lk(u,v);
		}
		else if(op == 0 || op == 3 || op == 4 || op == 5 || op == 11){
			ac(u);sp(u);
			if(op == 3 || op == 4 || op == 11){
				int as = t[u].val;
				for(j = 2;j < 4;++j) if(s(u,j)){
					info p = t[s(u,j)].all;
					if(op == 3) as = min(as,p.mn);
					else if(op == 4) as = max(as,p.mx);
					else as += p.sm;
				}
				out(as);pc('\n');
			}
			else{
				w = in();
				tag p = tag(op == 5,w);
				t[u].val = t[u].val * p.mul + p.add;
				for(int j = 2;j < 4;++j) if(s(u,j)) tagxu(s(u,j),p);
				pushup(u);
			}
		}
		else{
			v = in();
			mk(u);ac(v);sp(u);
			if(op == 7 || op == 8 || op == 10){
				info as = t[u].shi;
				out(op == 7 ? as.mn : op == 8 ? as.mx : as.sm);pc('\n'); 
			}
			else{
				w = in();
				tagshi(u,tag(op == 6,w));
			}
			mk(rt);
		}
	}
	return 0;
}