
// 链表.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include "conio.h"

typedef POINT datatype;
typedef struct node{
	datatype data;
	struct node *next;
}linklist,linknode;


void drawList(HDC hdc,linklist *list,bool sign);
linklist* createlist(void);
linknode* create2(void);
linklist* deleteElem(linklist* head,int place,bool sign);
linklist* create3(void);
linklist* insert(linklist *head,int place,POINT pt,bool sign);
void ClearWindows(HWND hwnd,HDC hdc);
void print(linklist *L,bool sign);
void freeElem(linklist *L);


int _tmain(int argc, _TCHAR* argv[])
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);

	::SelectObject( hdc, GetStockObject( DC_PEN ));
	::SetDCPenColor( hdc, RGB( 0,255,0));	

	::SelectObject (hdc,GetStockObject(DC_BRUSH));
	::SetDCBrushColor(hdc,RGB(67,40,45));

	linklist *list;
	list=create3();

	drawList(hdc,list,1); 
	
	POINT pt;
	int place;
	printf("input place:");
	scanf("%d",&place);
	printf("input coordinat:");
	scanf("%d,%d",&pt.x,&pt.y);

	getch();
	system("cls"); 
	ClearWindows(hwnd,hdc);  

	insert(list,place,pt,1); 
	drawList(hdc,list,1);
	getch();
	system("cls");
	ClearWindows(hwnd,hdc);

	printf("input the number you want to delete:");
	scanf("%d",&place);
	deleteElem(list,place,1);
	drawList(hdc,list,1);
	getch();
	system("cls");
	ClearWindows(hwnd,hdc);

	ReleaseDC(hwnd,hdc);
	print(list,1);
	free(list);
    getch();
	return 0;
}

linknode* createlist()
{
	linklist *head=NULL;
	linknode *tail=NULL;
	int num;
	printf("num：");
	scanf("%d",&num);
	printf("x,y:");
	for(int i=0;i<num;i++)
	{
     linklist *list =(linklist*) malloc(sizeof(linklist));
	 scanf("%d,%d",&list->data.x,&list->data.y);
	 if(head==NULL)
	 {
		 head=list;
		 tail=list;
	 }
	 else
	 {
		 tail->next=list;
		 tail=list;
	 }
	
	}
	tail->next=NULL;
	 return head;
}

linklist* create2()
{
	linklist *head=(linklist *) malloc(sizeof(linklist));
	linknode *tail=head;
	printf("num：");
	int num;
	scanf("%d",&num);
	printf("x,y:");
	
    for(int i=0;i<num;i++)
	{
		linklist *list =(linklist *) malloc(sizeof(linklist));
        scanf("%d,%d",&list->data.x,&list->data.y);
		tail->next=list;
		tail=list;
	}
	tail->next=NULL;
	return head;
}


void drawList(HDC hdc,linklist *list,bool sign) 
{
	linklist *h=list;
	if (h!=NULL)
	{

	if(sign)
	{
		h=h->next;
	}

	MoveToEx(hdc,h->data.x,h->data.y,0);
	while ((h=h->next)!=NULL)
       LineTo(hdc,h->data.x,h->data.y);
	}
}


linklist* create3() 
{
	linklist *head=(linklist *) malloc(sizeof(linklist));
	linknode *tail=head;
	FILE *fp=fopen("..\\line.txt","r");
	char s[1024];
	fgets(s,1024,fp);
	fgets(s,1024,fp);
	int type,id,vercount;
	fscanf(fp,"%d,%d,%d",&type,&id,&vercount);

	
	
	
    for(int i=0;i<vercount;i++)
	{
		linklist *list =(linklist *) malloc(sizeof(linklist));
        fscanf(fp,"%d,%d",&list->data.x,&list->data.y);
		tail->next=list;
		tail=list;
	}
	fclose(fp);
	tail->next=NULL;
	return head;
}
	

linklist* insert(linklist *head,int place,POINT pt,bool sign)
{
	linklist* temp=head;
	linklist* add=(linklist *)malloc(sizeof(linklist));
	int flag=0;
	add->data.x=pt.x;
	add->data.y=pt.y;
	int i=0; 
	if(temp!=NULL)
	{
		if(sign)  
		{
			temp=temp->next;
			
		}
    while(temp!=NULL)
	 {
		 i++;
		 if(i==place)
		 {
			 add->next=temp->next;
			 temp->next=add;
			 flag=1;
			 break;
		 }
		 temp=temp->next;
	 }
	}
		 if(flag)
		 return head;
		 else 
		 {printf("ERROR");
		 return NULL;
		 }
	
}


linklist *deleteElem(linklist* head,int place,bool sign)
{
	linklist* temp=head;
	int i=0,flag=0;
	if(temp!=NULL)
	{
		if(sign)
		{
			head=head->next;
		
		}
	while(temp!=NULL)
		{
			i++;
			if(i==place)
			{
				temp->next=temp->next->next;
				flag=1;
				break;
			}
			temp=temp->next;
		}
	}
	if(flag)
		 return head;
	else
		 {printf("ERROR");
		 return NULL;
		 }
}

void ClearWindows(HWND hwnd,HDC hdc)
{
    RECT rect;
	::GetClientRect(hwnd,&rect);
	::Rectangle(hdc,rect.left,rect.top,rect.right,rect.bottom);
}

void print(linklist *L,bool sign)
{
	linklist *temp=L;
	if(temp!=NULL)
	{
		if(sign) temp=temp->next;
		do{
			printf("%d,%d\n",temp->data.x,temp->data.y);
			temp=temp->next;
	}while(temp!=NULL);
}
	else printf("ERROR");
}

void freeElem(linklist *L)
{
	do{
		linklist *temp=L;
		L=L->next;
		free(temp);
	}while(L!=NULL);
}


