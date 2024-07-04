#include "gamescreen.h"
#include "ui_gamescreen.h"
#include <QDebug>

GameScreen::GameScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameScreen)
{
    ui->setupUi(this);
}

GameScreen::~GameScreen()
{
    delete ui;
}

void GameScreen::EmpezarJuego()
{
    // Arranca la wea esta weon
    qDebug() << "Comenze el juego";
}
