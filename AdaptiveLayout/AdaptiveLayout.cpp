#include "AdaptiveLayout.h"
#include "msg_box.h"
#include "messagebox.h"
#include "MessageBoxInfo.h"
#include "MessageBoxError.h"


#include <QMessageBox>


AdaptiveLayout::AdaptiveLayout(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void AdaptiveLayout::on_deleteSelectedImagesButton_clicked()
{
	/*MsgBox *msg_box2 = new MsgBox();
	msg_box2->setInfo(QString("testdialog"), QString("hello"), QPixmap(":/icon/attention"), true, true);
	msg_box2->exec();*/

	//QMessageBox message(QMessageBox::Warning, "Error", "hellohello", QMessageBox::Ok);
	//message.setStyleSheet("QMessageBox {background-color: #07090D;} QMessageBox QLabel {color: #828D9E;}");
	//message.exec();

	/*MessageBoxInfo *msg_box1 = new MessageBoxInfo();
	msg_box1->SetMessageBoxContent("1111111111111111111112222222222222222222222222233333333333333333333333333333444444444444444444");
	msg_box1->show();*/

	//MessageBoxError *msg_box1 = new MessageBoxError();
	//msg_box1->SetMessageBoxContent("111111111111111111112222222222222222222222222222223333333333333333333333333333444444444444444444444");
	//msg_box1->show();


}