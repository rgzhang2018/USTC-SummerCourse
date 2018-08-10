#include <stdio.h>

int main(int argc, char const *argv[])
{
	/* 约瑟夫环：认为环中是编号从0-99的人 */
	int a[100];
	for(int i=0;i<100;i++){
		a[i]=i;
	}
	int n;
	printf("input n:\n" );
	scanf("%d",&n);

	int count=0,p=0;
	int b[100];
	while(count<100){
		if((p+1)%n==0){
			while(a[p]==-1){
				p++;
				p%=100;
			}
			b[count++]=a[p];
			a[p]=-1;
		}
		p++;
		p%=100;
	}
	printf("The order is:\n" );
	for(int i=0;i<100;i++)printf("%d ",b[i]);
	return 0;
}