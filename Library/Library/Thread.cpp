#include"Thread.h"
#include"recommendBuffer.h"
#include<QPixmap>
#include<QUrl>
#include <qtnetwork/qnetworkaccessmanager>
#include <qtnetwork/QNetworkRequest>
#include <qtnetwork/QNetworkRequest>
#include <qtnetwork/QNetworkReply>
#include<QEventLoop>
Thread::Thread(QObject *parent)
{
}

Thread::~Thread()
{

}

void Thread::run()
{
	QNetworkAccessManager manager;
	QEventLoop loop;
	QNetworkReply *reply = manager.get(QNetworkRequest(recommendBuffer::headUrl));
	//���������������ɺ��˳����¼�ѭ��
	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	//�������¼�ѭ��
	loop.exec();
	QByteArray jpegData = reply->readAll();
	QPixmap pixmap;
	pixmap.loadFromData(jpegData);
	//�ı�ͼƬ��С
	pixmap = pixmap.scaled(110, 130, Qt::KeepAspectRatio);
	recommendBuffer::headBuffer.push_back(pixmap);

	for (int i = 0; i < 6; i++) {
		if (!recommendBuffer::isPostBack) {
			QPixmap pixmap;
			//����ͼƬ
			QUrl url(recommendBuffer::urlBuffer[i]);
			QNetworkAccessManager manager;
			QEventLoop loop;
			// qDebug() << "Reading picture form " << url;
			QNetworkReply *reply = manager.get(QNetworkRequest(url));
			//���������������ɺ��˳����¼�ѭ��
			QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
			//�������¼�ѭ��
			loop.exec();

			QByteArray jpegData = reply->readAll();
			pixmap.loadFromData(jpegData);
			pixmap = pixmap.scaled(110, 130, Qt::KeepAspectRatio);
			recommendBuffer::picBuffer.push_back(pixmap);
		}
	}
	emit UpdateSignal();
}