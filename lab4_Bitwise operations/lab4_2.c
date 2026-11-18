#include <stdio.h>
#include <math.h>

void inverter(int number, int i){
	unsigned int bit,res;
	bit=(number>>(i-1))&1;
	bit==1 ? (bit=0):(bit=1);
	bit==1 ? (res=number+pow(2,i-1)):(res=number-pow(2,i-1));
	printf("%d\n",res);
}

int main(void){
	int number,i;
	printf("Enter a number: ");
	scanf("%d",&number);
	printf("Shift: ");
	scanf("%d",&i);
	inverter(number,i);
	return 0;
}
