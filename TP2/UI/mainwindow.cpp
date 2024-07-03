#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <GenerarEstancia.h>
#include "atributoscomunes.h"
#include "generarui.h"

MainWindow::MainWindow(bool _valido) {
    valido = _valido;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    GenerarUI uiGen;
    uiGen.show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
