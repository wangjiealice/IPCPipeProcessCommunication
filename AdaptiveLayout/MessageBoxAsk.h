#pragma once
//Yes: return 1
//No: return 0

#include <QWidget>
#include "ui_MessageBoxAsk.h"
#include "messagebox.h"

class MessageBoxAsk : public MessageBox
{
	Q_OBJECT

public:
	MessageBoxAsk(QWidget *parent = Q_NULLPTR);
	void SetMessageBoxContent(QString content);

private:
	Ui::MessageBoxAsk ui;
};
