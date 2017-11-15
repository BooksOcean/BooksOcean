#include "student_index.h"
#include<string>
#include<iostream>
#include<QDateTime>
#include<QMessageBox>
#include <QTextCodec>
#include"qlabel.h"
#include"filedb.h"
#include"library.h"
#include"book.h"
#include<vector>
#include"userConfig.h"
#include"student.h"
#include"record.h"
#include"userConfig.h"
#include"student_borrow.h"
#include"student_searchbook.h"
#include"student_bookdetail.h"
#include"bookConfig.h"
#include"student_update.h"
#include"bookMap.h"
#include"student_borrowdetail.h"
#include"record.h"
#include<QSignalMapper>
using namespace std;	

student_index::student_index(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.lineEdit->setEnabled(false);
	ui.lineEdit_2->setEnabled(false);
	ui.etSnumber->setText(userConfig::username);
	ui.etSname->setEnabled(false);
	ui.etDebt->setEnabled(false);
	ui.etSdept->setEnabled(false);
	ui.etSnumber->setEnabled(false);
	ui.etBorrownumber->setEnabled(false);
	ui.etOrderNumber->setEnabled(false);
	ui.btnPersonal->installEventFilter(this);
	ui.btnInformationchange->installEventFilter(this);
	ui.btnSearchbook->installEventFilter(this);
	ui.btnBorrowmore->installEventFilter(this);
	ui.btnOrdermore->installEventFilter(this);
	ui.tableBorrow->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑	
	ui.tableBorrow->verticalHeader()->setVisible(false); //设置行号不可见
	ui.tableBorrow->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//表宽度自适应
	ui.tableBorrow->setFrameShape(QFrame::NoFrame);//设置无边框
	ui.tableBorrow->setShowGrid(false); //设置不显示格子线
	InitThisPage();
}

student_index::~student_index()
{

}

bool student_index::eventFilter(QObject *obj, QEvent *event) {
	QTextCodec * BianMa = QTextCodec::codecForName("GBK");
	if (obj ==ui.btnBorrowmore && event->type() == QEvent::MouseButtonPress) {
		student_borrow *rec = new student_borrow;
		rec->show();
		this->close();
	}
	if (obj == ui.btnSearchbook && event->type() == QEvent::MouseButtonPress) {
		student_searchBook *rec = new student_searchBook;
		this->close();
		rec->show();
	}
	if (obj == ui.btnInformationchange && event->type() == QEvent::MouseButtonPress) {
		student_update *rec = new student_update;
		this->close();
		rec->show();
	}
	return false;
}

QString student_index::strtoqs(const string &s)

{

	return QString(QString::fromLocal8Bit(s.c_str()));

}

string student_index::qstostr(const QString &s)

{

	return string((const char*)s.toLocal8Bit());

}

void student_index::addItemContent(int row, int column, QString content)
{
	QTableWidgetItem *item = new QTableWidgetItem(content);
	ui.tableBorrow->setItem(row, column, item);
}

