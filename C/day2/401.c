
#include <stdio.h>
int isABC(char c){
	if(c>'a'&&c<'z')return 1;
	if(c>'A'&&c<'Z')return 1;
	return 0;
}

int main()
{
	char s[100];
	int i=0;
	int count =0 ;
	gets(s);
	while(s[++i]!='\0'){
		if(!isABC(s[i])&&isABC(s[i-1]))count++;
		
	}
	if(isABC(s[i-1]))count++;
	printf("%d",count);
	
}
