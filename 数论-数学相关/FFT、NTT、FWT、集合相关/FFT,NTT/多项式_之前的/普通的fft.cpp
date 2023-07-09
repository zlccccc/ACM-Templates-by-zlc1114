namespace FFT {
    const int maxn=1<<18|7;
    struct complex {
        double a,b;
        complex(double _a=.0,double _b=.0):a(_a),b(_b) {}
        complex operator+(const complex x)const {return complex(a+x.a,b+x.b);}
        complex operator-(const complex x)const {return complex(a-x.a,b-x.b);}
        complex operator*(const complex x)const {return complex(a*x.a-b*x.b,a*x.b+b*x.a);}
    };
    complex wn[maxn];
    void initwn(int l) {
        static int len=0; int i;
        if (len==l) return; else len=l;
        REP(i,len) wn[i]=complex(cos(2*pi*i/l),sin(2*pi*i/l));
    }
    void fft(complex *A,int len,int inv) {
        int i,j,k; initwn(len);
        for (i=1,j=len/2; i<len-1; i++) {
            if (i<j) swap(A[i],A[j]);
            k=len/2;
            while (j>=k) j-=k,k/=2;
            if (j<k) j+=k;
        } for (i=2; i<=len; i<<=1) {
            for (j=0; j<len; j+=i) {
                for (k=j; k<(j+i/2); k++) {
                    complex a,b; a=A[k];
                    b=A[k+i/2]*wn[(ll)(k-j)*len/i];
                    A[k]=a+b; A[k+i/2]=a-b;
                }
            }
        } if (inv==-1) REP(i,len) A[i]=complex(A[i].a/len,A[i].b/len);
    }
    inline complex conj(complex &A) {return complex(A.a,-A.b);}
    void mul(int *A,int *B,int *ans,int len) { //ans=A*B
        static complex x1[maxn],x2[maxn]; int i;
        REP(i,len) x1[i]=complex(A[i],B[i]);
        fft(x1,len,1);
        REP(i,len) {//这个k1, b1就是前面的, 这就减掉了一半常数
            int j=(len-i)&(len-1);
            complex a=(conj(x1[i])+x1[j])*complex(0.5,0);//dft a
            complex b=(conj(x1[i])-x1[j])*complex(0,0.5);//dft b
            x2[i]=a*b;
        } fft(x2,len,-1);
        REP(i,len) ans[i]=x2[i].a+0.5;
    }
}