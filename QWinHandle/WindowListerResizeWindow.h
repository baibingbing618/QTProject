#ifndef WINDOWLISTERRESIZEWINDOW_H
#define WINDOWLISTERRESIZEWINDOW_H

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

class WindowListerResizeWindow : public QObject
{
    Q_OBJECT
public:
    typedef enum _Type{
        None,
        Top,
        Right,
        Bottom,
        Left,
        LeftTop,
        RightTop,
        LeftBottom,
        RightBottom
    }Type;

    explicit WindowListerResizeWindow(QObject *parent = nullptr);

    void registerWindow(QWidget *);

    int getWidthPixel() const;
    void setWidthPixel(int value);

    Type getType() const;

signals:
    void enterResize(bool bParent);

protected:
    virtual bool eventFilter(QObject *watched, QEvent *event);
public slots:
    void titleMouseEnter(QWidget *watched);
    void titleMouseLeave();

private:
    void handleEnter(QWidget* win, QMouseEvent * e);

    void handleMousePressed(QWidget* win, QMouseEvent * e);
    void handleMouseReleased(QWidget* win, QMouseEvent * e);
    void handleResize(QWidget* win, QMouseEvent * e);

    void handleEnterTopWindow(QWidget*win);
    void handleEnterRightWindow(QWidget*win);
    void handleEnterBottomWindow(QWidget*win);
    void handleEnterLeftWindow(QWidget*win);

    void handleEnterLeftTopWindow(QWidget*win);
    void handleEnterRightTopWindow(QWidget*win);
    void handleEnterLeftBottomWindow(QWidget*win);
    void handleEnterRightBottomWindow(QWidget*win);

    int  widthPixel;
    bool mouseInWidget;
    bool mousePressed;
    QPoint point;
    QPoint globalPoint;
    Type type;

    bool m_titleMouseEnter = false;
};

#endif // WINDOWLISTERRESIZEWINDOW_H
