
void fwt(LL *A,int len,int inv,int type){//xor,and,or
    int i,j,k;
    int div=powMM(2ll,M-2);
    for(i=2;i<=len;i<<=1){
        for(j=0;j<len;j+=i){
            for(k=j;k<j+i/2;k++){
                if (inv==1){
                    LL a=A[k],b=A[k+i/2];
                    if (type==1){
                        A[k]=(a+b)%M;
                        A[k+i/2]=(a-b+M)%M;
                    }else if (type==2){
                        A[k]=(a+b)%M;
                    }else if (type==3){
                        A[k+i/2]=(a+b)%M;
                    }
                }else{
                    LL a=A[k],b=A[k+i/2];
                    if (type==1){
                        A[k]=(a+b)*div%M;
                        A[k+i/2]=(a-b+M)%M*div%M;
                    }else if (type==2){
                        A[k]=(a-b+M)%M;
                    }else if (type==3){
                        A[k+i/2]=(b-a+M)%M;
                    }
                }
            }
        }
    }
}