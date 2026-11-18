#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_unique(int* unique,char* str,int len){
    for (int i=0;i<len;i++){
        if (str[i]-96>0){
            if ((unique[str[i]-97]>0)){
                printf("%c ",str[i]);
            }
        }
        else{
            if ((unique[str[i]-65]>0)){
                printf("%c ",str[i]);
            }
        }
    }
    printf("\n");
}

int main(void){
    char str[100];
    printf("Введите строку: ");
    fgets(str,sizeof(str),stdin);
    int len = strlen(str)-1;
    int flag=0;
    int* unique=calloc(26,sizeof(int));
    for (int i=0;i<len;i++){
        if (0<str[i]-96 && str[i]-96<27){
            if (unique[str[i]-97]==0){
                unique[str[i]-97]=str[i]-96;
            }
            else if(unique[str[i]-97]>0){
                unique[str[i]-97]=-1;
            }
        }
        else if (str[i]-64>0 && str[i]-64<27){
            if (unique[str[i]-65]==0){
                unique[str[i]-65]=str[i]-64;
            }
            else if(unique[str[i]-65]>0){
                unique[str[i]-65]=-1;
            }
        }
        else{
            flag=-1;
            break;
        }
    }
    if (flag==0){
        int counter=0;
        for (int i=0;i<26;i++){
            if (unique[i]>0){
                counter+=1;
            }
        }
        printf("Уникальные буквы: ");
        print_unique(unique,str,len);
        printf("Количество уникальных букв: %d\n",counter);
        return 0;
    }
    else{
        printf("В строке присутсутвуют не только буквы!\n");
    }
}

