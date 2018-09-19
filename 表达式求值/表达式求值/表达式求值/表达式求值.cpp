#include"stdafx.h"
#include"string.h"
#include"stdlib.h"

#define OVERFLOW 0
#define OK 1
#define ERROR 0

#define OPSETSIZE 7
unsigned char Prior[7][7] =
{// ��3.1  ���������ȹ�ϵ
	'>','>','<','<','<','>','>',
	'>','>','<','<','<','>','>',
	'>','>','>','>','<','>','>',
	'>','>','>','>','<','>','>',	
	'<','<','<','<','<','=',' ',
	'>','>','>','>',' ','>','>',
	'<','<','<','<','<',' ','='
};		
char OPSET[OPSETSIZE]={'+' , '-' , '*' , '/' ,'(' , ')' , '#'};


//ջ��˳��洢��ʾ
#define STACK_INIT_SIZE 100 //�洢�ռ��ʼ������
#define STACKINCREMENT 10 //�洢�ռ��������

typedef struct
{
	char *base; 
	char *top; 
	int stacksize; 
}StackChar;//������ջ

typedef struct
{
	float *base; 
	float *top; 
	int stacksize; 
}StackFloat;//������ջ

int InitStack(StackChar &S)
{	//����һ��������ջS
	S.base=(char*)malloc(STACK_INIT_SIZE*sizeof(char));
	if(!S.base)
		exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return OK;
}

int InitStack(StackFloat &S)
{	//����һ��������ջS
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
}//��������ջ

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
}//��������ջ

int Pop(StackChar &S,char &e)
{
	if(S.top==S.base)
		return ERROR;
	e=*--S.top;
	return OK;
}//��������ջ

int Pop(StackFloat &S,float &e)
{
	if(S.top==S.base)
		return ERROR;
	e=*--S.top;
	return OK;

}//��������ջ

//��������ջ���գ�����e����s��ջ��Ԫ�أ�������OK;���򷵻�ERROR
int GetTop(StackChar S,char &e)
{
	if(S.top==S.base)
		return ERROR;
	e=*(S.top-1);
	return OK;

}

//��������ջ���գ�����e����s��ջ��Ԫ�أ�������OK;���򷵻�ERROR
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
}//����	

int In(char Test,char* TestOp)
{
	bool Find=false;
	for (int i=0; i< OPSETSIZE; i++)
	{
		if (Test == TestOp[i])
			Find = true;
	}
	return Find;
}//�ж��Ƿ�Ϊ�����

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
}//������������������ȼ�

float EvaluateExpression()
{
	// ��OPTR��OPND�ֱ�Ϊ�����ջ��������ջ��OPΪ��������ϡ�
	StackChar  OPTR;// �����ջ���ַ�Ԫ��
	StackFloat OPND;// ������ջ��ʵ��Ԫ��
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
				Data=atof(TempData);//�������Ϊ�ַ���������atof�������ַ���ת��Ϊ������
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
	printf("��������ʽ:\n");
	printf("%f\n",EvaluateExpression());
	system("pause");
	return 0;
}
