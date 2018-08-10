
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
//typedof struct list {		
//	int number;
//	struct list *next;
// 
//}LIST;
//
//LIST *creat(int n)
//{
//	int i,x;
//	LIST *head,*p1,*p2;
//	head=NULL;
//	for(i=0;i<n;i++)
//	{
//		p1=(LIST*)malloc(sizeof(LIST));
//		scanf("%d",&x);
//		p1->number=x;
//		if(head==NULL)
//		{
//			head=p1;p2=p1;
//		} 
//		else
//		{
//			p2->next=p1;
//			p2=p1;
//		}
//		p2->next=NULL;
//	}
//	return head;     
//}

int cmp(const void* a;const void *b){
	return *(int *)a - *(int *)b;
}

int main()
{
	int N;
	
	scanf("%d",&N);
	int *p;
	p = (int*)malloc(N*(sizeof(int)));

	int i;
	for(i=0;i<N;i++){
		scanf("%d",&p[i]);
	}
	qsort(p,N,sizeof(int),cmp);
	for(i=0;i<N;i++){
		printf("%d",p[i]);
	}
	int x;
	printf("\n请输入要插入的数据：");
	scanf("%d",&x);
	for(i=0;i<N-1;i++){
		printf(" %d ",p[i]);
		if(x>=p[i] && x<=p[i+1])printf(" %d ",x);	
	}
	printf(" %d ",p[i]);
	if(x>p[i])printf(" %d ",x);
	
	
}
