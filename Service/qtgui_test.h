#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qtgui_test.h"
#include <windows.h>

#define MAX_CONNECT 1

typedef struct
{
	HANDLE	hTread;
	HANDLE	hPipe;
	HANDLE	hEvent;
	HANDLE  guiObject;
} PIPE_INSTRUCT;

typedef struct 
{
	//unsigned char *	yuvImageBuffer;
	//unsigned long imageBuffersize;
	bool isCameraType208;
} CameraInfo;

class QTGUI_Test : public QMainWindow
{
	Q_OBJECT

public:
	static QTGUI_Test & getInstance();
	QTGUI_Test(QWidget *parent = Q_NULLPTR);

	int  nResValue;
	int  nFirst;
	int  nSecond;
	bool bServerStatus;
	UINT nMaxConn = 1;
	PIPE_INSTRUCT PipeInst[MAX_CONNECT];

	UINT nMaxConn2 = 1;
	PIPE_INSTRUCT PipeInst2[MAX_CONNECT];

private:
	Ui::QTGUI_TestClass ui;
	static QTGUI_Test *plog_;
	//DWORD ServerThread(LPVOID lpParameter);

private:
	bool StartCameraInfoPipe();
	bool StartImagePipe();

signals:
	//数据发生改变之后发送此信号
	void onDataChanged(int a, int b);
	void onCameraTypeChanged(bool is208);


private slots:
	void on_start_button_clicked();
	void on_start_receive_image_button_clicked();
	void on_stop_button_clicked();
	void updateUi(int a, int b);
	void updateCameraType(bool is208);


};

