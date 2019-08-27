#include "AnnotationOnImage.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AnnotationOnImage w;
	w.show();
	return a.exec();
}
