#include "student_bookdetail.h"
#include"student_index.h"
#include"bookConfig.h"
#include"book.h"
#include"filedb.h"
#include"classify.h"
#include<vector>
#include<string>
#include<QMessageBox>
#include <QTextCodec>
#include<QDateTime>
#include"record.h"
#include"student.h"
#include"userConfig.h"
#include"bookConfig.h"
#include"bookMap.h"
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
		Classify classify;
		vector<Classify>resClassify;
		classify.setId(resBook[0].classifyId);
		FileDB::select("classify", classify, VALUES, resClassify);
		ui.etClassify->setText(chartoqs(resClassify[0].name));
		ui.etScore->setText(QString("%1").arg(resBook[0].score));
		ui.etCount->setText(QString::number(resBook[0].count));
		ui.etNowCount->setText(QString::number(resBook[0].nowCount));
	}
	else {
		QMessageBox::information(NULL, BianMa->toUnicode(""), BianMa->toUnicode("δ�ҵ��鱾"), QMessageBox::Ok);
	}
}
//���ֲ���isOUT=0
void searchBookMap(int bookId, vector<BookMap>& res) {
	ifstream readFile;
	int lastId;
	readFile.open("bookMapInfo.dat", ios::in | ios::out | ios::binary);
	readFile.read((char*)&lastId, sizeof(lastId));
	readFile.close();

	readFile.open("bookMap.dat", ios::in | ios::out | ios::binary);
	int left = 0;
	int right = lastId - 1;
	int size = sizeof(BookMap);
	BookMap temp;
	int tempID = 0;


	while (left <= right) {
		int middle = (left + right) / 2;
		readFile.seekg(middle * size, ios::beg);
		readFile.read(reinterpret_cast<char*>(&temp), sizeof(temp));
		if (temp.bookId == bookId) {
			if(!temp.dirty&&!temp.isOut)
				res.push_back(temp);
			int tempMiddle = middle;
			while (1) {
				tempMiddle--;
				readFile.seekg(tempMiddle * size, ios::beg);
				readFile.read(reinterpret_cast<char*>(&temp), sizeof(temp));
				if (temp.bookId != bookId) break;
				if (!temp.dirty && !temp.isOut)
					res.push_back(temp);
			}
			tempMiddle = middle;
			while (1) {
				tempMiddle++;
				readFile.seekg(tempMiddle * size, ios::beg);
				readFile.read(reinterpret_cast<char*>(&temp), sizeof(temp));
				if (temp.bookId != bookId) break;
				if (!temp.dirty && !temp.isOut)
					res.push_back(temp);
			}
			break;
		}
		if (temp.bookId > bookId)
			right = middle - 1;
		else
			left = middle + 1;
	}
	readFile.close();
}


