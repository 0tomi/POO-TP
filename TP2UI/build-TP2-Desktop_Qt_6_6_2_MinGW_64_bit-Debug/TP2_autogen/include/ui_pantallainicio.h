/********************************************************************************
** Form generated from reading UI file 'pantallainicio.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANTALLAINICIO_H
#define UI_PANTALLAINICIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PantallaInicio
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *comenzarJuego;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *PantallaInicio)
    {
        if (PantallaInicio->objectName().isEmpty())
            PantallaInicio->setObjectName("PantallaInicio");
        PantallaInicio->resize(1025, 693);
        PantallaInicio->setMinimumSize(QSize(800, 600));
        PantallaInicio->setMaximumSize(QSize(1920, 1080));
        PantallaInicio->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout = new QHBoxLayout(PantallaInicio);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(PantallaInicio);
        widget->setObjectName("widget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(800, 600));
        widget->setMaximumSize(QSize(1920, 1080));
        widget->setAutoFillBackground(false);
        widget->setStyleSheet(QString::fromUtf8("#widget{\n"
"	border-image: url(:/Resources/escritorio2.png);\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(395, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        comenzarJuego = new QPushButton(widget);
        comenzarJuego->setObjectName("comenzarJuego");

        horizontalLayout_2->addWidget(comenzarJuego);

        horizontalSpacer_2 = new QSpacerItem(395, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        horizontalLayout->addWidget(widget);


        retranslateUi(PantallaInicio);

        QMetaObject::connectSlotsByName(PantallaInicio);
    } // setupUi

    void retranslateUi(QWidget *PantallaInicio)
    {
        PantallaInicio->setWindowTitle(QCoreApplication::translate("PantallaInicio", "Form", nullptr));
        comenzarJuego->setText(QCoreApplication::translate("PantallaInicio", "Comenzar Juego Locura Insana", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PantallaInicio: public Ui_PantallaInicio {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANTALLAINICIO_H
