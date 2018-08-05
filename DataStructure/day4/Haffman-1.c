#include "targetver.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <tchar.h>
#include "stdafx.h"
#include <stdbool.h>
#define SIZE 27

//链表+树结构构造haffman树（未完工）
//1.存储权值表，采用链表，同时存储所有相关信息
//2.构造二叉树，利用从链表里找出最小值加入，同时将构造出的枝节也“插入到链表”，并标记出，他们是“非叶子”
//3.根据二叉树得到编码和解码表

typedef struct HaffmanTree
{
	char c;
	bool isLeaf;
	struct HaffmanTree *left;
	struct HaffmanTree *right;
}Tree;

typedef struct nodelist
{
	bool isLeaf;//用于makeLeaf
	int val;//存储权值
	char c = 0x1;//存储ascii
	struct nodelist * next;//链表的下一个节点
	Tree * inTree = NULL;//该点是否为huffman的中间节点（用处在makeLeaf函数里）
}List;

List* makeList(int *weigth);
Tree* makeHaffman(List *head);
void DeleteList(List *p);
Tree * putLeaf( List *m, List *n);

void putTree(Tree * T) {
	if (T == NULL)printf("0 ");
	else {
		printf("%c ", T->c);
		putTree(T->left);
		putTree(T->right);

	}
}

//头插法创造好链表，便于后续构造树
List* makeList(int *weigth) {
	List * head, *p;
	int i;
	head = (List*)malloc(sizeof(List));
	head->val = weigth[0];
	head->isLeaf = true;
	head->c = 0x41;
	head->next = NULL;
	for (i = 1; i<SIZE; i++) {
		p = (List*)malloc(sizeof(List));
		p->val = weigth[i];
		p->isLeaf = true;
		if (i != 26) {
			p->c = i + 0x41;
		}//对应的ascii
		else p->c = 0x20;//空格
		p->next = head->next;
		head->next = p;
	}
	return head;
}


Tree* makeHaffman(List *head) {
	Tree * T;
	//p是遍历指针，m和n是最小的两个,其中m最小
	List *m = head;
	List *n = head->next;
	List * p = head;
	while (head->next->next != NULL) {
		while (p != NULL) {
			if (p->val < m->val) {
				m = p;
				n = m;
			}
			p = p->next;
		}
		p = head;
		putLeaf(m,n);
		while (p->next != NULL) {
			if (p->next == n) {
				p->next = n->next;
				free(n);
				break;
			}
			p = p->next;
		}
		p = head;
		m = head;
		n = head->next;
	}
	if (m->val > n->val) {
		List *temp = m;
		m = n;
		n = temp;
	}
	T = putLeaf(m, n);
	return T;
}


//void DeleteList(List *p) {
//	if (p->next == NULL) {
//		free(p);
//		p = NULL;
//	}
//	else {
//		p->val = p->next->val;
//		p->isLeaf = p->next->isLeaf;
//		p->inTree = p->next->inTree;
//		p->next = p->next->next;
//		free(p->next);
//	}
//}

//putLeaf作用是把找到的这俩最小值给放到树上
Tree * putLeaf( List *m, List *n) {
	Tree * mT, *nT, *Root;

	if (m->inTree == NULL) {
		mT = (Tree*)malloc(sizeof(Tree));
		mT->isLeaf = m->isLeaf;
		mT->c = m->c;
		mT->left = NULL;
		mT->right = NULL;
	}
	else {
		mT = m->inTree;
	}
	if (n->inTree == NULL) {
		nT = (Tree*)malloc(sizeof(Tree));
		nT->isLeaf = n->isLeaf;
		nT->c = n->c;
		nT->left = NULL;
		nT->right = NULL;
	}
	else {
		nT = m->inTree;
	}
	Root = (Tree*)malloc(sizeof(Tree));
	Root->isLeaf = false;
	Root->c = 0x1;
	Root->left = mT;
	Root->right = nT;
	//设置完二叉树，接下来要把这个树枝节点放入链表的新节点中,这里就把m改造为该所需节点，然后删除n：
	m->val = m->val + n->val;
	m->inTree = Root;
	m->isLeaf = false;
	return Root;
	//DeleteList(n);
	return NULL;
}




int main(int argc, char const *argv[])
{
	//weight是权值表
	int weigth[SIZE] = {
		64,13,22,32,103,21,15,47,57,1,5,32,20,57,
		63,15,1,48,51,80,23,8,18,1,16,1,168
	};
	List * p = makeList(weigth);

	Tree * T = makeHaffman(p);

	putTree(T);
	return 0;
}