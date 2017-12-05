#include "admin_addbook.h"
#include "admin_adduser.h"
#include "admin_searchuser.h"
#include "admin_index.h"
#include"admin_searchbook.h"
#include"admin_searchuser.h"
#include"admin_classifyshow.h"
#include"admin_classify.h"
#include"filedb.h"
#include"dept.h"
#include"classifyMap.h"
#include"bookMap.h"
#include"Library.h"
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
admin_addbook::admin_addbook(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.btnSearchuser->installEventFilter(this);
	ui.btnClassify->installEventFilter(this);
	ui.btnPersonal->installEventFilter(this);
	ui.btnLogout->installEventFilter(this);
	ui.btnClassifyShow->installEventFilter(this);
	ui.btnAdd->installEventFilter(this);
	ui.btnCover->installEventFilter(this);
	filename = "images/default.png";
	img = new QPixmap;
	img->load(filename);
	ui.btnCover->setIcon(*img);
	ui.btnCover->setIconSize(QSize((*img).width(), (*img).height()));
	//不是修改
	isChange = false;
}

admin_addbook::~admin_addbook()
{

}

bool admin_addbook::eventFilter(QObject *obj, QEvent *event)
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
	if (obj == ui.btnClassifyShow && event->type() == QEvent::MouseButtonPress) {
		admin_classifyshow *rec = new admin_classifyshow;
		connect(rec, SIGNAL(UpdateClassSignal(QString)), this, SLOT(UpdateClassSlot(QString)));
		rec->show();
	}

	if (obj == ui.btnClassify && event->type() == QEvent::MouseButtonPress) {
		admin_classify *rec = new admin_classify;
		this->close();
		rec->show();
	}
	if (obj == ui.btnCover && event->type() == QEvent::MouseButtonPress) {
		openFileDiag();
	}
	if (obj == ui.btnAdd && event->type() == QEvent::MouseButtonPress) {
		QString bookName = ui.etName->text();
		QString bookClass = ui.btnClassifyShow->text();
		QString bookISBN = ui.etISBN->text();
		QString bookAuthor = ui.etAuthor->text();
		QString bookPublish = ui.etPublish->text();
		QString bookCount = ui.etCount->text();
		QString bookScore = ui.etScore->text();
		if (!bookName.length() || !bookClass.length()
			|| !bookISBN.length() || !bookAuthor.length()
			|| !bookISBN.length() || !bookISBN.length()
			|| !bookPublish.length() || !bookCount.length()
			|| !bookScore.length()) {
			QMessageBox::information(NULL, QString::fromLocal8Bit(""), QString::fromLocal8Bit("请填写完整"), QMessageBox::Ok);
			return true;
		}
		if (bookClass == QString::fromLocal8Bit("请选择分类")) {
			QMessageBox::information(NULL, QString::fromLocal8Bit(""), QString::fromLocal8Bit("必须选择分类"), QMessageBox::Ok);
			return true;
		}
		QByteArray ba1 = bookName.toLocal8Bit();
		char *name = ba1.data();
		QByteArray ba2 = bookClass.toLocal8Bit();
		char *classs = ba2.data();
		QByteArray ba3 = bookISBN.toLocal8Bit();
		char *ISBN = ba3.data();
		QByteArray ba4 = bookAuthor.toLocal8Bit();
		char *author = ba4.data();
		QByteArray ba5 = bookPublish.toLocal8Bit();
		char *publish = ba5.data();

		int countt = bookCount.toInt();
		float score = bookScore.toFloat();

		QByteArray ba6 = filename.toLocal8Bit();
		char *cover = ba6.data();

		if (!isChange) {

			//判断ISBN是否重复
			Book book;
			vector<string>VALUES;
			vector<Book>resBook;
			VALUES.push_back("one");
			VALUES.push_back("ISBN");
			book.setISBN(ISBN);
			FileDB::select("book", book, VALUES, resBook);

			if (resBook.size() > 0) {
				QMessageBox::information(NULL, QString::fromLocal8Bit(""), QString::fromLocal8Bit("ISBN与已有书本重复，不可添加"), QMessageBox::Ok);
				return true;
			}
			//获取classId
			Classify cla;
			vector<Classify>resCla;
			cla.setName(classs);
			VALUES.pop_back();
			VALUES.push_back("name");
			FileDB::select("classify", cla, VALUES, resCla);

			//插入book表
			book.setAuthor(author);
			book.setClassifyId(resCla[0].id);
			book.setCount(countt);
			book.setCover(cover);
			book.setISBN(ISBN);
			book.setName(name);
			book.setNowCount(countt);
			book.setPublish(publish);
			book.setScore(score);
			(*img).save(filename);

			resBook.push_back(book);
			FileDB::insert("book", resBook);


			//获取新插入书的id，维护classifyMap
			resBook.clear();
			VALUES.pop_back();
			VALUES.push_back("ISBN");
			FileDB::select("book", book, VALUES, resBook);
			ClassifyMap clamap;
			clamap.setBookId(resBook[0].id);
			clamap.setClassifyId(resCla[0].id);
			vector<ClassifyMap>resClsmap;
			resClsmap.push_back(clamap);
			FileDB::insert("classifyMap", resClsmap);

			//维护bookMap
			BookMap bookmap;
			vector<BookMap>resBookmap;
			for (int i = 1; i <= countt; i++) {
				bookmap.setBookId((resBook[0].id));
				bookmap.setBookNum(i);
				bookmap.setIsOut(0);
				resBookmap.push_back(bookmap);
			}
			FileDB::insert("bookMap", resBookmap);

			QMessageBox::information(NULL, QString::fromLocal8Bit(""), QString::fromLocal8Bit("添加成功"), QMessageBox::Ok);
		}
		//修改
		else {
			//获取classId
			vector<string>VALUES;
			Classify cla;
			vector<Classify>resCla;
			cla.setName(classs);
			VALUES.push_back("one");
			VALUES.push_back("name");
			FileDB::select("classify", cla, VALUES, resCla);

			Book book;
			//插入book表
			book.setAuthor(author);
			book.setClassifyId(resCla[0].id);
			book.setCount(countt);
			book.setCover(cover);
			book.setISBN(ISBN);
			book.setName(name);
			book.setNowCount(countt);
			book.setPublish(publish);
			book.setScore(score);
			(*img).save(filename);
			Book Sbook;
			Sbook.setId(BookId);
			VALUES.pop_back();
			VALUES.push_back("id");
			FileDB::update("book", Sbook, book, VALUES);
			//维护classifyMap
			ClassifyMap clamap;
			vector<ClassifyMap>resClamap;
			clamap.setBookId(BookId);
			VALUES.pop_back();
			VALUES.push_back("bookId");
			//全部删除
			FileDB::Delete("classifyMap", clamap, VALUES);
			//继续添加
			clamap.setBookId(BookId);
			clamap.setClassifyId(resCla[0].id);
			resClamap.push_back(clamap);
			FileDB::insert("classifyMap", resClamap);

			QMessageBox::information(NULL, QString::fromLocal8Bit(""), QString::fromLocal8Bit("修改成功"), QMessageBox::Ok);
		}

	}

	else {
		return QWidget::eventFilter(obj, event);
	}

	return false;
}

