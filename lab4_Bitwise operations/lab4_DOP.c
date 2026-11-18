#include <stdio.h>

int route_packet(unsigned int incoming_ip, unsigned int gateway_ip, int cidr_prefix);

int main(void){
    unsigned int incoming_ip=0, gateway_ip=0;
    int cidr_prefix=0,result=0;
    printf("Enter incoming_ip: ");
    scanf("%x",&incoming_ip);
    printf("Enter gateway_ip: ");
    scanf("%x",&gateway_ip);
    printf("Enter cidr_prefix_ip: ");
    scanf("%d",&cidr_prefix);
    result=route_packet(incoming_ip,gateway_ip,cidr_prefix);
    printf("Результат: %d\n",result);
    if ((result==1)&&(cidr_prefix==24)){
        printf("Описание кейса: Умная колонка\n");
    }
    else if ((result==0)&&(cidr_prefix==24)){
        printf("Описание кейса: Сервер Google\n");
    }
    else if ((result==1)&&(cidr_prefix==22)){
        printf("Описание кейса: ИИ-видеокамера\n");
    }
    else if ((result==1)&&(cidr_prefix==32)){
        printf("Описание кейса: Пакет адресован самому роутеру\n");
    }
    else if ((result==0)&&(cidr_prefix==32)){
        printf("Описание кейса: Адрес отличается на 1 бит\n");
    }
    else if ((result==0)&&(cidr_prefix==1)){
        printf("Описание кейса: Сравнение по старшему биту\n");
    }
    else if (result==-1){
        printf("Описание кейса: Кривой префикс\n");
    }
    else if (result==1){
        printf("Описание кейса: Пакет домашний\n");
    }
    else if (result==0){
        printf("Описание кейса: Пакет внешний\n");
    }
}

int route_packet(unsigned int incoming_ip, unsigned int gateway_ip, int cidr_prefix){
    if ((cidr_prefix>32)||(cidr_prefix<=0)){
        return -1;
    }
    unsigned int mask=0;
    for(int i=0;i<32;i++){
        if(i<cidr_prefix){
            mask=mask<<1;
            mask=mask|1;
        } 
        else{
            mask=mask<<1;
        }
    }
    if ((incoming_ip&mask)==(gateway_ip&mask)){
        return 1;
    }
    else{
        return 0;
    }
    
}