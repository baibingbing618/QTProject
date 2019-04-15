#ifndef WINDOWLISTERICONTITLE_H
#define WINDOWLISTERICONTITLE_H

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

class WindowListerIconTitle : public QObject
{
    Q_OBJECT
public:
    explicit WindowListerIconTitle(QObject *parent = nullptr);
    ~WindowListerIconTitle();

    void registerWindowTitle(QWidget * btn, QWidget * window);

signals:
    void mouseEnter(QWidget *watched);
    void mouseLeave(QWidget *watched);

public slots:
    void enterResize(bool bParent);
protected:
    virtual bool eventFilter(QObject *watched, QEvent *event);
private:
    void handleMousePressed(QWidget *watched, QMouseEvent *event);
    void handleMouseMove(QWidget *watched, QMouseEvent *event);
    void handleMouseRelease(QWidget *watched, QMouseEvent *event);
    void handleDoubleClicked(QWidget *watched, QMouseEvent *event);

    void handleEnter(QWidget *watched, QMouseEvent *event);
    void handleLeave(QWidget *watched, QMouseEvent *event);

    QMap<QWidget *, QWidget *> *winTitleMap;
    QPoint * point;
    bool m_move;
    bool m_pressed = false;
};

#endif // WINDOWLISTERICONTITLE_H
