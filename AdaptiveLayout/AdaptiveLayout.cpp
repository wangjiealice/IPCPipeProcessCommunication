#include "AdaptiveLayout.h"
#include "msg_box.h"
#include "messagebox.h"
#include "MessageBoxInfo.h"
#include "MessageBoxError.h"
#include "MessageBoxAsk.h"

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

	//QMessageBox message1(QMessageBox::Warning, "Error", "1", QMessageBox::Ok);
	//message1.exec();

	//QMessageBox message2(QMessageBox::Warning, "Error", "222222222222222222", QMessageBox::Ok);
	//message2.exec();

	/*MessageBoxInfo *msg_box1 = new MessageBoxInfo();
	msg_box1->SetMessageBoxContent("1111111111111111111112222222222222222222222222233333333333333333333333333333444444444444444444");
	msg_box1->show();*/

	//MessageBoxError *msg_box1 = new MessageBoxError();
	//msg_box1->SetMessageBoxContent("111111111111111111112222222222222222222222222222223333333333333333333333333333444444444444444444444");
	//msg_box1->show();

	MessageBoxAsk *msg_box1 = new MessageBoxAsk();
	msg_box1->SetMessageBoxContent("111");
	int result = msg_box1->exec();
	printf("Result is %d\n",result);


	MessageBoxAsk *msg_box2 = new MessageBoxAsk();
	msg_box2->SetMessageBoxContent("222");
	int result2 = msg_box2->exec();
	printf("Result is %d\n", result2);
}