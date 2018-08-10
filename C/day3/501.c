#include <stdio.h>

int sushu(int x){
	int flag =0;
	for(int i=3;i<=x/2;i++){
		if(x%i==0){
			flag = 1 ;	
			break;
		}

	}
	if(flag==1)return 0;
	return 1;
}


int main(int argc, char const *argv[])
{
	int n;
	
	int proS = 3;
	scanf("%d",&n);
	if(n<5)printf("wrong input!");
	for(int i=5;i<=n;i+=2){
		if(sushu(i)){
			if(i-2==proS)printf("|  %d and %d  |\n",proS,i);
			proS = i;
		}
	}
	return 0;
}