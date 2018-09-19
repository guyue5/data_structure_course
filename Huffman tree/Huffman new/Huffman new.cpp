// Huffman new.cpp : 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include "stdlib.h"
#include "string.h"
#include "conio.h"

#define MaxValue 100

/*哈夫曼树结构体*/
typedef  struct
{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
	char name;
}HTNode,*HuffmanTree;

typedef char **HuffmanCode;
	

/*构造哈夫曼树*/
void TreeCreate( HuffmanTree &HT, int *w, int n, char *s )
{//w存放n各字符的权值（均大于0），构造哈夫曼树HT，并求出n个字符的哈夫曼编码HC
	if (n<=1)
		return;
	int m=2*n-1;
	HT=(HuffmanTree)malloc( m*sizeof(HTNode));
	int i;
	HTNode *p;
	for (p=HT,i=0;i<n;++i,++p,++w,++s)
	{
		p->weight =*w;
		p->lchild =0;
		p->parent =0;
		p->rchild =0;
		p->name = *s;
	}//n个结点赋初值
		
	for ( ;i<m;++i,++p)
	{
		p->weight =0;
		p->lchild =0;
		p->parent =0;
		p->rchild =0;
		p->name = '#';
	}//其余结点初始化
	int m1,m2;//存放权重
	int s1,s2;
	for (int i=0; i<n-1; i++)
	{
		m1=m2=MaxValue;
		s1=s2=1;//存放序号
		for (int j=0; j< n+i; j++)//增加的结点
		{
			if (HT[j].parent == 0 && HT[j].weight < m1)
			{
				m2=m1;
				s2=s1;
				m1=HT[j].weight ;
				s1=j;
			}
			else if ( HT[j].parent ==0 && HT[j].weight < m2)
			{
				m2=HT[j].weight ;
				s2=j;
			}
		}
			HT[s1].parent = n+i; HT[s2].parent = n+i;
		    HT[n+i].lchild = s1;HT[n+i].rchild = s2;
		    HT[n+i].weight = HT[s1].weight + HT[s2].weight ;
		
	}
	/*for (int i=1; i<=m; i++)
		printf("%c,%d,%d,%d,%d\n",HT[i].name ,HT[i].lchild ,HT[i].rchild ,HT[i].parent ,HT[i].weight );*/
}
	
	
	/*哈夫曼编码*/
void  HuffmanCoding( HuffmanTree &HT, HuffmanCode &HC, int n)
{
	HC = (HuffmanCode)malloc (n*sizeof(char*));
	char *cd;
	cd =(char *)malloc (n*sizeof(char));
	cd[n-1]='\0';//反序存放
	for (int i=0; i<n; ++i)
	{
		 int start = n-1;
		 for (int c=i,f=HT[i].parent ;f!=0;c=f,f=HT[f].parent )
		 {
			 if (HT[f].lchild == c)
				 cd[--start] = '0';//左子树编码为0
			 else 
				 cd[--start] = '1';//右子树编码为1
		 }
		 HC[i] =(char *)malloc ((n-start)*sizeof(char));
		 strcpy(HC[i],&cd[start]);	
		 printf("%c: %s\n",HT[i].name ,HC[i]);
	}

	 free(cd);
}


/*解码*/
void HCodeSolve( HuffmanTree &HT,char code[],int n)
{
	char *p;
	int q;
	p=code;
	q=2*n-1-1;
	while ((*p)!='\0')//从根节点开始寻找编码值
	{
		while (HT[q].lchild != 0 || HT[q].rchild != 0)
		{
			if (*p == '0')
				q = HT[q].lchild ;
			else 
				q = HT[q].rchild ;
			p++;
			if ( (*p)=='\0' && HT[q].lchild != 0 || HT[q].rchild != 0 )//编码已结束，但还没到叶子结点，则结束
				break;
		}
	}	
	printf("the name is %c\n",HT[q].name );
	
}

/*输入字符，输出对应的编码*/
void PutCode(char name, HuffmanCode &HC,HuffmanTree HT,int n )
{
	for (int i=0; i<n;i++)
		if (HT[i].name == name)
			printf ("the code is :%s\n",HC[i]);	
}


/*主函数*/
int _tmain(int argc, _TCHAR* argv[])
{
	HuffmanTree HT;
	HuffmanCode HC;
	int n=7;
	int w[7]={3,4,1,4,2,6,8};
	char *s="abcdefg";
	TreeCreate( HT,w,n,s);
	int m=2*n-1;
	//HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));
	for (int i=0; i<m; i++)
		printf("%c,%d,%d,%d,%d\n",HT[i].name ,HT[i].lchild ,HT[i].rchild ,HT[i].parent ,HT[i].weight );//输出树
	HuffmanCoding( HT, HC, n);//输出编码
	printf("input a name：\n");
	char name;
	name = getchar();
	PutCode( name,HC, HT, n );//输入字符，输出对应的编码
	char code[100];	
	printf("input the code:");
	scanf("%s",code);
	HCodeSolve( HT,code, n);//输出解码后的字母
	getchar();
	getchar();                                                                                                                                                                                                                         
}


