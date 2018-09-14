/**
 * 自定义无边框窗体、对话框和提示框并封装成库
 *
 * framelesswindow.cpp
 * 实现了FramelessWindow、FramlessDialog、FramelessMessageBox
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 *
 */

#include "framelesswindow.h"
#include "framelesshelper.h"
#include "titlebar.h"
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QDialogButtonBox>
#include <QApplication>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QEvent>
#include <QMessageBox>
#include <QIcon>
#include <windows.h>
#include <QFile>

#ifdef Q_CC_MSVC
#pragma comment(lib, "user32.lib")
#endif

FramelessWindow::FramelessWindow(QWidget *parent)
    : QWidget(parent),
      m_pCentralWdiget(new QWidget(this))
{
    QWidget *pMainWindow = new QWidget(this);
    pMainWindow->setObjectName("framelessWindow");
    QVBoxLayout *pLayout = new QVBoxLayout(this);
    pLayout->addWidget(pMainWindow);
    pLayout->setContentsMargins(1, 1, 1, 1);

    QFile qss(":/style/style_white.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();

    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    m_pTitleBar = new TitleBar(this);
    installEventFilter(m_pTitleBar);
    setTitleHeight(m_pTitleBar->height());

    resize(800, 600);
    setWindowTitle("Custom Window");
    setWindowIcon(QIcon(":/images/logo.jpg"));

    pFrameLessWindowLayout = new QVBoxLayout(pMainWindow);
    pFrameLessWindowLayout->addWidget(m_pTitleBar);
    pFrameLessWindowLayout->addWidget(m_pCentralWdiget, 1);
    pFrameLessWindowLayout->setSpacing(0);
    pFrameLessWindowLayout->setContentsMargins(0, 0, 0, 0);

    m_helper = new FramelessHelper(this);
    m_helper->activateOn(this);  //激活当前窗体
    setTitleHeight();

    setWidgetMovalbe();
    setWidgetResizable();
    setRubberBandOnMove();
    setRubberBandOnResize();

    // 此行代码可以带回Aero效果，同时也带回了标题栏和边框,在nativeEvent()会再次去掉标题栏
#ifdef Q_OS_WIN32
    HWND hwnd = (HWND)this->winId();
    DWORD style = ::GetWindowLong(hwnd, GWL_STYLE);
    ::SetWindowLong(hwnd, GWL_STYLE, style | WS_MAXIMIZEBOX | WS_THICKFRAME);
#endif
}

void FramelessWindow::setTitleHeight(int h)
{
    m_helper->setTitleHeight(h);
}

void FramelessWindow::setWidgetMovalbe(bool movable)
{
    m_helper->setWidgetMovable(movable);
}

void FramelessWindow::setWidgetResizable(bool resizable)
{
    m_helper->setWidgetResizable(resizable);
}

void FramelessWindow::setMinimumVisible(bool vislble)
{
    m_pTitleBar->setMinimumVisible(vislble);
}

void FramelessWindow::setMaximumVisible(bool visible)
{
    m_pTitleBar->setMaximumVisible(visible);
}

void FramelessWindow::setRubberBandOnMove(bool move)
{
    m_helper->setRubberBandOnMove(move);
}

void FramelessWindow::setRubberBandOnResize(bool resize)
{
    m_helper->setRubberBandOnResize(resize);
}

void FramelessWindow::setCentralWidget(QWidget *w)
{
    m_pCentralWdiget->deleteLater();
    m_pCentralWdiget = w;
    pFrameLessWindowLayout->addWidget(w, 1);
}

bool FramelessWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG* msg = (MSG *)message;
    switch (msg->message)
    {
    case WM_NCCALCSIZE:
    {
        // this kills the window frame and title bar we added with WS_THICKFRAME and WS_CAPTION
        *result = 0;
        return true;
    }
    default:
        return QWidget::nativeEvent(eventType, message, result);
    }
}

