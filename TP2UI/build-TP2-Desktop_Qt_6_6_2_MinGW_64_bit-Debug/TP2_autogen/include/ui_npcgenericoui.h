/********************************************************************************
** Form generated from reading UI file 'npcgenericoui.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NPCGENERICOUI_H
#define UI_NPCGENERICOUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NPCGenericoUI
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;

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
        widget = new QWidget(NPCGenericoUI);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("border-image: url(:/Resources/npc1.png);"));

        verticalLayout->addWidget(widget);


        retranslateUi(NPCGenericoUI);

        QMetaObject::connectSlotsByName(NPCGenericoUI);
    } // setupUi

    void retranslateUi(QWidget *NPCGenericoUI)
    {
        NPCGenericoUI->setWindowTitle(QCoreApplication::translate("NPCGenericoUI", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NPCGenericoUI: public Ui_NPCGenericoUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NPCGENERICOUI_H
