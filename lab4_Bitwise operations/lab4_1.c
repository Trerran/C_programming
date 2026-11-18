#include <stdio.h>
#include <math.h>

void is_Divisible_by_16(int number){
	int res;
	res=number;
	number=number>>4;
	number*pow(2,4)==res ? printf("TRUE\n"):printf("FALSE\n");
}
int main(){
	int number;
	printf("Enter the number for verification: ");
	scanf("%d",&number);
	is_Divisible_by_16(number);
	return 0;
}
