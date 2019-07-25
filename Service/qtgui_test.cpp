// Similar with Axiocam20xTwain32

#define isCamera208 true
#define snapImageWidth 2160
#define snapImageHeight 3840

//#define isCamera208 false
//#define snapImageWidth 1080
//#define snapImageHeight 1920

#include "qtgui_test.h"
#include"global.h"

#define MAX_BUFFER_SIZE 1024
unsigned char *yuvImageBuffer;
unsigned long yuvImageBufferSize = 0;
int receiveMessageTime = 0;

QTGUI_Test* QTGUI_Test::plog_ = NULL;
QTGUI_Test & QTGUI_Test::getInstance()
{
	if (plog_ == NULL)
	{
		plog_ = new QTGUI_Test;
	}
	return *plog_;
}

QTGUI_Test::QTGUI_Test(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	if (isCamera208)
	{
		yuvImageBufferSize = snapImageWidth * snapImageHeight * 3 / 2;
	}
	else
	{
		yuvImageBufferSize = snapImageWidth * snapImageHeight;
	}
	connect(this, SIGNAL(onDataChanged(int, int)), this, SLOT(updateUi(int,int)));
}

DWORD WINAPI ServerThread(LPVOID lpParameter)
{
	DWORD	nReadByte = 0, nWriteByte = 0, dwByte = 0;
	char	szBuf[MAX_BUFFER_SIZE] = { 0 };
	PIPE_INSTRUCT	CurPipeInst = *(PIPE_INSTRUCT*)lpParameter;
	OVERLAPPED OverLapStruct = { 0, 0, 0, 0, CurPipeInst.hEvent };
	while (true)
	{
		memset(szBuf, 0, sizeof(szBuf));
		ConnectNamedPipe(CurPipeInst.hPipe, &OverLapStruct);
		WaitForSingleObject(CurPipeInst.hEvent, INFINITE);
		if (!GetOverlappedResult(CurPipeInst.hPipe, &OverLapStruct, &dwByte, true))
			break;

		// 从管道中读取客户端的请求信息
		if (!ReadFile(CurPipeInst.hPipe, szBuf, MAX_BUFFER_SIZE, &nReadByte, NULL))
		{
			MessageBox(0, L"读取管道错误！", 0, 0);
			break;
		}

		int a, b;
		sscanf(szBuf, "%d %d", &a, &b);

		QTGUI_Test &pMyDlg = *(QTGUI_Test*)CurPipeInst.guiObject;
		emit pMyDlg.onDataChanged(a,b);

		//memset(szBuf, 0, sizeof(szBuf));
		// 把反馈信息写入管道
		WriteFile(CurPipeInst.hPipe, "Succeed", 8, &nWriteByte, NULL);
		DisconnectNamedPipe(CurPipeInst.hPipe);
		printf("Already DisconnectNamedPipe.\n");
	}

	return 0;
}

void GreatStringFromCurrentTime(char* szBuf, int bufferSize)
{
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	//char szBuf[100] = { 0 };
	sprintf_s(szBuf, bufferSize,
		"C:\\Users\\zcalwang\\Desktop\\CameraTestFolder\\TWAIN\\SaveImage\\%d%d%d%d%d%d%d", 
		sys.wYear, 
		sys.wMonth,
		sys.wDay, 
		sys.wHour, 
		sys.wMinute, 
		sys.wSecond, 
		sys.wMilliseconds);
}

void SaveYUVImage()
{
	char name[200] = {0};
	GreatStringFromCurrentTime(name,sizeof(name));

	FILE *fp;
	fp = fopen(name, "wb+");
	if (fp)
	{
		fwrite(yuvImageBuffer, 1, yuvImageBufferSize, fp);
	}

	fclose(fp);
}


