#ifndef WINDOWLISTERMINMAXCLOSE_H
#define WINDOWLISTERMINMAXCLOSE_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QCommandLinkButton>
#include <QCheckBox>
#include <QMap>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QDesktopWidget>

class WindowListerMinMaxClose : public QObject
{
    enum Type{
        MinButton       = 0, // 最小化按钮
        NormalMaxButton = 1, // 正常、最大化按钮
        CloseButton     = 2  // 关闭按钮
    };

    Q_OBJECT
public:
    explicit WindowListerMinMaxClose(QObject *parent = nullptr);
    ~WindowListerMinMaxClose();

    void registerMinBtn(QWidget * btn, QWidget * window);
    void registerMaxBtn(QWidget * btn, QWidget * window);
    void registerCloseBtn(QWidget *btn, QWidget * window, QWidget * alert = NULL);

    void handleEnter(QWidget *watched, QMouseEvent *event);
    void handleLeave(QWidget *watched, QMouseEvent *event);
signals:
    void mouseEnter(QWidget *watched);
    void mouseLeave(QWidget *watched);
protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    QObject * pressedWidget; // 按下的按钮

};

#endif // WINDOWLISTERMINMAXCLOSE_H
