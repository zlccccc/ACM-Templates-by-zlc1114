#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring> 
#include <stack>
#include <queue>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=3e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

namespace fastIO {
#define BUF_SIZE 100000
#define OUT_SIZE 1000000
    bool IOerror = 0;

    inline char nc() {
        static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
        if (p1 == pend) {
            p1 = buf;
            pend = buf + fread(buf, 1, BUF_SIZE, stdin);
            if (pend == p1) {
                IOerror = 1;
                return -1;
            }
        }
        return *p1++;
    }

    inline bool blank(char ch) {
        return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
    }

    inline int read(char *s) {
        char ch = nc();
        for (; blank(ch); ch = nc());
        if (IOerror)
            return 0;
        for (; !blank(ch) && !IOerror; ch = nc())
            *s++ = ch;
        *s = 0;
        return 1;
    }

    inline int RI(int &a) {
        char ch = nc();

        a = 0;
        for (; blank(ch); ch = nc());
        if (IOerror)
            return 0;
        int flag;
        if (ch == '-') {
            flag = -1;
            ch = nc();
        } else { flag = 1; }
        for (; !blank(ch) && !IOerror; ch = nc())
            a = a * 10 + ch - '0';
        a = a * flag;
        return 1;
    }

    struct Ostream_fwrite {
        char *buf, *p1, *pend;

        Ostream_fwrite() {
            buf = new char[BUF_SIZE];
            p1 = buf;
            pend = buf + BUF_SIZE;
        }

        void out(char ch) {
            if (p1 == pend) {
                fwrite(buf, 1, BUF_SIZE, stdout);
                p1 = buf;
            }
            *p1++ = ch;
        }

        void flush() {
            if (p1 != buf) {
                fwrite(buf, 1, p1 - buf, stdout);
                p1 = buf;
            }
        }

        ~Ostream_fwrite() { flush(); }
    } Ostream;

    inline void print(char x) { Ostream.out(x); }

    inline void println() { Ostream.out('\n'); }

    inline void flush() { Ostream.flush(); }

    char Out[OUT_SIZE], *o = Out;

    inline void print1(char c) { *o++ = c; }

    inline void println1() { *o++ = '\n'; }

    inline void flush1() {
        if (o != Out) {
            if (*(o - 1) == '\n')
                *--o = 0;
            puts(Out);
        }
    }

    struct puts_write {
        ~puts_write() { flush1(); }
    } _puts;
};


int c;
int main(){
	int i;
	while (fastIO::RI(c)){
		printf("%d\n",c);
	}
}
/*
54623.654
*/
