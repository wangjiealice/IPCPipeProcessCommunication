#include "AdaptiveLayout.h"
#include "msg_box.h"
#include "messagebox.h"
#include "MessageBoxInfo.h"
#include "MessageBoxError.h"
#include "MessageBoxAsk.h"
#include <random>
#include <QMessageBox>

#include <io.h>
#include<windows.h>
#include<winbase.h>
#include <time.h>
#define SaveLogFolder "C:\\Users\\Public\\TWAIN\\TWAIN.tlog"
# define CleanLogDays 30

using namespace std;

void FindFile(string path, vector<string> &files);
bool RemoveFiles(vector<string> &files);

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


	//MessageBoxAsk *msg_box2 = new MessageBoxAsk();
	//msg_box2->SetMessageBoxContent("222");
	//int result2 = msg_box2->exec();
	//printf("Result is %d\n", result2);

	//for (int i = 0; i < 1000; i++)
	//{
	//	/*bool*/
	//	std::default_random_engine e(rand());
	//	std::uniform_int_distribution<unsigned> autoExposureUI(0, 1);
	//	bool boolValue = (bool)autoExposureUI(e);
	//	printf("Value is %d\n", boolValue);

	//	/*int*/
	//	std::default_random_engine e(rand());
	//	int minIntValue = 0;
	//	int maxIntValue = 1000;
	//	uniform_int_distribution<int> brightnessUI(minIntValue, maxIntValue);
	//	int intValue = brightnessUI(e);
	//	printf("Value is %d\n", intValue);

	//	/*double*/
	//	std::default_random_engine e(rand());
	//	double minDoubleValue = 0.24 * 10;
	//	double maxDoubleValue = 1000.111 * 10;
	//	uniform_int_distribution<int> exposureTimeUI(minDoubleValue, maxDoubleValue);
	//	double doubleValue = exposureTimeUI(e) / 10.0;
	//	printf("Value is %f\n", doubleValue);
	//}

	//emit closeEvent(0);
}

void AdaptiveLayout::on_fileButton_clicked()
{
	vector<string>fileNames;
	FindFile(SaveLogFolder, fileNames);
	RemoveFiles(fileNames);
}

bool RemoveFiles(vector<string> &files)
{
	for (unsigned int i = 0; i < files.size(); i++)
	{
		if (!remove(files[i].c_str()) == 0)
		{
			return false;
		}
	}

	return true;
}

int IsPointChar(char judge[])
{
	char true_[200];
	unsigned int i, j;
	for (i = 0, j = 0; i < strlen(judge); i++)
	{
		if (judge[i] == '.')
			continue;
		else
		{
			true_[j] = judge[i];
			j++;
		}
	}
	true_[j] = '\0';
	return (int)strlen(true_);
}

time_t SystemTimeToTimet(const SYSTEMTIME& st)
{
	struct tm gm = { st.wSecond, st.wMinute, st.wHour, st.wDay, st.wMonth - 1, st.wYear - 1900, st.wDayOfWeek, 0, 0 };
	return mktime(&gm);
}

SYSTEMTIME TimetToSystemTime(time_t t)
{
	tm temptm = *localtime(&t);
	SYSTEMTIME st = { 1900 + temptm.tm_year
		, 1 + temptm.tm_mon
		, temptm.tm_wday
		, temptm.tm_mday
		, temptm.tm_hour
		, temptm.tm_min
		, temptm.tm_sec
		, 0 };
	return st;
}

bool IsFileCreateTimeMoreThanNDaysToNow(_finddata_t fileinfo, int n)
{
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	time_t currentTime = SystemTimeToTimet(sys);
	time_t createTime = fileinfo.time_create;

	SYSTEMTIME sysTest = TimetToSystemTime(createTime);

	if (currentTime - createTime > n * 24 * 60 * 60)
	{
		return true;
	}

	return false;
}

SYSTEMTIME createTimeSystemtime;
void FindFile(string path, vector<string> &files)
{
	string p;
	long hFile = 0;                //文件句柄
	struct _finddata_t fileinfo;    //文件信息
									//查找文件夹中的第一个文件，然后利用句柄进行遍历
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != 0)
	{
		do
		{
			string path_s = p.assign(path).append("\\").append(fileinfo.name);
			if (IsPointChar(fileinfo.name) != 0 && 
				IsFileCreateTimeMoreThanNDaysToNow(fileinfo, CleanLogDays))
			{
				files.push_back(path_s);            //插入容器
			}
		} while (_findnext(hFile, &fileinfo) != -1);
		_findclose(hFile);    //关闭文件
	}
}