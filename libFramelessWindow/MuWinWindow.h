#ifndef MUWINWINDOW_H
#define MUWINWINDOW_H

#include <QWidget>

#ifdef Q_OS_WIN32

#include <Windows.h>
#include "FramelessWindow_Global.h"

namespace Ui {
class MuWinWindow;
}

class QHBoxLayout;
class QVBoxLayout;
class FRAMELESSWINDOWSHARED_EXPORT MuWinWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MuWinWindow(QWidget *parent = 0);
    ~MuWinWindow();

    QString iconFileName() const;
    void setWindowIcon(const QString &fileName);
    void setWindowTitle(const QString &title);

    bool isMaximized() const
    { return isMaximized_; }


protected:
    virtual bool nativeEvent(const QByteArray &eventType,
                             void *message,
                             long *result);

    void paintEvent(QPaintEvent *e);

private:
    LRESULT calculateBorder(const QPoint &pt);

private:
    Ui::MuWinWindow *ui;

    QString iconFileName_;
    QString title_;

    QVBoxLayout *mainLayout_;
    QWidget *clientWidget_;

    bool isMaximized_;
};

#endif

#endif // MUWINWINDOW_H
