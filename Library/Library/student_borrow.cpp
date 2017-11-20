#include "student_borrow.h"
#include "userConfig.h"
#include<string>
#include<iostream>
#include<QMessageBox>
#include <QTextCodec>
#include"student.h"
#include"record.h"
#include"book.h"
#include"filedb.h"
#include"student_index.h"
#include"student_searchbook.h"
#include"bookConfig.h"
#include"student_bookdetail.h"
#include"qlabel.h"
#include"student_update.h"
#include"student_borrowdetail.h"
#include"bookMap.h"
#include<QSignalMapper>
#include <qtnetwork/qnetworkaccessmanager>
#include <qtnetwork/QNetworkRequest>
#include <qtnetwork/QNetworkRequest>
#include <qtnetwork/QNetworkReply>
using namespace std;

student_borrow::student_borrow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.etBorrowNumber->setEnabled(false);
	ui.lineEdit->setEnabled(false);
	ui.lineEdit_3->setEnabled(false);
	ui.lineEdit_5->setEnabled(false);
	ui.btnInformationchange->installEventFilter(this);
	ui.btnPersonal->installEventFilter(this);
	ui.btnSearchbook->installEventFilter(this);
	ui.btnFirstPage->installEventFilter(this);
	ui.btnLastPage->installEventFilter(this);
	ui.btnNextPage->installEventFilter(this);
	ui.btnTheLast->installEventFilter(this);
	ui.btnReturn->installEventFilter(this);
	ui.tableBorrow->installEventFilter(this);
	ui.btnInformationchange->installEventFilter(this);
	InitThisPage();
}

