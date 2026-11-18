#include <stdio.h>

int main(void){
	int N;
	printf("Введите высоту: ");
	scanf("%d",&N);
	for(int i=0, s=(N+(N-1)),p=0;i<N;i++){
		for(int k=0;k<p;k++){
			printf(" ");
		}
		for(int j=0;j<s;j++){
			printf("V");
		}
		p+=1;
		s-=2;
		printf("\n");
	}
	return 0;
}
