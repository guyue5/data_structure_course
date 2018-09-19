// �Ľ���������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "conio.h";

#define MAXSIZE 20

typedef struct
{
	int key;
}Seq;//����һ���ṹ���Źؼ���

typedef struct
{
	Seq r[MAXSIZE];
	int length;
}SqList;//����˳���

/********����ȡ�з�ѡȡ�����¼********/
Seq Middle(SqList &L,int low,int high)
{
	int a = L.r[low].key ;
	int b = L.r[high].key ;
	int c = L.r[(low+high)/2].key ;

	if (( a>=b && b>=c) || ( c>=b && b>=a))
		return L.r[high] ;
	else if
		(( b>=c && c>=a) || (a>=c && c>=b))
		return L.r[(low+high)/2] ;
	else
		return L.r[low] ;

}


/********һ�˿����������********/
int Partition(SqList &L,int low,int high)
{
	int pivotkey;
	Seq temp;
	//temp = L.r[0];
	//L.r[0] = Middle( L,low,high );//���ӱ�ĵ�һ����¼�������¼
	temp = Middle( L,low,high );
	if (temp.key == L.r[high].key)//�ж������¼��λ��
	{
		L.r[high].key = L.r[low].key;
		L.r[low].key = temp.key;
	}
	else if( temp.key == L.r[(low+high)/2].key)	
	{
		 L.r[(low+high)/2].key = L.r[low].key;
		 L.r[low].key = temp.key;
	}
	else
		L.r[low].key = temp.key;

	pivotkey = L.r[low].key ;//�����¼�ؼ���
	while (low < high)//�ӱ�����˽������м�ɨ�裬ֱ������
	{
		while (low < high && L.r[high].key>=pivotkey)
			--high;
		L.r[low] = L.r[high];
		while (low<high && L.r[low].key<=pivotkey)
			++low;
		L.r[high] = L.r[low];
	}
	L.r[low].key = pivotkey;//������λ�ü�¼��λ
	return low;

}

/********�ݹ�����********/
void QSort(SqList &L,int low,int high)
{
	int pivotloc;
	if (low < high)//����>1
	{
		pivotloc = Partition(L,low,high);//Ϊ��һ���ؼ��ֵ�λ�ã��Դ�Ϊ����
		QSort(L,low,pivotloc-1);//�Ե��ӱ�ݹ�����
		QSort(L,pivotloc+1,high);//�Ը��ӱ�ݹ�����
	}
}

/********��������********/
void QuickSort(SqList &L)
{
	QSort(L,0,L.length-1);
	for (int i=0; i< L.length; i++)
		printf ("%5d",L.r[i].key);
}

/********������********/
int _tmain(int argc, _TCHAR* argv[])
{
	SqList L;
	//int length;
	printf("�������:");
	scanf("%d",&L.length);
	printf("������Ҫ���������:\n");
	Seq r[MAXSIZE];
	int num;
	for (int i=0; i< L.length; i++)
	{
		scanf ("%d",&num);
		L.r[i].key  = num;
		
	}
	printf("����������Ϊ��\n");
	//SqList L;
	QuickSort(L);
	getch();

	return 0;
}

