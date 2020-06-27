#include "MuWinTitlebar.h"
#include <QEvent>
#include <QLabel>
#include <QHBoxLayout>
#include <QIcon>
#include <QPushButton>
#include <QApplication>
#include <QPainter>
#include <QDebug>

#include "muwinwindow.h"

MuWinTitlebar::MuWinTitlebar(QWidget *parent)
    : QWidget(parent),
      minButton_(new QPushButton()),
      maxRestoreButton_(new QPushButton(this)),
      closeButton_(new QPushButton(this)),
      mainLayout_(new QHBoxLayout(this))
{
//    setAttribute(Qt::WA_TransparentForMouseEvents);
    maxRestoreButton_->setCheckable(true);

    mainLayout_->addStretch();
    mainLayout_->addWidget(minButton_);
    mainLayout_->addWidget(maxRestoreButton_);
    mainLayout_->addWidget(closeButton_);

    minButton_->setFixedSize(35, 35);
    maxRestoreButton_->setFixedSize(35, 35);
    closeButton_->setFixedSize(35, 35);

    minButton_->setObjectName("minButton");
    minButton_->setStyleSheet("QPushButton { "
                              "    border: none;"
                              "    padding: 3px;"
                              "    image: url(:/images/winwindow/minimize.png);"
                              "}"
                              "QPushButton:hover { "
                              "    border: none;"
                              "    background-color: #4baeeb;"
                              "}");

    maxRestoreButton_->setStyleSheet("QPushButton { "
                                     "    border: none;"
                                     "    padding: 8px;"
                                     "    image: url(:/images/winwindow/maximize.png);"
                                     "}"
                                     "QPushButton:hover { "
                                     "    border: none;"
                                     "    background-color: #4baeeb;"
                                     "}"
                                     "QPushButton::checked { "
                                     "    border: none;"
                                     "    padding: 8px;"
                                     "    image: url(:/images/winwindow/restore.png);"
                                     "}"
                                     "QPushButton::checked:hover { "
                                     "    border: none;"
                                     "    background-color: #4baeeb;"
                                     "}"
                                     );

    closeButton_->setStyleSheet("QPushButton { "
                                "    border: none;"
                                "    padding: 8px;"
                                "    image: url(:/images/winwindow/close.png);"
                                "}"
                                "QPushButton:hover { "
                                "    border: none;"
                                "    background-color: #4baeeb;"
                                "}");

    connect(minButton_, &QPushButton::clicked, this, &MuWinTitlebar::ShowMinimized);
    connect(closeButton_, &QPushButton::clicked, this, &MuWinTitlebar::Close);
    connect(maxRestoreButton_, &QPushButton::clicked, [this](bool checked) {
        if (checked)
            emit ShowMaximized();
        else
            emit ShowRestoreSize();
    });
}

bool MuWinTitlebar::eventFilter(QObject *watched, QEvent *event)
{
    MuWinWindow *window = qobject_cast<MuWinWindow *>(watched);
    if (window == nullptr)
        return false;

    switch (event->type()) {
    case QEvent::Resize: {
        if (window->isMaximized()) {
            maxRestoreButton_->setChecked(true);
        } else {
            maxRestoreButton_->setChecked(false);
        }
        return true;
    }

    default:
        break;
    }
    return QWidget::eventFilter(watched, event);
}

void MuWinTitlebar::resizeEvent(QResizeEvent *e)
{
    QRegion reg(frameGeometry());
    reg -= QRegion(geometry());
    reg += childrenRegion();
    setMask(reg);
    QWidget::resizeEvent(e);
}


