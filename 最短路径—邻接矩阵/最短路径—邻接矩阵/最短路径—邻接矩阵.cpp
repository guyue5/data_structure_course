// ���·�����ڽӾ���.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "windows.h"

#define MAX 20 //������ඥ�����
#define INFINITE 1000  //���������

int cost[MAX][MAX]; // ��Ȩ�ڽӾ���
int route[MAX]; // ���·��
POINT vertexcollection[MAX];//������Ϣ

HWND hwnd =::GetConsoleWindow ();
HDC hdc = ::GetDC (hwnd);

/*void ClearWindows(HWND hwnd,HDC hdc) //����
{
	InvalidateRect( hwnd, NULL ,false );
	UpdateWindow( hwnd );
}*/



/*����������*/
void CreatUDN(int n)
{
	::SelectObject(hdc,GetStockObject(DC_PEN));
    ::SetDCPenColor(hdc,RGB(255,0,0));   
	int x,y;
	char name[3];

	int ok=1;
	int vertex1,vertex2,weight;
	for (int i=0; i<n; i++)//��ʼ���ڽӾ���
	{
		for (int j=0; j<n; j++)
			cost[i][j] = INFINITE;
		cost[i][i] = 0;
	}
	printf("��������ƺͶ��������:\n");
	for (int j=0; j<n; j++)
	{
		scanf("%s%d%d",&name[0],&vertexcollection[j].x ,&vertexcollection[j].y);
		TextOutA(hdc,vertexcollection[j].x,vertexcollection[j].y,name,3);

	}
	printf("��������ߣ���0,0,0,��ʾ����:\n");
	int i=1;
	while (ok)
	{	
		printf("��%d���ߵ���������Ϊ,ȨֵΪ:\n",i);
		scanf("%d,%d,%d",&vertex1,&vertex2,&weight);	
		
		if (vertex1 == 0 && vertex2 == 0 && weight == 0)
		{
			ok = 0;
		}
		else if(0<=vertex1 && vertex1<n && 0<=vertex2 && vertex2<n && weight >0)
		{
			MoveToEx(hdc,vertexcollection[vertex1].x,vertexcollection[vertex1].y,NULL);
			LineTo(hdc,vertexcollection[vertex2].x,vertexcollection[vertex2].y );
			++i;
			cost[vertex1][vertex2] = weight;//�洢ʱ���Ϊ������Ԫ��
		}
		else
			printf("error!����������");
	}	

}


/*�������·��*/
void ShortestPath_DIJ( int v0,int vt,int n,int P[MAX][MAX] )
{
	::SelectObject(hdc,GetStockObject(DC_PEN));
    ::SetDCPenColor(hdc,RGB(0,255,0)); 

	int temp  ,dis;
	int j,m=0,i,u=1;
	int s[MAX];
	for (int i=0; i<n; i++)
	{
		route[i] = cost[v0][i];
		s[i] = 0;
		
	    
	}
	s[v0] = 1;
	for (int k=1; k<n; k++)
	{
	    temp= INFINITE;//��ʼ��
	    for ( i=0; i<n; i++)//�ҵ���v0��ص���С��·��
		if ( s[i]==0 && route[i] < temp)
		{
			j=i;
			temp = route[i];
			//P[i][0]=v0;
		}

		s[j]=1;		
		
	   for ( i=0; i<n; i++)
	   {
		 if (s[i]==0)
		  {
			dis = route[j]+cost[j][i];
			if ( dis < route[i])
			{
				route[i] = dis;
				P[i][u++]=j;
			}
		  }
	   }
	}
	
	printf ("���·��������%d:",route[vt]);
}




int _tmain(int argc, _TCHAR* argv[])
{
	
	printf("�����붥����Ŀ��");
	int n;
	scanf("%d",&n);
	CreatUDN(n);
	printf("��������ʼ������յ�:");
	int v0,vt;
	scanf("%d,%d",&v0,&vt);
	int P[MAX][MAX];
	ShortestPath_DIJ(v0,vt,n,P);
	ReleaseDC( hwnd, hdc );
	getchar();
	getchar();

	return 0;
}

