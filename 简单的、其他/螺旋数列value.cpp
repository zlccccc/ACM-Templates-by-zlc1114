
//123
//894
//765
inline ll getValue(ll n,ll x,ll y) {
	//n*n-x-y
	ll r = 0;
	x=n-x+1; y=n-y+1;
	if (x<=y && x+y <= n+1) {
		r = x;
		return  4*(r-1)*n - 4*(r-1)*(r-1) +1 + y-r;
	}
	if (x<=y && x+y >= n+1) {
		r = n- y + 1;
		return 4*(r-1)*n - 4*(r-1)*(r-1) + 1 + n-2*r + 1 + x - r;
	}
	if (x>=y && x+y >= n+1) {
		r = n - x +1;
		return 4*(r-1)*n - 4*(r-1)*(r-1) + 1 + 3*n-6*r + 3 - y + r;
	}
	if (x>=y && x+y <= n+1) {
		r = y;
		return 4*(r-1)*n - 4*(r-1)*(r-1) + 1 + 4*n-8*r + 4  - x + r;
	}
	assert(0);
	return -1;
}