FramelessDialog::FramelessDialog(QWidget *parent)
    : QDialog(parent),
      m_pCentralWidget(new QWidget(this))
{
    setObjectName("framelessDialog");
    resize(400, 300);

    QFile qss(":/style/style_white.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();

    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    m_pTitleBar = new TitleBar(this);
    installEventFilter(m_pTitleBar);
    setTitleHeight(m_pTitleBar->height());

    setWindowTitle("Custom Window");

    pFrameLessWindowLayout = new QVBoxLayout();
    pFrameLessWindowLayout->addWidget(m_pTitleBar);
    pFrameLessWindowLayout->addWidget(m_pCentralWidget, 1);
    pFrameLessWindowLayout->setSpacing(0);
    pFrameLessWindowLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(pFrameLessWindowLayout);

    m_helper = new FramelessHelper(this);
    m_helper->activateOn(this);  //激活当前窗体

    setTitleHeight(m_pTitleBar->height());
    setWidgetMovalbe();
    setWidgetResizable(false);
    setRubberBandOnMove(false);
    setRubberBandOnResize(false);
    // 设置最大和还原按钮不可见
    setMinimumVisible(false);
    setMaximumVisible(false);
}

void FramelessDialog::setTitleHeight(int h)
{
    m_helper->setTitleHeight(h);
}

void FramelessDialog::setWidgetMovalbe(bool movable)
{
    m_helper->setWidgetMovable(movable);
}

void FramelessDialog::setWidgetResizable(bool resizable)
{
    m_helper->setWidgetResizable(resizable);
}

void FramelessDialog::setMinimumVisible(bool vislble)
{
    m_pTitleBar->setMinimumVisible(vislble);
}

void FramelessDialog::setMaximumVisible(bool visible)
{
    m_pTitleBar->setMaximumVisible(visible);
}

void FramelessDialog::setRubberBandOnMove(bool move)
{
    m_helper->setRubberBandOnMove(move);
}

void FramelessDialog::setRubberBandOnResize(bool resize)
{
    m_helper->setRubberBandOnResize(resize);
}

void FramelessDialog::setCentralWidget(QWidget *w)
{
    m_pCentralWidget->deleteLater();
    m_pCentralWidget = w;
    pFrameLessWindowLayout->addWidget(m_pCentralWidget, 1);
}


FramelessMessageBox::FramelessMessageBox(QWidget *parent, const QString &title, const QString &text,
                       QMessageBox::StandardButtons buttons,
                       QMessageBox::StandardButton defaultButton)
    : FramelessDialog(parent)
{
    setObjectName("framelessMessagBox");
    setMinimumVisible(false);
    setMaximumVisible(false);
    setWidgetResizable(false);
    setWindowTitle(title);
    setMinimumSize(300, 130);
    resize(300, 130);

    m_pButtonBox = new QDialogButtonBox(this);
    m_pButtonBox->setStandardButtons(QDialogButtonBox::StandardButtons(int(buttons)));
    setDefaultButton(defaultButton);

    // 根据用到的按钮进行设置,太多了就不一一写了
    QPushButton *pYesButton = m_pButtonBox->button(QDialogButtonBox::Ok);
    if (pYesButton != NULL)
    {
        pYesButton->setObjectName("yesButton");
        pYesButton->setStyleSheet("QPushButton#yesButton { \
                                        background-color: #303030; \
                                        border: none; \
                                        width: 60px; \
                                        height: 25px; \
                                        color: white; \
                                   } \
                                   QPushButton#yesButton:hover { \
                                        background-color: #505050; \
                                   } ");
    }

    m_pIconLabel = new QLabel(this);
    m_pLabel = new QLabel(this);

    QPixmap pixmap(":/Images/information");
    m_pIconLabel->setPixmap(pixmap);
    m_pIconLabel->setFixedSize(35, 35);
    m_pIconLabel->setScaledContents(true);

    m_pLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_pLabel->setObjectName("messageTextLabel");
    m_pLabel->setOpenExternalLinks(true);
    m_pLabel->setText(text);

    m_pGridLayout = new QGridLayout();
    m_pGridLayout->addWidget(m_pIconLabel, 0, 0, 2, 1, Qt::AlignTop);
    m_pGridLayout->addWidget(m_pLabel, 0, 1, 2, 1);
    m_pGridLayout->addWidget(m_pButtonBox, m_pGridLayout->rowCount(), 0, 1, m_pGridLayout->columnCount());
    m_pGridLayout->setSizeConstraint(QLayout::SetNoConstraint);
    m_pGridLayout->setHorizontalSpacing(10);
    m_pGridLayout->setVerticalSpacing(10);
    m_pGridLayout->setContentsMargins(10, 10, 10, 10);
    pFrameLessWindowLayout->addLayout(m_pGridLayout);

    translateUI();

    connect(m_pButtonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));
}

FramelessMessageBox::~FramelessMessageBox()
{

}

QAbstractButton *FramelessMessageBox::clickedButton() const
{
    return m_pClickedButton;
}

QMessageBox::StandardButton FramelessMessageBox::standardButton(QAbstractButton *button) const
{
    return (QMessageBox::StandardButton)m_pButtonBox->standardButton(button);
}

void FramelessMessageBox::setDefaultButton(QPushButton *button)
{
    if (!m_pButtonBox->buttons().contains(button))
        return;

    m_pDefaultButton = button;
    button->setDefault(true);
    button->setFocus();
}

void FramelessMessageBox::setDefaultButton(QMessageBox::StandardButton button)
{
    setDefaultButton(m_pButtonBox->button(QDialogButtonBox::StandardButton(button)));
}

void FramelessMessageBox::setTitle(const QString &title)
{
    setWindowTitle(title);
}

void FramelessMessageBox::setText(const QString &text)
{
    m_pLabel->setText(text);
}

void FramelessMessageBox::setIcon(const QString &icon)
{
    m_pIconLabel->setPixmap(QPixmap(icon));
}

