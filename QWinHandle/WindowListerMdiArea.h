#ifndef WINDOWLISTERMDIARED_H
#define WINDOWLISTERMDIARED_H

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

class WindowListerMdiArea: public QObject
{
    Q_OBJECT
public:
    explicit WindowListerMdiArea(QObject *parent = nullptr);
    ~WindowListerMdiArea();

    void registerMdiArea(QWidget * btn, QWidget * window);

signals:
    void mouseEnter(QWidget *watched);
    void mouseLeave(QWidget *watched);

public slots:

protected:
    virtual bool eventFilter(QObject *watched, QEvent *event);
private:
    void handleMousePressed(QWidget *watched, QMouseEvent *event);
    void handleMouseMove(QWidget *watched, QMouseEvent *event);
    void handleMouseRelease(QWidget *watched, QMouseEvent *event);
    void handleDoubleClicked(QWidget *watched, QMouseEvent *event);

    void handleEnter(QWidget *watched, QMouseEvent *event);
    void handleLeave(QWidget *watched, QMouseEvent *event);

    //QMap<QWidget *, QWidget *> *winTitleMap;
};

#endif // WINDOWLISTERMDIARED_H
