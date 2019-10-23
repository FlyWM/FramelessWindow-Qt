/**
 * 自定义无边框窗体、对话框和提示框
 *
 * MuTitleBar.cpp
 * 自定义窗体的标题栏。
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 *
 */

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#ifdef Q_OS_WIN32
#include <qt_windows.h>
#endif
#include <QDesktopWidget>
#include <QStyleOption>
#include <QPainter>
#include "MuTitleBar.h"
#include "MuShadowWindow.h"
#include "MuCursorPosCalculator.h"

MuTitleBar::MuTitleBar(QWidget *parent, QWidget *window, QWidget *shadowContainerWidget, bool canResize)
    : QWidget(parent)
    , m_window(window)
    , m_shadowContainerWidget(shadowContainerWidget)
    , m_oldContentsMargin(10, 10, 10, 10)
    , m_canResize(canResize)
{
    setFixedHeight(MuCursorPosCalculator::m_nTitleHeight);

    m_pIconLabel = new QLabel(this);
    m_pTitleLabel = new QLabel(this);
    m_pMinimizeButton = new QPushButton(this);
    m_pMaximizeButton = new QPushButton(this);
    m_pCloseButton = new QPushButton(this);
    m_pCustomWidget = new QWidget(this);

    m_pIconLabel->setFixedSize(20, 20);
    m_pIconLabel->setScaledContents(true);

//    m_pTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_pMinimizeButton->setFixedSize(27, 22);
    m_pMaximizeButton->setFixedSize(27, 22);
    m_pCloseButton->setFixedSize(27, 22);

    m_pTitleLabel->setObjectName("titleLabel");
    m_pMinimizeButton->setObjectName("minimizeButton");
    m_pMaximizeButton->setObjectName("maximizeButton");
    m_pCloseButton->setObjectName("closeButton");

    m_pMinimizeButton->setCheckable(true);
    m_pMaximizeButton->setCheckable(true);
    m_pCloseButton->setCheckable(true);

    m_pMinimizeButton->setToolTip("Minimize");
    m_pMaximizeButton->setToolTip("Maximize");
    m_pCloseButton->setToolTip("Close");

    m_pCustomWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout *pLayout = new QHBoxLayout(this);
    pLayout->addWidget(m_pIconLabel);
    pLayout->addSpacing(5);
    pLayout->addWidget(m_pTitleLabel);
    pLayout->addWidget(m_pCustomWidget);
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
MuTitleBar::~MuTitleBar()
{

}

void MuTitleBar::setMinimumVisible(bool minimum)
{
    if (!minimum)
        m_pMinimizeButton->hide();
    else
        m_pMaximizeButton->show();
}

void MuTitleBar::setMaximumVisible(bool maximum)
{
    if (!maximum)
        m_pMaximizeButton->hide();
    else
        m_pMaximizeButton->show();
}

void MuTitleBar::setTitleHeight(int height)
{
    if (height < 0)
        height = 0;
    setFixedHeight(height);
    emit HeightChanged(height);
}

QWidget *MuTitleBar::customWidget() const
{
    return m_pCustomWidget;
}

QPushButton *MuTitleBar::minimizeButton() const
{
    return m_pMinimizeButton;
}

QPushButton *MuTitleBar::maximizeButton() const
{
    return m_pMaximizeButton;
}

QPushButton *MuTitleBar::closeButton() const
{
    return m_pCloseButton;
}

QLabel *MuTitleBar::titleLabel() const
{
    return m_pTitleLabel;
}

QSize MuTitleBar::oldSize() const
{
    return m_oldSize;
}

void MuTitleBar::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void MuTitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    emit m_pMaximizeButton->clicked();
}

bool MuTitleBar::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type()) {
    case QEvent::WindowTitleChange: {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget) {
            m_pTitleLabel->setText(pWidget->windowTitle());
            return true;
        }
    }
    case QEvent::WindowIconChange: {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget) {
            QIcon icon = pWidget->windowIcon();
            m_pIconLabel->setPixmap(icon.pixmap(m_pIconLabel->size()));
            return true;
        }
    }
    case QEvent::Move:
    case QEvent::WindowStateChange:
        updateMaximize();
        return true;

    case QEvent::Resize:
        if (m_window->isMaximized()) {
            QResizeEvent *re = reinterpret_cast<QResizeEvent *>(event);
            if (re != nullptr) {
                m_oldSize = re->oldSize();
            }
        }
        updateMaximize();
        return true;
    default:
        return QWidget::eventFilter(obj, event);
    }
}

void MuTitleBar::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel()) {
        if (pButton == m_pMinimizeButton) {
            pWindow->showMinimized();
        }
        else if (pButton == m_pMaximizeButton) {
            if (!m_canResize)
                return;

            if (Qt::WindowMaximized == m_window->windowState()) {
                m_shadowContainerWidget->setContentsMargins(m_oldContentsMargin);
                m_window->showNormal();
            } else {
                m_oldContentsMargin = m_shadowContainerWidget->contentsMargins();
                m_shadowContainerWidget->setContentsMargins(0, 0, 0, 0);
                m_window->showMaximized();
            }
        }
        else if (pButton == m_pCloseButton)  {
            pWindow->close();
        }
    }
}

void MuTitleBar::updateMaximize()
{
    if (m_window != nullptr) {
        bool bMaximize = m_window->isMaximized();
        if (bMaximize) {
            m_pMaximizeButton->setToolTip(tr("Restore"));
            m_pMaximizeButton->setProperty("maximizeProperty", "restore");
        } else {
            m_pMaximizeButton->setProperty("maximizeProperty", "maximize");
            m_pMaximizeButton->setToolTip(tr("Maximize"));
        }
        m_pMaximizeButton->setStyle(QApplication::style());
    }
}
