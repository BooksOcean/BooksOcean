#include "student_index.h"
#include<string>
#include<iostream>
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
#include"student_borrowdetail.h"
#include<QSignalMapper>
using namespace std;	

student_index::student_index(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.etSnumber->setText(userConfig::username);
	ui.etSname->setEnabled(false);
	ui.etDebt->setEnabled(false);
	ui.etSdept->setEnabled(false);
	ui.etSnumber->setEnabled(false);
	ui.etBorrownumber->setEnabled(false);
	ui.btnPersonal->installEventFilter(this);
	ui.btnInformationchange->installEventFilter(this);
	ui.btnSearchbook->installEventFilter(this);
	ui.btnBorrowmore->installEventFilter(this);
	ui.btnOrdermore->installEventFilter(this);
	ui.tableBorrow->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑	
	ui.tableBorrow->verticalHeader()->setVisible(false); //设置行号不可见
	ui.tableBorrow->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//表宽度自适应
	//ui.tableBorrow->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);//第0列宽度自适应
	//ui.tableBorrow->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);//第1列宽度自适应
	//ui.tableBorrow->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);//第2列宽度自适应
	//ui.tableBorrow->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);//第3列宽度自适应
	//ui.tableBorrow->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);//第4列宽度自适应
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
	Record record;
	vector<string>VALUES_2;
	vector<Record>resRecord;
	VALUES_2.push_back("one");
	VALUES_2.push_back("studentId");
	record.setStudentId(resStudent[0].id);
	FileDB::select("record", record, VALUES_2, resRecord);
	//每借阅的每一本书加载到表格里
	string borrowNumber = "(";
	char c[20];
	itoa(resRecord.size(), c, 10);
	borrowNumber += c;
	borrowNumber += ")";
	ui.etBorrownumber->setText(strtoqs(borrowNumber));
	QStringList header;
	header << strtoqs("封面") << strtoqs("书名") << strtoqs("作者") << strtoqs("出版社")<< strtoqs("查看详情");
	ui.tableBorrow->setHorizontalHeaderLabels(header);
	ui.tableBorrow->horizontalHeader()->setStretchLastSection(true);
	ui.tableBorrow->setEditTriggers(QAbstractItemView::NoEditTriggers);
	int sum_row = ui.tableBorrow->rowCount();
	ui.tableBorrow->removeRow(sum_row);
	Book book;
	vector<string>VALUES_3;
	vector<Book>resBook;
	VALUES_3.push_back("one");
	VALUES_3.push_back("id");
	//逐行加载到借阅表里
	for (int i = 0; i < resRecord.size(); i++) {
		resBook.clear();
		book.setId(resRecord[i].bookId);
		FileDB::select("book", book, VALUES_3, resBook);
		if (resRecord[0].id != -1) {
			int row = ui.tableBorrow->rowCount();
			ui.tableBorrow->insertRow(i);
			//加载图片
			string s = resBook[0].cover;
			QPixmap p;
			p.load("images/logo.png");
			QLabel *label = new QLabel;
			label->setPixmap(p);
			ui.tableBorrow->setCellWidget(i, 0, label);
			//加载书名作者出版社
			addItemContent(i, 1, chartoqs(resBook[0].name));
			addItemContent(i, 2, chartoqs(resBook[0].author));
			addItemContent(i, 3, chartoqs(resBook[0].publish));

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
			signalMapper->setMapping(btn, resBook[0].id);
			connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(OnBtnClicked(int)));
		}

	}

}

void student_index::ClickButton() {
}

void student_index::OnBtnClicked(int id)
{
	bookConfig::bookId = id;
	student_borrowdetail *rec = new student_borrowdetail;
	rec->show();
	this->close();
}

QString student_index::chartoqs(char *p) {
	string s = p;
	return QString(QString::fromLocal8Bit(s.c_str()));
}