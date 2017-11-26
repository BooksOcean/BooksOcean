#include "admin_searchbook.h"
#include "admin_index.h"
#include"admin_searchuser.h"
#include"admin_classify.h"
#include"classifyConfig.h"
#include"book.h"
#include"classify.h"
#include"classifyMap.h"
#include"admin_classifyshow.h"
#include"filedb.h"
#include<QSignalMapper>
#include<QMessageBox>
admin_searchbook::admin_searchbook(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.btnSearchuser->installEventFilter(this);
	ui.btnClassify->installEventFilter(this);
	ui.btnPersonal->installEventFilter(this);
	ui.btnLastPage->installEventFilter(this);
	ui.btnFirstPage->installEventFilter(this);
	ui.btnLastPage->installEventFilter(this);
	ui.btnNextPage->installEventFilter(this);
	ui.btnSearch->installEventFilter(this);
	ui.btnTheLast->installEventFilter(this);
	ui.tableWidget->setColumnCount(6);
	ui.btnLastPage->setEnabled(false);
	ui.btnFirstPage->setEnabled(false);
	//���ӷ����ź�
	connect(ui.radioClassify, SIGNAL(clicked(bool)), this, SLOT(radioBtnSlot()));
	//��������radio�ź�
	connect(ui.radioName, SIGNAL(clicked(bool)), this, SLOT(radioBtnSlotOther()));
	connect(ui.radioISBN, SIGNAL(clicked(bool)), this, SLOT(radioBtnSlotOther()));
	connect(ui.radioAuthor, SIGNAL(clicked(bool)), this, SLOT(radioBtnSlotOther()));

	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//���ò��ɱ༭	
	ui.tableWidget->verticalHeader()->setVisible(false); //�����кŲ��ɼ�
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//����������Ӧ
	ui.tableWidget->setFrameShape(QFrame::NoFrame);//�����ޱ߿�
	ui.tableWidget->setShowGrid(false); //���ò���ʾ������

	if (classifyConfig::isCheck) {
		SearchData();
		ui.radioClassify->setChecked(true);
		Classify classify;
		vector<string>VALUES;
		vector<Classify>res;
		VALUES.push_back("one");
		VALUES.push_back("id");
		classify.setId(classifyConfig::classifyId);
		FileDB::select("classify", classify, VALUES, res);
		ui.txtSearch->setText(QString::fromLocal8Bit("��ǰ���ࣺ") + QString::fromLocal8Bit(res[0].name));
		ui.txtSearch->setReadOnly(true);
		classifyConfig::isCheck = 0;
	}
	else {
		ui.radioName->setChecked(true);
	}
}


bool admin_searchbook::eventFilter(QObject *obj, QEvent *event)
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
	//if (obj == ui.btnLogout && event->type() == QEvent::MouseButtonPress) {
	//	QMessageBox::StandardButton button;
	//	button = QMessageBox::question(this, QString::fromLocal8Bit("�˳�����"),
	//		QString(QString::fromLocal8Bit("ȷ���˳�����?")),
	//		QMessageBox::Yes | QMessageBox::No);
	//	if (button == QMessageBox::No) {
	//		event->ignore();  //�����˳��źţ������������
	//	}
	//	else if (button == QMessageBox::Yes) {
	//		Library *rec = new Library;
	//		this->close();
	//		rec->show();
	//		event->accept();  //�����˳��źţ������˳�
	//	}
	//}

	if (obj == ui.btnSearchuser && event->type() == QEvent::MouseButtonPress) {
		admin_searchuser *rec = new admin_searchuser;
		this->close();
		rec->show();
	}
	if (obj == ui.btnPersonal && event->type() == QEvent::MouseButtonPress) {
		admin_index *rec = new admin_index;
		this->close();
		rec->show();
	}
	if (obj == ui.btnClassify && event->type() == QEvent::MouseButtonPress) {
		admin_classify *rec = new admin_classify;
		this->close();
		rec->show();
	}

	else {
		return QWidget::eventFilter(obj, event);
	}

	return false;
}
void admin_searchbook::FirstPage() {
	PageIndex = 1;
	ui.etIndexPage->setText(QString::number(PageIndex, 10));
	DataBind();
}

void admin_searchbook::TheLastPage() {
	PageIndex = PageCount;
	ui.etIndexPage->setText(QString::number(PageIndex, 10));
	DataBind();
}

