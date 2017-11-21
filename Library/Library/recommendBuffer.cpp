#include "recommendBuffer.h"
#include<qstring.h>
#include<QPixmap>
#include<string>
#include <QUrl>
bool recommendBuffer::isPostBack = false;
QVector<QPixmap>recommendBuffer::picBuffer;
QVector<QUrl>recommendBuffer::urlBuffer;
QVector<int>recommendBuffer::idBuffer;
QVector<QPixmap>recommendBuffer::headBuffer;
QUrl recommendBuffer::headUrl;
QString recommendBuffer::headUrlLocal = "";
recommendBuffer::recommendBuffer()
{
}


recommendBuffer::~recommendBuffer()
{
}
