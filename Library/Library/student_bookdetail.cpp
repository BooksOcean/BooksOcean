#include "student_bookdetail.h"
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

student_bookDetail::student_bookDetail(QWidget *parent)
	: QWidget(parent)
{
	QTextCodec * BianMa = QTextCodec::codecForName("GBK");
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
	ui.btnBorrow->installEventFilter(this);
	ui.btnOrder->installEventFilter(this);
	ui.btnReturn->installEventFilter(this);
	InitThisPage();
}

student_bookDetail::~student_bookDetail()
{

}

void student_bookDetail::InitThisPage() {
	QTextCodec * BianMa = QTextCodec::codecForName("GBK");
	Book book;
	vector<string>VALUES;
	vector<Book>resBook;
	VALUES.push_back("one");
	VALUES.push_back("id");
	book.setId(bookConfig::bookId);
	FileDB::select("book", book, VALUES, resBook);
	if (resBook.size() > 0) {
		ui.etBookNameHead->setText(chartoqs(resBook[0].name));
		ui.etBookName->setText(chartoqs(resBook[0].name));
		ui.etAuthor->setText(chartoqs(resBook[0].author));
		ui.etPublish->setText(chartoqs(resBook[0].publish));
		ui.etISBN->setText(chartoqs(resBook[0].ISBN));
	}
	else {
		QMessageBox::information(NULL, BianMa->toUnicode(""), BianMa->toUnicode("未找到书本"), QMessageBox::Ok);
	}
}

bool student_bookDetail::eventFilter(QObject *obj, QEvent *event) {
	QTextCodec * BianMa = QTextCodec::codecForName("GBK");
	if (obj == ui.btnBorrow && event->type() == QEvent::MouseButtonPress) {
		Record thisrecord; 
		vector<string>VALUES; 
		vector<Record>res; 
		VALUES.push_back("one"); 
		VALUES.push_back("studentId");
		VALUES.push_back("bookId"); 
		thisrecord.setStudentId(userConfig::id);
		thisrecord.setBookId(bookConfig::bookId);
		FileDB::select("record", thisrecord, VALUES, res);
		if (res.size() == 0) {
			vector<Record>entity;
			Record record;

			record.setStudentId(userConfig::id);
			record.setBookId(bookConfig::bookId);


			QDateTime dt;
			QTime time;
			QDate date;
			dt.setTime(time.currentTime());
			dt.setDate(date.currentDate());
			QString currentDate = dt.toString("yyyy:MM:dd:hh:mm:ss");
			char* ch1;
			QByteArray ba = currentDate.toLatin1();
			ch1 = ba.data();
			record.setTime(ch1);

			record.setType(0);
			record.setMoney(0);
			entity.push_back(record);
			int res = FileDB::insert("record", entity);
			if (res > 0) {
				QMessageBox::information(NULL, BianMa->toUnicode(""), BianMa->toUnicode("借书成功"), QMessageBox::Ok);
				student_index *rec = new student_index;
				rec->show();
				this->close();
				return true;
			}
			else {
				QMessageBox::information(NULL, BianMa->toUnicode(""), BianMa->toUnicode("借书失败，未知错误"), QMessageBox::Ok);
				return true;
			}
		}
		else {
			QMessageBox::information(NULL, BianMa->toUnicode(""), BianMa->toUnicode("抱歉，您已经借过这本书了"), QMessageBox::Ok);
			return true;
		}

	}

	if (obj == ui.btnOrder && event->type() == QEvent::MouseButtonPress) {
		QMessageBox::information(NULL, BianMa->toUnicode(""), BianMa->toUnicode("暂不支持"), QMessageBox::Ok);
		return true;
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

QString student_bookDetail::chartoqs(char *p) {
	string s = p;
	return QString(QString::fromLocal8Bit(s.c_str()));
}

QString student_bookDetail::strtoqs(const string &s)

{

	return QString(QString::fromLocal8Bit(s.c_str()));

}

string student_bookDetail::qstostr(const QString &s)

{

	return string((const char*)s.toLocal8Bit());

}
