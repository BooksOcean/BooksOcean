#ifndef ADMIN_INDEX_H
#define ADMIN_INDEX_H

#include <QWidget>
#include "ui_admin_index.h"

class admin_index : public QWidget
{
	Q_OBJECT

public:
	admin_index(QWidget *parent = 0);
	~admin_index();

private:
	Ui::admin_index ui;
};

#endif // ADMIN_INDEX_H