bool student_borrow::eventFilter(QObject *obj, QEvent *event) {
	QTextCodec * BianMa = QTextCodec::codecForName("GBK");

	if (obj == ui.btnLastPage) {
		if (event->type() == QEvent::MouseButtonPress) {
			if (!(PageIndex == 1))
				LastPage();
			return true;
		}
		else {
			return false;
		}
	}

	else if (obj == ui.btnNextPage) {
		if (event->type() == QEvent::MouseButtonPress) {
			if (!(PageIndex == PageCount))
				NextPage();
			return true;
		}
		else {
			return false;
		}
	}
	else if (obj == ui.btnFirstPage) {
		if (event->type() == QEvent::MouseButtonPress) {
			if (!(PageIndex == 1))
				FirstPage();
			return true;
		}
		else {
			return false;
		}
	}

	else if (obj == ui.btnTheLast) {
		if (event->type() == QEvent::MouseButtonPress) {
			if (!(PageIndex == PageCount))
				TheLastPage();
			return true;
		}
		else {
			return false;
		}
	}

	if (obj == ui.btnReturn && event->type() == QEvent::MouseButtonPress) {
		student_index *rec = new student_index;
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
	if (obj == ui.btnInformationchange && event->type() == QEvent::MouseButtonPress) {
		student_update *rec = new student_update;
		rec->show();
		this->close();
	}
	return false;
}

student_borrow::~student_borrow()
{

}

void student_borrow::InitThisPage() {
	QTextCodec * BianMa = QTextCodec::codecForName("GBK");
	//获取登录进来学生的学号
	char* ch1;
	QByteArray ba = userConfig::username.toLatin1();
	ch1 = ba.data();
	//查询这个学生的基本信息
	Student student;
	vector<string>VALUES;
	vector<Student>resStudent;
	VALUES.push_back("one");
	VALUES.push_back("usercode");
	student.setUsercode(ch1);
	FileDB::select("student", student, VALUES, resStudent);

	/*
	*以下更新借阅表
	*/
	//查询这个学生的借书记录
	Record record;
	VALUES.clear();
	VALUES.push_back("one");
	VALUES.push_back("studentId");
	record.setStudentId(resStudent[0].id);
	FileDB::select("record", record, VALUES, resRecord);
	PageIndex = 1;
	//每借阅的每一本书加载到表格里
	string borrowNumber = "(";
	char c1[20];
	itoa(resRecord.size(), c1, 10);
	borrowNumber += c1;
	borrowNumber += ")";
	ui.etBorrowNumber->setText(strtoqs(borrowNumber));
	QStringList header;
	header << strtoqs("封面") <<strtoqs("书名") << strtoqs("作者") << strtoqs("出版社")<< strtoqs("查看详情");
	ui.tableBorrow->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑	
	ui.tableBorrow->verticalHeader()->setVisible(false); //设置行号不可见
	ui.tableBorrow->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//表宽度自适应
	ui.tableBorrow->setFrameShape(QFrame::NoFrame);//设置无边框
	ui.tableBorrow->setShowGrid(false); //设置不显示格子线
	ui.tableBorrow->setHorizontalHeaderLabels(header);
	ui.tableBorrow->horizontalHeader()->setStretchLastSection(true);
	ui.tableBorrow->setEditTriggers(QAbstractItemView::NoEditTriggers);
	int sum_row = ui.tableBorrow->rowCount();
	ui.tableBorrow->removeRow(sum_row);
	PageCount = ceill(resRecord.size() / (double)PageLength);
	ui.etPageIndex->setText(QString::number(PageIndex, 10));
	ui.etPageCount->setText(QString::number(PageCount, 10));
	DataBind();

}

QString student_borrow::strtoqs(const string &s)

{

	return QString(QString::fromLocal8Bit(s.c_str()));

}

string student_borrow::qstostr(const QString &s)

{

	return string((const char*)s.toLocal8Bit());

}

void student_borrow::addItemContent(int row, int column, QString content)
{
	QTableWidgetItem *item = new QTableWidgetItem(content);
	ui.tableBorrow->setItem(row, column, item);
}

void student_borrow::FirstPage() {
	PageIndex=1;
	ui.etPageIndex->setText(QString::number(PageIndex, 10));
	DataBind();
}

void student_borrow::TheLastPage() {
	PageIndex=PageCount;
	ui.etPageIndex->setText(QString::number(PageIndex, 10));
	DataBind();
}

void student_borrow::NextPage() {
	if (PageIndex >= PageCount)return;
	PageIndex++;
	ui.etPageIndex->setText(QString::number(PageIndex, 10));
	DataBind();
}

void student_borrow::LastPage() {
	if (PageIndex <= 1)return;
	PageIndex--;
	ui.etPageIndex->setText(QString::number(PageIndex, 10));
	DataBind();
}

void student_borrow::DataBind() {
	for (int i = ui.tableBorrow->rowCount(); i > 0.; i--) {
		ui.tableBorrow->removeRow(0);
	}
	int currentPageBegin = (PageIndex - 1)*PageLength;
	int currentPageEnd = (currentPageBegin + PageLength) < resRecord.size() ? (currentPageBegin + PageLength) : resRecord.size();
	Book book;
	vector<string>VALUES;
	vector<Book>resBook;
	BookMap bookmap;
	vector<BookMap>resBookMap;
	for (int i = currentPageBegin; i < currentPageEnd; i++) {
		VALUES.clear();
		resBook.clear();
		VALUES.push_back("one");
		VALUES.push_back("id");
		resBook.clear();
		resBookMap.clear();
		bookmap.setId(resRecord[i].bookId);
		FileDB::select("bookMap", bookmap, VALUES, resBookMap);
		book.setId(resBookMap[0].bookId);
		FileDB::select("book", book, VALUES, resBook);
		ui.tableBorrow->insertRow(i - currentPageBegin);
		ui.tableBorrow->setRowHeight(i - currentPageBegin, 200);//第一行
		//加载图片
		QUrl url(resBook[0].cover);
		QNetworkAccessManager manager;
		QEventLoop loop;
		// qDebug() << "Reading picture form " << url;
		QNetworkReply *reply = manager.get(QNetworkRequest(url));
		//请求结束并下载完成后，退出子事件循环
		QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
		//开启子事件循环
		loop.exec();

		QByteArray jpegData = reply->readAll();
		QPixmap pixmap;
		pixmap.loadFromData(jpegData);
		//改变图片大小
		pixmap = pixmap.scaled(110, 130, Qt::KeepAspectRatio);
		QLabel *label = new QLabel;
		label->setPixmap(pixmap);
		ui.tableBorrow->setCellWidget(i - currentPageBegin, 0, label);
		//加载书名作者出版社

		addItemContent(i - currentPageBegin, 1, strtoqs(resBook[0].name));
		addItemContent(i - currentPageBegin, 2, strtoqs(resBook[0].author));
		addItemContent(i - currentPageBegin, 3, strtoqs(resBook[0].publish));

		//添加“详情”按钮，并绑定事件
		QPushButton *btn = new QPushButton;
		ui.tableBorrow->setCellWidget(i - currentPageBegin, 4, btn);
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

void student_borrow::ClickButton() {
	student_index *rec = new student_index;
	rec->show();
	this->close();
}

void student_borrow::OnBtnClicked(int id)
{
	bookConfig::bookNo = id;
	student_borrowdetail *rec = new student_borrowdetail;
	rec->show();
	this->close();
}

QString student_borrow::chartoqs(char *p) {
	string s = p;
	return QString(QString::fromLocal8Bit(s.c_str()));
}