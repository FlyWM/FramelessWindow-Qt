/**
 * 自定义无边框窗体、对话框和提示框
 *
 * MainWindow.h
 * 测试用例主要窗口
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 *
 */

#include <QLabel>
#include <QDebug>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ui_AeroClientWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : MuCustomWindow(parent)
    , ui(new Ui::MainWindow)
    , aeroUI(new Ui::AeroCLientWidget)
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

    // 设置中心客户区域
    setClientWidget(pClientWidget);

    // 设置messagebox的按钮样式表和标题样式表
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
#ifdef Q_OS_WIN32
    initAreoWindow();
    connect(ui->aeroBtn, &QPushButton::clicked, m_AeroWindow, &MuWinAeroShadowWindow::show);
#else
    ui->aeroBtn->hide();
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
#ifdef Q_OS_WIN32
    delete m_AeroWindow;
#endif
}

void MainWindow::onDialogBtnClicked()
{
    MuCustomDialog dialog;
    QLabel label("This is a Custom Dialog!");
    label.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    dialog.titleBar()->titleLabel()->setObjectName("dialogTitleLabel");
    dialog.setModal(false);
    dialog.setWindowTitle("dialog");
    dialog.setClientWidget(&label);
    dialog.setModal(false);
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

#ifdef Q_OS_WIN32
void MainWindow::initAreoWindow()
{
    m_AeroWindow = new MuWinAeroShadowWindow;
//    m_AeroWindow->setRubberBandOnMove(true);
//    m_AeroWindow->setRubberBandOnResize(true);
    m_AeroWindow->setWindowTitle(QStringLiteral("Test Aero Window"));
    m_AeroWindow->titleBar()->setObjectName("aeroTitleBar");
    QWidget *pClientWidget = new QWidget(m_AeroWindow);
    aeroUI->setupUi(pClientWidget);
    m_AeroWindow->setClientWidget(pClientWidget);
}
#endif
