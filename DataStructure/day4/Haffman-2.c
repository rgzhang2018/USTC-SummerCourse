#include <stdio.h>
#include <string.h>
#define SIZE 27//26大写字母+空格

//haffman编码之二：静态链表法
//优点：不需要申请内存，指针，简单易用
//并且便于从haffman树构造编码

//代码维护：仅需修改SIZE对应部分的代码和权值数组

typedef struct hfnode
{
	int weight, parent, lchild, rchild;
	char s[SIZE];
	int p;
}node;

void creatHfTree(node *hfTree, int * weight);
char** getNumber(node *hfTree,char * number[SIZE]);
bool isEqual(char *s1, char *s2);

void creatHfTree(node *hfTree, int * weight) {
	//初始化hafftree
	for (int i = 0; i<SIZE * 2 - 1; i++) {
		hfTree[i].parent = -1;
		hfTree[i].lchild = -1;
		hfTree[i].rchild = -1;
		hfTree[i].s[0] = '\0';
		hfTree[i].p = 0;
	}
	//初始化叶子节点（叶子节点为n个）
	for (int i = 0; i < SIZE; i++) {
		hfTree[i].weight = weight[i];
	}
	//对叶子节点设置双亲，并对双亲继续设置
	for (int i = 0; i<SIZE - 1; i++) {
		int mwet = 65536, nwet = 65536, m = 0, n = 0;
		//循环找到最小权值的节点，并分别放入m,n
		for (int j = 0; j<SIZE + i; j++) {
			if (hfTree[j].weight<mwet && hfTree[j].parent == -1) {
				nwet = mwet;
				n = m;
				mwet = hfTree[j].weight;
				m = j;
			}
			else if (hfTree[j].weight<nwet && hfTree[j].parent == -1) {
				nwet = hfTree[j].weight;
				n = j;
			}
		}
		//为m,n设置双亲i，并放入权值之和
		hfTree[i + SIZE].lchild = m;
		hfTree[i + SIZE].rchild = n;
		hfTree[m].parent = SIZE + i;
		hfTree[n].parent = SIZE + i;
		hfTree[i + SIZE].weight = mwet + nwet;
		//构造过程的规律：从最后一个元素开始，进行层次遍历，可以较为方便的得到内容
	}
}

void getNumber(node *hfTree,char number[SIZE][SIZE]) {
	int queue[SIZE * 2 - 1];
	queue[0] = SIZE * 2 - 2;
	int head = 0;
	int rear = 0;
	while (rear != SIZE * 2 - 1) {
		//出队
		if (hfTree[queue[rear]].lchild!= -1) {
			queue[++head] = hfTree[queue[rear]].lchild;
			hfTree[queue[head]].p = hfTree[queue[rear]].p;
			for (int i = 0; i < hfTree[queue[head]].p; i++) {
				hfTree[queue[head]].s[i] = hfTree[queue[rear]].s[i];
			}
			
			hfTree[queue[head]].s[hfTree[queue[head]].p] = '0';
			hfTree[queue[head]].p++;
			hfTree[queue[head]].s[hfTree[queue[head]].p] = '\0';
		}
		if (hfTree[queue[rear]].rchild != -1) {
			queue[++head] = hfTree[queue[rear]].rchild;
			hfTree[queue[head]].p = hfTree[queue[rear]].p;
			for (int i = 0; i < hfTree[queue[head]].p; i++) {
				hfTree[queue[head]].s[i] = hfTree[queue[rear]].s[i];
			}
			
			hfTree[queue[head]].s[hfTree[queue[head]].p] = '1';
			hfTree[queue[head]].p++;
			hfTree[queue[head]].s[hfTree[queue[head]].p] = '\0';
		}
		rear++;
	}
	for (int i = 0; i<SIZE; i++) {
		for (int j = 0; j<SIZE; j++) {
			number[i][j] = hfTree[i].s[j];
		}
	}

}
bool isEqual(char *s1, char *s2) {
	for (int i = 0; i < strlen(s1); i++) {
		if (s1[i] != s2[i])return false;
	}
	return true;
}

int main(int argc, char const *argv[])
{
	node hfTree[SIZE * 2 - 1];//2*SIZE-1 是在有SIZE个节点的情况下 haffman树的总结点数。
	
	int weight[SIZE] = {
		64,13,22,32,103,21,15,47,57,1,5,32,20,57,
		63,15,1,48,51,80,23,8,18,1,16,1,168
	};
	creatHfTree(hfTree, weight);
	char number[SIZE][SIZE];
	getNumber(hfTree,number);

	// for (int i = 0; i < SIZE; i++) {
	// 	puts(number[i]);
	// }
	printf("Input the message u want to make into Haffman:\n");
	char in[1000];
	gets(in);
	printf("The haffman is:\n");
	for (int i = 0; i < strlen(in); i++) {
		if (in[i] == 32) {
			for (int j = 0; j < strlen(number[SIZE - 1]); j++) {
				printf("%c", number[SIZE - 1][j]);
			}
		}
		else if(in[i]>='A' && in[i]<='Z'){
			for (int j = 0; j < strlen(number[in[i] - 'A']); j++) {
				printf("%c", number[in[i] - 'A'][j]);
			}
		}
	}
	printf("\nInput the message by Haffman:\n");
	char out[1000];
	char temp[20];
	gets(out);
	int j = 0;
	int p = 0;
	printf("The message is:\n");
	while (out[j] != '\0') {
		temp[p++] = out[j];
		temp[p] = '\0';
		for (int i=0; i < SIZE;i++ ) {
			if (strlen(temp) == strlen(number[i])) {
				if (isEqual(temp,number[i])) {
					if(i!=SIZE-1)printf("%c", i + 'A');
					else printf(" ");
					for (int q = 0; q < p; q++) {
						temp[q] = '\0';
					}
					p = 0;
				}
			}
		}
		j++;

	}
	printf("\nend\n");
	return 0;
}