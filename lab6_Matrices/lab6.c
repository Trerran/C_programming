#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double* fill_matrix(int N){
    double *arr=malloc(N*N*sizeof(double));
    if (arr==NULL){
        printf("Error malloc in function fill_matrix!\n");
        return NULL;
    }
    else{
        printf("Введите коэффициенты переменных, начиная с первой строки и двигаясь слева направо: ");
        for(int i=0;i<N*N;i++){
            scanf("%lf",arr+i); 
        }
        return arr;
    }
}

double* constant_terms(int N){
    double *arr=malloc(N*sizeof(double));
    if (arr==NULL){
        printf("Error malloc in function constant_terms!\n");
        return NULL;
    }
    else{
        printf("Введите столбец свободных членов: ");
        for(int i=0;i<N;i++){
            scanf("%lf",arr+i); 
        }
        return arr;
    }
}

int swap_lines(double* local_matrix, int N);

double determinant(double* pointer_matrix,double* pointer_constant,int N,int num){
    double* local_matrix=malloc(N*N*sizeof(double));
    if (local_matrix==NULL){
        printf("Error malloc in function Determinant!\n");
        return 0;
    }
    else{
        int sign=0;
        for (int i=0;i<N*N;i++){
            *(local_matrix+i)=(double)*(pointer_matrix+i);
        }
        if (num!=-1){
            for (int i=0;i<N;i++){
                *(local_matrix+num+i*N)=*(pointer_constant+i);
            }
        }
        double det;
        double c=0;
        sign+=swap_lines(local_matrix,N);
        for (int i=0;i<N;i++){
            if (*(local_matrix+i+i*N)==0){
                free(local_matrix);
                return 0;
            }
            else{
                for (int j=i+1;j<N;j++){
                    c=*(local_matrix+i+j*N)/(*(local_matrix+i+i*N));
                    for (int k=0;k<N;k++){
                        *(local_matrix+k+j*N)-=c*(*(local_matrix+k+i*N));
                    }
                }
            }
        sign+=swap_lines(local_matrix,N);
        }
        det=(sign%2==0) ? 1.0 : -1.0;
        for (int i=0;i<N;i++){
            det*=*(local_matrix+i+i*N);
        }
        free(local_matrix);
        return det;
    }
}

int swap_lines(double* local_matrix, int N){
    int sign=0;
    for (int i=0;i<N;i++){
        if (*(local_matrix+i+i*N)==0){ 
            for (int j=i+1;j<N;j++){
                if (*(local_matrix+i+j*N)!=0){
                    double tmp=0;
                    for (int k=0;k<N;k++){
                        tmp=*(local_matrix+k+i*N);
                        *(local_matrix+k+i*N)=*(local_matrix+k+j*N);
                        *(local_matrix+k+j*N)=tmp;
                    }
                    sign+=1;
                    break;
                }
            }
        }
    }
    return sign;
}

int main(void){
    printf("Введите количество переменных: ");
    int N;
    scanf("%d",&N);
    double* pointer_matrix=fill_matrix(N);
    double* pointer_constant=constant_terms(N);
    double det=determinant(pointer_matrix,pointer_constant,N,-1);
    if (det==0){
        printf("Нет единственного решения.\n");
    }
    else{
        double x=0;
        for (int i=0;i<N;i++){
            x=determinant(pointer_matrix,pointer_constant,N,i)/det;
            if (fabs(x)<0.0000005){
                x=0.0;
            }
            printf("x%d = %.2lf\n",i,x);
            
        }
        free(pointer_matrix);
        free(pointer_constant);
    return 0;
    }
}