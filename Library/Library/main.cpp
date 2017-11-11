#include "library.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>
#include"test.h"
#include"student_update.h"
#include<iostream>
#include<vector>
using namespace std;
int main(int argc, char *argv[])
{
	QTextCodec * BianMa = QTextCodec::codecForName("GBK");
	QApplication a(argc, argv);
	
	Library w;
	w.show();

	return a.exec();
}
