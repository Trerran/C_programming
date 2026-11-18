#include <stdio.h>
#include <unistd.h>

int main(void){
	for(;;){
	for(int level=0;level<3;level++){
		printf("\033[2J\033[H");
		if (level==0){
			for(int y=0;y<100;y++){
				for(int x=0;x<64;x++){
					if ((x>=32-y)&&(x<=32+y)){
						printf("*");
					}
					else{
						printf(" ");
					}
				}
				printf("\n");
				if (32-y==1){
					break;
				}
			usleep(100000);
			}
		}
		else if (level==1){
			for(int y=0;y<100;y++){
                                for(int x=0;x<64;x++){
                                        if ((y<16)&&(x>=32-y)&&(x<=32+y)){
                                                printf("*");
                                        }
					else if ((y>15)&&(x>=16-(y-16))&&(x<=16+(y-16))&&(x<32)){
						printf("*");
					}
					else if ((y>15)&&(x>=48-(y-16))&&(x<=48+(y-16))&&(x>31)){
                                                printf("*");
                                        }
                                        else{
                                                printf(" ");
                                        }
                                }
                                printf("\n");
                                if (32-y==1){
                                        break;
                                }
                        usleep(100000);
                        }
		}
		else if (level==2){
                        for(int y=0;y<100;y++){
                                for(int x=0;x<64;x++){
                                        if ((y<8)&&(x>=32-y)&&(x<=32+y)){
						printf("*");
					}
					else if(((16>y)&&(7<y))&&(x>=24-(y-8))&&(x<=24+(y-8))&&(x<32)){
						printf("*");
					}
                                        else if (((16>y)&&(7<y))&&(x>=40-(y-8))&&(x<=40+(y-8))&&(x>=32)){
                                                printf("*");
                                        }
					else if(((y>15)&&(y<24))&&(x>=16-(y-16))&&(x<=16+(y-16))&&(x<32)){
						printf("*");
					}
					else if(((y>15)&&(y<24))&&(x>=48-(y-16))&&(x<=48+(y-16))&&(x>=32)){
						printf("*");
					}
					else if(((y<32)&&(y>=24))&&(x>=8-(y-24))&&(x<=8+(y-24))&&(x<16)){
						printf("*");
					}
					else if(((y<32)&&(y>=24))&&(x>=56-(y-24))&&(x<=56+(y-24))&&(x>48)){
                                                printf("*");
                                        }
					else if(((y<32)&&(y>=24))&&(x>=24-(y-24))&&(x<=24+(y-24))&&(x<32)&&(x>=16)){
                                                printf("*");
                                        }
					else if(((y<32)&&(y>=24))&&(x>=40-(y-24))&&(x<=40+(y-24))&&(x>=32)&&(x<48)){
                                                printf("*");
                                        }
                                        else{
                                                printf(" ");
                                        }
                                }
                                printf("\n");
                                if (32-y==1){
                                        break;
                                }
                        usleep(100000);
                        }
                }
		usleep(500000);
		}
	}
	return 0;
}
