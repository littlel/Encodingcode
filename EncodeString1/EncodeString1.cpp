// EncodeString1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <tchar.h>
using namespace std;

void EncodeString(LPCTSTR lpszText, LPTSTR *lpszReturn, LPCTSTR lpszKey)
{
	int nTextLen = 0;   //�ַ�������
	char *cPos = NULL;
	char *pDest = NULL;
	if(lpszReturn)	// ����
	{
		nTextLen = ::_tcslen(lpszText); 
		pDest = new char[nTextLen + 3];	// ==\0
	}
	else	// ����
	{
		// �����Զ�����ֹ���
		cPos = (LPTSTR)lpszText;
		while(true)	// ��������Կ��������������������Զ�����ֹ��ǣ������һֱ������ȥ
		{
			if(*cPos == '=')
				if(cPos[1] == '=')
					if(cPos[2] == '\0')
						break;
			cPos++;
		}
		if(!cPos)	// û���ҵ�������ǣ�Ҳ���Ǽ���
			return;
		nTextLen = cPos - lpszText;
		pDest = (LPTSTR)lpszText;
	}

	int nKeyLen = ::_tcslen(lpszKey);
	int i = 0;
	int k = 0;
	int t = nTextLen;
	int cn = 0;
	for(int a = 0; a < nKeyLen; a++)	// ����Կ����ֵ������
		cn += lpszKey[a];

	for(; i < nTextLen; i++)
	{
		if(lpszReturn)	// ����
		{
			pDest[i] = lpszText[i] + t;
			pDest[i] = pDest[i] ^ lpszKey[k];
			pDest[i] = pDest[i] ^ cn;
		}
		else	// ���ܣ�˳�������ʱ�෴
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
	cout<<"���ģ�\r\n";cout<<strText<<endl;

	
	cout<<"========================================"<<endl;	
	EncodeString(strText , &lpszDest, "hbrx");	// ����
	cout<<"���ģ�\r\n";cout<<lpszDest<<endl;
	cout<<"========================================"<<endl;
	
	
	EncodeString(lpszDest, NULL, "hbrx");	// ����
	if(lpszDest && *lpszDest)
	{
		cout<<"���ܣ�\r\n";
		cout<<lpszDest<<endl;
		delete [] lpszDest;
		lpszDest = NULL;
	}
	else
	{
		cout<<"���ܣ�\r\n";
		cout<<_T("(NULL)")<<endl;

	}
		
	system("pause");
	return 0;
}

