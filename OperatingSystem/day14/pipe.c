#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// 创建一个无名管道fd包含2个文件描述符的数组，fd[0]用于读，fd[1]用于写若成功返回0,否则反回-1
//一般某个进程用于读，另一个进程用于写，用于读的进程需要close(fd[1]),用于写的进程需要close(fd[0]);
int main(void)
{
    
    int fd[2],i,n;
    int p1ID,p2ID;
    char chr[20]="sdas";
    pipe(fd);       //fd0 --read  fd1--write
    pid_t pid1,pid2;
    pid1=fork();
    p1ID=pid1;
    if(pid1!=0)pid2=fork();    //child process 1,2
    p2ID=pid2;
    if(pid1==-1||pid2==-1)printf("process wrong!\n");
    if(pid1==0){
        lockf(fd[1],1,0);
        fgets(chr,20,stdin);
        write(fd[1],&chr,20);
        printf("child1 Write: %s\n",chr);
        lockf(fd[1],0,0);

        exit(pid1);

    }else if(pid2==0){
        //dengdai 1//
        sleep(2);
        lockf(fd[1],1,0);
        fgets(chr,20,stdin);
        // printf("in child2 now\n");
        write(fd[1],&chr,20);
        printf("child2 Write: %s\n",chr);
        lockf(fd[1],0,0);
        exit(pid2);
    }else { 
        waitpid(p1ID,0,0);
        lockf(fd[0],1,0);
        read(fd[0],&chr,20);
        printf("farther Read in child1: %s\n",chr);
        lockf(fd[0],0,0);
        waitpid(p2ID,0,0);
        read(fd[0],&chr,20);
        printf("farther Read in child2: %s\n",chr);

    }

 //    if(pid==0)          //子进程
 //    {
 //        close(fd[1]);
 //        for(i=0;i<10;i++)
 //        {
 //            read(fd[0],&chr,20);
 //            printf("Read: %s\n",chr);
 //        }
 //        close(fd[0]);
 //        exit(0);
 //    }else {           //父进程
 //        close(fd[0]);           //close read child
	// for(i=0;i<10;i++)
	// {
	//     printf("\nInput buffers in 20 bytes:");
 //        fgets(chr,20,stdin);
	//     write(fd[1],&chr,20);
	//     printf("Write: %s\n",chr);
	//     sleep(1);
	// }
	// close(fd[1]);
 //    }

    return 0;
}
