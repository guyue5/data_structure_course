// ����͹����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "windows.h"
#include "conio.h"

//�����������
void ClearWindows(HWND hwnd,HDC hdc)
{
	InvalidateRect( hwnd, NULL ,false );
	UpdateWindow( hwnd );
}


int _tmain(int argc, _TCHAR* argv[])
{
	HWND hwnd =::GetConsoleWindow ();
	HDC hdc = ::GetDC (hwnd);//��ȡ����̨���ھ��

	FILE *fp =fopen("..\\ͼƬint.dat","rb");
	if (fp)
	{
		int width,height;
		fread( &width, sizeof(int),1,fp);
		fread( &height, sizeof(int),1,fp);//��ȡ�߶ȺͿ��

		int num=width*height;

		COLORREF *dpi = (COLORREF*)malloc ( ( num + 1)*sizeof(COLORREF) );
		COLORREF **pic = (COLORREF**)malloc (height* sizeof(COLORREF*));
		
		for (int row=0; row <height; ++row)
			pic[row]=dpi + row*width;//���д洢��ַ

		fread(dpi,sizeof(COLORREF),num,fp);
		dpi[num] = dpi[num - 1] - 1;//�����ĵ�Ԫ��Ϊ�ڱ���Ԫ�����������һ��ͼ������ֵ��ͬ

		printf("ԭͼ��Ϊ��\n");
		getch();
		for (int row=0; row <height; ++row)
			for (int col=0; col<width; ++col)
				::SetPixel( hdc,col,row, pic[row][col] );//�����鱣��ͼ����Ϣ

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
		}//�ҳ����ж��ٸ���ͬ�������Ա�����ڴ�

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
		}//�����γ̱������ѹ������¼����

		FILE *fp1 =fopen("..\\ͼƬ1int.dat","wb");
		fwrite( &count1, sizeof(int),1,fp1);
		fwrite( &width, sizeof(int),1,fp1);
		fwrite( &height, sizeof(int),1,fp1);
	    fwrite(dpi2,sizeof(COLORREF),2*count1,fp1);
		free(dpi);
		free(pic);
		free(dpi2);
		fclose(fp1);
			   
	    FILE * fp2 = fopen("../ͼƬ1int.dat","rb");
		fread(&count1,sizeof(int),1,fp2);
		fread(&width,sizeof(int),1,fp2);
		fread(&height,sizeof(int),1,fp2);
		dpi2 = (COLORREF*)malloc ( 2*count1*sizeof(COLORREF));
		fread(dpi2,sizeof(COLORREF),2*count1,fp2);//��ȡѹ�����ͼ��
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

		}//��ѹ
			
		COLORREF **pic1 = (COLORREF**)malloc (height* sizeof(COLORREF*));

		for ( int row = 0 ; row < height; ++row)
			pic1[row] = dpi3+ row* width;

		printf("��ѹ���ͼ��Ϊ:\n");
		getch();
		for (int row=0; row <height; row++)
			for (int col=0; col<width; col++)
				::SetPixel( hdc,col,row, pic1[row][col] );//��ʾͼ��

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
				
	


	
	

	
	



	