void FramelessMessageBox::addWidget(QWidget *pWidget)
{
    m_pLabel->hide();
    m_pGridLayout->addWidget(pWidget, 0, 1, 2, 1);
}

QMessageBox::StandardButton FramelessMessageBox::showInformation(QWidget *parent,
                                                                 const QString &title,
                                                                 const QString &text,
                                                                 QMessageBox::StandardButtons buttons,
                                                                 QMessageBox::StandardButton defaultButton)
{
    FramelessMessageBox msgBox(parent, title, text, buttons, defaultButton);
    msgBox.setIcon(":/images/informationBlue_48.png");
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;
    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton FramelessMessageBox::showError(QWidget *parent,
                                                           const QString &title,
                                                           const QString &text,
                                                           QMessageBox::StandardButtons buttons,
                                                           QMessageBox::StandardButton defaultButton)
{
    FramelessMessageBox msgBox(parent, title, text, buttons, defaultButton);
    msgBox.setIcon(":/images/errorRed_48.png");
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;
    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton FramelessMessageBox::showSuccess(QWidget *parent,
                                                             const QString &title,
                                                             const QString &text,
                                                             QMessageBox::StandardButtons buttons,
                                                             QMessageBox::StandardButton defaultButton)
{
    FramelessMessageBox msgBox(parent, title, text, buttons, defaultButton);
    msgBox.setIcon(":/images/successGreen_48.png");
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;
    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton FramelessMessageBox::showQuestion(QWidget *parent,
                                                              const QString &title,
                                                              const QString &text,
                                                              QMessageBox::StandardButtons buttons,
                                                              QMessageBox::StandardButton defaultButton)
{
    FramelessMessageBox msgBox(parent, title, text, buttons, defaultButton);
    msgBox.setIcon(":/images/questionBlue_48.png");
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;
    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton FramelessMessageBox::showWarning(QWidget *parent,
                                                             const QString &title,
                                                             const QString &text,
                                                             QMessageBox::StandardButtons buttons,
                                                             QMessageBox::StandardButton defaultButton)
{
    FramelessMessageBox msgBox(parent, title, text, buttons, defaultButton);
    msgBox.setIcon(":/images/warningYellow_48.png");
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;
    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton FramelessMessageBox::showCritical(QWidget *parent,
                                                              const QString &title,
                                                              const QString &text,
                                                              QMessageBox::StandardButtons buttons,
                                                              QMessageBox::StandardButton defaultButton)
{
    FramelessMessageBox msgBox(parent, title, text, buttons, defaultButton);
    msgBox.setIcon(":/images/warningYellow_48.png");
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;
    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton FramelessMessageBox::showCheckBoxQuestion(QWidget *parent,
                                                                      const QString &title,
                                                                      const QString &text,
                                                                      QMessageBox::StandardButtons buttons,
                                                                      QMessageBox::StandardButton defaultButton)
{
    FramelessMessageBox msgBox(parent, title, text, buttons, defaultButton);
    msgBox.setIcon(":/images/questionBlue_48.png");

    QCheckBox *pCheckBox = new QCheckBox(&msgBox);
    pCheckBox->setText(text);
    msgBox.addWidget(pCheckBox);
    if (msgBox.exec() == -1)
        return QMessageBox::Cancel;

    QMessageBox::StandardButton standardButton = msgBox.standardButton(msgBox.clickedButton());
    if (standardButton == QMessageBox::Yes)
    {
        return pCheckBox->isChecked() ? QMessageBox::Yes : QMessageBox::No;
    }
    return QMessageBox::Cancel;
}

void FramelessMessageBox::changeEvent(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::LanguageChange:
        translateUI();
        break;

    default:
        FramelessDialog::changeEvent(event);
    }
}

void FramelessMessageBox::onButtonClicked(QAbstractButton *button)
{
    m_pClickedButton = button;
    done(execReturnCode(button));
}

void FramelessMessageBox::translateUI()
{
    QPushButton *pYesButton = m_pButtonBox->button(QDialogButtonBox::Yes);
    if (pYesButton != NULL)
        pYesButton->setText(tr("Yes"));

    QPushButton *pNoButton = m_pButtonBox->button(QDialogButtonBox::No);
    if (pNoButton != NULL)
        pNoButton->setText(tr("No"));

    QPushButton *pOkButton = m_pButtonBox->button(QDialogButtonBox::Ok);
    if (pOkButton != NULL)
        pOkButton->setText(tr("Ok"));

    QPushButton *pCancelButton = m_pButtonBox->button(QDialogButtonBox::Cancel);
    if (pCancelButton != NULL)
        pCancelButton->setText(tr("Cancel"));
}

int FramelessMessageBox::execReturnCode(QAbstractButton *button)
{
    int nResult = m_pButtonBox->standardButton(button);
    return nResult;
}
