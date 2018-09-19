// ����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "windows.h"
#define overflow 0

typedef int datatype;

typedef struct queuenode
{//����һ���洢�ṹ
	datatype data;
	queuenode* next;
}LNode;

typedef struct
{//����βָ��
	LNode* rear;
}LQueue;

LNode *InitQueue(LQueue &Q)
{//��ʼ������
	Q.rear=(queuenode* )malloc(sizeof(queuenode));
	if (!Q.rear ) exit(overflow);//�洢����ʧ��
	Q.rear->next=Q.rear;
    Q.rear->data=NULL ;//��βָ��ָ��ͷ���
	LNode* s;
	while (Q.rear !=Q.rear ->next )
	{//���в���ʱ��ɾ��s
		s=Q.rear ->next ;
		Q.rear ->next =s->next ;
		free(s);
	}
	return Q.rear;
}


int QueueEmpty(LQueue &Q)
{//�ж϶����Ƿ�Ϊ��
	if (Q.rear ->next == Q.rear ->next->next )//��ͷָ��ָ���Լ�����Ϊ��
		return 1;
	else
		return 0;
}


LNode* EnQueue(LQueue &Q,datatype x)
{//���,����Ԫ��Ϊe���µĶ�βԪ��
	LNode* e=(LNode *)malloc(sizeof(LNode));
	e->data=x;
	e->next =Q.rear ->next ;
	Q.rear ->next =e;
	Q.rear =e;//��βָ�������½��
	return Q.rear ;
}


int DeQueue(LQueue &Q)
{//���ӣ�ɾ��
	LNode *e;
	datatype x;
	if  (QueueEmpty(Q))
	return overflow;//�ж��Ƿ�Ϊ�ն�
	e=Q.rear->next->next;
	x=e->data;
	if(e==Q.rear )
	{
		Q.rear =Q.rear->next;
		Q.rear ->next=e->next;
	}
	else
		Q.rear->next ->next =e->next ;
	free(e);//�ͷŽ��
	return 1;
}

void PriQueue(LNode *rear)
{
	LNode *q=rear->next->next;
	for(;q->data !=NULL;q=q->next)
	{
		printf("%d  ",q->data);
	}//ѭ������ԭ������ӵ�Ԫ��Ҳ���
	printf("\n");
}

int _tmain(int argc, _TCHAR* argv[])
{ 
	int x;
	LQueue Q;
	LNode *rear=InitQueue(Q);//��ʼ������

	printf("�������1����������-1������������0 : ");
	scanf("%d",&x);

	while(x!=0)
	{
		if(x==1)
		{
			printf("��������ӵ����֣�");
			int num;
	        scanf("%d",&num); 
			Q.rear=EnQueue(Q, num);
		}
		else if(x==-1)
		{
			if(!QueueEmpty(Q))
			{
			printf("ɾ��Ԫ�غ����Ϊ��");
	        DeQueue(Q);
			}
			else 
				printf("�ӿ�\n");
		}
		PriQueue(rear);
		printf("��������Ӽ���1,�����Լ���-1,������������0 : ");
	    scanf("%d",&x);

	}
	return 0;
}







	



	


