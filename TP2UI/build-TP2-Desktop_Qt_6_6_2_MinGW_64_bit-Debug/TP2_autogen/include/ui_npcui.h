/********************************************************************************
** Form generated from reading UI file 'npcui.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NPCUI_H
#define UI_NPCUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NPCUI
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *CaraNPC;

    void setupUi(QWidget *NPCUI)
    {
        if (NPCUI->objectName().isEmpty())
            NPCUI->setObjectName("NPCUI");
        NPCUI->resize(300, 300);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NPCUI->sizePolicy().hasHeightForWidth());
        NPCUI->setSizePolicy(sizePolicy);
        NPCUI->setMinimumSize(QSize(100, 100));
        NPCUI->setMaximumSize(QSize(300, 300));
        NPCUI->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(NPCUI);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        CaraNPC = new QWidget(NPCUI);
        CaraNPC->setObjectName("CaraNPC");
        sizePolicy.setHeightForWidth(CaraNPC->sizePolicy().hasHeightForWidth());
        CaraNPC->setSizePolicy(sizePolicy);
        CaraNPC->setMinimumSize(QSize(200, 200));
        CaraNPC->setMaximumSize(QSize(400, 400));
        CaraNPC->setStyleSheet(QString::fromUtf8("border-image: url(:/Resources/npc1.png);"));

        verticalLayout->addWidget(CaraNPC);


        retranslateUi(NPCUI);

        QMetaObject::connectSlotsByName(NPCUI);
    } // setupUi

    void retranslateUi(QWidget *NPCUI)
    {
        NPCUI->setWindowTitle(QCoreApplication::translate("NPCUI", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NPCUI: public Ui_NPCUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NPCUI_H
