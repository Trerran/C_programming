#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* decryption(char* str, int shift){
    char* local=malloc(strlen(str)+1);
    shift=shift%26;
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
    local[strlen(str)] = '\0';
    return local;
}

int main(void){
    char str[100];
    printf("Введите строку: ");
    fgets(str,sizeof(str),stdin);
    int* len=calloc(26, sizeof(int));
    for (int i=0;i<26;i++){
        char* tmp=decryption(str,i);
        int c=0;
        for (int j=0;j<strlen(tmp);j++){
            if (tmp[j]=='e' || tmp[j]=='t' || tmp[j]=='E' || tmp[j]=='T'){
                c+=1;
            }
        }
        free(tmp);
        len[i]=c;
    }
    int max=-1,ind=0;
    for (int i=0;i<26;i++){
        if (len[i]>=max){
            max=len[i];
            ind=i;
        }
    }
    free(len);
    char* answer=decryption(str,ind);
    printf("Сдвиг: %d\n",ind);
    printf("%s",answer);
    free(answer);
    return 0;
}