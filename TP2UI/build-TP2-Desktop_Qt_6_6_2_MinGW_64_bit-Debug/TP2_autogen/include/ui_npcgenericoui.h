/********************************************************************************
** Form generated from reading UI file 'NPCGenericoUIui.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NPCGenericoUIUI_H
#define UI_NPCGenericoUIUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NPCGenericoUI
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *ContenedorNPC;
    QLabel *Cuerpo;
    QLabel *Cejas;
    QLabel *Ojos;
    QLabel *Nariz;
    QLabel *Boca;

    void setupUi(QWidget *NPCGenericoUI)
    {
        if (NPCGenericoUI->objectName().isEmpty())
            NPCGenericoUI->setObjectName("NPCGenericoUI");
        NPCGenericoUI->resize(300, 300);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NPCGenericoUI->sizePolicy().hasHeightForWidth());
        NPCGenericoUI->setSizePolicy(sizePolicy);
        NPCGenericoUI->setMinimumSize(QSize(100, 100));
        NPCGenericoUI->setMaximumSize(QSize(300, 300));
        verticalLayout = new QVBoxLayout(NPCGenericoUI);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        ContenedorNPC = new QWidget(NPCGenericoUI);
        ContenedorNPC->setObjectName("ContenedorNPC");
        ContenedorNPC->setStyleSheet(QString::fromUtf8(""));
        Cuerpo = new QLabel(ContenedorNPC);
        Cuerpo->setObjectName("Cuerpo");
        Cuerpo->setGeometry(QRect(0, 0, 300, 300));
        Cuerpo->setStyleSheet(QString::fromUtf8(""));
        Cejas = new QLabel(ContenedorNPC);
        Cejas->setObjectName("Cejas");
        Cejas->setGeometry(QRect(125, 134, 50, 20));
        Cejas->setMinimumSize(QSize(50, 20));
        Cejas->setMaximumSize(QSize(50, 20));
        Cejas->setStyleSheet(QString::fromUtf8("border-image: url(:/Resources/NPCs/Cejas1.png);"));
        Ojos = new QLabel(ContenedorNPC);
        Ojos->setObjectName("Ojos");
        Ojos->setGeometry(QRect(125, 145, 50, 20));
        Ojos->setMinimumSize(QSize(50, 20));
        Ojos->setMaximumSize(QSize(50, 20));
        Ojos->setStyleSheet(QString::fromUtf8("border-image: url(:/Resources/NPCs/Ojos1.png);"));
        Nariz = new QLabel(ContenedorNPC);
        Nariz->setObjectName("Nariz");
        Nariz->setGeometry(QRect(124, 159, 50, 20));
        Nariz->setMinimumSize(QSize(50, 20));
        Nariz->setMaximumSize(QSize(50, 20));
        Nariz->setStyleSheet(QString::fromUtf8("border-image: url(:/Resources/NPCs/Nariz1.png);"));
        Boca = new QLabel(ContenedorNPC);
        Boca->setObjectName("Boca");
        Boca->setGeometry(QRect(125, 170, 50, 20));
        Boca->setMinimumSize(QSize(50, 20));
        Boca->setMaximumSize(QSize(50, 20));
        Boca->setStyleSheet(QString::fromUtf8("border-image: url(:/Resources/NPCs/Boca1.png);"));
        Cuerpo->raise();
        Ojos->raise();
        Nariz->raise();
        Boca->raise();
        Cejas->raise();

        verticalLayout->addWidget(ContenedorNPC);


        retranslateUi(NPCGenericoUI);

        QMetaObject::connectSlotsByName(NPCGenericoUI);
    } // setupUi

    void retranslateUi(QWidget *NPCGenericoUI)
    {
        NPCGenericoUI->setWindowTitle(QCoreApplication::translate("NPCGenericoUI", "Form", nullptr));
        Cuerpo->setText(QString());
        Cejas->setText(QString());
        Ojos->setText(QString());
        Nariz->setText(QString());
        Boca->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class NPCGenericoUI: public Ui_NPCGenericoUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NPCGenericoUIUI_H
