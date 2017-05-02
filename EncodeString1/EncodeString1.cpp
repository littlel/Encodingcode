// EncodeString1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <tchar.h>
using namespace std;

void EncodeString(LPCTSTR lpszText, LPTSTR *lpszReturn, LPCTSTR lpszKey)
{
	int nTextLen = 0;   //字符串长度
	char *cPos = NULL;
	char *pDest = NULL;
	if(lpszReturn)	// 加密
	{
		nTextLen = ::_tcslen(lpszText); 
		pDest = new char[nTextLen + 3];	// ==\0
	}
	else	// 解密
	{
		// 查找自定的中止标记
		cPos = (LPTSTR)lpszText;
		while(true)	// 从这里可以看到，除非搜索到我们自定的中止标记，否则会一直搜索下去
		{
			if(*cPos == '=')
				if(cPos[1] == '=')
					if(cPos[2] == '\0')
						break;
			cPos++;
		}
		if(!cPos)	// 没有找到结束标记，也不是加密
			return;
		nTextLen = cPos - lpszText;
		pDest = (LPTSTR)lpszText;
	}

	int nKeyLen = ::_tcslen(lpszKey);
	int i = 0;
	int k = 0;
	int t = nTextLen;
	int cn = 0;
	for(int a = 0; a < nKeyLen; a++)	// 将密钥所有值加起来
		cn += lpszKey[a];

	for(; i < nTextLen; i++)
	{
		if(lpszReturn)	// 加密
		{
			pDest[i] = lpszText[i] + t;
			pDest[i] = pDest[i] ^ lpszKey[k];
			pDest[i] = pDest[i] ^ cn;
		}
		else	// 解密，顺序与加密时相反
		{
			pDest[i] = lpszText[i] ^ cn;
			pDest[i] = pDest[i] ^ lpszKey[k];
			pDest[i] = pDest[i] - t;
		}
		k++;
		t--;
		if(k >= nKeyLen)
			k = 0;
		if(t <= 0)
			t = nTextLen;
	}

	if(!cPos)
	{
		memcpy(pDest + nTextLen, _T("==\0"), 3 * sizeof(TCHAR));
		*lpszReturn = pDest;
	}
	else
		memset(pDest  + nTextLen, _T('\0'), sizeof(TCHAR));
}

int main(int argc, char* argv[])
{
	system("color A");
	char strText[] = "<xml utf-8=1.0>\r\n<hbrx>test</hbrx>\r\n</xml>\r\n";
	char *lpszDest = NULL;
	cout<<"明文：\r\n";cout<<strText<<endl;

	
	cout<<"========================================"<<endl;	
	EncodeString(strText , &lpszDest, "hbrx");	// 加密
	cout<<"密文：\r\n";cout<<lpszDest<<endl;
	cout<<"========================================"<<endl;
	
	
	EncodeString(lpszDest, NULL, "hbrx");	// 解密
	if(lpszDest && *lpszDest)
	{
		cout<<"解密：\r\n";
		cout<<lpszDest<<endl;
		delete [] lpszDest;
		lpszDest = NULL;
	}
	else
	{
		cout<<"解密：\r\n";
		cout<<_T("(NULL)")<<endl;

	}
		
	system("pause");
	return 0;
}

