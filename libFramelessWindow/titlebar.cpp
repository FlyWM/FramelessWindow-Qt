/**
 * 自定义无边框窗体、对话框和提示框并封装成库
 *
 * titlebar.cpp
 * 自定义窗体的标题栏。
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 *
 */

#include "titlebar.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <qt_windows.h>

TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent)
{
    setFixedHeight(30);

    m_pIconLabel = new QLabel(this);
    m_pTitleLabel = new QLabel(this);
    m_pMinimizeButton = new QPushButton(this);
    m_pMaximizeButton = new QPushButton(this);
    m_pCloseButton = new QPushButton(this);

    m_pIconLabel->setFixedSize(20, 20);
    m_pIconLabel->setScaledContents(true);

    m_pTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_pMinimizeButton->setFixedSize(27, 22);
    m_pMaximizeButton->setFixedSize(27, 22);
    m_pCloseButton->setFixedSize(27, 22);

    m_pTitleLabel->setObjectName("titleLabel");
    m_pMinimizeButton->setObjectName("minimizeButton");
    m_pMaximizeButton->setObjectName("maximizeButton");
    m_pCloseButton->setObjectName("closeButton");

    m_pMinimizeButton->setToolTip("Minimize");
    m_pMaximizeButton->setToolTip("Maximize");
    m_pCloseButton->setToolTip("Close");

//    m_pMinimizeButton->setStyleSheet("QPushButton#minimizeButton { \
//                                          background: #323232; \
//                                          border: none;               \
//                                          image: url(:/images/minimizeBtnWhite_16.png); \
//                                      }  \
//                                      QPushButton#minimizeButton:hover { \
//                                          background: #505050;  \
//                                      } \
//                                      QPushButton#minimizeButton:pressed { \
//                                          background: #C8C8C8; \
//                                          image: url(:/images/minimizeBtnBlack_16.png);\
//                                      }");
//    m_pMaximizeButton->setStyleSheet("QPushButton#maximizeButton[maximizeProperty=restore] { \
//                                          background: #323232; \
//                                          border: none; \
//                                          image: url(:/images/restoreWhite_16.png); \
//                                      }\
//                                      QPushButton#maximizeButton[maximizeProperty=restore]:hover { \
//                                          background: #505050; \
//                                      }\
//                                      QPushButton#maximizeButton[maximizeProperty=restore]:pressed { \
//                                          background: #C8C8C8; \
//                                          image: url(:/images/restoreBlack_16.png);\
//                                      } \
//                                      QPushButton#maximizeButton[maximizeProperty=maximize] { \
//                                          background: #323232; \
//                                          border: none; \
//                                          image: url(:/images/maximizeBtnWhite_16.png); \
//                                      } \
//                                      QPushButton#maximizeButton[maximizeProperty=maximize]:hover { \
//                                          background: #505050;\
//                                      } \
//                                      QPushButton#maximizeButton[maximizeProperty=maximize]:pressed { \
//                                          background: #C8C8C8;\
//                                          image: url(:/images/maximizeBtnBlack_16.png) \
//                                      }");
//    m_pCloseButton->setStyleSheet("QPushButton#closeButton { \
//                                       background: #323232; \ \
//                                       border: none; \
//                                       image: url(:/images/closeBtnWhite_16.png);\
//                                   }  \
//                                   QPushButton#closeButton:hover { \
//                                       background: #505050; \
//                                   } \
//                                   QPushButton#closeButton:pressed { \
//                                       background: #C8C8C8;\
//                                       image: url(:/images/closeBtnBlack_16.png); \
//                                   }");


    QHBoxLayout *pLayout = new QHBoxLayout(this);
    pLayout->addWidget(m_pIconLabel);
    pLayout->addSpacing(5);
    pLayout->addWidget(m_pTitleLabel);
    pLayout->addStretch();
    pLayout->addWidget(m_pMinimizeButton);
    pLayout->addWidget(m_pMaximizeButton);
    pLayout->addWidget(m_pCloseButton);
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(5, 0, 5, 0);

    setLayout(pLayout);

    connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pMaximizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
}
TitleBar::~TitleBar()
{

}

void TitleBar::setMinimumVisible(bool minimum)
{
    if (!minimum)  m_pMinimizeButton->hide();
}

void TitleBar::setMaximumVisible(bool maximum)
{
    if (!maximum) m_pMaximizeButton->hide();
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    emit m_pMaximizeButton->clicked();
}

//void TitleBar::mousePressEvent(QMouseEvent *event)
//{
//    if (ReleaseCapture())
//    {
//        QWidget *pWindow = this->window();
//        if (pWindow->isTopLevel())
//        {
//           SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
//        }
//    }
//    event->ignore();
//}

bool TitleBar::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::WindowTitleChange:
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            m_pTitleLabel->setText(pWidget->windowTitle());
            return true;
        }
    }
    case QEvent::WindowIconChange:
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            QIcon icon = pWidget->windowIcon();
            m_pIconLabel->setPixmap(icon.pixmap(m_pIconLabel->size()));
            return true;
        }
    }
    case QEvent::WindowStateChange:
    case QEvent::Resize:
        updateMaximize();
        return true;
    default:
        return QWidget::eventFilter(obj, event);
    }
}

void TitleBar::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if (pButton == m_pMinimizeButton)
        {
            pWindow->showMinimized();
        }
        else if (pButton == m_pMaximizeButton)
        {
            pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
        }
        else if (pButton == m_pCloseButton)
        {
            pWindow->close();
        }
    }
}

void TitleBar::updateMaximize()
{
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        bool bMaximize = pWindow->isMaximized();
        if (bMaximize)
        {
            m_pMaximizeButton->setToolTip(tr("Restore"));
            m_pMaximizeButton->setProperty("maximizeProperty", "restore");
        }
        else
        {
            m_pMaximizeButton->setProperty("maximizeProperty", "maximize");
            m_pMaximizeButton->setToolTip(tr("Maximize"));
        }

        m_pMaximizeButton->setStyle(QApplication::style());
    }
}
