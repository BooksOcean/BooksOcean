#include "admin_addclassify.h"
#include <QMessageBox>
#include<QTextCodec>
#include"classify.h"
#include"filedb.h"
#include"library.h"
admin_addclassify::admin_addclassify(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.btnAdd->installEventFilter(this);
}

admin_addclassify::~admin_addclassify()
{
}
bool admin_addclassify::eventFilter(QObject *obj, QEvent *event)
{
	QTextCodec * BianMa = QTextCodec::codecForName("GBK");
	if (obj == ui.btnAdd && event->type() == QEvent::MouseButtonPress) {
		QString str = ui.etName->text();
		if (str.length() == 0) {
			QMessageBox::information(NULL, BianMa->toUnicode(""), BianMa->toUnicode("分类名不能为空"), QMessageBox::Ok);
			return true;
		}
		QByteArray ba = str.toLocal8Bit();
		char *name = ba.data();
		Classify classify;
		vector<Classify>resClassify;
		vector<string>VALUES;
		VALUES.push_back("one");
		VALUES.push_back("name");
		FileDB::select("classify", classify, VALUES, resClassify);
		if (resClassify.size() > 0) {
			QMessageBox::information(NULL, BianMa->toUnicode(""), BianMa->toUnicode("分类名重复"), QMessageBox::Ok);
			return true;
		}
		classify.setName(name);
		resClassify.push_back(classify);
		FileDB::insert("classify", resClassify);
		QMessageBox::information(NULL, BianMa->toUnicode(""), BianMa->toUnicode("添加成功"), QMessageBox::Ok);
		this->close();
		return true;
	}
	return true;

}
