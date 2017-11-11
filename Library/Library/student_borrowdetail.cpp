#include "student_borrowdetail.h"
#include"student_index.h"
#include"bookConfig.h"
#include"book.h"
#include"filedb.h"
#include<vector>
#include<string>
#include<QMessageBox>
#include <QTextCodec>
#include<QDateTime>
#include"record.h"
#include"student.h"
#include"userConfig.h"
#include"bookConfig.h"
#include"student_update.h"
#include"student_searchbook.h"
using namespace std;

student_borrowdetail::student_borrowdetail(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.etBookNameHead->setEnabled(false);
	ui.etBookName->setEnabled(false);
	ui.etAuthor->setEnabled(false);
	ui.etPublish->setEnabled(false);
	ui.etISBN->setEnabled(false);
	ui.etClassify->setEnabled(false);
	ui.etBookNameHead->setEnabled(false);
	ui.etBookName->setEnabled(false);
	ui.etAuthorHead->setEnabled(false);
	ui.etPublishHead->setEnabled(false);
	ui.etISBNHead->setEnabled(false);
	ui.etClassifyHead->setEnabled(false);
	ui.btnPersonal->installEventFilter(this);
	ui.btnSearchbook->installEventFilter(this);
	ui.btnInformationchange->installEventFilter(this);
	ui.btnBorrowagain->installEventFilter(this);
	ui.btnReturnbook->installEventFilter(this);
	ui.btnReturn->installEventFilter(this);
	InitThisPage();
}

student_borrowdetail::~student_borrowdetail()
{

}

void student_borrowdetail::InitThisPage() {
	Book book;
	vector<string>VALUES;
	vector<Book>resBook;
	VALUES.push_back("one");
	VALUES.push_back("id");
	book.setId(bookConfig::bookId);
	FileDB::select("book", book, VALUES, resBook);
	ui.etBookNameHead->setText(chartoqs(resBook[0].name));
	ui.etBookName->setText(chartoqs(resBook[0].name));
	ui.etAuthor->setText(chartoqs(resBook[0].author));
	ui.etPublish->setText(chartoqs(resBook[0].publish));
	ui.etISBN->setText(chartoqs(resBook[0].ISBN));
}

bool student_borrowdetail::eventFilter(QObject *obj, QEvent *event) {
	QTextCodec * BianMa = QTextCodec::codecForName("GBK");
	if (obj == ui.btnReturnbook && event->type() == QEvent::MouseButtonPress) {
		Record record; 
		vector<string>VALUES; 
		vector<Record>res; 
		VALUES.push_back("one"); 
		VALUES.push_back("bookId"); 
		VALUES.push_back("studentId");
		record.setBookId(bookConfig::bookId);
		record.setStudentId(userConfig::id); 
		FileDB::select("record", record, VALUES, res);
		if (res.size()!=1) {
			QMessageBox::information(NULL, BianMa->toUnicode(""), BianMa->toUnicode("错误，存在两条一模一样的数据,或未找到记录"), QMessageBox::Ok);
			return true;
		}
		else {
			Record record_delete; 
			vector<string>VALUES_2; 
			VALUES_2.push_back("one"); 
			VALUES_2.push_back("id"); 
			record_delete.setId(res[0].id); 
			int res_2 = FileDB::Delete("record", record_delete, VALUES_2);
			if (res_2 > 0) {
				QMessageBox::information(NULL, BianMa->toUnicode(""), BianMa->toUnicode("还书成功"), QMessageBox::Ok);
				student_index *rec = new student_index;
				rec->show();
				this->close();
				return true;
			}
			else {
				QMessageBox::information(NULL, BianMa->toUnicode(""), BianMa->toUnicode("未知错误"), QMessageBox::Ok);
				return true;
			}
		}
	}
	if (obj == ui.btnBorrowagain && event->type() == QEvent::MouseButtonPress) {
		QMessageBox::information(NULL, BianMa->toUnicode(""), BianMa->toUnicode("暂不支持"), QMessageBox::Ok);
	}
	if (obj == ui.btnReturn && event->type() == QEvent::MouseButtonPress) {
		student_index *rec = new student_index;
		rec->show();
		this->close();
	}
	if (obj == ui.btnInformationchange && event->type() == QEvent::MouseButtonPress) {
		student_update *rec = new student_update;
		rec->show();
		this->close();
	}
	if (obj == ui.btnPersonal && event->type() == QEvent::MouseButtonPress) {
		student_index *rec = new student_index;
		rec->show();
		this->close();
	}
	if (obj == ui.btnSearchbook && event->type() == QEvent::MouseButtonPress) {
		student_searchBook *rec = new student_searchBook;
		rec->show();
		this->close();
	}
	return false;
}

QString student_borrowdetail::chartoqs(char *p) {
	string s = p;
	return QString(QString::fromLocal8Bit(s.c_str()));
}

QString student_borrowdetail::strtoqs(const string &s)

{

	return QString(QString::fromLocal8Bit(s.c_str()));

}

string student_borrowdetail::qstostr(const QString &s)

{

	return string((const char*)s.toLocal8Bit());

}