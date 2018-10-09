/**
 * 自定义无边框窗体、对话框和提示框并封装成库/测试程序
 *
 * mainwindow.cpp
 * 测试窗体。
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 *
 */

#include "mainwindow.h"
#include "stylesheethelper.h"
#include <QPushButton>
#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : FramelessWindow(parent)
{
    setWindowTitle(tr("Custom Frameless Window"));
    QWidget *pWidget = new QWidget(this);
    QPushButton *pDialogBtn = new QPushButton(tr("Dialog"), pWidget);
    pDialogBtn->setObjectName("openDlgBtn");
    pDialogBtn->setFixedSize(60, 25);
    QPushButton *pMessageBoxBtn = new QPushButton(tr("MessageBox"), pWidget);
    FramelessDialog *pDialog = new FramelessDialog(this);
    pDialog->setWindowTitle(tr("Custom Frameless Dialog"));
    QWidget *pDlgWidget = new QWidget(pDialog);
    QPushButton *pDlgBtn = new QPushButton("DialogButton", pDlgWidget);
    pDlgBtn->move(80, 30);
    pDialog->setCentralWidget(pDlgWidget);

    QPushButton *pChangeSkinBtn = new QPushButton("White Skin", this);
    QPushButton *pChangeSkinBtn1 = new QPushButton("Dark Skin", this);
    pChangeSkinBtn->move(50, 30);
    pChangeSkinBtn1->move(160, 30);
    connect(pChangeSkinBtn, &QPushButton::clicked, [=](){
        StyleSheetHelper::setStyle(":/style_white.qss");
    });
    connect(pChangeSkinBtn1, &QPushButton::clicked, [=](){
        StyleSheetHelper::setStyle(":/style_black.qss");
    });

    connect(pDialogBtn, &QPushButton::clicked, [=]() {
        pDialog->show();
    });
    connect(pMessageBoxBtn, &QPushButton::clicked, [=]() {
        FramelessMessageBox::showInformation(this,
                                             tr("Information!"),
                                             tr("Custom Frameless Dialog"),
                                             QMessageBox::Yes);
    });

    QHBoxLayout *pLayout = new QHBoxLayout(pWidget);
    pLayout->addStretch();
    pLayout->addWidget(pDialogBtn);
    pLayout->addWidget(pMessageBoxBtn);
    pLayout->addStretch();

    setCentralWidget(pWidget);
}
