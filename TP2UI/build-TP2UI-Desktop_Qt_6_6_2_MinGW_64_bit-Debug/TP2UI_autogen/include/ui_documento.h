/********************************************************************************
** Form generated from reading UI file 'documento.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCUMENTO_H
#define UI_DOCUMENTO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Documento
{
public:

    void setupUi(QWidget *Documento)
    {
        if (Documento->objectName().isEmpty())
            Documento->setObjectName("Documento");
        Documento->resize(400, 300);

        retranslateUi(Documento);

        QMetaObject::connectSlotsByName(Documento);
    } // setupUi

    void retranslateUi(QWidget *Documento)
    {
        Documento->setWindowTitle(QCoreApplication::translate("Documento", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Documento: public Ui_Documento {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCUMENTO_H
