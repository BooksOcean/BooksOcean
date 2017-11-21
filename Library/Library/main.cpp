#include "library.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>
#include"test.h"
#include"student_update.h"
#include<iostream>
#include<vector>
#include"userConfig.h"
#include<student_classify.h>
using namespace std;
int main(int argc, char *argv[])
{
	QTextCodec * BianMa = QTextCodec::codecForName("GBK");
	QApplication a(argc, argv);
	userConfig::id = 4614;
	userConfig::username = "15020031106";
	userConfig::password = "111111";
	student_index w;
	w.show();

	return a.exec();
}
