#include "student_searchbook.h"
#include<string>
#include"book.h"
#include"filedb.h"
#include"student_index.h"
#include"student_update.h"
#include"qlabel.h"
#include"bookConfig.h"
#include"student_bookdetail.h"
#include<QSignalMapper>
#include <qtnetwork/qnetworkaccessmanager>
student_searchBook::student_searchBook(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.btnInformationchange->installEventFilter(this);
	ui.btnPersonal->installEventFilter(this);
	ui.btnFirstPage->installEventFilter(this);
	ui.btnLastPage->installEventFilter(this);
	ui.btnNextPage->installEventFilter(this);
	ui.btnSearch->installEventFilter(this);
	ui.btnTheLast->installEventFilter(this);
	ui.tableWidget->setColumnCount(7);
	ui.btnLastPage->setEnabled(false);
	ui.btnFirstPage->setEnabled(false);
	ui.btnTheLast->setEnabled(false);
	ui.btnNextPage->setEnabled(false);
	QStringList Header;
	Header << QString(u8"封面") << QString(u8"书名") << QString(u8"作者") << QString(u8"出版社") << QString(u8"馆藏数量") << QString(u8"可借本数") << QString(u8"查看详情");
	ui.tableWidget->setHorizontalHeaderLabels(Header);
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑	
	ui.tableWidget->verticalHeader()->setVisible(false); //设置行号不可见
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//表宽度自适应
//	ui.tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//表宽度自适应
	//ui.tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);//第0列宽度自适应
	//ui.tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);//第1列宽度自适应
	//ui.tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);//第2列宽度自适应
	//ui.tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);//第3列宽度自适应
	//ui.tableWidget->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);//第4列宽度自适应
	ui.tableWidget->setFrameShape(QFrame::NoFrame);//设置无边框
	ui.tableWidget->setShowGrid(false); //设置不显示格子线
}

student_searchBook::~student_searchBook()
{

}

bool student_searchBook::eventFilter(QObject *obj, QEvent *event)
{
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

	/*else if (obj == ui.btnGo) {
		if (event->type() == QEvent::MouseButtonPress) {
			JumpPage();
			return true;
		}
		else {
			return false;
		}
	}*/

	else if (obj == ui.btnSearch) {
		if (event->type() == QEvent::MouseButtonPress) {
			SearchData();
			return true;
		}
		else {
			return false;
		}
	}

	else if (obj == ui.btnFirstPage) {
		if (event->type() == QEvent::MouseButtonPress) {
			FirstPage();
			return true;
		}
		else {
			return false;
		}
	}

	else if (obj == ui.btnTheLast) {
		if (event->type() == QEvent::MouseButtonPress) {
			TheLastPage();
			return true;
		}
		else {
			return false;
		}
	}
	if (obj == ui.btnPersonal && event->type() == QEvent::MouseButtonPress) {
		student_index *rec = new student_index;
		this->close();
		rec->show();

	}
	if (obj == ui.btnInformationchange && event->type() == QEvent::MouseButtonPress) {
		student_update *rec = new student_update;
		this->close();
		rec->show();

	}

	else {
		return QWidget::eventFilter(obj, event);
	}

	return false;
}

void student_searchBook::FirstPage() {
	PageIndex = 1;
	ui.etIndexPage->setText(QString::number(PageIndex, 10));
	DataBind();
}

void student_searchBook::TheLastPage() {
	PageIndex = PageCount;
	ui.etIndexPage->setText(QString::number(PageIndex, 10));
	DataBind();
}

void student_searchBook::SearchData() {
	QString str = ui.txtSearch->toPlainText();
	QByteArray ba = str.toLocal8Bit();
	char *name = ba.data();
	DataTable.clear();
	FileDB::selectLike("book", "name", name, DataTable);
	PageIndex = 1;
	PageCount = ceill(DataTable.size() / (double)PageLength);
	DataBind();
	/*ui.btnGo->setEnabled(true);*/
	ui.btnLastPage->setEnabled(false);
	if (PageIndex<PageCount)
		ui.btnNextPage->setEnabled(true);
	ui.etIndexPage->setText(QString::number(PageIndex, 10));
	ui.etCountPage->setText(QString::number(PageCount, 10));
	ui.btnFirstPage->setEnabled(true);
	ui.btnTheLast->setEnabled(true);
}

