/*
2、通过读取/proc下的相关文件，得到系统CPU信息，内存信息。
*/
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int arg, char *args[])
{

    FILE * pr = fopen("/proc/meminfo","r");
    int pw = open("/proc/cpuinfo",O_RDONLY);//这里相对路径，没有/home/...

    if(pr == NULL || pw < 0)
    {
        printf("%s",strerror(errno));
        return -1;
    }

    char buf[10];
    memset(buf,0,sizeof(buf));//将之内容初始化为0

    while(fgets(buf,sizeof(buf),pr))
    {
       write(STDOUT_FILENO,buf,sizeof(buf));
       memset(buf,0,sizeof(buf));
    }

    while(read(pw,buf,sizeof(buf)))
    {
       write(STDOUT_FILENO,buf,sizeof(buf));
       memset(buf,0,sizeof(buf));
    }

    fclose(pr);
    close(pw);
    return 0;
}
