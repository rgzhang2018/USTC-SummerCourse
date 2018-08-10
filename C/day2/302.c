

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
			//f1管x,y轴方向的运动
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
				//flagline管理分方向斜上，斜下的运动
				i--;
				j++;
				if (i == 0)flag = 1;
			}
			else {
				j--;
				i++;
				if (j == 0)flag = 0;
			}
		}
		
	}
	printf("the num is : %d/%d", i+1, j+1);


    return 0;
}

