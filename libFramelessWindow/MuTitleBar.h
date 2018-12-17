/**
 * 自定义无边框窗体、对话框和提示框并封装成库
 *
 * titlebar.h
 * 自定义窗体的标题栏。
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 *
 */

#ifndef MUTITLEBAR_H
#define MUTITLEBAR_H

#include <QWidget>
#include "framelesswindow_global.h"

class QLabel;
class QPushButton;
class FRAMELESSWINDOWSHARED_EXPORT MuTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit MuTitleBar(QWidget *parent = nullptr);
    ~MuTitleBar();

    void setMinimumVisible(bool minimum);
    void setMaximumVisible(bool maximum);

protected:
    /**
     * @brief mouseDoubleClickEvent
     *  双击标题栏进行界面的最大化/还原
     * @param event
     *  QMouseEvent *
     */
    virtual void mouseDoubleClickEvent(QMouseEvent *event);   

    // 进行鼠界面的拖动
//    virtual void mousePressEvent(QMouseEvent *event);

    /**
     * @brief eventFilter
     *  设置界面标题与图标
     * @param obj
     * @param event
     * @return
     *  bool
     */
    virtual bool eventFilter(QObject *obj, QEvent *event);

private slots:
    /**
     * @brief onClicked
     *   进行最小化、最大化/还原、关闭操作
     */
    void onClicked();

private:
    /**
     * @brief updateMaximize
     *  最大化/还原
     */
    void updateMaximize();

private:
    QLabel *m_pIconLabel;
    QLabel *m_pTitleLabel;
    QPushButton *m_pMinimizeButton;
    QPushButton *m_pMaximizeButton;
    QPushButton *m_pCloseButton;
};

#endif // MUTITLEBAR_H
