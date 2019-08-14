#include"messagebox.h"

MessageBox::MessageBox(QWidget *parent)
	: QDialog(parent)
{
	//ui.setupUi(this);
	this->setModal(true);
	//Window Transparent background
	this->setAttribute(Qt::WA_TranslucentBackground, true);
	//Hide title
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	//QObject::connect(ui.OKButton, SIGNAL(clicked()), this, SLOT(okOperate()));
	//QObject::connect(ui.messageBoxContent, SIGNAL(clicked()), this, SLOT(cancelOperate()));
}

//void MessageBox::SetMessageBoxContent(QString content)
//{
//	ui.messageBoxContent->setText(content);
//}

void MessageBox::okOperate()
{
	this->accept();
}

void MessageBox::cancelOperate()
{
	this->reject();
}

void MessageBox::mousePressEvent(QMouseEvent * event)
{
	//ֻ�����������ƶ��͸ı��С
	if (event->button() == Qt::LeftButton)
	{
		mouse_press = true;
	}

	//�����ƶ�����
	move_point = event->globalPos() - pos();
}

void MessageBox::mouseReleaseEvent(QMouseEvent *)
{
	mouse_press = false;
}

void MessageBox::mouseMoveEvent(QMouseEvent *event)
{
	//�ƶ�����
	if (mouse_press)
	{
		QPoint move_pos = event->globalPos();
		move(move_pos - move_point);
	}
}