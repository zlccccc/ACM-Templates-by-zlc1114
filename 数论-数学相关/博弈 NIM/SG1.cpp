//f[]������ȡ�ߵ�ʯ�Ӹ���
//sg[]:0~n��SG����ֵ
//hash[]:mex{}
int f[N],sg[N],hash[N];
void getSG(int n) {
    int i,j;
    memset(sg,0,sizeof(sg));
    for(i=1; i<=n; i++) {
        memset(hash,0,sizeof(hash));
        for(j=1; f[j]<=i; j++)
            hash[sg[i-f[j]]]=1;
        for(j=0; j<=n; j++) { //��mex{}��δ���ֵ���С�ķǸ�����
            if(hash[j]==0) {
                sg[i]=j;
                break;
            }
        }
    }
}

