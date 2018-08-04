
#include <stdio.h>

int main()
{
	int num = 1;
	int i;
	for(i=10;i>1;i--){
		num=2*(num+1);
	}
	printf("第一天的桃子数量为：%d",num);
}
