
int a[MAXN],b[MAXN];
tot = 0;
for (int dir = 0; dir < 4; dir++) {
//4种坐标变换
    if (dir == 1 || dir == 3) {
        for (int i = 0; i < n; i++) swap(p[i].x,p[i].y);
    } else if (dir == 2) {
        for (int i = 0; i < n; i++) p[i].x = -p[i].x;
    }
    sort(p,p+n,cmp);
    for (int i = 0; i < n; i++)
        a[i] = b[i] = p[i].y - p[i].x;
    sort(b,b+n);
    int m = unique(b,b+n) - b;
    for (int i = 1; i <= m; i++) bit[i].init();
    for (int i = n-1 ; i >= 0; i--) {
        int pos = lower_bound(b,b+m,a[i]) - b + 1;
        int ans = ask(pos,m);
        if (ans != -1)
            addedge(p[i].id,p[ans].id,dist(p[i],p[ans]));
        update(pos,p[i].x+p[i].y,i);
    }
}
