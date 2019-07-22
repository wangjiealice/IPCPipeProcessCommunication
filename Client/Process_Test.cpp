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
inline void winerr(void);		//用于打印windows错误代码

void RunExe()
{
	STARTUPINFO stStartUpInfo;
	::memset(&stStartUpInfo, 0, sizeof(stStartUpInfo));
	stStartUpInfo.cb = sizeof(stStartUpInfo);

	PROCESS_INFORMATION stProcessInfo;
	::memset(&stProcessInfo, 0, sizeof(stProcessInfo));

	TCHAR szPath[] = _T("C:\\SmartCameraTFSCode\\SmartCam\\SmartCamApp\\Win32\\Release\\AxiocamApplication.exe");
	TCHAR szCmd[] = _T(" https://www.zeiss.com/corporate/int/home.htmle");   //lpCommandLine的内容中开头需要一个空格，不然就和lpApplicationName连在一起去了

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
			//等待3s后关闭进程
			WaitForSingleObject(stProcessInfo.hProcess, 10000);
			PostThreadMessage(stProcessInfo.dwThreadId, WM_QUIT, 0, 0);
		}
		else
		{
			//如果创建进程失败，查看错误码
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

	SECURITY_ATTRIBUTES sa;		//Windows安全设置:此结构为各种函数创建的对象提供安全设置
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

	//启动信息

	STARTUPINFO s_info;		//指定创建时进程的窗口工作站，桌面，标准句柄和主窗口的外观
	GetStartupInfo(&s_info);
	s_info.cb = sizeof(STARTUPINFO);
	s_info.lpReserved = NULL;
	s_info.wShowWindow = SW_HIDE;
	s_info.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	s_info.hStdError = hwcmd;
	s_info.hStdInput = hrcmd;
	s_info.hStdOutput = hwcmd;

	cout << "初始化完成" << endl;

	WCHAR cmdpath[1024] = _T("\n");
	//GetSystemDirectory(cmdpath, sizeof(cmdpath));
	//wcsncat_s(cmdpath, _T("\\cmd.exe"), 9);	//宽字符串连接。。

	wcscpy_s(cmdpath, L"C:\\SmartCameraTFSCode\\SmartCam\\LusterDriverVS2015\\Win32\\Debug\\QTGUI_Test.exe"); //路径

	wcout << "path:" << cmdpath << endl;

	//创建cmd进程
	if (!CreateProcess(cmdpath, NULL, NULL, NULL, TRUE, NULL, NULL, NULL, &s_info, &pro_info))
	{
		winerr();
		CloseHandle(hwexe);
		CloseHandle(hrexe);
		return;
	}

	cout << "开始读写管道...." << endl;
	cout << "注意：为了完整读取例如 ping等需要等待时间的命令的返回数据在输入数据后会有5秒延迟" << endl
		<< "输入END即退出该程序" << endl;

	//---注意!!!  CMD是ASCII编码用WCHAR(UNICODE编码)会乱码
	char rbuf[2048];
	unsigned long rn = 0, wn = 0;
	//----------------------------读写管道----------------------------
	do
	{
		do
		{
			if (!PeekNamedPipe(hrexe, NULL, NULL, NULL, &rn, 0))	//管道是否有数据可读
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
					cout << "读管道错误" << endl;
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
		//---------写管道---------
		string wbuf;
		getline(cin, wbuf);
		if (wbuf == "END")
		{
			break;
		}
		wbuf += "\r\n";
		if (!WriteFile(hwexe, wbuf.c_str(), strlen(wbuf.c_str()), &wn, NULL))
		{
			cout << "写管道错误" << endl;
			winerr();
			break;
		}
		else
		{
			cout << wbuf;
		}
		Sleep(500);
	} while (true);

	TerminateProcess(pro_info.hProcess, 0);		//用于关闭cmd进程
}

void Submit()
{
	// 打开管道
	HANDLE hPipe = CreateFile(L"\\\\.\\Pipe\\NamedPipe", GENERIC_READ | GENERIC_WRITE, \
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hPipe == INVALID_HANDLE_VALUE)
	{
		MessageBox(0,L"打开管道失败，服务器尚未启动,或者客户端数量过多",0,0);
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

	// 把两个整数(a,b)格式化为字符串
	sprintf_s(szBuf, "%d %d", nFirst, nSecond);
	// 把数据写入管道
	WriteFile(hPipe, szBuf, strlen(szBuf), &nWriteByte, NULL);

	memset(szBuf, 0, sizeof(szBuf));
	// 读取服务器的反馈信息
	ReadFile(hPipe, szBuf, 1024, &nReadByte, NULL);
	// 把返回信息格式化为整数
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