#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    MuCustomWindow(parent),
    ui(new Ui::MainWindow)
{
    QWidget *pClientWidget = new QWidget(clientWidget());
    clientLayout()->addWidget(pClientWidget);
    ui->setupUi(pClientWidget);

    resize(800, 600);
}

MainWindow::~MainWindow()
{
    delete ui;
}
