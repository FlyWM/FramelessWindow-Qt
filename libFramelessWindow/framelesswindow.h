/**
 * 自定义无边框窗体、对话框和提示框并封装成库
 *
 * framelesswindow.h
 * 定义了FramelessWindow、FramlessDialog、FramelessMessageBox
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 *
 */

#ifndef FRAMELESSWINDOW_H
#define FRAMELESSWINDOW_H

#include "framelesswindow_global.h"
#include <QWidget>
#include <QDialog>
#include <QMessageBox>
#include <QVBoxLayout>


/** 是否启用 window AREO 效果 **/
//#undef HAVE_WINDOW_AERO

class MuFramelessHelper;
class MuTitleBar;

/**
 * @brief The FramelessWindow class
 *  无边框自定义窗体
 */
class FRAMELESSWINDOWSHARED_EXPORT FramelessWindow : public QWidget
{
    Q_OBJECT

public:
    FramelessWindow(QWidget *parent = nullptr);

    /**
     * @brief setTitleHeight
     *  设置标题栏高度，如果设置了窗口可移动，拖动标题栏可以移动窗体
     * @param h
     *  标题栏的高度,默认是25
     */
    void setTitleHeight(int h = 25);

    /**
     * @brief setWidgetMovalbe
     *  设置窗口是否可移动，默认可移动
     * @param movable
     */
    void setWidgetMovalbe(bool movable = true);

    /**
     * @brief setWidgetResizable
     *  设置窗口是否可缩放，默认是可以进行缩放
     * @param resizable
     */
    void setWidgetResizable(bool resizable = true);

    /**
     * @brief setMinimumVisible
     *  设置窗口标题栏最小化按钮是否可见
     * @param vislble
     */
    void setMinimumVisible(bool vislble = true);

    /**
     * @brief setMaximumVisible
     *  设置窗口标题栏最大化或还原按钮是否可见
     * @param visible
     */
    void setMaximumVisible(bool visible = true);

    /**
     * @brief setRubberBandOnMove
     *  设置窗口缩放时橡皮筋是否可移动，默认是可移动
     * @param rubber
     */
    void setRubberBandOnMove(bool move = true);

    /**
     * @brief setRubberBandOnResize
     *  设置窗口缩放时橡皮筋是否可缩放，默认可缩放
     * @param resize
     */
    void setRubberBandOnResize(bool resize = true);

    /**
     * @brief setCentralWidget
     *  设置中心界面
     * @param w
     *  QWidget *
     */
    void setCentralWidget(QWidget *w);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private:
    MuFramelessHelper *m_helper;
    MuTitleBar *m_pTitleBar = nullptr;
    QVBoxLayout *pFrameLessWindowLayout;
    QWidget *m_pCentralWdiget;
    //bool m_haveAero;
};

/**
 * @brief The FramelessDialog class
 *  无边框自定义对话框
 */
class FRAMELESSWINDOWSHARED_EXPORT FramelessDialog : public QDialog
{
    Q_OBJECT

public:
    FramelessDialog(QWidget *parent = nullptr);

    /**
     * @brief setTitleHeight
     *  设置标题栏高度，如果设置了窗口可移动，拖动标题栏可以移动窗体
     * @param h
     *  标题栏的高度,默认是25
     */
    void setTitleHeight(int h = 25);

    /**
     * @brief setWidgetMovalbe
     *  设置窗口是否可移动，默认可移动
     * @param movable
     */
    void setWidgetMovalbe(bool movable = true);

    /**
     * @brief setWidgetResizable
     *  设置窗口是否可缩放，默认是可以进行缩放
     * @param resizable
     */
    void setWidgetResizable(bool resizable = true);

    /**
     * @brief setMinimumVisible
     *  设置窗口标题栏最小化按钮是否可见
     * @param vislble
     */
    void setMinimumVisible(bool vislble = true);

    /**
     * @brief setMaximumVisible
     *  设置窗口标题栏最大化或还原按钮是否可见
     * @param visible
     */
    void setMaximumVisible(bool visible = true);

