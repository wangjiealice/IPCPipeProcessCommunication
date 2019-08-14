#pragma once

#include <QDialog>
#include <QString>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QBitmap>
#include <QPainter>
#include <QMouseEvent>
#include <QPoint>


class MsgBox : public QDialog
{
	Q_OBJECT

public:
	MsgBox(QWidget *parent = Q_NULLPTR);
	//~MsgBox();

	void translateLanguage();
	void setInfo(QString title_info, QString info, QPixmap pixmap, bool is_check_hidden, bool is_ok_hidden);

	bool mouse_press;
	QPushButton* close_button;
	QLabel* title_label;
	QLabel* msg_label;
	QLabel* ask_label;
	QCheckBox* check_box;
	QPushButton* cancel_button;
	QPushButton* ok_button;

	QString ok_text;
	QString cancel_text;
	QPoint move_point;

	private slots:
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *event);
	void okOperate();
	void cancelOperate();

};
