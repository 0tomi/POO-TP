/********************************************************************************
** Form generated from reading UI file 'generarui.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERARUI_H
#define UI_GENERARUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GenerarUI
{
public:
    QLabel *fondo;
    QLabel *tipoVisita;
    QLabel *duracionVisita;

    void setupUi(QWidget *GenerarUI)
    {
        if (GenerarUI->objectName().isEmpty())
            GenerarUI->setObjectName("GenerarUI");
        GenerarUI->resize(302, 297);
        fondo = new QLabel(GenerarUI);
        fondo->setObjectName("fondo");
        fondo->setGeometry(QRect(0, -10, 341, 321));
        fondo->setStyleSheet(QString::fromUtf8("#fondo{\n"
"	border-image: url(:/C:/Users/Joaquin/Downloads/Documento Estancia.png);\n"
"}"));
        fondo->setPixmap(QPixmap(QString::fromUtf8(":/C:/Users/Joaquin/Downloads/Documento Estancia.png")));
        tipoVisita = new QLabel(GenerarUI);
        tipoVisita->setObjectName("tipoVisita");
        tipoVisita->setGeometry(QRect(120, 100, 121, 20));
        QFont font;
        font.setFamilies({QString::fromUtf8("Nirmala UI")});
        font.setPointSize(11);
        font.setBold(true);
        tipoVisita->setFont(font);
        tipoVisita->setAlignment(Qt::AlignCenter);
        duracionVisita = new QLabel(GenerarUI);
        duracionVisita->setObjectName("duracionVisita");
        duracionVisita->setGeometry(QRect(120, 170, 121, 20));
        duracionVisita->setFont(font);
        duracionVisita->setAlignment(Qt::AlignCenter);

        retranslateUi(GenerarUI);

        QMetaObject::connectSlotsByName(GenerarUI);
    } // setupUi

    void retranslateUi(QWidget *GenerarUI)
    {
        GenerarUI->setWindowTitle(QCoreApplication::translate("GenerarUI", "Form", nullptr));
        fondo->setText(QString());
        tipoVisita->setText(QCoreApplication::translate("GenerarUI", "TextLabel", nullptr));
        duracionVisita->setText(QCoreApplication::translate("GenerarUI", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GenerarUI: public Ui_GenerarUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERARUI_H
