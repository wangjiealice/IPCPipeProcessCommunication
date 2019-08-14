#include"messagebox_info.h"

MessageBoxInfo::MessageBoxInfo(QWidget *parent)
	: MessageBox(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.OKButton, SIGNAL(clicked()), this, SLOT(okOperate()));
	//QObject::connect(ui.messageBoxContent, SIGNAL(clicked()), this, SLOT(cancelOperate()));
}

void MessageBoxInfo::SetMessageBoxContent(QString content)
{
	ui.messageBoxContent->setText(content);
}