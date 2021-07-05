char buffer[36000000],*buf=buffer;
char write[7000000],*ed=write;
void read(int &x){
    for(x=0;*buf<48;++buf);
    while(*buf>=48)x=x*10+*buf-48,++buf;
}
void read(int &x){
    for(x=0;(*buf<'0'||*buf>'9')&&*buf!='-';++buf);
    int flag=0;if (*buf=='-') flag=1,buf++;
    while('0'<=*buf&&*buf<='9')x=x*10+*buf-48,++buf;
    if (flag) x=-x;
}
int pp[20];
void print(LL x){
    if (!x) *ed++='0';
    else {
        int now=0,i;
        while (x) pp[now++]=x%10,x/=10;
        while (now) *ed++=pp[--now]+48;
    }*ed++='\n';
}
    fread(buffer,1,36000000,stdin);
    fwrite(write,1,ed-write,stdout);
