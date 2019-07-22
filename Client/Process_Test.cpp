// Process_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <windows.h>
#include <iostream>
#include <string>
#include <tchar.h>

using namespace std;

constexpr auto SEND_BUFF_SIZE = 1024;
inline void winerr(void);		//���ڴ�ӡwindows�������

void RunExe()
{
	STARTUPINFO stStartUpInfo;
	::memset(&stStartUpInfo, 0, sizeof(stStartUpInfo));
	stStartUpInfo.cb = sizeof(stStartUpInfo);

	PROCESS_INFORMATION stProcessInfo;
	::memset(&stProcessInfo, 0, sizeof(stProcessInfo));

	TCHAR szPath[] = _T("C:\\SmartCameraTFSCode\\SmartCam\\SmartCamApp\\Win32\\Release\\AxiocamApplication.exe");
	TCHAR szCmd[] = _T(" https://www.zeiss.com/corporate/int/home.htmle");   //lpCommandLine�������п�ͷ��Ҫһ���ո񣬲�Ȼ�ͺ�lpApplicationName����һ��ȥ��

	try
	{
		printf("Start CreateProcess \n");

		bool bRet = ::CreateProcess(
			szPath,
			szCmd,
			NULL,
			NULL,
			false,
			CREATE_NEW_CONSOLE,
			NULL,
			NULL,
			&stStartUpInfo,
			&stProcessInfo);
		printf("End CreateProcess \n");

		if (bRet)
		{
			//�ȴ�3s��رս���
			WaitForSingleObject(stProcessInfo.hProcess, 10000);
			PostThreadMessage(stProcessInfo.dwThreadId, WM_QUIT, 0, 0);
		}
		else
		{
			//�����������ʧ�ܣ��鿴������
			DWORD dwErrCode = GetLastError();
			printf_s("ErrCode : %d\n", dwErrCode);

		}
	}
	catch (char* &e)
	{
		printf_s("catch exception %s\n", e);
	}
}

void IPC_cmd()
{
	HANDLE hrcmd = NULL;
	HANDLE hwcmd = NULL;
	HANDLE hrexe = NULL;
	HANDLE hwexe = NULL;
	HANDLE hpro = NULL;

	SECURITY_ATTRIBUTES sa;		//Windows��ȫ����:�˽ṹΪ���ֺ��������Ķ����ṩ��ȫ����
	PROCESS_INFORMATION pro_info;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = true;

	if (!CreatePipe(&hrexe, &hwcmd, &sa, 0))
	{
		winerr();
		return;
	}
	else
	{
		cout << "creat pipe1 no error" << endl;
	}
	if (!CreatePipe(&hrcmd, &hwexe, &sa, 0))
	{
		winerr();
		return;
	}
	else
	{
		cout << "creat pipe2 no error" << endl;
	}

	//������Ϣ

	STARTUPINFO s_info;		//ָ������ʱ���̵Ĵ��ڹ���վ�����棬��׼����������ڵ����
	GetStartupInfo(&s_info);
	s_info.cb = sizeof(STARTUPINFO);
	s_info.lpReserved = NULL;
	s_info.wShowWindow = SW_HIDE;
	s_info.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	s_info.hStdError = hwcmd;
	s_info.hStdInput = hrcmd;
	s_info.hStdOutput = hwcmd;

	cout << "��ʼ�����" << endl;

	WCHAR cmdpath[1024] = _T("\n");
	//GetSystemDirectory(cmdpath, sizeof(cmdpath));
	//wcsncat_s(cmdpath, _T("\\cmd.exe"), 9);	//���ַ������ӡ���

	wcscpy_s(cmdpath, L"C:\\SmartCameraTFSCode\\SmartCam\\LusterDriverVS2015\\Win32\\Debug\\QTGUI_Test.exe"); //·��

	wcout << "path:" << cmdpath << endl;

	//����cmd����
	if (!CreateProcess(cmdpath, NULL, NULL, NULL, TRUE, NULL, NULL, NULL, &s_info, &pro_info))
	{
		winerr();
		CloseHandle(hwexe);
		CloseHandle(hrexe);
		return;
	}

	cout << "��ʼ��д�ܵ�...." << endl;
	cout << "ע�⣺Ϊ��������ȡ���� ping����Ҫ�ȴ�ʱ�������ķ����������������ݺ����5���ӳ�" << endl
		<< "����END���˳��ó���" << endl;

	//---ע��!!!  CMD��ASCII������WCHAR(UNICODE����)������
	char rbuf[2048];
	unsigned long rn = 0, wn = 0;
	//----------------------------��д�ܵ�----------------------------
	do
	{
		do
		{
			if (!PeekNamedPipe(hrexe, NULL, NULL, NULL, &rn, 0))	//�ܵ��Ƿ������ݿɶ�
			{
				cout << "no data" << endl;
				winerr();
				break;
			}
			if ((rn>0) && (rn<2048))
			{
				memset(rbuf, 0, 2048);
				if (!ReadFile(hrexe, rbuf, rn, NULL, NULL))
				{
					cout << "���ܵ�����" << endl;
					winerr();
					break;
				}
				else
				{
					cout << rbuf;
				}
			}
			Sleep(1000);
		} while (rn != 0);
		//---------д�ܵ�---------
		string wbuf;
		getline(cin, wbuf);
		if (wbuf == "END")
		{
			break;
		}
		wbuf += "\r\n";
		if (!WriteFile(hwexe, wbuf.c_str(), strlen(wbuf.c_str()), &wn, NULL))
		{
			cout << "д�ܵ�����" << endl;
			winerr();
			break;
		}
		else
		{
			cout << wbuf;
		}
		Sleep(500);
	} while (true);

	TerminateProcess(pro_info.hProcess, 0);		//���ڹر�cmd����
}

void Submit()
{
	// �򿪹ܵ�
	HANDLE hPipe = CreateFile(L"\\\\.\\Pipe\\NamedPipe", GENERIC_READ | GENERIC_WRITE, \
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hPipe == INVALID_HANDLE_VALUE)
	{
		MessageBox(0,L"�򿪹ܵ�ʧ�ܣ���������δ����,���߿ͻ�����������",0,0);
		return;
	}

	DWORD nReadByte, nWriteByte;
	char szBuf[1024] = { 0 };
	/*string nFirst;
	getline(cin, nFirst);

	string nSecond;
	getline(cin, nSecond);*/

	int nFirst = 1;
	int nSecond = 2;

	// ����������(a,b)��ʽ��Ϊ�ַ���
	sprintf_s(szBuf, "%d %d", nFirst, nSecond);
	// ������д��ܵ�
	WriteFile(hPipe, szBuf, strlen(szBuf), &nWriteByte, NULL);

	memset(szBuf, 0, sizeof(szBuf));
	// ��ȡ�������ķ�����Ϣ
	ReadFile(hPipe, szBuf, 1024, &nReadByte, NULL);
	// �ѷ�����Ϣ��ʽ��Ϊ����
	int nResValue;
	sscanf_s(szBuf, "%d", &nResValue);
	//this->UpdateData(false);
	CloseHandle(hPipe);
}

int main()
{
	Submit();
	/*for(int i = 0; i < 100; i++)
	{ 
		printf("This is %d times. \n", i);
		Sleep(3000);
		RunExe();
	}*/

    return 0;
}

inline void winerr(void)
{
	cout << "win error:" << GetLastError() << endl;
}