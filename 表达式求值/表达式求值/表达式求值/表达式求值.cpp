#include"stdafx.h"
#include"string.h"
#include"stdlib.h"

#define OVERFLOW 0
#define OK 1
#define ERROR 0

#define OPSETSIZE 7
unsigned char Prior[7][7] =
{// 表3.1  算符间的优先关系
	'>','>','<','<','<','>','>',
	'>','>','<','<','<','>','>',
	'>','>','>','>','<','>','>',
	'>','>','>','>','<','>','>',	
	'<','<','<','<','<','=',' ',
	'>','>','>','>',' ','>','>',
	'<','<','<','<','<',' ','='
};		
char OPSET[OPSETSIZE]={'+' , '-' , '*' , '/' ,'(' , ')' , '#'};


//栈的顺序存储表示
#define STACK_INIT_SIZE 100 //存储空间初始分配量
#define STACKINCREMENT 10 //存储空间分配增量

typedef struct
{
	char *base; 
	char *top; 
	int stacksize; 
}StackChar;//操作符栈

typedef struct
{
	float *base; 
	float *top; 
	int stacksize; 
}StackFloat;//操作数栈

int InitStack(StackChar &S)
{	//构造一个操作符栈S
	S.base=(char*)malloc(STACK_INIT_SIZE*sizeof(char));
	if(!S.base)
		exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return OK;
}

int InitStack(StackFloat &S)
{	//构造一个操作数栈S
	S.base=(float*)malloc(STACK_INIT_SIZE*sizeof(float));
	if(!S.base)
		exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return OK;
}

int Push(StackChar &S, char e)
{
	if(S.top-S.base >= S.stacksize)
	{
		S.base=(char*)realloc(S.base,
			(S.stacksize+STACKINCREMENT)*sizeof (char));
		if(!S.base)
			return (OVERFLOW);
		S.top=S.base+S.stacksize;
		S.stacksize+=STACKINCREMENT;
	}
	*S.top++=e;
	return OK; 
}//操作符进栈

int Push(StackFloat &S, float e)
{
	if(S.top-S.base >= S.stacksize)
	{
		S.base=(float*)realloc(S.base,
			(S.stacksize+STACKINCREMENT)*sizeof (float));
		if(!S.base)
			return (OVERFLOW);
		S.top=S.base+S.stacksize;
		S.stacksize+=STACKINCREMENT;
	}
	*S.top++=e;
	return OK; 
}//操作数进栈

int Pop(StackChar &S,char &e)
{
	if(S.top==S.base)
		return ERROR;
	e=*--S.top;
	return OK;
}//操作符出栈

int Pop(StackFloat &S,float &e)
{
	if(S.top==S.base)
		return ERROR;
	e=*--S.top;
	return OK;

}//操作数出栈

//若操作符栈不空，则用e返回s的栈顶元素，并返回OK;否则返回ERROR
int GetTop(StackChar S,char &e)
{
	if(S.top==S.base)
		return ERROR;
	e=*(S.top-1);
	return OK;

}

//若操作数栈不空，则用e返回s的栈顶元素，并返回OK;否则返回ERROR
int GetTop(StackFloat S,float &e)
{
	if(S.top==S.base)
		return ERROR;
	e=*(S.top-1);
	return OK;

}

float Operate(float a,unsigned char theta, float b)
{
	switch(theta)
	{
	case '+':
		return a+b;
	case '-':
		return a-b;
	case '*':
		return a*b;
	case '/':
		return a/b;
	default:
		return 0;
	}
}//运算	

int In(char Test,char* TestOp)
{
	bool Find=false;
	for (int i=0; i< OPSETSIZE; i++)
	{
		if (Test == TestOp[i])
			Find = true;
	}
	return Find;
}//判断是否为运算符

int ReturnOpOrd(char op,char* TestOp)
{
	int i;
	for(i=0; i< OPSETSIZE; i++)
	{
		if (op == TestOp[i])
			return i;
	}
	return 0;
}

char precede(char Aop, char Bop)
{
	return Prior[ReturnOpOrd(Aop,OPSET)][ReturnOpOrd(Bop,OPSET)];
}//查找两个运算符的优先级

float EvaluateExpression()
{
	// 设OPTR和OPND分别为运算符栈和运算数栈，OP为运算符集合。
	StackChar  OPTR;// 运算符栈，字符元素
	StackFloat OPND;// 运算数栈，实数元素
	char TempData[20];
	float Data,a,b;
	char theta,c,x,Dr[2];

	char e;
	float d;
	
	InitStack (OPTR);
	Push (OPTR, '#');
	InitStack (OPND);
	c = getchar();
	strcpy(TempData,"\0");
	while (c!= '#' || (GetTop(OPTR,e),e)!= '#')
	{
		if (!In(c, OPSET))
		{
			Dr[0]=c;
			Dr[1]='\0';
			strcat(TempData,Dr);
			c = getchar();
			if(In(c,OPSET))
			{
				Data=atof(TempData);//若输入的为字符串，则用atof函数将字符串转化为浮点数
				Push(OPND, Data);
				strcpy(TempData,"\0");
			}
		}
		else
		{
			switch (precede((GetTop(OPTR,e),e), c))
			{
			case '<':
				Push(OPTR, c);		
				c = getchar();
				break;
			case '=':
				Pop(OPTR, x);
				c=getchar();
				break;
			case '>':
				Pop(OPTR, theta);
				Pop(OPND, b);
				Pop(OPND, a);
				Push(OPND, Operate(a, theta, b));
				break;
			}
		}
	}
	return (GetTop(OPND,d),d);
}


int _tmain(int argc, _TCHAR* argv[])
{
	printf("请输入表达式:\n");
	printf("%f\n",EvaluateExpression());
	system("pause");
	return 0;
}
