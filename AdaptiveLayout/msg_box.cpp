#include "msg_box.h" 
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QBitmap>
#include <QPainter>
#include <QMouseEvent>
#include <QPoint>

MsgBox::MsgBox(QWidget *parent)
	: QDialog(parent)
{
	this->resize(320, 160);
	this->setStyleSheet("background-color:#07090D; border-radius: 20px;color:#828D9E");
	//获取主界面的宽度
	int width = this->width();
	int height = this->height();

	//初始化为未按下鼠标左键
	mouse_press = false;

	//设置标题栏隐藏
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

	close_button = new QPushButton(this);
	close_button->setText("Close");
	//close_button->loadPixmap("tipclose");
	close_button->setGeometry(width - 30, 0, 30, 30);

	//设置标题
	title_label = new QLabel(this);
	title_label->setObjectName(QString::fromUtf8("labelOne"));
	QFont font = title_label->font();
	font.setBold(true);
	title_label->setFont(font);
	title_label->setGeometry(0, 0, width - 50, 30);

	//设置提示图片
	msg_label = new QLabel(this);
	msg_label->setGeometry(20, 50, 36, 36);
	msg_label->setScaledContents(true);

	//设置提示信息，让QLabel能够自动判断并换行显示：
	ask_label = new QLabel(this);
	ask_label->setGeometry(65, 60, width - 100, 25 * 2);
	ask_label->setWordWrap(true);
	ask_label->setAlignment(Qt::AlignTop);

	check_box = new QCheckBox(this);
	check_box->setGeometry(10, height - 35, 160, 25);
	check_box->setHidden(true);

	cancel_button = new QPushButton(this);
	cancel_button->resize(70, 25);
	cancel_button->move(width - cancel_button->width() - 10, height - 35);

	ok_button = new QPushButton(this);
	ok_button->resize(70, 25);
	ok_button->move(width - ok_button->width() - cancel_button->width() - 20, height - 35);

	check_box->setStyleSheet("background:transparent;");

	ok_button->setObjectName(QString::fromUtf8("pushButtonTwo"));
	cancel_button->setObjectName(QString::fromUtf8("pushButtonTwo"));

	QObject::connect(ok_button, SIGNAL(clicked()), this, SLOT(okOperate()));
	QObject::connect(close_button, SIGNAL(clicked()), this, SLOT(cancelOperate()));
	QObject::connect(cancel_button, SIGNAL(clicked()), this, SLOT(cancelOperate()));
}

void MsgBox::translateLanguage()
{
	close_button->setToolTip(tr("close"));
	check_box->setText(tr("remember"));
	ok_text = tr("ok");
	cancel_text = tr("cancel");
}

void MsgBox::setInfo(QString title_info, QString info, QPixmap pixmap, bool is_check_hidden, bool is_ok_hidden)
{
	title_label->setText(QString("  ") + title_info);

	//设置提示信息
	ask_label->setText(info);
	msg_label->setPixmap(pixmap);

	//是否隐藏复选框
	check_box->setChecked(false);
	check_box->setHidden(is_check_hidden);

	//是否隐藏确定按钮
	ok_button->setHidden(is_ok_hidden);
	if (is_ok_hidden)
	{
		cancel_button->setText(ok_text);
	}
	else
	{
		ok_button->setText(ok_text);
		cancel_button->setText(cancel_text);
	}

	//设置默认按钮为取消按钮
	cancel_button->setFocus();
}

void MsgBox::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.drawPixmap(rect(), QPixmap(":/icon/tip"));

	QBitmap bitmap(this->size());
	QPainter painter2(&bitmap);
	painter2.fillRect(bitmap.rect(), Qt::white);
	painter2.setBrush(QColor(0, 0, 0));
	painter2.drawRoundedRect(rect(), 4, 4);
	setMask(bitmap);
}

void MsgBox::mousePressEvent(QMouseEvent * event)
{
	//只能是鼠标左键移动和改变大小
	if (event->button() == Qt::LeftButton)
	{
		mouse_press = true;
	}

	//窗口移动距离
	move_point = event->globalPos() - pos();
}

void MsgBox::mouseReleaseEvent(QMouseEvent *)
{
	mouse_press = false;
}

void MsgBox::mouseMoveEvent(QMouseEvent *event)
{
	//移动窗口
	if (mouse_press)
	{
		QPoint move_pos = event->globalPos();
		move(move_pos - move_point);
	}
}

void MsgBox::okOperate()
{
	this->accept();
}

void MsgBox::cancelOperate()
{
	this->reject();
}