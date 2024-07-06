/********************************************************************************
** Form generated from reading UI file 'npcgenerico.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NPCGENERICO_H
#define UI_NPCGENERICO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NPCGenerico
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;

    void setupUi(QWidget *NPCGenerico)
    {
        if (NPCGenerico->objectName().isEmpty())
            NPCGenerico->setObjectName("NPCGenerico");
        NPCGenerico->resize(300, 300);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NPCGenerico->sizePolicy().hasHeightForWidth());
        NPCGenerico->setSizePolicy(sizePolicy);
        NPCGenerico->setMinimumSize(QSize(300, 300));
        NPCGenerico->setMaximumSize(QSize(300, 300));
        verticalLayout = new QVBoxLayout(NPCGenerico);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(NPCGenerico);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("border-image: url(:/Resources/npc1.png);"));

        verticalLayout->addWidget(label);


        retranslateUi(NPCGenerico);

        QMetaObject::connectSlotsByName(NPCGenerico);
    } // setupUi

    void retranslateUi(QWidget *NPCGenerico)
    {
        NPCGenerico->setWindowTitle(QCoreApplication::translate("NPCGenerico", "Form", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class NPCGenerico: public Ui_NPCGenerico {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NPCGENERICO_H
