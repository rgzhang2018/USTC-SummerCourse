
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
int main()
{
	int N;
	int i;
	float num=0;
	scanf("%d",&N);
	int *p;
	p = (int*)malloc(N*(sizeof(int)));
	for(i=0;i<N;i++){
		scanf("%d",&p[i]);
	}
	for(i=0;i<N;i++){
		num+=p[i];
	}
	num /= N;
	for(i=0;i<N;i++){
		if(p[i]>num)printf("%d ",p[i]);
	}
}

