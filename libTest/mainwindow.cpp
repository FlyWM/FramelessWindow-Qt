#include <QLabel>
#include <QDebug>
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : MuCustomWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowTitle("Test Custom Window");
    resize(800, 600);

    QWidget *pClientWidget = new QWidget(this);
    ui->setupUi(pClientWidget);

    this->titleBar()->setTitleHeight(50);
    this->titleBar()->setObjectName("titleBar");
    this->titleBar()->titleLabel()->setObjectName("titleLabel");
    this->titleBar()->minimizeButton()->setObjectName("minimizeButton");
    this->titleBar()->maximizeButton()->setObjectName("maximizeButton");
    this->titleBar()->closeButton()->setObjectName("closeButton");
    setClientWidget(pClientWidget);

    const QString buttonStyle = "QPushButton {  \
                                    border: none; \
                                    background-color: #52baff; \
                                    width: 80px; \
                                    height: 30px; \
                                 } \
                                 QPushButton::pressed { \
                                    background-color: gray; \
                                 }";
    MuCustomMessageBox::setTitleStyleSheet(QStringLiteral("QLabel { color: black }"));
    MuCustomMessageBox::setButtonStyleSheet(QDialogButtonBox::Ok, buttonStyle);

    connect(ui->dialogBtn, &QPushButton::clicked, this, &MainWindow::onDialogBtnClicked);
    connect(ui->informationBtn, &QPushButton::clicked, this, &MainWindow::onInformationBtnClicked);
    connect(ui->errorBtn, &QPushButton::clicked, this, &MainWindow::onErrorBtnClicked);
    connect(ui->successBtn, &QPushButton::clicked, this, &MainWindow::onSuccessBtnClicked);
    connect(ui->warningBtn, &QPushButton::clicked, this, &MainWindow::onWarningBtnClicked);
    connect(ui->aeroBtn, &QPushButton::clicked, this, &MainWindow::onAeroBtnClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDialogBtnClicked()
{
    MuCustomDialog dialog;
    QLabel label("This is a Custom Dialog!");
    label.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    dialog.titleBar()->titleLabel()->setObjectName("dialogTitleLabel");
    dialog.setModal(true);
    dialog.setWindowTitle("dialog");
    dialog.setClientWidget(&label);
    dialog.exec();
}

void MainWindow::onInformationBtnClicked()
{
    MuCustomMessageBox::showInformation(nullptr,
                                        QStringLiteral("Information!"),
                                        QStringLiteral("This is a Information MessageBox!"));
}

void MainWindow::onErrorBtnClicked()
{
    MuCustomMessageBox::showError(nullptr,
                                  QStringLiteral("Error!"),
                                  QStringLiteral("This is a Error MessageBox!"));
}

void MainWindow::onSuccessBtnClicked()
{
    MuCustomMessageBox::showSuccess(nullptr,
                                    QStringLiteral("Success!"),
                                    QStringLiteral("This is a Success MessageBox!"));
}

void MainWindow::onWarningBtnClicked()
{
    MuCustomMessageBox::showWarning(nullptr,
                                    QStringLiteral("Warning!"),
                                    QStringLiteral("This is a Warning MessageBox!"));
}

void MainWindow::onAeroBtnClicked()
{
    MuWinAeroShadowWindow *window = new MuWinAeroShadowWindow;
    window->show();
}

