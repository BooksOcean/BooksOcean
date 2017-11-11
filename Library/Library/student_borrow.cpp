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
#include<QSignalMapper>
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
	//��ȡ��¼����ѧ����ѧ��
	char* ch1;
	QByteArray ba = userConfig::username.toLatin1();
	ch1 = ba.data();
	//��ѯ���ѧ���Ļ�����Ϣ
	Student student;
	vector<string>VALUES;
	vector<Student>resStudent;
	VALUES.push_back("one");
	VALUES.push_back("usercode");
	student.setUsercode(ch1);
	FileDB::select("student", student, VALUES, resStudent);

	/*
	*���¸��½��ı�
	*/
	//��ѯ���ѧ���Ľ����¼
	Record record;
	VALUES.clear();
	VALUES.push_back("one");
	VALUES.push_back("studentId");
	record.setStudentId(resStudent[0].id);
	FileDB::select("record", record, VALUES, resRecord);
	PageIndex = 1;
	//ÿ���ĵ�ÿһ������ص�������
	string borrowNumber = "(";
	char c1[20];
	itoa(resRecord.size(), c1, 10);
	borrowNumber += c1;
	borrowNumber += ")";
	ui.etBorrowNumber->setText(strtoqs(borrowNumber));
	QStringList header;
	header << strtoqs("����") <<strtoqs("����") << strtoqs("����") << strtoqs("������")<< strtoqs("�鿴����");
	ui.tableBorrow->setEditTriggers(QAbstractItemView::NoEditTriggers);//���ò��ɱ༭	
	ui.tableBorrow->verticalHeader()->setVisible(false); //�����кŲ��ɼ�
	ui.tableBorrow->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//����������Ӧ
	ui.tableBorrow->setFrameShape(QFrame::NoFrame);//�����ޱ߿�
	ui.tableBorrow->setShowGrid(false); //���ò���ʾ������
	ui.tableBorrow->setHorizontalHeaderLabels(header);
	ui.tableBorrow->horizontalHeader()->setStretchLastSection(true);
	ui.tableBorrow->setEditTriggers(QAbstractItemView::NoEditTriggers);
	int sum_row = ui.tableBorrow->rowCount();
	ui.tableBorrow->removeRow(sum_row);
	PageCount = ceill(resRecord.size() / (double)PageLength);
	ui.etPageIndex->setText(QString::number(PageIndex, 10));
	ui.etPageCount->setText(QString::number(PageCount, 10));
	DataBind();
	/*Book book;
	vector<Book>resBook;*/
	//���м��ص����ı���
	/*for (int i = 0; i < resRecord.size(); i++) {
		VALUES.clear();
		resBook.clear();
		VALUES.push_back("one");
		VALUES.push_back("id");
		book.setId(resRecord[i].bookId);
		FileDB::select("book", book, VALUES, resBook);
		int row = ui.tableBorrow->rowCount();
		ui.tableBorrow->insertRow(i);
		addItemContent(i, 0, strtoqs(resBook[0].name));
		addItemContent(i, 1, strtoqs(resBook[0].author));
		addItemContent(i, 2, strtoqs(resBook[0].publish));
	}*/
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
	for (int i = currentPageBegin; i < currentPageEnd; i++) {
		VALUES.clear();
		resBook.clear();
		VALUES.push_back("one");
		VALUES.push_back("id");
		book.setId(resRecord[i].bookId);
		FileDB::select("book", book, VALUES, resBook);
		ui.tableBorrow->insertRow(i - currentPageBegin);
		//����ͼƬ
		string s = resBook[0].cover;
		QPixmap p;
		p.load("images/logo.png");
		QLabel *label = new QLabel;
		label->setPixmap(p);
		ui.tableBorrow->setCellWidget(i - currentPageBegin, 0, label);
		//�����������߳�����
		addItemContent(i - currentPageBegin, 1, strtoqs(resBook[0].name));
		addItemContent(i - currentPageBegin, 2, strtoqs(resBook[0].author));
		addItemContent(i - currentPageBegin, 3, strtoqs(resBook[0].publish));

		//���ӡ����顱��ť�������¼�
		QPushButton *btn = new QPushButton;
		ui.tableBorrow->setCellWidget(i - currentPageBegin, 4, btn);
		btn->setText(strtoqs("����"));
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
	bookConfig::bookId = id;
	student_borrowdetail *rec = new student_borrowdetail;
	rec->show();
	this->close();
}

QString student_borrow::chartoqs(char *p) {
	string s = p;
	return QString(QString::fromLocal8Bit(s.c_str()));
}