#ifndef ADMIN_CLASSIFY_H
#define ADMIN_CLASSIFY_H

#include <QWidget>
#include "ui_admin_classify.h"

class admin_classify : public QWidget
{
	Q_OBJECT

public:
	admin_classify(QWidget *parent = 0);
	~admin_classify();



private:
	Ui::admin_classify ui;
};

#endif // ADMIN_CLASSIFY_H
