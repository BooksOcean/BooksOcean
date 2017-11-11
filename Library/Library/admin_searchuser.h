#ifndef ADMIN_SEARCHUSER_H
#define ADMIN_SEARCHUSER_H

#include <QWidget>
#include "ui_admin_searchuser.h"

class admin_searchuser : public QWidget
{
	Q_OBJECT

public:
	admin_searchuser(QWidget *parent = 0);
	~admin_searchuser();

private:
	Ui::admin_searchuser ui;
};

#endif // ADMIN_SEARCHUSER_H
