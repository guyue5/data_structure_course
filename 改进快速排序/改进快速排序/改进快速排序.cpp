// 改进快速排序.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "conio.h";

#define MAXSIZE 20

typedef struct
{
	int key;
}Seq;//定义一个结构体存放关键字

typedef struct
{
	Seq r[MAXSIZE];
	int length;
}SqList;//定义顺序表

/********三者取中法选取枢轴记录********/
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


/********一趟快速排序过程********/
int Partition(SqList &L,int low,int high)
{
	int pivotkey;
	Seq temp;
	//temp = L.r[0];
	//L.r[0] = Middle( L,low,high );//用子表的第一个记录做枢轴记录
	temp = Middle( L,low,high );
	if (temp.key == L.r[high].key)//判断枢轴记录的位置
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

	pivotkey = L.r[low].key ;//枢轴记录关键字
	while (low < high)//从表的两端交替想中间扫描，直至相遇
	{
		while (low < high && L.r[high].key>=pivotkey)
			--high;
		L.r[low] = L.r[high];
		while (low<high && L.r[low].key<=pivotkey)
			++low;
		L.r[high] = L.r[low];
	}
	L.r[low].key = pivotkey;//将枢轴位置记录到位
	return low;

}

/********递归排序********/
void QSort(SqList &L,int low,int high)
{
	int pivotloc;
	if (low < high)//表长度>1
	{
		pivotloc = Partition(L,low,high);//为第一个关键字的位置，以此为界限
		QSort(L,low,pivotloc-1);//对低子表递归排序
		QSort(L,pivotloc+1,high);//对高子表递归排序
	}
}

/********快速排序********/
void QuickSort(SqList &L)
{
	QSort(L,0,L.length-1);
	for (int i=0; i< L.length; i++)
		printf ("%5d",L.r[i].key);
}

/********主函数********/
int _tmain(int argc, _TCHAR* argv[])
{
	SqList L;
	//int length;
	printf("请输入表长:");
	scanf("%d",&L.length);
	printf("请输入要排序的序列:\n");
	Seq r[MAXSIZE];
	int num;
	for (int i=0; i< L.length; i++)
	{
		scanf ("%d",&num);
		L.r[i].key  = num;
		
	}
	printf("排序后的序列为：\n");
	//SqList L;
	QuickSort(L);
	getch();

	return 0;
}

