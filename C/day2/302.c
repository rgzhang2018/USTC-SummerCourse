// myCpp-1.cpp: �������̨Ӧ�ó������ڵ㡣
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
			//f1=0�������ƶ�
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
				//f1=2��ʾб���ƶ���f2=0�������������ƶ�
				i--;
				j++;
				if (i == 0)flag = 1;
			}
			else {
				//f2=1��ʾ�����������ƶ�
				j--;
				i++;
				if (j == 0)flag = 0;
			}
		}
		
	}
	printf("the num is : %d/%d", i+1, j+1);


    return 0;
}

