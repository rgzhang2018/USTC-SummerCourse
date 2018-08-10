读者-写者问题的疑惑----写者优先

int readcount, writecount = 0;
semaphore rsem, wsem = 1; //
semaphore x,y,z = 1; //

void reader(){
   while(1){
     wait(z);//这个不知道干嘛使得。。。
      wait(rsem);//是否有写进程在访问了，如果有rsem为0，则读进程阻塞；
       wait(x);//x是为了对readcount的互斥修改；
        readcount++;
        if (readcount==1) //只要有一个读进程访问，
             wait(wsem);//则阻塞写进程；
       signal(x);
      signal(rsem);//这个是为了后续读进程对readcount、wsem的访问
     signal(z);
     doReading();
     wait(x);
        readcount--;
        if (readcount==0)//没有读进程了，
             signal(wsem);//允许写进程访问；
     signal(x);
   }
}



void writer(){
  while(1){
      wait(y);
        writecount++;
        if (writecount==1) 
             wait(rsem);
      signal(y);
      wait(wsem);
      doWriting();
      signal(wsem);
      wait(y);
        writecount--;
        if (writecount==0)
             signal(rsem);
      signal(y);
   }
}
