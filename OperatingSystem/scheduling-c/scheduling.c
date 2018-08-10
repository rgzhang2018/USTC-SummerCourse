#include <stdio.h>
#include <stdlib.h>

#include <windows.h>


//模拟CPU运行：设置PCB并设计程序控制

//思路：
//分别设置函数为 初始化、运行、等待队列（后续再加入IO和阻塞(其实就是另外一个'cpu'和另外一个'等待队列')）
typedef struct ThreadLine
{
	int id;
	int priorty;
	int restTime;
	int needTime;
//	int IOtime;
	int workTime;//已经工作的时间
	int state;//现状，队列中(0)、运行(1)、终止(-1)
	struct ThreadLine * next;
}PCB;

PCB* start(int num);
void cpuwork(PCB *head, PCB *rear);
PCB* scheduling(PCB* head, PCB *rear);
PCB* getRear(PCB * head);

//初始化函数，初始化一个随机的进程队列
PCB* start(int num) {
	srand(num);
	PCB * head = (PCB*)malloc(sizeof(PCB));
	int id = 0;
	head->id = ++id;
	head->priorty = rand() * 3;//设置优先级最高有三种，0,1,2，其中2最大
	head->needTime =(rand()% 10)*100 ;
	head->restTime = head->needTime;
	head->workTime = 0;
	head->state = 0;
	head->next = NULL;
	PCB *p;
	for (int i = 0; i < num-1; i++) {
		p = (PCB*)malloc(sizeof(PCB));
		p->id = ++id;
		p->priorty = rand() * 3;
		p->needTime = (rand() % 10) * 100;
		p->restTime = p->needTime;
		p->workTime = 0;
		p->state = 0;
		p->next = head->next;
		head->next = p;
	}
	return head;
}

void cpuwork(PCB *head ,PCB *rear) {
	PCB * work = head->next;
	if (work->restTime > 0) {
		Sleep(100);
		work->workTime += 100;
		work->restTime -= 100;
		printf("ID:%d in CPU ,work 100ms this time,%d in total. The restTime is : %d\n", work->id, work->workTime, work->restTime);
	}

}

PCB* scheduling(PCB* head, PCB *rear) {
	if (head->next->restTime <= 0) {
		PCB *p = head->next;
		head->next = head->next->next;
		printf("Thread ID:%d end. \n", p->id);
		free(p);
		p = NULL;
	}
	else {
		PCB *p = head->next;
		head->next = p->next;
		rear->next = p;
		rear = p;
		rear->next = NULL;
	}
	return head;
}

PCB* getRear(PCB * head) {
	PCB *p = head,*rear;
	while (p->next != NULL) {
		p = p->next;
	}
	rear = p;
	return rear;
}

int main(int argc, char const *argv[])
{
	
	PCB * head = (PCB*)malloc(sizeof(PCB));//设置头结点，不是头指针，便于删除第一个元素
	head->next = start(4);
	PCB * rear = getRear(head);

	while (head->next != NULL) {
		cpuwork(head,rear);
		head=scheduling(head, rear);
		rear = getRear(head);
	}
	printf("end\n");
	return 0;
}