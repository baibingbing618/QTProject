#ifndef QWINHANDLE_H
#define QWINHANDLE_H

#include <QWidget>
#include <QToolBar>
#include <WindowLister.h>
#include "formfile.h"

namespace Ui {
class QWinHandle;
}

class QWinHandle : public QWidget
{
    Q_OBJECT

public:
    explicit QWinHandle(QWidget *parent = 0);
    ~QWinHandle();

    void initFixSize();
    void setWindowTitle(const QString text);

    void	paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

public:
    QPushButton* m_tabBtnToolFile;
    QLineEdit* m_tabSearchEdit = nullptr;

    QToolBar* m_toolbar = nullptr;
    QPushButton* m_tabBtnAuto = nullptr;

    FormFile* m_formFile = nullptr;

    int m_nTabHeight = 0;
    int m_nTabHeaderHeight = 0;
    bool bHide = false;
private:
    Ui::QWinHandle *ui;

signals:

public slots:
    // 点击文件按钮
    void clickToolFile();

    void clickToolHide();
};

#endif // QWINHANDLE_H
