#ifndef WINDOWLISTER_H
#define WINDOWLISTER_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QCommandLinkButton>
#include <QCheckBox>
#include <QMap>
#include <QEvent>
#include <QMouseEvent>

#include "WindowListerMinMaxClose.h"
#include "WindowListerIconTitle.h"
#include "WindowListerResizeWindow.h"
#include "WindowListerTabWidget.h"
#include "WindowListerMdiArea.h"

class WindowLister : public QObject
{
    Q_OBJECT
public:
    explicit WindowLister(QObject *parent = nullptr);

    void registerWindow(QWidget *);

    void registerMinBtn(QWidget * btn, QWidget * window);
    void registerMaxBtn(QWidget * btn, QWidget * window);
    void registerCloseBtn(QWidget * btn, QWidget * window, QWidget * alert = NULL);

    void registerWindowTitle(QWidget * btn, QWidget * window);

    void registerTabWidget(QWidget* btn, QWidget * window);
    void registerMdiArea(QWidget* btn, QWidget * window);
signals:

public slots:

private:
    WindowListerMinMaxClose  * minMaxClose;         // 最小、正常最大化、关闭
    WindowListerIconTitle    * iconTitle;           // 标题栏
    WindowListerResizeWindow * resizeWindow;        // 改变大小
    WindowListerTabWidget    * tabWidget;
    WindowListerMdiArea      * mdiArea;
};

#endif // WINDOWLISTER_H
