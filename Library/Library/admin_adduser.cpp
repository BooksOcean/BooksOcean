#include "admin_adduser.h"
#include "admin_searchuser.h"
#include "admin_index.h"
#include"admin_searchbook.h"
#include"admin_searchuser.h"
#include"admin_classifyshow.h"
#include"admin_classify.h"
#include"filedb.h"
#include"library.h"
#include"dept.h"
#include"admin_studentclassify.h"
#include<vector>
#include<QMessageBox>
#include<QFileDialog>
#include<QDateTime>
#include<QPixmap>
#include<QUrl>
#include <qtnetwork/qnetworkaccessmanager>
#include <qtnetwork/QNetworkRequest>
#include <qtnetwork/QNetworkRequest>
#include <qtnetwork/QNetworkReply>
#include<QEventLoop>
admin_adduser::admin_adduser(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	showFullScreen();
	ui.lineEdit->setEnabled(false);
	ui.lineEdit_2->setEnabled(false);
	ui.lineEdit_3->setEnabled(false);
	ui.lineEdit_4->setEnabled(false);
	ui.lineEdit_5->setEnabled(false);
	ui.lineEdit_6->setEnabled(false);
	ui.btnSearchbook->installEventFilter(this);
	ui.btnClassify->installEventFilter(this);
	ui.btnPersonal->installEventFilter(this);
	ui.btnLogout->installEventFilter(this);
	ui.btnDept->installEventFilter(this);
	ui.btnAdd->installEventFilter(this);
	ui.btnHeadIcon->installEventFilter(this);
	filename = "images/default.png";
	img = new QPixmap;
	img->load(filename);
	ui.btnHeadIcon->setIcon(*img);
	ui.btnHeadIcon->setIconSize(QSize((*img).width(), (*img).height()));
	//不是修改
	isChange = false;
	
}

admin_adduser::~admin_adduser()
{

}

bool admin_adduser::eventFilter(QObject *obj, QEvent *event)
{
	if (obj == ui.btnLogout && event->type() == QEvent::MouseButtonPress) {
		QMessageBox::StandardButton button;
		button = QMessageBox::question(this, QString::fromLocal8Bit("退出程序"),
			QString(QString::fromLocal8Bit("确认退出程序?")),
			QMessageBox::Yes | QMessageBox::No);
		if (button == QMessageBox::No) {
			event->ignore();  //忽略退出信号，程序继续运行
		}
		else if (button == QMessageBox::Yes) {
			Library *rec = new Library;
			this->close();
			rec->show();
			event->accept();  //接受退出信号，程序退出
		}
	}

	if (obj == ui.btnSearchbook && event->type() == QEvent::MouseButtonPress) {
		admin_searchbook *rec = new admin_searchbook;
		this->close();
		rec->show();
	}
	if (obj == ui.btnPersonal && event->type() == QEvent::MouseButtonPress) {
		admin_index *rec = new admin_index;
		this->close();
		rec->show();
	}
	if (obj == ui.btnDept && event->type() == QEvent::MouseButtonPress) {
		admin_studentclassify *rec = new admin_studentclassify;
		connect(rec, SIGNAL(UpdateDeptSignal(QString)), this, SLOT(UpdateDeptSlot(QString)));
		rec->show();
	}

	if (obj == ui.btnClassify && event->type() == QEvent::MouseButtonPress) {
		admin_classify *rec = new admin_classify;
		this->close();
		rec->show();
	}
	if (obj == ui.btnHeadIcon && event->type() == QEvent::MouseButtonPress) {
		openFileDiag();
	}
	if (obj == ui.btnAdd && event->type() == QEvent::MouseButtonPress) {
		QString userName = ui.etName->text();
		QString userDept = ui.btnDept->text();
		QString userCode = ui.etCode->text();
		QString userMail = ui.etMail->text();
		if (!userCode.length() || !userName.length() || !userMail.length()) {
			QMessageBox::information(NULL,QString::fromLocal8Bit(""), QString::fromLocal8Bit("请填写完整"), QMessageBox::Ok);
			return true;
		}
		if (userDept == QString::fromLocal8Bit("请选择专业")) {
			QMessageBox::information(NULL, QString::fromLocal8Bit(""), QString::fromLocal8Bit("必须选择专业"), QMessageBox::Ok);
			return true;
		}
		QByteArray ba1 = userName.toLocal8Bit();
		char *name = ba1.data();
		QByteArray ba2 = userCode.toLocal8Bit();
		char *code = ba2.data();
		QByteArray ba3 = userMail.toLocal8Bit();
		char *mail = ba3.data();
		QByteArray ba4 = userDept.toLocal8Bit();
		char *dept = ba4.data();
		QByteArray ba5 = filename.toLocal8Bit();
		char *icon = ba5.data();
		Student student;
		student.setUsername(name);
		student.setPassword("111111");
		student.setMail(mail);
		student.setUsercode(code);
		student.setIcon(icon);
		student.setDept(dept);
		if (ui.radioMan->isChecked()) {
			student.setSex("男");
		}
		else {
			student.setSex("女");
		}
		(*img).save(filename);
		if (!isChange) {
			student.setMoney(0);
			vector<Student>resStudent2;
			resStudent2.push_back(student);
			FileDB::insert("student", resStudent2);
			QMessageBox::information(NULL, QString::fromLocal8Bit(""), QString::fromLocal8Bit("添加成功！"), QMessageBox::Ok);
		}
		else {
			vector<string>VALUES;
			VALUES.push_back("one");
			VALUES.push_back("id");
			student.setMoney(resStudent[0].money);
			FileDB::update("student", resStudent[0], student, VALUES);
			QMessageBox::information(NULL, QString::fromLocal8Bit(""), QString::fromLocal8Bit("修改成功！"), QMessageBox::Ok);
		}

	}

	else {
		return QWidget::eventFilter(obj, event);
	}

	return false;
}
void admin_adduser::UpdateDeptSlot(QString id) {
	/*vector<string>VALUES;
	Dept dept;
	dept.setId(id);
	vector<Dept>resDept;
	FileDB::select("dept", dept, VALUES, resDept);*/
	ui.btnDept->setText(id);
}

