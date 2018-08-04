

#include <stdio.h>


int wanshu(int num) {
	if (num <= 1)return 0;
	int sum=0;
	int i;
	for (i = 2; i <= num / 2; i++) {
		if (num%i == 0) {
			sum += i;
		}
	}
	sum++;
	if (sum == num)return 1;
	return 0;
}

int main()
{
	int num;
	int i, count=0;
	for (i = 0; i < 1000; i++) {
		if (wanshu(i) == 1) {
			printf("%5d", i);
			count++;
		}
		if (count == 5)printf("\n");
	}
	printf("\n");
	
}

