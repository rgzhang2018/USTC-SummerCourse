
#include <stdio.h>
#include <string.h>


int main()
{
	char s1[10000];
	char *s2="debug";
	gets(s1);
	int count = 0;
	char *p = s1;
	while(strstr(p,s2)!=NULL){
		p=strstr(p,s2)+5;
		count++;
	}
	printf("���ַ�����'dubug'������:%d��",count);
	
}