void admin_adduser::openFileDiag() {
	filename = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择图像"), "", tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
	if (filename.isEmpty()) {
		return;
	}
	else {
		img = new QPixmap;
		if (!(img->load(filename))) {
			QMessageBox::information(this,
				QString::fromLocal8Bit("打开图像失败"),
				QString::fromLocal8Bit("打开图像失败!"));
		}
		QDateTime time = QDateTime::currentDateTime();   //获取当前时间  
		int timeT = time.toTime_t();   //将当前时间转为时间戳
		filename = "images/" + QString::number(timeT, 10) + ".jpg";
		ui.btnHeadIcon->setIcon(*img);
		ui.btnHeadIcon->setIconSize(QSize((*img).width(), (*img).height()));
		return;
	}
}

void admin_adduser::InitStudent(int id) {
	//修改
	isChange = true;
	Student cla;
	cla.setId(id);
	vector<string>VALUES;
	VALUES.push_back("one");
	VALUES.push_back("id");
	FileDB::select("student", cla, VALUES, resStudent);
	ui.etName->setText(QString::fromLocal8Bit(resStudent[0].username));
	ui.etCode->setText(QString::fromLocal8Bit(resStudent[0].usercode));
	ui.etMail->setText(QString::fromLocal8Bit(resStudent[0].mail));
	if (strcmp("男", resStudent[0].sex)) {
		ui.radioMan->setChecked(true);
	}
	else {
		ui.radioWoman->setChecked(true);
	}
	ui.btnDept->setText(QString::fromLocal8Bit(resStudent[0].dept));
	filename = QString::fromLocal8Bit(resStudent[0].icon);
	if (!strstr(resStudent[0].icon,"images")) {
		QNetworkAccessManager manager;
		QEventLoop loop;
		QNetworkReply *reply = manager.get(QNetworkRequest(QUrl(filename)));
		//请求结束并下载完成后，退出子事件循环
		QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
		//开启子事件循环
		loop.exec();
		QByteArray jpegData = reply->readAll();
		QPixmap pixmap;
		pixmap.loadFromData(jpegData);
		//改变图片大小
		ui.btnHeadIcon->setIcon(pixmap);
		ui.btnHeadIcon->setIconSize(QSize((pixmap).width(), (pixmap).height()));
	}
	else {
		img = new QPixmap;
		img->load(filename);
		//改变图片大小
		ui.btnHeadIcon->setIcon(*img);
		ui.btnHeadIcon->setIconSize(QSize((*img).width(), (*img).height()));
	}
}