void admin_addbook::openFileDiag() {
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
		ui.btnCover->setIcon(*img);
		ui.btnCover->setIconSize(QSize((*img).width(), (*img).height()));
		return;
	}
}
void admin_addbook::UpdateClassSlot(QString id) {
	ui.btnClassifyShow->setText(id);
}

void admin_addbook::InitBook(int id) {
	//修改
	BookId = id;
	isChange = true;
	Book book;
	book.setId(id);
	vector<string>VALUES;
	VALUES.push_back("one");
	VALUES.push_back("id");
	FileDB::select("book", book, VALUES, resBook);
	ui.etName->setText(QString::fromLocal8Bit( resBook[0].name));
	ui.etAuthor->setText(QString::fromLocal8Bit(resBook[0].author));
	ui.etISBN->setText(QString::fromLocal8Bit(resBook[0].ISBN));
	ui.etPublish->setText(QString::fromLocal8Bit(resBook[0].publish));
	ui.etCount->setText(QString::number(resBook[0].count));
	ui.etScore->setText(QString("%1").arg(resBook[0].score));
	ui.etCount->setReadOnly(true);
	Classify classify;
	vector<Classify>resClassify;
	classify.setId(resBook[0].classifyId);
	FileDB::select("classify", classify, VALUES, resClassify);
	ui.btnClassifyShow->setText(QString::fromLocal8Bit(resClassify[0].name));

	
	filename = QString::fromLocal8Bit(resBook[0].cover);
	if (!strstr(resBook[0].cover, "images")) {
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
		ui.btnCover->setIcon(pixmap);
		ui.btnCover->setIconSize(QSize((pixmap).width(), (pixmap).height()));
	}
	else {
		img = new QPixmap;
		img->load(filename);
		//改变图片大小
		ui.btnCover->setIcon(*img);
		ui.btnCover->setIconSize(QSize((*img).width(), (*img).height()));
	}
}


