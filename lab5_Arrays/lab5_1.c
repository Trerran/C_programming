#include <stdio.h>
#define N 10
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(void){
    srand(time(NULL));
    int array[N];
    short int max[N];
    short int tmp1=0,tmp2=0;
    for(int i=0,tmp=0;i<N;i++){
        tmp1=((rand()%65536)-32768);
        tmp2=((rand()%65536)-32768);
        tmp=(((tmp1&0xffff)<<16)|(tmp2&0xffff));
        array[i]=tmp;
        tmp=0;
    }
    long long int E=0;
    for(int i=0;i<10;i++){
        printf("array[%d] = %d + j*(%d)\n",i,(short)((array[i]>>16)&0xffff),(short)(array[i]&0xffff));
        max[i]=(short)((array[i]>>16)&0xffff);
        E+=(pow(((array[i]>>16)&0xffff),2)+pow((array[i]&0xffff),2));
    }   
    printf("%lld\n",E);
    int m=-2147483648;
    for(int i=0;i<N;i++){
        if (max[i]>m){
            m=max[i];
        }
    }
    printf("Максимальное число: %d\n",m);
}
