/*
1、编写一个程序读取a.txt文件，将文件内容数字从小到大排序，并将排序结果写入b.txt。
a.txt文件内容如下：
32
45
65
32
67
454
89
54
24
75
3
67
890
32
1
*/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(int arg, char *args[])
{
    if(arg<2)
    {
        printf("PRGM Error!\n");
    }

    FILE * pr = fopen(args[1],"r");
    FILE * pw = fopen("sorta.txt","w");

    if(pr == NULL)
    {
        printf("%s",strerror(errno));
    return -1;
    }
    int num[15],Count=0,i,j;
    char buf[10];
    memset(buf,0,sizeof(buf));

    while(fgets(buf,sizeof(buf),pr))
    {
        num[Count++] = atoi(buf);
    }

    for(i = 0; i < 15; ++i)
        for(j = i+1; j < 15; j++)
        {
            if(num[i]>num[j])
            {
                num[i] ^= num[j];//用异或实现交换
                num[j] ^= num[i];
                num[i] ^= num[j];

            }
        }

    if(pr == NULL)
    {
        printf("%s",strerror(errno));
        return -1;
    }

    for(i = 0; i < 15; ++i)
        {
            fprintf(pw,"%d\n",num[i]);

        }

    fclose(pr);
    fclose(pw);
    return 0;
}
