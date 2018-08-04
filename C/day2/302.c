// myCpp-1.cpp: 定义控制台应用程序的入口点。
//

#include <stdio.h>

int main()
{
	int x;
	int i=0,j=0;
	int flag = 0, flagline = 0;
	scanf("%d", &x);
	x--;
	while (--x>=0) {
		
		if (flag==0) {
			//f1=0，横向移动
			i++;
			flag = 2;
			flagline = 0;
		}
		if (flag == 1) {
			j++;
			flag = 2;
			flagline = 1;
		}
		if (flag == 2) {
			if (flagline == 0) {
				//f1=2表示斜侧移动，f2=0表右上往左下移动
				i--;
				j++;
				if (i == 0)flag = 1;
			}
			else {
				//f2=1表示左下往右上移动
				j--;
				i++;
				if (j == 0)flag = 0;
			}
		}
		
	}
	printf("the num is : %d/%d", i+1, j+1);


    return 0;
}

