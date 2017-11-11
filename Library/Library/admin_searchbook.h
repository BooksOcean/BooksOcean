#ifndef ADMIN_SEARCHBOOK_H
#define ADMIN_SEARCHBOOK_H

#include <QWidget>
#include "ui_admin_searchbook.h"

class admin_searchbook : public QWidget
{
	Q_OBJECT

public:
	admin_searchbook(QWidget *parent = 0);
	~admin_searchbook();

private:
	Ui::admin_searchbook ui;
};

#endif // ADMIN_SEARCHBOOK_H
