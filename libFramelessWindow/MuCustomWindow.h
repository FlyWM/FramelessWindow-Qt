#ifndef MUCUSTOMWINDOW_H
#define MUCUSTOMWINDOW_H

#include "MuShadowWindow.h"

class FRAMELESSWINDOWSHARED_EXPORT MuCustomWindow : public MuShadowWindow<QWidget>
{
public:
    explicit MuCustomWindow(QWidget *parent = nullptr);

};

class FRAMELESSWINDOWSHARED_EXPORT MuCustomWinAeroWindow : public MuShadowWindow<QWidget>
{
public:
    explicit MuCustomWinAeroWindow(QWidget *parent = nullptr);

protected:
#ifdef Q_OS_WIN32
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
#endif
};

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

private slots:
    void onButtonClicked(QAbstractButton *button);

private:
    int execReturnCode(QAbstractButton *button);
    void translateUI();

private:
    QLabel *m_pIconLabel;
    QLabel *m_pLabel;
    QGridLayout *m_pGridLayout;
    QDialogButtonBox *m_pButtonBox;
    QAbstractButton *m_pClickedButton;
    QAbstractButton *m_pDefaultButton;
};

#endif // MUCUSTOMWINDOW_H
