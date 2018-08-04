#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
void put(int *a,int x,int length){
	
	for(int i = 0 ;i<length;i++){
		if(x<a[i]){
			for(int j = length-1; j>=i ;j--){
				a[j+1]=a[j];
			}
			
			a[i]=x;
			break;
		}
	}
	if(x>a[length-1])a[length]=x;
}

int main(int argc, char const *argv[])
{
	int *a;
	int n; 
	printf("input the numbers of array elements：\n" );
	scanf("%d",&n);
	int x;
	a = (int *)malloc(n*sizeof(int));
	memset(a,65535,n);
	printf("input elements：\n" );
	scanf("%d",&a[0]);
	for(int i=0;i<n-1;i++){
		scanf("%d",&x);
		put(a,x,i+1);
	}

	printf("sort：\n" );
	for(int i=0;i<n;i++){
		printf(" %d ",a[i] );
	}
	int p=0,q=n;
	while(p<=q){
		//找到非奇数
		while(a[p]%2!=0&&p<=n)p++;
		//找到尾部q指向处的非偶数
		while(a[q]%2==0&&q>=0)q--;
		if(p<q){
			int temp = a[p];
			a[p]=a[q];
			a[q]=temp;			
		}

	}
	printf("\n resort：\n" );
	for(int i=0;i<n;i++){
		printf(" %d ",a[i] );
	}
	return 0;
}