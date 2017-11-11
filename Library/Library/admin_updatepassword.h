#ifndef ADMIN_UPDATEPASSWORD_H
#define ADMIN_UPDATEPASSWORD_H

#include <QWidget>
#include "ui_admin_updatepassword.h"

class admin_updatepassword : public QWidget
{
	Q_OBJECT

public:
	admin_updatepassword(QWidget *parent = 0);
	~admin_updatepassword();

private:
	Ui::admin_updatepassword ui;
};

#endif // ADMIN_UPDATEPASSWORD_H