void student_searchBook::DataBind() {
	for (int i = ui.tableWidget->rowCount(); i > 0; i--) {
		ui.tableWidget->removeRow(0);
	}
	int currentPageBegin = (PageIndex - 1)*PageLength;
	int currentPageEnd = (currentPageBegin + PageLength) < DataTable.size() ? (currentPageBegin + PageLength) : DataTable.size();
	for (int i = currentPageBegin; i < currentPageEnd; i++) {
		ui.tableWidget->insertRow(i - currentPageBegin);
		ui.tableWidget->setRowHeight(i - currentPageBegin, 200);//第一行
		//加载图片
		string s = DataTable[i].cover;
		QPixmap p;
		p.load("images/example.png");
		QLabel *label = new QLabel;
		label->setPixmap(p);
		ui.tableWidget ->setCellWidget(i - currentPageBegin, 0, label);
		//加载书名作者出版社
		ui.tableWidget->setItem(i - currentPageBegin, 1, new QTableWidgetItem(QString::fromLocal8Bit(DataTable[i].name)));
		ui.tableWidget->setItem(i - currentPageBegin, 2, new QTableWidgetItem(QString::fromLocal8Bit(DataTable[i].author)));
		ui.tableWidget->setItem(i - currentPageBegin, 3, new QTableWidgetItem(QString::fromLocal8Bit(DataTable[i].publish)));
		ui.tableWidget->setItem(i - currentPageBegin, 4, new QTableWidgetItem(QString::number(DataTable[i].count,10)));
		ui.tableWidget->setItem(i - currentPageBegin, 5, new QTableWidgetItem(QString::number(DataTable[i].nowCount,10)));
		//添加“详情”按钮，并绑定事件
		QPushButton *btn = new QPushButton;
		ui.tableWidget->setCellWidget(i - currentPageBegin, 6, btn);
		btn->setText(strtoqs("详情"));
		btn->setStyleSheet(
			"color:#4695d2;"
			"border:none;"
			"background:white;"
			"text-size:20px;"
		);
		QSignalMapper* signalMapper = new QSignalMapper(this);
		connect(btn, SIGNAL(clicked()), signalMapper, SLOT(map()));
		signalMapper->setMapping(btn, DataTable[i].id);
		connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(OnBtnClicked(int)));
	}
}

void student_searchBook::NextPage() {
	if (PageIndex >= PageCount)return;
	if (PageIndex == 1)
		ui.btnLastPage->setEnabled(true);
	PageIndex++;
	ui.etIndexPage->setText(QString::number(PageIndex, 10));
	DataBind();
}

void student_searchBook::LastPage() {
	if (PageIndex <= 1)return;
	if (PageIndex == PageCount)
		ui.btnNextPage->setEnabled(true);
	PageIndex--;
	ui.etIndexPage->setText(QString::number(PageIndex, 10));
	DataBind();
}

/*void student_searchBook::JumpPage() {
	QString str = ui.txtPage->toPlainText();
	int page = str.toInt();
	if (page<1 || page>PageCount) {
		QMessageBox::information(NULL, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("页码超出范围"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return;
	}
	PageIndex = page;
	if (PageIndex > 1)
		ui.btnLastPage->setEnabled(true);
	if (PageIndex < PageCount)
		ui.btnNextPage->setEnabled(true);
	ui.lbCurrentPage->setText(QString::number(PageIndex, 10));
	DataBind();
}*/

QString student_searchBook::strtoqs(const string &s)

{

	return QString(QString::fromLocal8Bit(s.c_str()));

}

string student_searchBook::qstostr(const QString &s)

{

	return string((const char*)s.toLocal8Bit());

}

void student_searchBook::addItemContent(int row, int column, QString content)
{
	QTableWidgetItem *item = new QTableWidgetItem(content);
	ui.tableWidget->setItem(row, column, item);
}

void student_searchBook::OnBtnClicked(int id)
{
	bookConfig::bookId = id;
	student_bookDetail *rec = new student_bookDetail;
	rec->show();
	this->close();
}