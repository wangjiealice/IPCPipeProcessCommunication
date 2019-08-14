#include"MessageBoxAsk.h"

MessageBoxAsk::MessageBoxAsk(QWidget *parent)
	: MessageBox(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.YesButton, SIGNAL(clicked()), this, SLOT(okOperate()));
	QObject::connect(ui.NoButton, SIGNAL(clicked()), this, SLOT(cancelOperate()));
}

void MessageBoxAsk::SetMessageBoxContent(QString content)
{
	ui.messageBoxContent->setText(content);
}