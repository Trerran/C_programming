#define size 9
#include <stdlib.h>
#include <stdio.h>

int check_rows(int* p){
    int res=0;
    for (int i=0;i<size;i++){
        int x=0;
        int *arr=calloc(9,sizeof(*arr));
        for (int j=0;j<size;j++){
            x=*(p+i*size+j);
            *(arr+x-1)=x;
        }
        int tmp=0;
        for (int j=0;j<size;j++){
            if (*(arr+j)==0){
                res-=1;
                break;
            }
            else{
                tmp+=1;
            }
        }
        if (tmp==9){
            res+=1;
        }
        free(arr);
    }
    return res;
}

int check_columns(int* p){
    int res=0;
    for (int i=0;i<size;i++){
        int x=0;
        int *arr=calloc(9,sizeof(*arr));
        for (int j=0;j<size;j++){
            x=*(p+j*size+i);
            *(arr+x-1)=x;
        }
        int tmp=0;
        for (int j=0;j<size;j++){
            if (*(arr+j)==0){
                res-=1;
                break;
            }
            else{
                tmp+=1;
            }
        }
        if (tmp==9){
            res+=1;
        }
        free(arr);
    }
    return res;
}

int check_squares(int* p){
    int res=0;
    for (int i=0;i<size;i++){
        int x=0;
        int *arr=calloc(9,sizeof(*arr));
        if (i<=2){
            for (int j=0;j<3;j++){
                for (int k=i*3;k<(i+1)*3;k++){
                    x=*(p+j*size+k);
                    *(arr+x-1)=x;
                }
            }
        }
        else if (i>2 && i<=5){
            for (int j=3;j<6;j++){
                for (int k=(i-3)*3;k>=(i-3)*3 && k<(i-2)*3;k++){
                    x=*(p+j*size+k);
                    *(arr+x-1)=x;
                }
            }
        }
        else{
            for (int j=6;j<9;j++){
                for (int k=(i-6)*3;k<(i-5)*3;k++){
                    x=*(p+j*size+k);
                    *(arr+x-1)=x;
                }
            }
        }
        int tmp=0;
        for (int j=0;j<size;j++){
            if (*(arr+j)==0){
                res-=1;
                break;
            }
            else{
                tmp+=1;
            }
        }
        if (tmp==9){
            res+=1;
        }
        free(arr);
    }
    return res;
}

void is_valid(int* p){
    if (check_columns(p)==9 && check_rows(p)==9 && check_squares(p)==9){
        printf("Это судоку!\n");
    }
    else{
        printf("Это не судоку!\n");
    }
}

int main(void){
    int sudoku[size][size] = {
        {9, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };
    int* pointer=&sudoku[0][0];
    is_valid(pointer);
    return 0;
}