DWORD WINAPI AcceptImageThread(LPVOID lpParameter)
{
	DWORD	nReadByte = 0, nWriteByte = 0, dwByte = 0;
	yuvImageBuffer = (unsigned char *)malloc(yuvImageBufferSize);
	memset(yuvImageBuffer, 0, yuvImageBufferSize);

	PIPE_INSTRUCT CurPipeInst = *(PIPE_INSTRUCT*)lpParameter;
	OVERLAPPED OverLapStruct = { 0, 0, 0, 0, CurPipeInst.hEvent };
	while (true)
	{

		ConnectNamedPipe(CurPipeInst.hPipe, &OverLapStruct);
		WaitForSingleObject(CurPipeInst.hEvent, INFINITE);
		if (!GetOverlappedResult(CurPipeInst.hPipe, &OverLapStruct, &dwByte, true))
			break;

		// 从管道中读取客户端的请求信息
		if (!ReadFile(CurPipeInst.hPipe, yuvImageBuffer, yuvImageBufferSize, &nReadByte, NULL))
		{
			MessageBox(0, L"读取管道错误！", 0, 0);
			break;
		}
		else
		{
			printf("Receive message from client %d times.\n", receiveMessageTime);
			SaveYUVImage();
			++receiveMessageTime;
		}

		QTGUI_Test &pMyDlg = *(QTGUI_Test*)CurPipeInst.guiObject;
		emit pMyDlg.onDataChanged(yuvImageBuffer[0], yuvImageBuffer[1]);

		DisconnectNamedPipe(CurPipeInst.hPipe);
		printf("Already DisconnectNamedPipe.\n");
	}

	return 0;
}

void QTGUI_Test::on_start_button_clicked()
{
	//onDataChanged(2,4);

	LPCWSTR lpPipeName = L"\\\\.\\Pipe\\NamedPipe";
	unsigned long lpThreadId;

	for (UINT i = 0; i < nMaxConn; i++)
	{
		// 创建管道实例
		PipeInst[i].hPipe = CreateNamedPipe(lpPipeName, PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED, \
			PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, nMaxConn, 0, 0, 1000, NULL);
		if (PipeInst[i].hPipe == INVALID_HANDLE_VALUE)
		{
			DWORD dwErrorCode = GetLastError();
			MessageBox(0, L"创建管道错误！", 0, 0);
			return;
		}
		// 为每个管道实例创建一个事件对象，用于实现重叠IO
		PipeInst[i].hEvent = CreateEvent(NULL, false, false, false);
		PipeInst[i].guiObject = &QTGUI_Test::getInstance();
		// 为每个管道实例分配一个线程，用于响应客户端的请求
		PipeInst[i].hTread = CreateThread(NULL, 0, ServerThread, &PipeInst[i], 0, &lpThreadId);
	}

	this->setWindowTitle("IPC pipe(RUNNING)");
	MessageBox(0, L"服务启动成功", L"Info", 0);
}

void QTGUI_Test::on_start_receive_image_button_clicked()
{
	LPCWSTR lpPipeName = L"\\\\.\\Pipe\\NamedPipe";
	unsigned long lpThreadId;

	for (UINT i = 0; i < nMaxConn; i++)
	{
		// 创建管道实例
		PipeInst[i].hPipe = CreateNamedPipe(lpPipeName, PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED, \
			PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, nMaxConn, 0, 0, 1000, NULL);
		if (PipeInst[i].hPipe == INVALID_HANDLE_VALUE)
		{
			DWORD dwErrorCode = GetLastError();
			MessageBox(0,L"创建管道错误！",0,0);
			return;
		}
		// 为每个管道实例创建一个事件对象，用于实现重叠IO
		PipeInst[i].hEvent = CreateEvent(NULL, false, false, false);
		PipeInst[i].guiObject = &QTGUI_Test::getInstance();
		// 为每个管道实例分配一个线程，用于响应客户端的请求
		PipeInst[i].hTread = CreateThread(NULL,0, AcceptImageThread, &PipeInst[i], 0,	&lpThreadId);
	}

	this->setWindowTitle("IPC accept image pipe(RUNNING)");
	MessageBox(0,L"接受图像服务启动成功",L"Info",0);
}

void QTGUI_Test::on_stop_button_clicked()
{
	DWORD dwNewMode = PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_NOWAIT;
	for (UINT i = 0; i < nMaxConn; i++)
	{
		SetEvent(PipeInst[i].hEvent);
		CloseHandle(PipeInst[i].hTread);
		CloseHandle(PipeInst[i].hPipe);
	}

	this->setWindowTitle("IPC pipe server(STOP)");
	MessageBox(0,L"停止启动成功", L"Info",0);
}

void  QTGUI_Test::updateUi(int a, int b)
{
	ui.a_text->setText(QString::number(a));
	ui.b_text->setText(QString::number(b));
	ui.c_text->setText(QString::number(a + b));

	ui.a_text->repaint();
	ui.b_text->repaint();
	ui.c_text->repaint();


}