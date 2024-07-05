/********************************************************************************
** Form generated from reading UI file 'uaderpass.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UADERPASS_H
#define UI_UADERPASS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UADERpass
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *Documento;

    void setupUi(QWidget *UADERpass)
    {
        if (UADERpass->objectName().isEmpty())
            UADERpass->setObjectName("UADERpass");
        UADERpass->resize(300, 300);
        UADERpass->setMinimumSize(QSize(300, 300));
        UADERpass->setMaximumSize(QSize(400, 400));
        verticalLayout = new QVBoxLayout(UADERpass);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Documento = new QWidget(UADERpass);
        Documento->setObjectName("Documento");
        Documento->setStyleSheet(QString::fromUtf8("#Documento{\n"
"	\n"
"	border-image: url(:/Resources/UADER.png);\n"
"}"));

        verticalLayout->addWidget(Documento);


        retranslateUi(UADERpass);

        QMetaObject::connectSlotsByName(UADERpass);
    } // setupUi

    void retranslateUi(QWidget *UADERpass)
    {
        UADERpass->setWindowTitle(QCoreApplication::translate("UADERpass", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UADERpass: public Ui_UADERpass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UADERPASS_H
