// 数组和广义表.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include "conio.h"

//清除窗口内容
void ClearWindows(HWND hwnd,HDC hdc)
{
	InvalidateRect( hwnd, NULL ,false );
	UpdateWindow( hwnd );
}


int _tmain(int argc, _TCHAR* argv[])
{
	HWND hwnd =::GetConsoleWindow ();
	HDC hdc = ::GetDC (hwnd);//获取控制台窗口句柄

	FILE *fp =fopen("..\\图片int.dat","rb");
	if (fp)
	{
		int width,height;
		fread( &width, sizeof(int),1,fp);
		fread( &height, sizeof(int),1,fp);//读取高度和宽度

		int num=width*height;

		COLORREF *dpi = (COLORREF*)malloc ( ( num + 1)*sizeof(COLORREF) );
		COLORREF **pic = (COLORREF**)malloc (height* sizeof(COLORREF*));
		
		for (int row=0; row <height; ++row)
			pic[row]=dpi + row*width;//按行存储地址

		fread(dpi,sizeof(COLORREF),num,fp);
		dpi[num] = dpi[num - 1] - 1;//多分配的单元作为哨兵单元，必须与最后一个图像像素值不同

		printf("原图像为：\n");
		getch();
		for (int row=0; row <height; ++row)
			for (int col=0; col<width; ++col)
				::SetPixel( hdc,col,row, pic[row][col] );//用数组保存图像信息

		fclose(fp);
		system("pause");
		system("cls");
		ClearWindows(hwnd,hdc);


		int count1 = 0;
		for (int i = 0; i < num ; i++)
		{
			if (dpi[i]!=dpi[i+1])
			{
				count1++;
			}
		}//找出共有多少个不同的数，以便分配内存

		COLORREF *dpi2 = (COLORREF*)malloc ( 2*count1*sizeof(COLORREF));
		int k = 0;
		int count2=0;
		for (int i = 0; i < num; i++)
		{
			++count2;
			if( dpi[i] != dpi[i+1] )
			{
				dpi2[2*k] = dpi[i];
				dpi2[2*k+1] = (COLORREF)count2;
				++k;
				count2 = 0 ;
			}
		}//采用游程编码进行压缩，记录长度

		FILE *fp1 =fopen("..\\图片1int.dat","wb");
		fwrite( &count1, sizeof(int),1,fp1);
		fwrite( &width, sizeof(int),1,fp1);
		fwrite( &height, sizeof(int),1,fp1);
	    fwrite(dpi2,sizeof(COLORREF),2*count1,fp1);
		free(dpi);
		free(pic);
		free(dpi2);
		fclose(fp1);
			   
	    FILE * fp2 = fopen("../图片1int.dat","rb");
		fread(&count1,sizeof(int),1,fp2);
		fread(&width,sizeof(int),1,fp2);
		fread(&height,sizeof(int),1,fp2);
		dpi2 = (COLORREF*)malloc ( 2*count1*sizeof(COLORREF));
		fread(dpi2,sizeof(COLORREF),2*count1,fp2);//读取压缩后的图像
		fclose(fp2);

		COLORREF *dpi3= (COLORREF*)malloc (width*height*sizeof(COLORREF));	
		long m=0;
		for(int i=0; i< count1; i++)
		{
			int count = (int)dpi2[2*i+1];
			COLORREF color = dpi2[2*i];
			for(int p=1;p <= count;p++)
			{
				dpi3[m++] = color;
			}

		}//解压
			
		COLORREF **pic1 = (COLORREF**)malloc (height* sizeof(COLORREF*));

		for ( int row = 0 ; row < height; ++row)
			pic1[row] = dpi3+ row* width;

		printf("解压后的图像为:\n");
		getch();
		for (int row=0; row <height; row++)
			for (int col=0; col<width; col++)
				::SetPixel( hdc,col,row, pic1[row][col] );//显示图像

		system("pause");
		system("cls");
		ClearWindows(hwnd,hdc);
	
		free(pic1);
		free(dpi2);
		free(dpi3);

		}
	    ReleaseDC(hwnd,hdc);
		getch();
		return 0;		
}
				
	


	
	

	
	



	