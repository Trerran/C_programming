#include <stdio.h>

int main(void){
    int N=0;
    printf("Введите сторону квадрата: ");
    scanf("%d", &N);
    int array[N][N];
    int num=1,f=0,step0=0,step1=0;
    while((step0+step1)<N){
        if (f==0){
            f=-1;
            for(int j=step1;j<(N-step0);j++){
                array[step0][j]=num;
                num+=1;
            }
            for(int i=step0+1;i<(N-step1);i++){
                array[i][(N-1)-step0]=num;
                num+=1;
            }
            step0+=1;
        }
        else{
            f=0;
            for(int j=(N-1)-step0;j>=step1;j--){
                array[(N-1)-step1][j]=num;
                num+=1;
            }
            for(int i=(N-1)-(step1+1);i>=step0;i--){
                array[i][step1]=num;
                num+=1;
            }
            step1+=1;
        }
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            printf("%2d ",array[i][j]);
        }   
        printf("\n");
    }
    return 0;   
}