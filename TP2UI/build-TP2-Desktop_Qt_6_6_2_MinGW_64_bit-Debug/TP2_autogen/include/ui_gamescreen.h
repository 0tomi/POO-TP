/********************************************************************************
** Form generated from reading UI file 'gamescreen.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMESCREEN_H
#define UI_GAMESCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameScreen
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *Contenedor;
    QGridLayout *gridLayout;
    QWidget *Mesa;
    QWidget *Escritorio;
    QWidget *Nose;
    QWidget *FondoNPC;

    void setupUi(QWidget *GameScreen)
    {
        if (GameScreen->objectName().isEmpty())
            GameScreen->setObjectName("GameScreen");
        GameScreen->resize(800, 600);
        GameScreen->setMinimumSize(QSize(800, 600));
        GameScreen->setMaximumSize(QSize(1920, 1080));
        horizontalLayout = new QHBoxLayout(GameScreen);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Contenedor = new QWidget(GameScreen);
        Contenedor->setObjectName("Contenedor");
        Contenedor->setMinimumSize(QSize(800, 600));
        Contenedor->setMaximumSize(QSize(1920, 1080));
        gridLayout = new QGridLayout(Contenedor);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        Mesa = new QWidget(Contenedor);
        Mesa->setObjectName("Mesa");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Mesa->sizePolicy().hasHeightForWidth());
        Mesa->setSizePolicy(sizePolicy);
        Mesa->setMinimumSize(QSize(200, 200));
        Mesa->setMaximumSize(QSize(550, 550));
        Mesa->setStyleSheet(QString::fromUtf8("#Mesa{\n"
"	border-image: url(:/Resources/mesa2.png);\n"
"}"));

        gridLayout->addWidget(Mesa, 2, 0, 1, 1);

        Escritorio = new QWidget(Contenedor);
        Escritorio->setObjectName("Escritorio");
        Escritorio->setMinimumSize(QSize(500, 500));
        Escritorio->setMaximumSize(QSize(1920, 1080));
        Escritorio->setStyleSheet(QString::fromUtf8("#Escritorio{\n"
"	border-image: url(:/Resources/escritorio2.png);\n"
"}"));

        gridLayout->addWidget(Escritorio, 1, 1, 2, 1);

        Nose = new QWidget(Contenedor);
        Nose->setObjectName("Nose");
        Nose->setMaximumSize(QSize(1920, 1080));
        Nose->setStyleSheet(QString::fromUtf8("#Nose{\n"
"	border-image: url(:/Resources/fondo.png);\n"
"}"));

        gridLayout->addWidget(Nose, 0, 1, 1, 1);

        FondoNPC = new QWidget(Contenedor);
        FondoNPC->setObjectName("FondoNPC");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(FondoNPC->sizePolicy().hasHeightForWidth());
        FondoNPC->setSizePolicy(sizePolicy1);
        FondoNPC->setMinimumSize(QSize(200, 250));
        FondoNPC->setMaximumSize(QSize(800, 600));
        FondoNPC->setStyleSheet(QString::fromUtf8("#FondoNPC{\n"
"	border-image: url(:/Resources/fondoAlturas.png);\n"
"}"));

        gridLayout->addWidget(FondoNPC, 0, 0, 2, 1);


        horizontalLayout->addWidget(Contenedor);


        retranslateUi(GameScreen);

        QMetaObject::connectSlotsByName(GameScreen);
    } // setupUi

    void retranslateUi(QWidget *GameScreen)
    {
        GameScreen->setWindowTitle(QCoreApplication::translate("GameScreen", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameScreen: public Ui_GameScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMESCREEN_H
