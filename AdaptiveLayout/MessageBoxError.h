#pragma once

#include <QWidget>
#include "ui_MessageBoxError.h"
#include "messagebox.h"

class MessageBoxError : public MessageBox
{
	Q_OBJECT

public:
	MessageBoxError(QWidget *parent = Q_NULLPTR);
	void SetMessageBoxContent(QString content);

private:
	Ui::MessageBoxError ui;
};
