#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"
#include <windows.h>


//模拟页面置换算法

//思路：
//设置 数据结构 包括页面数、已经访问的队列、置换情况等
//设置 页面初始化 函数，随机生成n个页面，让他们以随机顺序到达
//设置 调度函数  根据具体算法 设置为LRU FIFO两个函数

typedef struct pages
{
	int * blocks;			//存放的物理块数
	int * willVisit;		//存放页面队列
	int * visitedList;		//页面访问过的次数，未访问过为0
	int listNum;
	int blockNum;
	int visitTimes = 0;

}Page;



void start(Page &thisPage, int &length, int &pages, int &blocks);
void showQueue(Page thisPage);
void FIFOschedul(Page &thisPage);
void LRUschedul(Page &thisPage);
void schedul(Page &thisPage, int next,int p);

//初始化，根据要求的块数和页面数，随机生成页面
void start(Page &thisPage, int &length, int &pages, int &blockNum) {
	srand(pages);
	printf("Input numbers of pages:");
	scanf_s("%d", &pages);
	printf("Input numbers of blocks:");
	scanf_s("%d", &blockNum);
	printf("Input numbers of visitedList:");
	scanf_s("%d", &length);
	printf("\nRandom Generation: \n");
	thisPage.blocks = (int *)malloc(blockNum * sizeof(int));
	thisPage.willVisit = (int *)malloc(length * sizeof(int));
	thisPage.visitedList = (int *)malloc(pages * sizeof(int));
	for (int i = 0; i < length; i++) {
		thisPage.willVisit[i] = rand() % pages;//随机产生0到pages-1的页面，填满访问列表
	}
	memset(thisPage.blocks, -1, blockNum * sizeof(int));//初始化物理块为0
	memset(thisPage.visitedList, 0, pages * sizeof(int));//初始化访问位为0
	thisPage.listNum = length;
	thisPage.blockNum = blockNum;

}

//用于显示调度信息
void showQueue(Page thisPage) {
	printf("\nTimes:      %d ",thisPage.visitTimes);
	printf("\nThe blocks now:       ");
	for (int i = 0; i < thisPage.blockNum; i++) {
		printf("%d  ", thisPage.blocks[i]);
	}
	printf("\nThe willVisit now:    ");
	for (int i = thisPage.visitTimes; i < thisPage.listNum; i++) {
		printf("%d  ", thisPage.willVisit[i]);
	}
	printf("\nThe visitedList now:  ");
	for (int i = 0; i < sizeof(thisPage.visitedList)+1; i++) {
		printf("page:%d times:%d |",i, thisPage.visitedList[i]);
	}
	printf("\n=========================================================\n");
}

//fifo方式
void FIFOschedul(Page &thisPage) {
	int Pblock = 0;
	int length = thisPage.listNum;
	for (int i = 0; i < length; i++) {
		int find = 0;
		for (int j = 0; j < thisPage.blockNum; j++) {
			if (thisPage.blocks[j] == thisPage.willVisit[i])find = 1;
		}
		if (find == 1) {
			printf("\n Find page%d in blocks ! Don't need schedul", thisPage.willVisit[i]);
			thisPage.visitedList[thisPage.willVisit[i]]++;
			thisPage.willVisit[i] = -1;				//页面置为-1，表示访问过了
			Sleep(400);
		}
		else {
			schedul(thisPage, i, Pblock);
			Pblock++;
			Pblock = Pblock % thisPage.blockNum;
		}
		thisPage.visitTimes++;
		showQueue(thisPage);
	}
}

void LRUschedul(Page &thisPage) {
	int *lru;
	int blockNum = thisPage.blockNum;
	int length = thisPage.listNum ;
	lru = (int*)malloc(blockNum * sizeof(int));
	for (int i = 0; i < blockNum; i++) {//初始化LRU队列，使初值为1，每次访问会使当前所有位置的值-1，某个位置新进入了一个页面，则将其LRU置1
		lru[i] = 0;
	}
	for (int i = 0; i < length; i++) {	//初始化访问每个物理块
		int find = 0;
		for (int j = 0; j < blockNum; j++) {
			if (thisPage.blocks[j] == thisPage.willVisit[i])find = 1;
		}
		for (int j = 0; j < blockNum; j++) {
			lru[j]--;
		}
		if (find == 1) {
			printf("\n Find page%d in blocks ! Don't need schedul", thisPage.willVisit[i]);
			thisPage.visitedList[thisPage.willVisit[i]]++;
			thisPage.willVisit[i] = -1;
			Sleep(400);
		}
		else {//如果没找到，则需要页面置换
			int min = 0;
			for (int j = 0; j < blockNum; j++) {//置换：找出lru数组中的最小值，就是当前在里面呆了最久还没有更新的数值
				if (lru[j] < lru[min])min = j;
			}
			schedul(thisPage, i,min);
			lru[min] = 0;
		}
		
		
		thisPage.visitTimes++;
		showQueue(thisPage);
	}
}

void schedul(Page &thisPage,int next,int p) {
	thisPage.blocks[p] = thisPage.willVisit[next];
	thisPage.visitedList[thisPage.willVisit[next]]++;
	thisPage.willVisit[next] = -1;
	Sleep(1200);
}

int main(int argc, char const *argv[])
{
	Page FIFO,LRU ;
	int length, pages, blocks;
	start(FIFO,length, pages, blocks);
	printf("Queues in FIFO:\n");
	showQueue(FIFO);
	FIFOschedul(FIFO);

	start(LRU, length, pages, blocks);
	printf("\nQueues in LRU:\n");
	showQueue(LRU);
	LRUschedul(LRU);
	return 0;
}