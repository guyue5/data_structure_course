// 最短路径—邻接矩阵.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"

#define MAX 20 //定义最多顶点个数
#define INFINITE 1000  //定义无穷大

int cost[MAX][MAX]; // 带权邻接矩阵
int route[MAX]; // 最短路径
POINT vertexcollection[MAX];//坐标信息

HWND hwnd =::GetConsoleWindow ();
HDC hdc = ::GetDC (hwnd);

/*void ClearWindows(HWND hwnd,HDC hdc) //清屏
{
	InvalidateRect( hwnd, NULL ,false );
	UpdateWindow( hwnd );
}*/



/*创建无向网*/
void CreatUDN(int n)
{
	::SelectObject(hdc,GetStockObject(DC_PEN));
    ::SetDCPenColor(hdc,RGB(255,0,0));   
	int x,y;
	char name[3];

	int ok=1;
	int vertex1,vertex2,weight;
	for (int i=0; i<n; i++)//初始化邻接矩阵
	{
		for (int j=0; j<n; j++)
			cost[i][j] = INFINITE;
		cost[i][i] = 0;
	}
	printf("顶点的名称和顶点的坐标:\n");
	for (int j=0; j<n; j++)
	{
		scanf("%s%d%d",&name[0],&vertexcollection[j].x ,&vertexcollection[j].y);
		TextOutA(hdc,vertexcollection[j].x,vertexcollection[j].y,name,3);

	}
	printf("请输入各边，以0,0,0,表示结束:\n");
	int i=1;
	while (ok)
	{	
		printf("第%d条边的两个顶点为,权值为:\n",i);
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
			cost[vertex1][vertex2] = weight;//存储时存的为上三角元素
		}
		else
			printf("error!请重新输入");
	}	

}


/*生成最短路径*/
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
	    temp= INFINITE;//初始化
	    for ( i=0; i<n; i++)//找到与v0相关的最小的路径
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
	
	printf ("最短路径长度是%d:",route[vt]);
}




int _tmain(int argc, _TCHAR* argv[])
{
	
	printf("请输入顶点数目：");
	int n;
	scanf("%d",&n);
	CreatUDN(n);
	printf("请输入起始顶点和终点:");
	int v0,vt;
	scanf("%d,%d",&v0,&vt);
	int P[MAX][MAX];
	ShortestPath_DIJ(v0,vt,n,P);
	ReleaseDC( hwnd, hdc );
	getchar();
	getchar();

	return 0;
}

