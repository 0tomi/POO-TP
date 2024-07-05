/********************************************************************************
** Form generated from reading UI file 'nivel.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NIVEL_H
#define UI_NIVEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Nivel
{
public:

    void setupUi(QWidget *Nivel)
    {
        if (Nivel->objectName().isEmpty())
            Nivel->setObjectName("Nivel");
        Nivel->resize(800, 600);
        Nivel->setMinimumSize(QSize(800, 600));
        Nivel->setMaximumSize(QSize(1920, 1080));

        retranslateUi(Nivel);

        QMetaObject::connectSlotsByName(Nivel);
    } // setupUi

    void retranslateUi(QWidget *Nivel)
    {
        Nivel->setWindowTitle(QCoreApplication::translate("Nivel", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Nivel: public Ui_Nivel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NIVEL_H
