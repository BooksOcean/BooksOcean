#include "library.h"
#include"ui_library.h"
#include"student_index.h"
#include"filedb.h"
#include"student.h"
#include<string>
#include<iostream>
#include<QMessageBox>
#include <QTextCodec>
#include"userConfig.h"
using namespace std;



Library::Library(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.btnLogin->installEventFilter(this);
}

Library::~Library()
{

}

bool Library::eventFilter(QObject *obj, QEvent *event) {
	QTextCodec * BianMa = QTextCodec::codecForName("GBK");
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
	if (obj == ui.btnLogin && event->type()==QEvent::MouseButtonPress) {
		char* ch1;
		QByteArray ba = ui.etUsername->text().toLatin1();
		ch1 = ba.data();
		Student student;
		vector<string>VALUES;
		vector<Student>res;
		VALUES.push_back("one");
		VALUES.push_back("usercode");
		student.setUsercode(ch1);
		FileDB::select("student", student, VALUES, res);
		if (res.size() > 0) {
			char* ch2;
			QByteArray ba = ui.etPassword->text().toLatin1();
			ch2 = ba.data();
			if (!strcmp(ch2,res[0].password)) {
				userConfig::id = res[0].id;
				connect(ui.btnLogin, SIGNAL(clicked()), this, SLOT(ClickButton()));
			}
			else {
				QMessageBox::information(NULL, BianMa->toUnicode(""), BianMa->toUnicode("用户名或密码输入错误"), QMessageBox::Ok);
			}
		}
		else {
			QMessageBox::information(NULL, BianMa->toUnicode(""), BianMa->toUnicode("用户名或密码输入错误"), QMessageBox::Ok);
		}
	}
	return false;
}
QString Library::strtoqs(const string &s)

{

	return QString(QString::fromLocal8Bit(s.c_str()));

}

string Library::qstostr(const QString &s)

{

	return string((const char*)s.toLocal8Bit());

}

void Library::ClickButton() {
	userConfig::username = ui.etUsername->text();
	userConfig::password = ui.etPassword->text();
	student_index *rec = new student_index;
	rec->show();
	this->close();
}
