#include "qtgui_test.h"
#include"global.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTGUI_Test &pMyDlg = QTGUI_Test::getInstance();
	pMyDlg.show();
	return a.exec();
}
