/********************************************************************************
** Form generated from reading UI file 'documentosui.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCUMENTOSUI_H
#define UI_DOCUMENTOSUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DocumentosUI
{
public:

    void setupUi(QWidget *DocumentosUI)
    {
        if (DocumentosUI->objectName().isEmpty())
            DocumentosUI->setObjectName("DocumentosUI");
        DocumentosUI->resize(400, 300);

        retranslateUi(DocumentosUI);

        QMetaObject::connectSlotsByName(DocumentosUI);
    } // setupUi

    void retranslateUi(QWidget *DocumentosUI)
    {
        DocumentosUI->setWindowTitle(QCoreApplication::translate("DocumentosUI", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DocumentosUI: public Ui_DocumentosUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCUMENTOSUI_H