bool student_bookDetail::eventFilter(QObject *obj, QEvent *event) {
	QTextCodec * BianMa = QTextCodec::codecForName("GBK");
	if (obj == ui.btnBorrow && event->type() == QEvent::MouseButtonPress) {
		Student student;
		vector<string>VALUES0;
		vector<Student>resStudent;
		VALUES0.push_back("one");
		VALUES0.push_back("id");
		student.setId(userConfig::id);
		FileDB::select("student", student, VALUES0, resStudent);
		if (resStudent[0].money > 50) {
			QMessageBox::information(NULL, BianMa->toUnicode(""), BianMa->toUnicode("Ƿ��������ޣ����ȹ黹Ƿ��"), QMessageBox::Ok);
			return true;
		}
		
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
			
			
			vector<BookMap>allBooks;
			searchBookMap(bookConfig::bookId, allBooks);
			if (allBooks.size() > 0) {

				//���¿ɽ豾��
				Book book;
				vector<string>VALUES_3;
				vector<Book>resBook;
				VALUES_3.push_back("one");
				VALUES_3.push_back("id");
				book.setId(bookConfig::bookId);
				FileDB::select("book", book, VALUES_3, resBook);

				Book lbook;
				lbook.setId(bookConfig::bookId);
				resBook[0].setNowCount(resBook[0].nowCount - 1);
				FileDB::update("book", lbook, resBook[0], VALUES_3);

				//����bookMap
				BookMap lbookMap, nbookMap;
				lbookMap.setId(allBooks[0].id);
				nbookMap.setBookId(allBooks[0].bookId);
				nbookMap.setBookNum(allBooks[0].bookNum);
				nbookMap.setIsOut(1);
				FileDB::update("bookMap", lbookMap, nbookMap, VALUES_3);

				//������ļ�¼
				vector<Record>entity;
				Record record;
				record.setStudentId(userConfig::id);
				record.setBookId(allBooks[0].id);

				/*QDateTime dt;
				QTime time;
				QDate date;
				dt.setTime(time.currentTime());
				dt.setDate(date.currentDate());*/
				QDateTime dt = QDateTime::currentDateTime();
				QDateTime afterOneMonthDateTime = dt.addMonths(1);
				QString currentDate = afterOneMonthDateTime.toString("yyyy-MM-dd");
			
				char* ch1;
				QByteArray ba = currentDate.toLatin1();
				ch1 = ba.data();
				record.setTime(ch1);

				record.setType(0);
				record.setMoney(0);
				entity.push_back(record);
				int res = FileDB::insert("record", entity);
				if (res > 0) {
					QMessageBox::information(NULL, BianMa->toUnicode(""), BianMa->toUnicode("����ɹ�"), QMessageBox::Ok);
					student_index *rec = new student_index;
					rec->show();
					this->close();
					return true;
				}
				else {
					QMessageBox::information(NULL, BianMa->toUnicode(""), BianMa->toUnicode("����ʧ�ܣ�δ֪����"), QMessageBox::Ok);
					return true;
				}
			}
			else {
				QMessageBox::information(NULL, BianMa->toUnicode(""), BianMa->toUnicode("����ʧ�ܣ�û�пɽ豾"), QMessageBox::Ok);
				return true;
			}
	
		}
		else {
			QMessageBox::information(NULL, BianMa->toUnicode(""), BianMa->toUnicode("��Ǹ�����Ѿ�����Ȿ����"), QMessageBox::Ok);
			return true;
		}

	}

	if (obj == ui.btnOrder && event->type() == QEvent::MouseButtonPress) {
		Book book;
		vector<string>VALUES_3;
		vector<Book>resBook;
		VALUES_3.push_back("one");
		VALUES_3.push_back("id");
		book.setId(bookConfig::bookId);
		FileDB::select("book", book, VALUES_3, resBook);
		if (resBook[0].nowCount>0) {
			QMessageBox::information(NULL, BianMa->toUnicode(""), BianMa->toUnicode("�������пɽ豾���޷�ԤԼ"), QMessageBox::Ok);
			return true;
		}
		else {//���Խ���ԤԼ
			Student student;
			vector<string>VALUES;
			vector<Student>resStudent;
			VALUES.push_back("one");
			VALUES.push_back("id");
			student.setId(userConfig::id);
			FileDB::select("student", student, VALUES, resStudent);
			if (resStudent[0].money > 50) {
				QMessageBox::information(NULL, BianMa->toUnicode(""), BianMa->toUnicode("Ƿ��������ޣ����ȹ黹Ƿ��"), QMessageBox::Ok);
				return true;
			}

			//����Ƿ��Ѿ��������ԤԼ���Ȿ����
			Record thisrecord;
			VALUES.clear();
			vector<Record>res;
			VALUES.push_back("one");
			VALUES.push_back("studentId");
			VALUES.push_back("bookId");
			thisrecord.setStudentId(userConfig::id);
			thisrecord.setBookId(bookConfig::bookId);
			FileDB::select("record", thisrecord, VALUES, res);
			if (res.size() == 0) {


				//vector<BookMap>allBooks;
				//searchBookMap(bookConfig::bookId, allBooks);
				//if (allBooks.size() > 0) {

				//	//����bookMap
				//	BookMap lbookMap, nbookMap;
				//	lbookMap.setId(allBooks[0].id);
				//	nbookMap.setBookId(allBooks[0].bookId);
				//	nbookMap.setBookNum(allBooks[0].bookNum);
				//	nbookMap.setIsOut(2);
				//	FileDB::update("bookMap", lbookMap, nbookMap, VALUES_3);

					//������ļ�¼
					vector<Record>entity;
					Record record;
					record.setStudentId(userConfig::id);
					record.setBookId(bookConfig::bookId);

					/*QDateTime dt;
					QTime time;
					QDate date;
					dt.setTime(time.currentTime());
					dt.setDate(date.currentDate());*/

					//��¼ԤԼʱ���Ӧ������ԤԼ��ʱ��
					QDateTime dt = QDateTime::currentDateTime();
					QDateTime afterFiveDaysDateTime = dt.addDays(5);
					QString currentDate = afterFiveDaysDateTime.toString("yyyy-MM-dd");
					//��������ת����Ӧ��������ʱ���¼�ļ�
					char* ch1;
					QByteArray ba = currentDate.toLatin1();
					ch1 = ba.data();
					record.setTime(ch1);

					record.setType(2);
					record.setMoney(0);
					entity.push_back(record);
					int res = FileDB::insert("record", entity);
					if (res > 0) {
						QMessageBox::information(NULL, BianMa->toUnicode(""), BianMa->toUnicode("ԤԼ�ɹ�"), QMessageBox::Ok);
						student_searchBook *rec = new student_searchBook;
						rec->show();
						this->close();
						return true;
					}
					else {
						QMessageBox::information(NULL, BianMa->toUnicode(""), BianMa->toUnicode("ԤԼʧ�ܣ�δ֪����"), QMessageBox::Ok);
						return true;
					}
			}
			else {
				QMessageBox::information(NULL, BianMa->toUnicode(""), BianMa->toUnicode("��Ǹ�����Ѿ��������ԤԼ���Ȿ����"), QMessageBox::Ok);
				return true;
			}
		}
		return true;
	}
	if (obj == ui.btnReturn && event->type() == QEvent::MouseButtonPress) {
		student_searchBook *rec = new student_searchBook;
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
