/**
 * 自定义无边框窗体、对话框和提示框
 *
 * MuCustomWindow.h
 * 自定义无边框窗体、对话框和提示框的实现文件，主要API头文件
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 *
 */

#ifndef MUCUSTOMWINDOW_H
#define MUCUSTOMWINDOW_H

#include <QDialogButtonBox>
#include <QHash>
#include "MuShadowWindow.h"

class FRAMELESSWINDOWSHARED_EXPORT MuCustomWindow : public MuShadowWindow<QWidget>
{
public:
    explicit MuCustomWindow(QWidget *parent = nullptr);

protected:
};

#ifdef Q_OS_WIN32
/**
 * @brief The MuWinAeroShadowWindow class
 *  实现Aero部分特效的窗体
 */
class FRAMELESSWINDOWSHARED_EXPORT MuWinAeroShadowWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MuWinAeroShadowWindow(QWidget *parent = nullptr);

    QWidget *clientWidget() const { return m_pClientWidget; }
    QVBoxLayout *clientLayout() const { return m_pClientLayout; }
    MuTitleBar *titleBar() const { return m_titleBar; }
    void setRubberBandOnMove(bool enable) { m_pHelper->setRubberBandOnMove(enable); }
    void setRubberBandOnResize(bool enable) { m_pHelper->setRubberBandOnResize(enable); }
    void setTitleBarHeight(int height);

    /**
     * @brief setClientWidget
     *  设置client替换掉旧的m_pClientWidget
     *  \warning
     *  如果调用了该函数就不能调用clientLayout()函数了，因为m_pClientLayout指针已被释放
     * @param client
     */
    void setClientWidget(QWidget *client);

protected:
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private:
    QWidget *m_pContainerWidget;
    QVBoxLayout *m_pContainerLayout;
    MuTitleBar *m_titleBar;
    QWidget *m_pClientWidget;
    QVBoxLayout *m_pClientLayout;
    MuFramelessHelper *m_pHelper;
};
#endif

class FRAMELESSWINDOWSHARED_EXPORT MuCustomDialog : public MuShadowWindow<QDialog>
{
public:
    explicit MuCustomDialog(QWidget *parent = nullptr);
};

class QDialogButtonBox;
class FRAMELESSWINDOWSHARED_EXPORT MuCustomMessageBox : public MuShadowWindow<QDialog>
{
    Q_OBJECT
public:
    explicit MuCustomMessageBox(QWidget *parent = nullptr,
                                const QString &title = tr("Tip"),
                                const QString &text = "",
                                QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                QMessageBox::StandardButton defaultButton = QMessageBox::Ok);

    QAbstractButton *clickedButton() const;
    QMessageBox::StandardButton standardButton(QAbstractButton *button) const;

    void setDefaultButton(QPushButton *button);
    void setDefaultButton(QMessageBox::StandardButton button);

    void setTitle(const QString &title);
    void setText(const QString &text);
    void setIcon(const QString &icon);
    void addWidget(QWidget *pWidget);

    QLabel *titleLabel() const;

    QDialogButtonBox *buttonBox() const;

    static QMessageBox::StandardButton showInformation(QWidget *parent,
                                                       const QString &title,
                                                       const QString &text,
                                                       QMessageBox::StandardButton buttons = QMessageBox::Ok);

    static QMessageBox::StandardButton showError(QWidget *parent,
                                                 const QString &title,
                                                 const QString &text,
                                                 QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                                 QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);

    static QMessageBox::StandardButton showSuccess(QWidget *parent,
                                                   const QString &title,
                                                   const QString &text,
                                                   QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                                   QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);

    static QMessageBox::StandardButton showQuestion(QWidget *parent,
                                                    const QString &title,
                                                    const QString &text,
                                                    QMessageBox::StandardButtons buttons = QMessageBox::Yes | QMessageBox::No,
                                                    QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);

    static QMessageBox::StandardButton showWarning(QWidget *parent,
                                                   const QString &title,
                                                   const QString &text,
                                                   QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                                   QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);

    static QMessageBox::StandardButton showCritical(QWidget *parent,
                                                    const QString &title,
                                                    const QString &text,
                                                    QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                                    QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);

    static QMessageBox::StandardButton showCheckBoxQuestion(QWidget *parent,
                                                            const QString &title,
                                                            const QString &text,
                                                            QMessageBox::StandardButtons buttons,
                                                            QMessageBox::StandardButton defaultButton);

public:
    /**
     * @brief setButtonStyleSheet 设置MessagBox的Button的样式表
     * @param button StandardButton
     * @param styleSheet
     */
    static void setButtonStyleSheet(QDialogButtonBox::StandardButton button, const QString &styleSheet);

    /**
     * @brief setTitleStyleSheet 设置标题栏label的样式表
     * @param styleSheet
     */
    static void setTitleStyleSheet(const QString &styleSheet);

private slots:
    void onButtonClicked(QAbstractButton *button);

private:
    int execReturnCode(QAbstractButton *button);
    void translateUI();
    void initStyle();

private:
    QLabel *m_pIconLabel;
    QLabel *m_pLabel;
    QGridLayout *m_pGridLayout;
    QDialogButtonBox *m_pButtonBox;
    QAbstractButton *m_pClickedButton;
    QAbstractButton *m_pDefaultButton;

    // StandardButton, styleSheet
    static QHash<QDialogButtonBox::StandardButton, QString> m_buttonsStyleSheet;
    static QString m_titleStyleSheet;
};

#endif // MUCUSTOMWINDOW_H