    /**
     * @brief setRubberBandOnMove
     *  设置窗口缩放时橡皮筋是否可移动，默认是可移动
     * @param rubber
     */
    void setRubberBandOnMove(bool move = true);

    /**
     * @brief setRubberBandOnResize
     *  设置窗口缩放时橡皮筋是否可缩放，默认可缩放
     * @param resize
     */
    void setRubberBandOnResize(bool resize = true);

    /**
     * @brief setCentralWidget
     *  设置 dialog 中心控件
     * @param w
     *  QWidget *
     */
    void setCentralWidget(QWidget *w);

protected:
    QVBoxLayout *pFrameLessWindowLayout;

private:
    MuFramelessHelper *m_helper;
    MuTitleBar *m_pTitleBar = nullptr;
    QWidget *m_pCentralWidget;
};


class QLabel;
class QGridLayout;
class QDialogButtonBox;
class QHBoxLayout;
class QAbstractButton;
/**
 * @brief The FramelessMessageBox class
 *  无边框自定义提示框
 */
class FRAMELESSWINDOWSHARED_EXPORT FramelessMessageBox : public FramelessDialog
{
    Q_OBJECT

public:
    FramelessMessageBox(QWidget *parent = nullptr, const QString &title = tr("Tip"), const QString &text = "",
               QMessageBox::StandardButtons buttons = QMessageBox::Ok, QMessageBox::StandardButton defaultButton = QMessageBox::Ok);

    ~FramelessMessageBox();
    QAbstractButton *clickedButton() const;
    QMessageBox::StandardButton standardButton(QAbstractButton *button) const;
    /**
     * @brief setDefaultButton
     *  设置默认按钮
     * @param button
     */
    void setDefaultButton(QPushButton *button);
    void setDefaultButton(QMessageBox::StandardButton button);
    /**
     * @brief setTitle
     *  设置窗体标题
     * @param title
     */
    void setTitle(const QString &title);
    /**
     * @brief setText
     *  设置提示信息
     * @param text
     */
    void setText(const QString &text);
    /**
     * @brief setIcon
     *  设置窗体图标
     * @param icon
     */
    void setIcon(const QString &icon);
    /**
     * @brief addWidget
     *  添加控件-替换提示信息所在的QLabel
     * @param pWidget
     */
    void addWidget(QWidget *pWidget);

    static QMessageBox::StandardButton showInformation(QWidget *parent, const QString &title,
                                                const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                                QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);
    static QMessageBox::StandardButton showError(QWidget *parent, const QString &title,
                                                 const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                                 QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);
    static QMessageBox::StandardButton showSuccess(QWidget *parent, const QString &title,
                                                   const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                                   QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);
    static QMessageBox::StandardButton showQuestion(QWidget *parent, const QString &title,
                                             const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::Yes | QMessageBox::No,
                                             QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);
    static QMessageBox::StandardButton showWarning(QWidget *parent, const QString &title,
                                                   const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                                   QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);
    static QMessageBox::StandardButton showCritical(QWidget *parent, const QString &title,
                                                    const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                                    QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);
    static QMessageBox::StandardButton showCheckBoxQuestion(QWidget *parent, const QString &title,
                                                            const QString &text, QMessageBox::StandardButtons buttons,
                                                            QMessageBox::StandardButton defaultButton);


protected:
    /**
     * @brief changeEvent
     *  多语言翻译
     * @param event
     */
    void changeEvent(QEvent *event);

private slots:
    void onButtonClicked(QAbstractButton *button);

private:
    void translateUI();
    int execReturnCode(QAbstractButton *button);

private:
    QLabel *m_pIconLabel;
    QLabel *m_pLabel;
    QGridLayout *m_pGridLayout;
    QDialogButtonBox *m_pButtonBox;
    QAbstractButton *m_pClickedButton;
    QAbstractButton *m_pDefaultButton;
    QHBoxLayout *m_pLayout;
};

#endif // FRAMELESSWINDOW_H
