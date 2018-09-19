// draw.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "conio.h"
#include "windows.h"

int _tmain(int argc, _TCHAR* argv[])
{
	HWND hwnd = ::GetConsoleWindow();
	HDC hdc = ::GetDC( hwnd);

	::SelectObject( hdc, ::GetStockObject( DC_PEN));
	::SetDCPenColor( hdc, RGB( 255, 255, 0));

	::SelectObject( hdc, ::GetStockObject( DC_BRUSH));
	::SetDCBrushColor( hdc, RGB( 0, 255, 255));


	FILE* fp = fopen( "..\\shapes.txt", "r");
	if( fp)
	{
		char line[200];
		fgets( line,200, fp);
		//printf( "%s", line);
		
		int shapeCount;
		fscanf( fp, "%d\n",&shapeCount);
		//printf( "shapeCount = %d \n", shapeCount );
		//getch();

		int shapeType, id , vertexCount;
		int x,y;
		POINT vertexCollection[10];

		for( int i = 0 ; i < shapeCount; ++i)
		{
			fscanf( fp, "%d,%d,%d\n",&shapeType, &id , &vertexCount);
			//printf( "shapeType = %d ,id = %d, vertexCount = %d \n", shapeType,id, vertexCount );
			//getch();
			for( int j = 0 ; j < vertexCount; ++j)
			{
				fscanf( fp, "%d,%d\n",&vertexCollection[j].x, &vertexCollection[j].y );
				//fscanf( fp, "%d,%d\n",&x, &y );
				//printf( "x = %d ,y = %d \n", x, y );
				//getch();

			}
			switch( shapeType)
			{
			case 0:
				{
					x = vertexCollection[0].x;
					y = vertexCollection[0].y;
					::Ellipse( hdc,x - 5, y - 5, x + 5, y + 5 );
				}
				break;
			case 1:
				{
					::Polyline( hdc, vertexCollection, vertexCount);
				}
				break;
			case 2:
				{
					::Polygon( hdc, vertexCollection, vertexCount);
				}
				break;
			}
		}

		fclose(fp);
	}

	::ReleaseDC( hwnd, hdc);

	getch();

	return 0;
}

