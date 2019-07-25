#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qtgui_test.h"
#include <windows.h>

#define MAX_CONNECT 128

typedef struct {
	HANDLE	hTread;
	HANDLE	hPipe;
	HANDLE	hEvent;
	HANDLE  guiObject;
} PIPE_INSTRUCT;


class QTGUI_Test : public QMainWindow
{
	Q_OBJECT

public:
	static QTGUI_Test & getInstance();
	QTGUI_Test(QWidget *parent = Q_NULLPTR);

	int  nResValue;
	int  nFirst;
	int  nSecond;
	UINT nMaxConn = 1;
	bool	bServerStatus;
	PIPE_INSTRUCT PipeInst[MAX_CONNECT];

public:

private:
	Ui::QTGUI_TestClass ui;
	static QTGUI_Test *plog_;
	//DWORD ServerThread(LPVOID lpParameter);

signals:
	//数据发生改变之后发送此信号
	void onDataChanged(int a, int b);

private slots:
	void on_start_button_clicked();
	void on_start_receive_image_button_clicked();
	void on_stop_button_clicked();
	void updateUi(int a, int b);

};

