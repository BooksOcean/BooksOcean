#ifndef STUDENT_INDEX_H
#define STUDENT_INDEX_H

#include<string>
#include<iostream>
#include <QWidget>
#include "ui_student_index.h"
#include"record.h"
using namespace std;
  
class student_index : public QWidget
{
	Q_OBJECT

public:
	student_index(QWidget *parent = Q_NULLPTR);
	~student_index();
	void addItemContent(int row, int column, QString content);
	QString strtoqs(const string &s);
	string qstostr(const QString &s);
	void InitThisPage();
	QString chartoqs(char *p);

public slots:
	void ClickButton();
	void OnBtnClicked(int id);

protected:
	bool eventFilter(QObject *obj, QEvent *event);

private:
	Ui::student_index ui;
};

#endif // STUDENT_INDEX_H
