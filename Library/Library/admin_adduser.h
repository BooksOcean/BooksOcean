#ifndef ADMIN_ADDUSER_H
#define ADMIN_ADDUSER_H

#include <QWidget>
#include "ui_admin_adduser.h"

class admin_adduser : public QWidget
{
	Q_OBJECT

public:
	admin_adduser(QWidget *parent = 0);
	~admin_adduser();

private:
	Ui::admin_adduser ui;
};

#endif // ADMIN_ADDUSER_H
