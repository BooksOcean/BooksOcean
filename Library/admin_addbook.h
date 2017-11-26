#ifndef ADMIN_ADDBOOK_H
#define ADMIN_ADDBOOK_H

#include <QWidget>
#include "ui_admin_addbook.h"

class admin_addbook : public QWidget
{
	Q_OBJECT

public:
	admin_addbook(QWidget *parent = 0);
	~admin_addbook();

private:
	Ui::admin_addbook ui;
};

#endif // ADMIN_ADDBOOK_H
