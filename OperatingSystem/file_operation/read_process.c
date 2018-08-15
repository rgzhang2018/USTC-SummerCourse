/*
3、通过读取读取c.txt文件内容中等号右值，并将右值最大值，最小值和平均值打印到屏幕。

c.txt文件内容如下
index1 = 45
index2 = 36
index3 = 231
index4 = 43
index5 = 100
index6 = 123
index7 = 51
*/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>


int main(int arg, char *args[])
{

    FILE * pr = fopen("c.txt","r");


    if(pr == NULL)
    {
        printf("%s",strerror(errno));
        return -1;
    }
    int num[7]={0},Count=-1,i,j;
    float sum=0;
    char buf[20];
    memset(buf,0,sizeof(buf));

    while(++Count,fgets(buf,sizeof(buf),pr))
    {
        char *tmp = NULL;
        tmp = strstr(buf,"=");
        num[Count] = atoi(tmp+strlen("="));
        sum += num[Count];

    }

    for(i = 0; i < 7; ++i)
        for(j = i+1; j < 7; j++)
        {
            if(num[i]>num[j])
            {
                num[i] ^= num[j];
                num[j] ^= num[i];
                num[i] ^= num[j];

            }
        }

    printf("Max:%d \nMin:%d \nAvg:%f \n",num[0],num[6],sum/7);

    fclose(pr);

    return 0;
}