void student_index::InitThisPage() {
	QTextCodec * BianMa = QTextCodec::codecForName("GBK");

	//获取登录进来学生的学号
	char* ch1;
	QByteArray ba = ui.etSnumber->text().toLatin1();
	ch1 = ba.data();

	//查询这个学生的基本信息，并更新页面
	Student student;
	vector<string>VALUES;
	vector<Student>resStudent;
	VALUES.push_back("one");
	VALUES.push_back("usercode");
	student.setUsercode(ch1);
	FileDB::select("student", student, VALUES, resStudent);
	ui.etSname->setText(BianMa->toUnicode(resStudent[0].username));
	ui.etSdept->setText(BianMa->toUnicode(resStudent[0].dept));
	
	/*
	 *以下更新借阅表
	*/
	//查询这个学生的借书记录
	//未超期的书
	Record record;
	vector<string>VALUES_2;
	vector<Record>resRecord;
	VALUES_2.push_back("one");
	VALUES_2.push_back("studentId");
	VALUES_2.push_back("type");
	record.setStudentId(resStudent[0].id);
	record.setType(0);
	FileDB::select("record", record, VALUES_2, resRecord);

	//早已超期的书
	Record record_2;
	VALUES_2.clear();
	vector<Record>resRecord_2;
	VALUES_2.push_back("one");
	VALUES_2.push_back("studentId");
	VALUES_2.push_back("type");
	record_2.setStudentId(resStudent[0].id);
	record_2.setType(1);
	FileDB::select("record", record_2, VALUES_2, resRecord_2);

	//预约的书
	//查询全部预约记录
	Record record_3;
	VALUES_2.clear();
	vector<Record>resRecord_3;
	VALUES_2.push_back("one");
	VALUES_2.push_back("studentId");
	VALUES_2.push_back("type");
	record_3.setStudentId(resStudent[0].id);
	record_3.setType(2);
	FileDB::select("record", record_3, VALUES_2, resRecord_3);
	//删去超期的预约记录
	//计算时间,并删除超期的预约记录
	QDateTime now = QDateTime::currentDateTime();
	for (int i = 0; i < resRecord_3.size(); i++) {
		QDateTime then = QDateTime::fromString(resRecord_3[i].time, "yyyy-MM-dd");
		int span = then.secsTo(now);
		if (span > 0) {
			if (resRecord_3[i].type == 2) {
				Record rec;
				VALUES_2.clear();
				VALUES_2.push_back("one");
				VALUES_2.push_back("id");
				rec.setId(resRecord_3[i].id);
				FileDB::Delete("record", rec, VALUES_2);
			}
		}
	}
	//重新查询预约记录，得到此用户全部合法的预约记录
	Record record_4;
	VALUES_2.clear();
	vector<Record>resRecord_4;
	VALUES_2.push_back("one");
	VALUES_2.push_back("studentId");
	VALUES_2.push_back("type");
	record_4.setStudentId(resStudent[0].id);
	record_4.setType(2);
	FileDB::select("record", record_4, VALUES_2, resRecord_4);

	//每借阅的每一本书加载到表格里
	string borrowNumber = "(";
	char c[20];
	itoa(resRecord.size()+resRecord_2.size(), c, 10);
	borrowNumber += c;
	borrowNumber += ")";
	ui.etBorrownumber->setText(strtoqs(borrowNumber));
	QStringList header;
	header << strtoqs("书名") << strtoqs("作者") << strtoqs("出版社") << strtoqs("状态") << strtoqs("查看详情");
	ui.tableBorrow->setHorizontalHeaderLabels(header);
	ui.tableBorrow->horizontalHeader()->setStretchLastSection(true);
	ui.tableBorrow->setEditTriggers(QAbstractItemView::NoEditTriggers);
	int sum_row = ui.tableBorrow->rowCount();
	ui.tableBorrow->removeRow(sum_row);

	Book book;
	BookMap bookmap;
	vector<string>VALUES_3;
	vector<Book>resBook;
	vector<BookMap>resBookMap;
	VALUES_3.push_back("one");
	VALUES_3.push_back("id");
	//逐行加载到借阅表里

	float money = 0;
	//加载借阅但未超期的数目（注意此时可能有一部分变为超期）
	for (int i = 0; i < resRecord.size(); i++) {
		QDateTime then = QDateTime::fromString(resRecord[i].time, "yyyy-MM-dd");
		int span = then.secsTo(now);
		if (span > 0) {
			if (resRecord[i].type == 0) {
				Record rec;
				rec.setId(resRecord[i].id);
				int day = span / (60 * 60 * 24);
				money += day;
				resRecord[i].type = 1;
				FileDB::update("record", rec, resRecord[i], VALUES_3);
			}
		}

		resBook.clear();
		resBookMap.clear();
		bookmap.setId(resRecord[i].bookId);
		FileDB::select("bookMap", bookmap, VALUES_3, resBookMap);
		book.setId(resBookMap[0].bookId);
		FileDB::select("book", book, VALUES_3, resBook);
		int row = ui.tableBorrow->rowCount();
		ui.tableBorrow->insertRow(i);
		////加载图片
		//string s = resBook[0].cover;
		//QPixmap p;
		//p.load("images/logo.png");
		//QLabel *label = new QLabel;
		//label->setPixmap(p);
		//ui.tableBorrow->setCellWidget(i, 0, label);
		//加载书名作者出版社
		addItemContent(i, 0, chartoqs(resBook[0].name));
		addItemContent(i, 1, chartoqs(resBook[0].author));
		addItemContent(i, 2, chartoqs(resBook[0].publish));
		if(resRecord[i].type==0)
			addItemContent(i, 3, chartoqs("正常"));
		else
			addItemContent(i, 3, chartoqs("超期"));
		//添加“详情”按钮，并绑定事件
		QPushButton *btn = new QPushButton;
		ui.tableBorrow->setCellWidget(i, 4, btn);
		btn->setText(strtoqs("详情"));
		btn->setStyleSheet(
			"color:#4695d2;"
			"border:none;"
			"background:white;"
			"text-size:20px;"
		);
		QSignalMapper* signalMapper = new QSignalMapper(this);
		connect(btn, SIGNAL(clicked()), signalMapper, SLOT(map()));
		signalMapper->setMapping(btn, resRecord[i].bookId);
		connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(OnBtnClicked(int)));
		
	}
	//加载早已超期的数目
	for (int i = 0; i < resRecord_2.size(); i++) {
		QDateTime then = QDateTime::fromString(resRecord_2[i].time, "yyyy-MM-dd");
		int span = then.secsTo(now);
		if (span > 0) {
				Record rec;
				rec.setId(resRecord_2[i].id);
				int day = span / (60 * 60 * 24);
				money += day;
				resRecord_2[i].type = 1;
				FileDB::update("record", rec, resRecord_2[i], VALUES_3);
		}

		resBook.clear();
		resBookMap.clear();
		bookmap.setId(resRecord_2[i].bookId);
		FileDB::select("bookMap", bookmap, VALUES_3, resBookMap);
		book.setId(resBookMap[0].bookId);
		FileDB::select("book", book, VALUES_3, resBook);
		int row = ui.tableBorrow->rowCount();
		ui.tableBorrow->insertRow(i+resRecord.size());
		////加载图片
		//string s = resBook[0].cover;
		//QPixmap p;
		//p.load("images/logo.png");
		//QLabel *label = new QLabel;
		//label->setPixmap(p);
		//ui.tableBorrow->setCellWidget(i, 0, label);
		//加载书名作者出版社
		addItemContent(i + resRecord.size(), 0, chartoqs(resBook[0].name));
		addItemContent(i + resRecord.size(), 1, chartoqs(resBook[0].author));
		addItemContent(i + resRecord.size(), 2, chartoqs(resBook[0].publish));
		if (resRecord_2[i].type == 0)
			addItemContent(i + resRecord.size(), 3, chartoqs("正常"));
		else if(resRecord_2[i].type==1)
			addItemContent(i + resRecord.size(), 3, chartoqs("超期"));
		//添加“详情”按钮，并绑定事件
		QPushButton *btn = new QPushButton;
		ui.tableBorrow->setCellWidget(i + resRecord.size(), 4, btn);
		btn->setText(strtoqs("详情"));
		btn->setStyleSheet(
			"color:#4695d2;"
			"border:none;"
			"background:white;"
			"text-size:20px;"
		);
		QSignalMapper* signalMapper = new QSignalMapper(this);
		connect(btn, SIGNAL(clicked()), signalMapper, SLOT(map()));
		signalMapper->setMapping(btn, resRecord_2[i].bookId);
		connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(OnBtnClicked(int)));

	}
	
	//保存欠费金额
	if (money > resStudent[0].money) {
		resStudent[0].setMoney(money);
		student.setId(resStudent[0].id);
		FileDB::update("student", student, resStudent[0], VALUES_3);
	}
	QString total = QString("%1").arg(resStudent[0].money);
	ui.etDebt->setText(chartoqs("欠款金额：") + total + chartoqs("元"));

	//加载预约书目
	string orderNumber = "(";
	char c2[20];
	itoa(resRecord_4.size(), c2, 10);
	orderNumber += c2;
	orderNumber += ")";
	ui.etOrderNumber->setText(strtoqs(orderNumber));
	QStringList header2;
	header2 << strtoqs("书名") << strtoqs("作者") << strtoqs("出版社") << strtoqs("状态");
	ui.tableOrder->setHorizontalHeaderLabels(header2);
	ui.tableOrder->horizontalHeader()->setStretchLastSection(true);
	ui.tableOrder->setEditTriggers(QAbstractItemView::NoEditTriggers);
	int sum_row2 = ui.tableOrder->rowCount();
	ui.tableOrder->removeRow(sum_row2);

	Book book_2;
	BookMap bookmap_2;
	vector<string>VALUES_4;
	vector<Book>resBook_2;
	vector<BookMap>resBookMap_2;
	VALUES_4.push_back("one");
	VALUES_4.push_back("id");
	for (int i = 0; i < resRecord_4.size(); i++) {
		resBook_2.clear();
		resBookMap_2.clear();
		bookmap_2.setId(resRecord_4[i].bookId);
		FileDB::select("bookMap", bookmap_2, VALUES_4, resBookMap_2);
		book_2.setId(resBookMap_2[0].bookId);
		FileDB::select("book", book_2, VALUES_4, resBook_2);
		int row = ui.tableOrder->rowCount();
		ui.tableOrder->insertRow(i);
		////加载图片
		//string s = resBook[0].cover;
		//QPixmap p;
		//p.load("images/logo.png");
		//QLabel *label = new QLabel;
		//label->setPixmap(p);
		//ui.tableBorrow->setCellWidget(i, 0, label);
		//加载书名作者出版社
		addItemContent(i, 0, chartoqs(resBook_2[0].name));
		addItemContent(i, 1, chartoqs(resBook_2[0].author));
		addItemContent(i, 2, chartoqs(resBook_2[0].publish));
		if (resRecord[i].type == 2)
			addItemContent(i, 3, chartoqs("正常"));

	}
}

void student_index::ClickButton() {
}

void student_index::OnBtnClicked(int id)
{
	bookConfig::bookNo = id;
	student_borrowdetail *rec = new student_borrowdetail;
	rec->show();
	this->close();
}

QString student_index::chartoqs(char *p) {
	string s = p;
	return QString(QString::fromLocal8Bit(s.c_str()));
}