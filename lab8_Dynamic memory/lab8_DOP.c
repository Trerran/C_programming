#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 256

int** transpose_matrix(int** matrix_b){
    int** matrix_transponed=malloc(N*sizeof(*matrix_transponed));
    if (matrix_transponed==NULL){
        printf("Ошибка выделения памяти в функции transpose_matrix");
    }
    else{
        for (int i=0;i<N;i++){
            matrix_transponed[i]=malloc(N*sizeof(int));
            if (matrix_transponed[i]==NULL){
                printf("Ошибка выделения памяти в функции transpose_matrix");
                break;
            }
        }
        for (int i=0;i<N;i++){
            for (int j=0;j<N;j++){
                matrix_transponed[i][j]=matrix_b[j][i];
            }
        }
    }
    return matrix_transponed;
}

int** matrix_multiplication(int** matrix_A, int** matrix_B, char type){
    int** matrix_multiplication=malloc(N*sizeof(*matrix_multiplication));
    if (matrix_multiplication==NULL){
        printf("Ошибка выделения памяти в функции naive_matrix_multiplication");
    }
    else{
        for (int i=0;i<N;i++){
            matrix_multiplication[i]=calloc(N,sizeof(int));
            if (matrix_multiplication[i]==NULL){
                printf("Ошибка выделения памяти в функции naive_matrix_multiplication");
                break;
            }
        }
        if (type=='n'){
            for (int i=0;i<N;i++){
                for (int j=0;j<N;j++){
                    for (int k=0;k<N;k++){
                        matrix_multiplication[i][j]+=matrix_A[i][k]*matrix_B[k][j];
                    }
                }
            }
        }
        if (type=='t'){
            for (int i=0;i<N;i++){
                for (int k=0;k<N;k++){
                    for (int j=0;j<N;j++){
                        matrix_multiplication[i][j]+=matrix_A[i][k]*matrix_B[k][j];
                    }
                }
            }   
        }
    }
    return matrix_multiplication;
}

int main(void){
    int** matrix_A=malloc(N*sizeof(*matrix_A));
    int** matrix_B=malloc(N*sizeof(*matrix_B));
    if (matrix_A==NULL || matrix_B==NULL){
        printf("Ошибка выделения памяти в функции main");
        return -1;
    }
    for (int i=0;i<N;i++){
        matrix_A[i]=malloc(N*sizeof(int));
        matrix_B[i]=malloc(N*sizeof(int));
        if (matrix_A[i]==NULL || matrix_B[i]==NULL){
            printf("Ошибка выделения памяти в функции main");
            return -1;
        }
    }
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            matrix_A[i][j]=1+i+j;
            matrix_B[i][j]=1+i+j;
        }
    }
    int** matrix_b_transponed=transpose_matrix(matrix_B);
    double start_naive=0,end_naive=0;
    struct timespec start_ts, end_ts;
    clock_gettime(CLOCK_MONOTONIC,&start_ts);
    int** matrix_multiplication_naive=matrix_multiplication(matrix_A,matrix_B,'n');
    clock_gettime(CLOCK_MONOTONIC,&end_ts);
    start_naive=start_ts.tv_sec+(double)start_ts.tv_nsec/1e9;
    end_naive=end_ts.tv_sec+(double)end_ts.tv_nsec/1e9;
    printf("Время умножения(наивный метод): %lf\n",end_naive-start_naive);
    double start_transponed=0,end_transponed=0;
    clock_gettime(CLOCK_MONOTONIC,&start_ts);
    int** matrix_multiplication_transponed=matrix_multiplication(matrix_A,matrix_b_transponed,'t');
    clock_gettime(CLOCK_MONOTONIC,&end_ts);
    start_transponed=start_ts.tv_sec+(double)start_ts.tv_nsec/1e9;
    end_transponed=end_ts.tv_sec+(double)end_ts.tv_nsec/1e9;
    printf("Время умножения(траспонированная): %lf\n",end_transponed-start_transponed);
    free(matrix_multiplication_naive); //забыл освободить столбцы
    free(matrix_multiplication_transponed);//забыл освободить столбцы
    free(matrix_b_transponed);
    free(matrix_A);
    free(matrix_B);
    return 0;
}