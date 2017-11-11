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
	ui.tableBorrow->setEditTriggers(QAbstractItemView::NoEditTriggers);//���ò��ɱ༭	
	ui.tableBorrow->verticalHeader()->setVisible(false); //�����кŲ��ɼ�
	ui.tableBorrow->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//��������Ӧ
	//ui.tableBorrow->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);//��0�п������Ӧ
	//ui.tableBorrow->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);//��1�п������Ӧ
	//ui.tableBorrow->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);//��2�п������Ӧ
	//ui.tableBorrow->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);//��3�п������Ӧ
	//ui.tableBorrow->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);//��4�п������Ӧ
	ui.tableBorrow->setFrameShape(QFrame::NoFrame);//�����ޱ߿�
	ui.tableBorrow->setShowGrid(false); //���ò���ʾ������
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

	//��ȡ��¼����ѧ����ѧ��
	char* ch1;
	QByteArray ba = ui.etSnumber->text().toLatin1();
	ch1 = ba.data();

	//��ѯ���ѧ���Ļ�����Ϣ��������ҳ��
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
	 *���¸��½��ı�
	*/
	//��ѯ���ѧ���Ľ����¼
	Record record;
	vector<string>VALUES_2;
	vector<Record>resRecord;
	VALUES_2.push_back("one");
	VALUES_2.push_back("studentId");
	record.setStudentId(resStudent[0].id);
	FileDB::select("record", record, VALUES_2, resRecord);
	//ÿ���ĵ�ÿһ������ص������
	string borrowNumber = "(";
	char c[20];
	itoa(resRecord.size(), c, 10);
	borrowNumber += c;
	borrowNumber += ")";
	ui.etBorrownumber->setText(strtoqs(borrowNumber));
	QStringList header;
	header << strtoqs("����") << strtoqs("����") << strtoqs("����") << strtoqs("������")<< strtoqs("�鿴����");
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
	//���м��ص����ı���
	for (int i = 0; i < resRecord.size(); i++) {
		resBook.clear();
		book.setId(resRecord[i].bookId);
		FileDB::select("book", book, VALUES_3, resBook);
		if (resRecord[0].id != -1) {
			int row = ui.tableBorrow->rowCount();
			ui.tableBorrow->insertRow(i);
			//����ͼƬ
			string s = resBook[0].cover;
			QPixmap p;
			p.load("images/logo.png");
			QLabel *label = new QLabel;
			label->setPixmap(p);
			ui.tableBorrow->setCellWidget(i, 0, label);
			//�����������߳�����
			addItemContent(i, 1, chartoqs(resBook[0].name));
			addItemContent(i, 2, chartoqs(resBook[0].author));
			addItemContent(i, 3, chartoqs(resBook[0].publish));

			//��ӡ����顱��ť�������¼�
			QPushButton *btn = new QPushButton;
			ui.tableBorrow->setCellWidget(i, 4, btn);
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