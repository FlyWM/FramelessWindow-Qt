#ifndef MUTITLEBAR_H
#define MUTITLEBAR_H

#include <QWidget>
#include "FramelessWindow_Global.h"

class QHBoxLayout;
class QPushButton;
class FRAMELESSWINDOWSHARED_EXPORT MuWinTitlebar : public QWidget
{
    Q_OBJECT
public:
    explicit MuWinTitlebar(QWidget *parent = nullptr);

    bool eventFilter(QObject *watched, QEvent *event);
    void resizeEvent(QResizeEvent *e);

signals:
    void ShowMinimized();
    void ShowMaximized();
    void ShowRestoreSize();
    void Close();

public slots:

private:
    QPushButton *minButton_;
    QPushButton *maxRestoreButton_;
    QPushButton *closeButton_;

    QHBoxLayout *mainLayout_;
};

#endif // MUTITLEBAR_H
