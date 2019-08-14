#pragma once

#include <QWidget>
#include "ui_MessageBoxForm.h"
#include "messagebox.h"

class MessageBoxInfo : public MessageBox
{
	Q_OBJECT

public:
	MessageBoxInfo(QWidget *parent = Q_NULLPTR);
	void SetMessageBoxContent(QString content);

private:
	Ui::MessageBox ui;
	bool mouse_press;
	QPoint move_point;
};
