#include"MessageBoxInfo.h"

MessageBoxInfo::MessageBoxInfo(QWidget *parent)
	: MessageBox(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.OKButton, SIGNAL(clicked()), this, SLOT(okOperate()));
}

void MessageBoxInfo::SetMessageBoxContent(QString content)
{
	ui.messageBoxContent->setText(content);
}