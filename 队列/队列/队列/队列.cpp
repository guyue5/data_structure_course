// 队列.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#define overflow 0

typedef int datatype;

typedef struct queuenode
{//定义一个存储结构
	datatype data;
	queuenode* next;
}LNode;

typedef struct
{//定义尾指针
	LNode* rear;
}LQueue;

LNode *InitQueue(LQueue &Q)
{//初始化队列
	Q.rear=(queuenode* )malloc(sizeof(queuenode));
	if (!Q.rear ) exit(overflow);//存储分配失败
	Q.rear->next=Q.rear;
    Q.rear->data=NULL ;//将尾指针指向头结点
	LNode* s;
	while (Q.rear !=Q.rear ->next )
	{//队列不空时，删除s
		s=Q.rear ->next ;
		Q.rear ->next =s->next ;
		free(s);
	}
	return Q.rear;
}


int QueueEmpty(LQueue &Q)
{//判断队列是否为空
	if (Q.rear ->next == Q.rear ->next->next )//若头指针指向自己，则为空
		return 1;
	else
		return 0;
}


LNode* EnQueue(LQueue &Q,datatype x)
{//入队,插入元素为e的新的队尾元素
	LNode* e=(LNode *)malloc(sizeof(LNode));
	e->data=x;
	e->next =Q.rear ->next ;
	Q.rear ->next =e;
	Q.rear =e;//将尾指针移至新结点
	return Q.rear ;
}


int DeQueue(LQueue &Q)
{//出队，删除
	LNode *e;
	datatype x;
	if  (QueueEmpty(Q))
	return overflow;//判断是否为空队
	e=Q.rear->next->next;
	x=e->data;
	if(e==Q.rear )
	{
		Q.rear =Q.rear->next;
		Q.rear ->next=e->next;
	}
	else
		Q.rear->next ->next =e->next ;
	free(e);//释放结点
	return 1;
}

void PriQueue(LNode *rear)
{
	LNode *q=rear->next->next;
	for(;q->data !=NULL;q=q->next)
	{
		printf("%d  ",q->data);
	}//循环，将原本已入队的元素也输出
	printf("\n");
}

int _tmain(int argc, _TCHAR* argv[])
{ 
	int x;
	LQueue Q;
	LNode *rear=InitQueue(Q);//初始化队列

	printf("入队输入1，出队输入-1，结束请输入0 : ");
	scanf("%d",&x);

	while(x!=0)
	{
		if(x==1)
		{
			printf("请输入入队的数字：");
			int num;
	        scanf("%d",&num); 
			Q.rear=EnQueue(Q, num);
		}
		else if(x==-1)
		{
			if(!QueueEmpty(Q))
			{
			printf("删除元素后队列为：");
	        DeQueue(Q);
			}
			else 
				printf("队空\n");
		}
		PriQueue(rear);
		printf("若继续入队键入1,若出对键入-1,结束操作键入0 : ");
	    scanf("%d",&x);

	}
	return 0;
}







	



	


