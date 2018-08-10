


#include <stdio.h>
#include <stdlib.h>
//题目：二叉排序树的创建、查找、插入
//难点：删除操作
//做法：找到左孩子的右右右孩子或者右孩子的左左左孩子，用来代替根节点

typedef struct BSNode
{
	int val;
	struct BSNode * left, *right;
}BSTree;

int compare(const void* a, const void *b);
BSTree* CreateNode(int num,BSTree * s);
void perOrder(BSTree* t);
BSTree* findNode(BSTree * t, int num);
void deleteNode(BSTree* t,BSTree * root);
BSTree * findNextLeft(BSTree* T, BSTree* pre);
BSTree * findNextRight(BSTree* T, BSTree* pre);



int compare(const void* a, const void *b) {
	return *(int *)a - *(int *)b;
}


//常规创建方法，从无序表的第一个数字开始创建，以无序表的顺序形成二叉排序树
BSTree* CreateNode(int num, BSTree *s) {
	if (s == NULL) {
		BSTree *s = (BSTree*)malloc(sizeof(BSTree));
		s->left = NULL;
		s->right = NULL;
		s->val = num;
		return s;
	}
	else if (num<s->val)
	{
		s->left = CreateNode(num,s->left);
		return s;
	}
	else
	{
		s->right = CreateNode(num, s->right);
		return s;
	}

}

//除了常规方法，可以对有序数列用二分法创建二叉排序树，这时候是完全二叉树，查找效率远高于直接建立
//BSTree *Create(int a[], int low, int high)        //初始调用：low=0,high=n-1
//
//{
//	BSTree *b;
//	if (high - low + 1 == 0) return NULL;
//	int mid = (low + high) / 2;
//	b = (BSTree *)malloc(sizeof(BSTree));
//	b->val = a[mid];
//	b->left = Create(a, low, mid - 1);
//	b->right = Create(a, mid + 1, high);
//	return b;
//}

void perOrder(BSTree* t) {
	if (t == NULL)printf(" NULL ");
	else {
		printf(" %d ", t->val);
		if (t->left != NULL)perOrder(t->left);
		if (t->right != NULL)perOrder(t->right);
	}
}



BSTree* findNode(BSTree* root, int num) {
	BSTree *t = root;
	if (t->val == num)return t;
	if (t->val>num && t->left!=NULL)return findNode(t->left, num);
	if(t->val<num && t->right!=NULL)return findNode(t->right, num);
	return NULL;
	
}

void deleteNode(BSTree * t,BSTree * root) {
	
	if (t->left != NULL) {//如果左孩子不为空，左孩子的最右侧节点一定是可以用来替代跟节点的
		BSTree *nextroot = findNextRight(t->left,t);
		t->val = nextroot->val;
		free(nextroot);
	}
	else if (t->right != NULL) {
		BSTree *nextroot = findNextLeft(t->right ,t);
		t->val = nextroot->val;
		free(nextroot);
	}
	else {//如果是叶子节点，只需找到双亲，使之指向NULL，然后删除该叶子节点
		if (t == root) {
			free(t);
			root = NULL;
		}
		else{
			BSNode * n = root;
			while (n->left != t && n->right !=t) {
				if (t->val < n->val)n = n->left;
				else n = n->right;
			}
			if (n->left == t)n->left = NULL;
			else n->right = NULL;
			free(t);
			t = NULL;
		}
	}
}


BSTree * findNextLeft(BSTree* T, BSTree* pre) {
	BSTree * p = T;
	BSTree * q = pre;
	while (p->left != NULL) {//找到最下面的节点，即要用来替换删除的节点
		q = p;
		p = p->left;
	}
	if (q == pre)q->right = p->right;
	else q->left = p->right;//该节点的另一侧的子树直接交给它父亲，代替他的位置
	return p;
}

BSTree * findNextRight(BSTree* T, BSTree* pre) {
	BSTree * p = T;
	BSTree * q = pre;
	while (p->right != NULL) {//找到最下面的节点，即要用来替换删除的节点
		q = p;
		p = p->right;
	}
	if (q == pre)q->left = p->left;//如果没有循环，即p节点就是最近的节点，那么要让指向p节点的指针指向p的非空子节点
	else q->right = p->left;//如果进行了循环，q就代替了p之前的位置，这时候拿走p的话，q空缺的就是右节点了
	return p;
}

int main(int argc, char const *argv[])
{
	int len;
	printf("input nums of array:");
	scanf("%d", &len);
	int *nums;
	nums = (int*)malloc(len * sizeof(int));
	printf("input elemnets:");
	for (int i = 0; i<len; i++) {
		scanf("%d", &nums[i]);
	}
	//如果使用上述备注的非常规方法的话 需要在此对数列排序
	BSTree * t = (BSTree*)malloc(sizeof(BSTree));
	t->left = NULL;
	t->right = NULL;
	t->val = nums[0];
	for (int i = 1; i < len; i++) CreateNode(nums[i], t);
	printf("\n the perOrder of the BSTree:\n");
	perOrder(t);
	int number = 1;
	while (number != -1 && t!=NULL) {
		printf("\n Input the num to lookup(Inpute -1 to Exit):\n");
		scanf("%d", &number);
		fflush(stdin);
		BSTree * node = findNode(t, number);
		if (node == NULL)printf("\n No Find! \n");
		else {
			printf("Find it!\n");
			printf("Do you want Detete this node?(y/n)");
			char x = 0;
			scanf("%c", &x);
			fflush(stdin);//scanf 在循环中读入字符的时候可能会引入换行符
			if(x=='y'){
				deleteNode(node,t);
				printf("\nDelete node successful.\n");
				printf("\n the perOrder of the BSTree:\n"); 
				perOrder(t);
			}
			
		}
		

	}
	return 0;
}


