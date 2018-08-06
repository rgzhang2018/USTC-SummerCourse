#include <stdio.h>
#include <stdlib.h>
//构建Hash表，H(key)=key%P ，其中P=11.用两种方法实现

#define P 11
#define LONG 13//LONG是指线性哈希表的实际长度，一般是取大于P的最小素数


typedef struct HList
{
	int val;
	struct HList* next;
}Hash;

void hash1Add(int *hash, int num, int temp) {
	if (hash[temp] == -1)hash[temp] = num;
	else {
		temp++;
		temp %= LONG;//保证不会溢出
		hash1Add(hash, num,temp );
	}
}

void hash2Add(Hash hash2[],int x,int temp) {
	Hash* p = (Hash*)malloc(sizeof(Hash));
	p->next = hash2[temp].next;
	hash2[temp].next = p;
	p->val = x;
}

int main(int argc, char const *argv[])
{
	int key[12] = {
		19,14,23,1,68,20,84,27,56,11,10,79
	};
	int hash1[LONG];
	Hash hash2[P];
	//初始化Hash表
	for (int i = 0; i<LONG; i++) {
		hash1[i] = -1;
	}

	printf("num in hash-array:\n");
	for (int i = 0; i<12; i++) {
		int x = key[i];
		int temp = x % P;
		if (hash1[temp] == -1) {
			hash1[temp] = x;
		}
		else hash1Add(hash1, x, temp);
	}
	for (int i = 0; i<LONG; i++) {
		printf("%d\n", hash1[i]);
	}

	//初始化
	for (int i = 0; i<P; i++) {
		hash2[i].val = -1;
		hash2[i].next = NULL;
	}
	//存储
	for (int i = 0; i<12; i++) {
		int x = key[i];
		int temp = x % P;
		if (hash2[temp].val == -1) {
			hash2[temp].val = x;
		}
		else hash2Add(hash2, x, temp);
	}
	printf("\n num in hash-linkList:\n");
	//打印
	for (int i = 0; i<P; i++) {
		printf("%d ", hash2[i].val);
		Hash *p = hash2[i].next;
		while (p!= NULL) {
			printf("-> %d ", p->val);
			p = p->next;
		}
		printf("\n");
	}
	return 0;
}