#include"MessageBoxError.h"

MessageBoxError::MessageBoxError(QWidget *parent)
	: MessageBox(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.OKButton, SIGNAL(clicked()), this, SLOT(okOperate()));
}

void MessageBoxError::SetMessageBoxContent(QString content)
{
	ui.messageBoxContent->setText(content);
}