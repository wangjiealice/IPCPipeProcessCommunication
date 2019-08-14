#pragma once

#include <QDialog>
#include <QString>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

 class MessageBox : public QDialog
{
	Q_OBJECT

public:
	MessageBox(QWidget *parent = Q_NULLPTR);
	virtual void SetMessageBoxContent(QString content) = 0;

private:
	//Ui::MessageBox ui;
	bool mouse_press;
	QPoint move_point;

	protected slots:
	virtual void cancelOperate();
	virtual void okOperate();
	virtual void mousePressEvent(QMouseEvent * event);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *event);

};
