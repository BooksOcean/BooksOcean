/********************************************************************************
** Form generated from reading UI file 'student_borrowdetail.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STUDENT_BORROWDETAIL_H
#define UI_STUDENT_BORROWDETAIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_student_borrowdetail
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QFrame *frame_2;
    QFrame *frame_8;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout;
    QPushButton *btnPersonal;
    QPushButton *btnInformationchange;
    QPushButton *btnSearchbook;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnReturn;
    QLineEdit *etBookNameHead;
    QFrame *frame_6;
    QHBoxLayout *horizontalLayout_4;
    QFrame *frameBookCover;
    QFrame *frame_9;
    QLineEdit *etBookName;
    QLineEdit *etAuthorHead;
    QLineEdit *etPublishHead;
    QLineEdit *etISBNHead;
    QLineEdit *etClassifyHead;
    QLineEdit *etAuthor;
    QLineEdit *etPublish;
    QLineEdit *etISBN;
    QLineEdit *etClassify;
    QFrame *frame_5;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnReturnbook;
    QPushButton *btnBorrowagain;

    void setupUi(QWidget *student_borrowdetail)
    {
        if (student_borrowdetail->objectName().isEmpty())
            student_borrowdetail->setObjectName(QStringLiteral("student_borrowdetail"));
        student_borrowdetail->resize(1021, 722);
        horizontalLayout = new QHBoxLayout(student_borrowdetail);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        frame = new QFrame(student_borrowdetail);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMinimumSize(QSize(300, 700));
        frame->setStyleSheet(QLatin1String("\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(51, 153, 255,1), stop:1 rgba(52, 246, 177,1));"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(70, 30, 171, 176));
        frame_2->setMinimumSize(QSize(0, 0));
        frame_2->setBaseSize(QSize(0, 100));
        frame_2->setStyleSheet(QLatin1String("image: url(:/Library/images/logo2.png);\n"
"background:transparent;"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        frame_8 = new QFrame(frame);
        frame_8->setObjectName(QStringLiteral("frame_8"));
        frame_8->setGeometry(QRect(0, 230, 301, 371));
        frame_8->setStyleSheet(QStringLiteral("background:transparent;"));
        frame_8->setFrameShape(QFrame::StyledPanel);
        frame_8->setFrameShadow(QFrame::Raised);
        verticalLayout_6 = new QVBoxLayout(frame_8);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(7);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        btnPersonal = new QPushButton(frame_8);
        btnPersonal->setObjectName(QStringLiteral("btnPersonal"));
        btnPersonal->setMinimumSize(QSize(0, 100));
        btnPersonal->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color:white;\n"
"background:transparent;"));

        verticalLayout->addWidget(btnPersonal);

        btnInformationchange = new QPushButton(frame_8);
        btnInformationchange->setObjectName(QStringLiteral("btnInformationchange"));
        btnInformationchange->setMinimumSize(QSize(0, 100));
        btnInformationchange->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color:white;\n"
"background:transparent;"));

        verticalLayout->addWidget(btnInformationchange);

        btnSearchbook = new QPushButton(frame_8);
        btnSearchbook->setObjectName(QStringLiteral("btnSearchbook"));
        btnSearchbook->setMinimumSize(QSize(0, 100));
        btnSearchbook->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color:white;\n"
"background:transparent;\n"
"background-color:rgba(255,255,255,0.4);\n"
""));

        verticalLayout->addWidget(btnSearchbook);


        verticalLayout_6->addLayout(verticalLayout);


        horizontalLayout->addWidget(frame);

        frame_3 = new QFrame(student_borrowdetail);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setStyleSheet(QStringLiteral("background:white;"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        frame_4 = new QFrame(frame_3);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(200);
        sizePolicy1.setHeightForWidth(frame_4->sizePolicy().hasHeightForWidth());
        frame_4->setSizePolicy(sizePolicy1);
        frame_4->setStyleSheet(QLatin1String("border:2px solid #cccccc;\n"
"border-top:0px;\n"
"border-left:0px;\n"
"border-right:0px;"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_4);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        btnReturn = new QPushButton(frame_4);
        btnReturn->setObjectName(QStringLiteral("btnReturn"));
        btnReturn->setMinimumSize(QSize(30, 0));
        btnReturn->setStyleSheet(QString::fromUtf8("color:#4D4D4D;\n"
"border:none;\n"
"font-size:24px;\n"
"font-weight:500;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"text-align:center;\n"
""));

        horizontalLayout_3->addWidget(btnReturn);

        etBookNameHead = new QLineEdit(frame_4);
        etBookNameHead->setObjectName(QStringLiteral("etBookNameHead"));
        etBookNameHead->setStyleSheet(QString::fromUtf8("color:#4D4D4D;\n"
"border:none;\n"
"font-size:24px;\n"
"font-weight:500;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"text-align:left;"));

        horizontalLayout_3->addWidget(etBookNameHead);


        verticalLayout_2->addWidget(frame_4);

        frame_6 = new QFrame(frame_3);
        frame_6->setObjectName(QStringLiteral("frame_6"));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_6);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        frameBookCover = new QFrame(frame_6);
        frameBookCover->setObjectName(QStringLiteral("frameBookCover"));
        frameBookCover->setStyleSheet(QStringLiteral("image: url(:/Library/images/example.png);"));
        frameBookCover->setFrameShape(QFrame::StyledPanel);
        frameBookCover->setFrameShadow(QFrame::Raised);

        horizontalLayout_4->addWidget(frameBookCover);

        frame_9 = new QFrame(frame_6);
        frame_9->setObjectName(QStringLiteral("frame_9"));
        frame_9->setFrameShape(QFrame::StyledPanel);
        frame_9->setFrameShadow(QFrame::Raised);
        etBookName = new QLineEdit(frame_9);
        etBookName->setObjectName(QStringLiteral("etBookName"));
        etBookName->setGeometry(QRect(20, 80, 141, 21));
        etBookName->setStyleSheet(QString::fromUtf8("color:#4D4D4D;\n"
"border:none;\n"
"font-size:20px;\n"
"font-weight:500;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"text-align:left;"));
        etAuthorHead = new QLineEdit(frame_9);
        etAuthorHead->setObjectName(QStringLiteral("etAuthorHead"));
        etAuthorHead->setGeometry(QRect(30, 150, 80, 21));
        etAuthorHead->setStyleSheet(QString::fromUtf8("color:#808080;\n"
"border:none;\n"
"font-size:18px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"text-align:left;"));
        etPublishHead = new QLineEdit(frame_9);
        etPublishHead->setObjectName(QStringLiteral("etPublishHead"));
        etPublishHead->setGeometry(QRect(30, 190, 80, 21));
        etPublishHead->setStyleSheet(QString::fromUtf8("color:#808080;\n"
"border:none;\n"
"font-size:18px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"text-align:left;"));
        etISBNHead = new QLineEdit(frame_9);
        etISBNHead->setObjectName(QStringLiteral("etISBNHead"));
        etISBNHead->setGeometry(QRect(30, 230, 80, 21));
        etISBNHead->setStyleSheet(QString::fromUtf8("color:#808080;\n"
"border:none;\n"
"font-size:18px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"text-align:left;"));
        etClassifyHead = new QLineEdit(frame_9);
        etClassifyHead->setObjectName(QStringLiteral("etClassifyHead"));
        etClassifyHead->setGeometry(QRect(30, 270, 80, 21));
        etClassifyHead->setStyleSheet(QString::fromUtf8("color:#808080;\n"
"border:none;\n"
"font-size:18px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"text-align:left;"));
        etAuthor = new QLineEdit(frame_9);
        etAuthor->setObjectName(QStringLiteral("etAuthor"));
        etAuthor->setGeometry(QRect(110, 150, 171, 21));
        etAuthor->setStyleSheet(QString::fromUtf8("color:#808080;\n"
"border:none;\n"
"font-size:18px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"text-align:left;"));
        etPublish = new QLineEdit(frame_9);
        etPublish->setObjectName(QStringLiteral("etPublish"));
        etPublish->setGeometry(QRect(110, 190, 171, 21));
        etPublish->setStyleSheet(QString::fromUtf8("color:#808080;\n"
"border:none;\n"
"font-size:18px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"text-align:left;"));
        etISBN = new QLineEdit(frame_9);
        etISBN->setObjectName(QStringLiteral("etISBN"));
        etISBN->setGeometry(QRect(110, 230, 171, 21));
        etISBN->setStyleSheet(QString::fromUtf8("color:#808080;\n"
"border:none;\n"
"font-size:18px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"text-align:left;"));
        etClassify = new QLineEdit(frame_9);
        etClassify->setObjectName(QStringLiteral("etClassify"));
        etClassify->setGeometry(QRect(110, 270, 181, 21));
        etClassify->setStyleSheet(QString::fromUtf8("color:#808080;\n"
"border:none;\n"
"font-size:18px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"text-align:left;"));

        horizontalLayout_4->addWidget(frame_9);


        verticalLayout_2->addWidget(frame_6);

        frame_5 = new QFrame(frame_3);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(frame_5->sizePolicy().hasHeightForWidth());
        frame_5->setSizePolicy(sizePolicy2);
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_5);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btnReturnbook = new QPushButton(frame_5);
        btnReturnbook->setObjectName(QStringLiteral("btnReturnbook"));
        sizePolicy2.setHeightForWidth(btnReturnbook->sizePolicy().hasHeightForWidth());
        btnReturnbook->setSizePolicy(sizePolicy2);
        btnReturnbook->setStyleSheet(QString::fromUtf8("color:white;\n"
"border:none;\n"
"font-size:20px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(51, 153, 255,1), stop:1 rgba(52, 246, 177,1));\n"
"padding-top:5;\n"
"padding-bottom:5;"));

        horizontalLayout_2->addWidget(btnReturnbook);

        btnBorrowagain = new QPushButton(frame_5);
        btnBorrowagain->setObjectName(QStringLiteral("btnBorrowagain"));
        sizePolicy2.setHeightForWidth(btnBorrowagain->sizePolicy().hasHeightForWidth());
        btnBorrowagain->setSizePolicy(sizePolicy2);
        btnBorrowagain->setStyleSheet(QString::fromUtf8("color:white;\n"
"border:none;\n"
"font-size:20px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:1, y2:0, stop:0 rgba(51, 153, 255,1), stop:1 rgba(52, 246, 177,1));\n"
"padding-top:5;\n"
"padding-bottom:5;"));

        horizontalLayout_2->addWidget(btnBorrowagain);


        verticalLayout_2->addWidget(frame_5);


        horizontalLayout->addWidget(frame_3);


        retranslateUi(student_borrowdetail);

        QMetaObject::connectSlotsByName(student_borrowdetail);
    } // setupUi

    void retranslateUi(QWidget *student_borrowdetail)
    {
        student_borrowdetail->setWindowTitle(QApplication::translate("student_borrowdetail", "student_borrowdetail", Q_NULLPTR));
        btnPersonal->setText(QApplication::translate("student_borrowdetail", "\344\270\252\344\272\272\344\270\255\345\277\203", Q_NULLPTR));
        btnInformationchange->setText(QApplication::translate("student_borrowdetail", "\344\277\241\346\201\257\344\277\256\346\224\271", Q_NULLPTR));
        btnSearchbook->setText(QApplication::translate("student_borrowdetail", "\345\233\276\344\271\246\346\237\245\350\257\242", Q_NULLPTR));
        btnReturn->setText(QApplication::translate("student_borrowdetail", "<", Q_NULLPTR));
        etBookNameHead->setText(QApplication::translate("student_borrowdetail", "\350\277\275\351\243\216\347\255\235\347\232\204\344\272\272", Q_NULLPTR));
        etBookName->setText(QApplication::translate("student_borrowdetail", "\343\200\212\350\277\275\351\243\216\347\255\235\347\232\204\344\272\272\343\200\213", Q_NULLPTR));
        etAuthorHead->setText(QApplication::translate("student_borrowdetail", "\344\275\234\350\200\205\357\274\232", Q_NULLPTR));
        etPublishHead->setText(QApplication::translate("student_borrowdetail", "\345\207\272\347\211\210\347\244\276\357\274\232", Q_NULLPTR));
        etISBNHead->setText(QApplication::translate("student_borrowdetail", "ISBN\357\274\232", Q_NULLPTR));
        etClassifyHead->setText(QApplication::translate("student_borrowdetail", "\345\210\206\347\261\273\357\274\232", Q_NULLPTR));
        btnReturnbook->setText(QApplication::translate("student_borrowdetail", "\345\275\222\350\277\230\344\271\246\346\234\254", Q_NULLPTR));
        btnBorrowagain->setText(QApplication::translate("student_borrowdetail", "\345\233\276\344\271\246\347\273\255\345\200\237", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class student_borrowdetail: public Ui_student_borrowdetail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUDENT_BORROWDETAIL_H
