// 串.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "malloc.h"

typedef char *String;


int StrLen( String str)
{
	return *(int*)(str-4);//返回的是字符串实际长度
}


String _newString( int len)
{
	String s = (String)malloc(4 + len);
	*(int *)s = len;
	return s + 4;//返回的是字符串的首地址
}//数组初始化


void _resetStrLen( String* str, int newLen )
{//判断复制的字符串长度与原字符串长度的关系
	if( *str == 0 ) 
	{
		*str = _newString( newLen );
		return ;
	}

	int oldLen = StrLen( *str );
	if( oldLen > newLen )
	{
		*(int *)( *str - 4) = newLen;
	}
	else if( oldLen < newLen )
	{
		*str = (String)realloc( *str - 4, newLen + 4 );//原数组空间不够，再次分配存储空间
		*(int *)( *str ) = newLen;
		*str += 4;
	}
}


bool StrEmpty( String str)
{//判断是否为空
	return StrLen(str) == 0;
}


void DestroyString( String str)
{//释放内存
	free( str - 4);
}


void StrAssign ( String* str, const char* chars)
{//初始化
	int len = 0;
	char* pchar = (char*)chars;
	while ( *pchar++)//等价于while（*pchar ++ !='\0')
	{
		++len;
	}

	_resetStrLen( str, len );

	for( int i = 0;i < len;++i)
	{
		(*str)[i]=chars[i];
	}
}


void SubString( String* sub, String str, int pos, int len)
{//从str的pos位置开始取len长的子串，赋给串sub
	int strLen = StrLen( str);
	if( pos < 1 || pos > strLen || len <= 0 || len > strLen - pos +1)
		printf("error!");//判断位置是否正确
	else
	{
		_resetStrLen( sub, len );
		for( int i = 0; i <= len; i++)
		{
			(*sub)[i] = str[pos-1+i];
		}
	}
}


int StrCopy( String targetStr, String srcStr)
{
	int srcLen = StrLen(srcStr);
	if( srcLen >0 )
	{
		int targetLen = StrLen( targetStr );
		if( targetLen < srcLen ) srcLen = targetLen;
		SubString( &targetStr, srcStr, 1, srcLen);
		return 1;
	}
	return 0;	
}


int StrCompare( String str1, String str2)
{//字符串长度比较
	int len1 = StrLen(str1);
	int len2 = StrLen(str2);

	if ( len1 < len2 ) return -1;
	if( len1 > len2 ) return 1; 
	/*if(len1==len2) return 0*/

	for( int i = 0; i < len1 ; i++)
	{//字符大小比较
		if( str1[i] < str2[i] ) return -1;
		if( str1[i] > str2[i] ) return 1;
		/*if (str1[i]==str2[i]) return 0*/
	}
	return 0;
}


void Concat(String* sub, String str1, String str2)
{//将str1+str2赋给sub
	int i;
	int len1 = StrLen(str1);
	int len2 = StrLen(str2);

	*sub = _newString( len1 + len2 );
	for(i = 0; i < len1; i++)
	{
		(*sub)[i] = str1[i];
	}
	for(i=0; i< len2; i++)
	{
		(*sub)[i+len1] = str2[i];
	}
}


int Index(String S, String T, int pos)
{
	if( pos > 0) 
	{
		String sub =  0;
		int len1=StrLen(S), len2=StrLen(T);
		int i=pos;
		while(i<=len1-len2+1)//检索到最后才匹配上
		{
			SubString(&sub, S, i, len2);//从S中的i位置取len2长的子串赋给sub
			if(StrCompare(sub, T)!=0)//将sub与T进行模式匹配
				++i;
			else 
				return i;//返回位置
		}
	}
	return 0;
}

void StrInsert(String* str, int pos, String sub)
{
	int strLen = StrLen(*str);
	int subLen = StrLen(sub);
	if(pos<1 || pos > strLen + 1 )
		printf("error!");
	else 
	{
		_resetStrLen( str, strLen + subLen );		
		int i;
		for( i = strLen - 1; i >= pos-1; i--)
			(*str)[i+subLen] = (*str)[i];//插入sub后pos后字符的位置后移subLen
		for(i = 0; i < subLen; i++)
			(*str)[pos-1+i] = sub[i];//在pos位置上插入sub
	}
}

void StrDelete(String* str, int pos, int len)
{
	int i;
	int strLen = StrLen(*str);
	if( pos < 1 || pos > strLen )
		printf("error!");
	else 
	{
		if( pos + len - 1 > strLen ) len = strLen - pos  + 1;//开始空间存放字符串长度

		_resetStrLen( str, strLen - len );

		for( i = 0; i< len; i++)
		{
			str[pos+i-1]=str[pos+i+len-1];//从串str1中删除pos位置开始长度为len的子串
		}
		
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	String s =  0 , sub = 0;
	StrAssign ( &s,"abcdefg");
	StrAssign ( &sub,"m");

	StrInsert(&s, 3, sub);

	int len = StrLen( s);
	for( int i=0; i < len ;++i) 
	{
		printf("%c",s[i]);
	}

	printf("\n");

	String str1 = 0;

	SubString( &str1, s, 1, 4);

	StrCopy( str1, s);
	for( int i=0; i< StrLen(str1) ;++i) 
	{
		printf("%c",str1[i]);
	}
	printf("\n");

	StrAssign ( &str1,"abcdefgh");
	printf("%d",StrCompare(str1, s));
	printf("\n");

	Concat( &str1, s,  s);
	for( int i=0; i< StrLen(str1) ;++i) 
	{
		printf("%c",str1[i]);
	}

	printf("\n");
	String S = 0 ,T =  0;
	StrAssign ( &S,"abcdefghabcdefgabcdabcdabc");
	StrAssign ( &T,"abc");
	printf("%d",Index(S, T, 17));

	printf("\n");

   
	DestroyString( s);
	getchar();
	return 0;
}