void admin_searchbook::SearchData() {
	if (classifyConfig::isCheck) {
		//���ݷ����ѯbookID
		ClassifyMap classifymap;
		classifymap.setClassifyId(classifyConfig::classifyId);
		vector<ClassifyMap>resClassifyMap;
		vector<string> VALUES;
		VALUES.push_back("one");
		VALUES.push_back("classifyId");
		FileDB::select("classifyMap", classifymap, VALUES, resClassifyMap);
		//����bookid��ѯ�鼮
		Book book;
		VALUES.pop_back();
		VALUES.push_back("id");
		for (int i = 0; i < resClassifyMap.size(); i++) {
			book.setId(resClassifyMap[i].bookId);
			FileDB::select("book", book, VALUES, DataTable);
		}
	}
	else {

		QString str = ui.txtSearch->toPlainText();
		QByteArray ba = str.toLocal8Bit();
		char *name = ba.data();
		DataTable.clear();
		//ʲôҲ�����룬��ѯȫ��ͼ��
		if (str.length() == 0) {
			Book book;
			vector<string>VALUES;
			VALUES.push_back("all");
			FileDB::select("book", book, VALUES, DataTable);
		}
		else {
			//����������ѯ
			if (ui.radioName->isChecked())
				FileDB::selectLike("book", "name", name, DataTable);
			//�������߲�ѯ
			else if (ui.radioAuthor->isChecked())
				FileDB::selectLike("book", "author", name, DataTable);
			//����ISBN��ѯ
			else if (ui.radioISBN->isChecked())
				FileDB::selectLike("book", "ISBN", name, DataTable);
		}
	}

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

void admin_searchbook::DataBind() {
	for (int i = ui.tableWidget->rowCount(); i > 0; i--) {
		ui.tableWidget->removeRow(0);
	}
	int currentPageBegin = (PageIndex - 1)*PageLength;
	int currentPageEnd = (currentPageBegin + PageLength) < DataTable.size() ? (currentPageBegin + PageLength) : DataTable.size();
	for (int i = currentPageBegin; i < currentPageEnd; i++) {
		ui.tableWidget->insertRow(i - currentPageBegin);
		ui.tableWidget->setRowHeight(i - currentPageBegin, 50);//��

		//�����������߳�����
		ui.tableWidget->setItem(i - currentPageBegin, 0, new QTableWidgetItem(QString::fromLocal8Bit(DataTable[i].name)));
		ui.tableWidget->setItem(i - currentPageBegin, 1, new QTableWidgetItem(QString::fromLocal8Bit(DataTable[i].author)));
		ui.tableWidget->setItem(i - currentPageBegin, 2, new QTableWidgetItem(QString::fromLocal8Bit(DataTable[i].publish)));
		ui.tableWidget->setItem(i - currentPageBegin, 3, new QTableWidgetItem(QString::number(DataTable[i].count, 10)));
		ui.tableWidget->setItem(i - currentPageBegin, 4, new QTableWidgetItem(QString::number(DataTable[i].nowCount, 10)));
		//���ӡ����顱��ť�������¼�
		QPushButton *btn = new QPushButton;
		ui.tableWidget->setCellWidget(i - currentPageBegin, 5, btn);
		btn->setText(QString::fromLocal8Bit("�޸�"));
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

void admin_searchbook::NextPage() {
	if (PageIndex >= PageCount)return;
	if (PageIndex == 1)
		ui.btnLastPage->setEnabled(true);
	PageIndex++;
	ui.etIndexPage->setText(QString::number(PageIndex, 10));
	DataBind();
}

void admin_searchbook::LastPage() {
	if (PageIndex <= 1)return;
	if (PageIndex == PageCount)
		ui.btnNextPage->setEnabled(true);
	PageIndex--;
	ui.etIndexPage->setText(QString::number(PageIndex, 10));
	DataBind();
}

admin_searchbook::~admin_searchbook()
{

}
//�򿪷���ҳ��
void admin_searchbook::radioBtnSlot() {
	if (!classifyConfig::isCheck) {
		classifyConfig::isCheck = 1;
		admin_classifyshow *rec = new admin_classifyshow;
		this->hide();
		rec->show();
	}
}

//�ָ��ɱ༭
void admin_searchbook::radioBtnSlotOther() {
	classifyConfig::isCheck = 0;
	ui.txtSearch->setText("");
	ui.txtSearch->setReadOnly(false);
}

void admin_searchbook::OnBtnClicked(int id)
{
	/*bookConfig::bookId = id;
	student_bookDetail *rec = new student_bookDetail;
	rec->show();
	this->close();*/
}
