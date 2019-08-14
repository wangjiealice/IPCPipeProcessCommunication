#include "AdaptiveLayout.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AdaptiveLayout w;
	w.show();
	return a.exec();
}
