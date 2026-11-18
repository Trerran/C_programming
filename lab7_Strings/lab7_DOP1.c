#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* cipher(char* str, int shift,char action){
    char* local=malloc(strlen(str)+1);
    shift=shift%26;
    if (action=='e' || action=='E'){
        for (int i=0;i<strlen(str);i++){
            if (isupper(str[i])){
                local[i]=(str[i]-'A'+shift+26)%26+'A';
            }
            else if(islower(str[i])){
                local[i]=(str[i]-'a'+shift+26)%26+'a';
            }
            else{
                local[i]=str[i];
            }
        }
    }
    else if (action=='d' || action=='D'){
        for (int i=0;i<strlen(str);i++){
            if (isupper(str[i])){
                local[i]=(str[i]-'A'-shift+26)%26+'A';
            }
            else if(islower(str[i])){
                local[i]=(str[i]-'a'-shift+26)%26+'a';
            }
            else{
                local[i]=str[i];
            }
        }
    }
    else{
        return NULL;
    }
    local[strlen(str)] = '\0';
    return local;
}

int main(void){
    char str[100];
    int shift=0;
    char action;
    printf("Введите строку: ");
    fgets(str,sizeof(str),stdin);
    printf("Введите сдвиг: ");
    scanf("%d",&shift);
    printf("Выберете действие(e,d): ");
    getchar();
    scanf("%c",&action);
    char* txt=cipher(str,shift,action);
    if (txt!=NULL){
        printf("%s\n",txt);
        free(txt);
    }
    else{
        printf("Действие введено неверно!\n");
    }
    return 0;
}