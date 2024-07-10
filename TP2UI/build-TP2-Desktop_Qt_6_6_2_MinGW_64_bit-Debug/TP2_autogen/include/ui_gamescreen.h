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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameScreen
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *Contenedor;
    QGridLayout *gridLayout;
    QWidget *Escritorio;
    QVBoxLayout *verticalLayout;
    QWidget *ContenedorBotones;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *BotonCentrar;
    QSpacerItem *horizontalSpacer;
    QPushButton *aceptarBoton;
    QPushButton *rechazarBoton;
    QWidget *Separador2;
    QWidget *Separador1;
    QWidget *FondoNPC;
    QHBoxLayout *horizontalLayout_3;
    QWidget *Nose;
    QWidget *Mesa;

    void setupUi(QWidget *GameScreen)
    {
        if (GameScreen->objectName().isEmpty())
            GameScreen->setObjectName("GameScreen");
        GameScreen->resize(1280, 720);
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
        Escritorio = new QWidget(Contenedor);
        Escritorio->setObjectName("Escritorio");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(7);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Escritorio->sizePolicy().hasHeightForWidth());
        Escritorio->setSizePolicy(sizePolicy);
        Escritorio->setMinimumSize(QSize(400, 500));
        Escritorio->setMaximumSize(QSize(1350, 1080));
        Escritorio->setStyleSheet(QString::fromUtf8("#Escritorio{\n"
"	border-image: url(:/Resources/escritorio2.png);\n"
"}"));
        verticalLayout = new QVBoxLayout(Escritorio);
        verticalLayout->setObjectName("verticalLayout");
        ContenedorBotones = new QWidget(Escritorio);
        ContenedorBotones->setObjectName("ContenedorBotones");
        ContenedorBotones->setMinimumSize(QSize(500, 100));
        ContenedorBotones->setMaximumSize(QSize(1920, 150));
        horizontalLayout_2 = new QHBoxLayout(ContenedorBotones);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        BotonCentrar = new QPushButton(ContenedorBotones);
        BotonCentrar->setObjectName("BotonCentrar");
        BotonCentrar->setMinimumSize(QSize(100, 50));
        BotonCentrar->setMaximumSize(QSize(200, 75));
        BotonCentrar->setCheckable(true);
        BotonCentrar->setChecked(false);
        BotonCentrar->setAutoExclusive(true);
        BotonCentrar->setFlat(false);

        horizontalLayout_2->addWidget(BotonCentrar);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        aceptarBoton = new QPushButton(ContenedorBotones);
        aceptarBoton->setObjectName("aceptarBoton");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(aceptarBoton->sizePolicy().hasHeightForWidth());
        aceptarBoton->setSizePolicy(sizePolicy1);
        aceptarBoton->setMinimumSize(QSize(50, 50));
        aceptarBoton->setMaximumSize(QSize(200, 75));
        aceptarBoton->setCheckable(true);
        aceptarBoton->setChecked(false);
        aceptarBoton->setAutoExclusive(true);

        horizontalLayout_2->addWidget(aceptarBoton);

        rechazarBoton = new QPushButton(ContenedorBotones);
        rechazarBoton->setObjectName("rechazarBoton");
        sizePolicy1.setHeightForWidth(rechazarBoton->sizePolicy().hasHeightForWidth());
        rechazarBoton->setSizePolicy(sizePolicy1);
        rechazarBoton->setMinimumSize(QSize(50, 50));
        rechazarBoton->setMaximumSize(QSize(200, 75));
        rechazarBoton->setCheckable(true);
        rechazarBoton->setChecked(true);
        rechazarBoton->setAutoExclusive(true);
        rechazarBoton->setFlat(false);

        horizontalLayout_2->addWidget(rechazarBoton);


        verticalLayout->addWidget(ContenedorBotones);

        Separador2 = new QWidget(Escritorio);
        Separador2->setObjectName("Separador2");
        Separador2->setMinimumSize(QSize(500, 100));
        Separador2->setMaximumSize(QSize(500, 200));

        verticalLayout->addWidget(Separador2);

        Separador1 = new QWidget(Escritorio);
        Separador1->setObjectName("Separador1");
        Separador1->setMinimumSize(QSize(500, 100));
        Separador1->setMaximumSize(QSize(1920, 200));

        verticalLayout->addWidget(Separador1);


        gridLayout->addWidget(Escritorio, 1, 1, 2, 1);

        FondoNPC = new QWidget(Contenedor);
        FondoNPC->setObjectName("FondoNPC");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(3);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(FondoNPC->sizePolicy().hasHeightForWidth());
        FondoNPC->setSizePolicy(sizePolicy2);
        FondoNPC->setMinimumSize(QSize(300, 300));
        FondoNPC->setMaximumSize(QSize(600, 600));
        FondoNPC->setSizeIncrement(QSize(50, 0));
        FondoNPC->setStyleSheet(QString::fromUtf8("#FondoNPC{\n"
"	border-image: url(:/Resources/fondoAlturas.png);\n"
"}"));
        horizontalLayout_3 = new QHBoxLayout(FondoNPC);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(-1, -1, -1, 0);

        gridLayout->addWidget(FondoNPC, 0, 0, 2, 1);

        Nose = new QWidget(Contenedor);
        Nose->setObjectName("Nose");
        Nose->setMinimumSize(QSize(400, 100));
        Nose->setMaximumSize(QSize(1350, 400));
        Nose->setStyleSheet(QString::fromUtf8("#Nose{\n"
"	border-image: url(:/Resources/fondo.png);\n"
"}"));

        gridLayout->addWidget(Nose, 0, 1, 1, 1);

        Mesa = new QWidget(Contenedor);
        Mesa->setObjectName("Mesa");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(2);
        sizePolicy3.setHeightForWidth(Mesa->sizePolicy().hasHeightForWidth());
        Mesa->setSizePolicy(sizePolicy3);
        Mesa->setMinimumSize(QSize(300, 300));
        Mesa->setMaximumSize(QSize(600, 600));
        Mesa->setStyleSheet(QString::fromUtf8("#Mesa{\n"
"	border-image: url(:/Resources/mesa2.png);\n"
"}"));

        gridLayout->addWidget(Mesa, 2, 0, 1, 1);


        horizontalLayout->addWidget(Contenedor);


        retranslateUi(GameScreen);

        QMetaObject::connectSlotsByName(GameScreen);
    } // setupUi

    void retranslateUi(QWidget *GameScreen)
    {
        GameScreen->setWindowTitle(QCoreApplication::translate("GameScreen", "Form", nullptr));
        BotonCentrar->setText(QCoreApplication::translate("GameScreen", "Centrar documentos", nullptr));
        aceptarBoton->setText(QCoreApplication::translate("GameScreen", "Aceptar", nullptr));
        rechazarBoton->setText(QCoreApplication::translate("GameScreen", "Rechazar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameScreen: public Ui_GameScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMESCREEN_H
