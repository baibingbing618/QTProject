#include "WindowListerResizeWindow.h"
#include <QDebug>

WindowListerResizeWindow::WindowListerResizeWindow(QObject *parent) : QObject(parent)
{
    setWidthPixel(1);
    mouseInWidget = false;
    mousePressed  = false;
    type = None;
}

void WindowListerResizeWindow::registerWindow(QWidget *win)
{
    win->setWindowFlags(Qt::FramelessWindowHint);//no titleBar
    //this->setAttribute(Qt::WA_TranslucentBackground, true);//ocp
    win->setMouseTracking(true);
    win->setFocusPolicy(Qt::StrongFocus);
    win->installEventFilter(this); // 安装事件过滤器
}

int WindowListerResizeWindow::getWidthPixel() const
{
    return widthPixel;
}

void WindowListerResizeWindow::setWidthPixel(int value)
{
    widthPixel = value;
}

// 事件过滤器
bool WindowListerResizeWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::Enter){
        // 鼠标进入
        mouseInWidget = true;
    }
    else if(event->type() == QEvent::Leave){
        // 鼠标离开
        mouseInWidget = false;
    }
    else if(event->type() == QEvent::MouseMove){
        // 鼠标移动
        if(mouseInWidget){
            QMouseEvent * e = static_cast<QMouseEvent *>(event);
            QWidget* win = static_cast<QWidget*>(watched);

            if(mousePressed && m_titleMouseEnter == false){ // 鼠标按下移动
                qDebug() << "WindowListerResizeWindow:: Mouse Move" << endl;
                handleResize(win, e);
                //if(win->height() < qApp->desktop()->height()){
                if(win->height() < qApp->desktop()->availableGeometry(qApp->desktop()->screenNumber(win->pos())).height()){
                    win->setProperty("_winIsMax_", false);
                }
                else{
                    QSize size = win->property("_winNormalSize_").toSize();
                    size.setWidth(win->width());
                    win->setProperty("_winNormalSize_", size);

                    QPoint p = win->property("_winNormalPos_").toPoint();
                    p.setX(win->pos().x());
                    win->setProperty("_winNormalPos_", p);
                }
            }
            else{
                handleEnter(win, e);
            }
        }
    }
    else if(event->type() == QEvent::MouseButtonPress){
        // 按下按钮
        QMouseEvent * e = static_cast<QMouseEvent *>(event);
        QWidget* win = static_cast<QWidget*>(watched);

        handleMousePressed(win, e);
    }
    else if(event->type() == QEvent::MouseButtonRelease){
        // 放开按钮
        QMouseEvent * e = static_cast<QMouseEvent *>(event);
        QWidget* win = static_cast<QWidget*>(watched);

        handleMouseReleased(win, e);
    }
    else if(event->type() == QEvent::MouseButtonDblClick){
        // 双击按钮
        if(type == Top){
            QMouseEvent * e = static_cast<QMouseEvent *>(event);
            QWidget* win = static_cast<QWidget*>(watched);

            if(win->property("_winIsMax_").toBool()){

                win->move(win->property("_winNormalPos_").toPoint());
                win->resize(win->property("_winNormalSize_").toSize());
                win->setProperty("_winIsMax_", false);
            }
            else{
                win->setProperty("_winNormalPos_", win->pos());
                win->setProperty("_winNormalSize_", QSize(win->width(), win->height()));
                win->setProperty("_winIsMax_", true);
                win->move(win->pos().x(), 0);
                win->resize(win->width(), qApp->desktop()->availableGeometry(qApp->desktop()->screenNumber(win->pos())).height());
            }
        }
    }
    event->accept();

    return false;
}

// 进入框架,鼠标未按下,移动按钮,处理事件
void WindowListerResizeWindow::handleEnter(QWidget *win, QMouseEvent *e)
{
    qDebug() << "WindowListerResizeWindow:";
    if(e->pos().x() <= getWidthPixel() && e->y() <= getWidthPixel()){
        // 左上角进入
        qDebug() << QString::fromLocal8Bit("左上角进入") << endl;
        emit enterResize(true);
        handleEnterLeftTopWindow(win);
        return;
    }
    else if(e->pos().x() <= getWidthPixel() && e->y() >= win->height() - getWidthPixel()){
        // 左下角进入
        qDebug() << QString::fromLocal8Bit("左下角进入") << endl;
        emit enterResize(true);
        handleEnterLeftBottomWindow(win);
        return;
    }
    else if(e->x() >= win->width() - getWidthPixel() && e->y() <= getWidthPixel()){
        // 右上角进入
        qDebug() << QString::fromLocal8Bit("右上角进入") << endl;
        emit enterResize(true);
        handleEnterRightTopWindow(win);
        return;
    }
    else if(e->x() >= win->width() - getWidthPixel() && e->y() >= win->height() - getWidthPixel()){
        // 右下角进入
        qDebug() << QString::fromLocal8Bit("右下角进入") << endl;
        emit enterResize(true);
        handleEnterRightBottomWindow(win);
        return;
    }
    else if(e->pos().x() <= getWidthPixel()){
        // 左侧进入
        qDebug() << QString::fromLocal8Bit("左侧进入") << endl;
        emit enterResize(true);
        handleEnterLeftWindow(win);
        return ;
    }
    else if(e->y() <= getWidthPixel()){
        // 顶部进入
        qDebug() << QString::fromLocal8Bit("顶部进入") << e->y() << getWidthPixel() << endl;
        emit enterResize(true);
        handleEnterTopWindow(win);
        return;
    }
    else if(e->x() >= win->width() - getWidthPixel()){
        // 右侧进入
        qDebug() << QString::fromLocal8Bit("右侧进入") << endl;
        emit enterResize(true);
       handleEnterRightWindow(win);
       return;
    }
    else if(e->y() >= win->height() - getWidthPixel()){
        // 底部进入
        qDebug() << QString::fromLocal8Bit("底部进入") << endl;
        emit enterResize(true);
        handleEnterBottomWindow(win);
        return;
    }
    else{
        //qDebug() << QString::fromLocal8Bit("其他") << endl;
        emit enterResize(false);
        win->setCursor(Qt::ArrowCursor);
        type = None;
    }
}

// 按下按钮
void WindowListerResizeWindow::handleMousePressed(QWidget *, QMouseEvent *e)
{
    if(m_titleMouseEnter == true)
        return;
    qDebug() << "WindowListerResizeWindow:: Mouse Pressed" << endl;

    point = e->pos();
    globalPoint = e->globalPos();
    mousePressed = true;
    e->accept();
}

// 释放按钮
void WindowListerResizeWindow::handleMouseReleased(QWidget *win, QMouseEvent *e)
{
    if(m_titleMouseEnter == true)
        return;

    qDebug() << "WindowListerResizeWindow:: Mouse Released" << endl;

    handleResize(win, e);
    mousePressed = false;
}

void WindowListerResizeWindow::handleResize(QWidget *win, QMouseEvent *e)
{
    qDebug() << "WindowListerResizeWindow:: Resize" << endl;

    if(type == None){
        return;
    }
    int dx = e->pos().x() - point.x();
    int dy = e->pos().y() - point.y();

    int gdx = e->globalPos().x() - globalPoint.x();
    int gdy = e->globalPos().y() - globalPoint.y();

    switch(type){
    case Top:
        win->resize(win->width(), win->height() - gdy);
        win->move(win->x(), win->y() + gdy);
        break;

    case Right:
        win->resize(win->width() + dx, win->height());
        break;

    case Bottom:
        win->resize(win->width(), win->height() + dy);
        break;

    case Left:
        win->resize(win->width() - gdx, win->height());
        win->move(win->x()+gdx, win->y());
        break;

    case LeftTop:
        win->move(win->x()+gdx, win->y()+gdy);
        win->resize(win->width() - gdx, win->height() - gdy);
        break;

    case RightTop:
        win->move(win->x(), win->y()+gdy);
        win->resize(win->width() + gdx, win->height() - gdy);
        break;

    case LeftBottom:
        win->move(win->x()+gdx, win->y());
        win->resize(win->width() - gdx, win->height() + dy);
        break;

    case RightBottom:
        win->resize(win->width() + dx, win->height() + dy);
        break;

    default:
        break;
    }
    point = e->pos();
    globalPoint = e->globalPos();
}

void WindowListerResizeWindow::handleEnterTopWindow(QWidget *win)
{
    win->setCursor(Qt::SizeVerCursor);
    type = Top;
}

void WindowListerResizeWindow::handleEnterRightWindow(QWidget *win)
{
    win->setCursor(Qt::SizeHorCursor);
    type = Right;
}

void WindowListerResizeWindow::handleEnterBottomWindow(QWidget *win)
{
    win->setCursor(Qt::SizeVerCursor);
    type = Bottom;
}

void WindowListerResizeWindow::handleEnterLeftWindow(QWidget *win)
{
    handleEnterRightWindow(win);
    type = Left;
}

void WindowListerResizeWindow::handleEnterLeftTopWindow(QWidget *win)
{
    win->setCursor(Qt::SizeFDiagCursor);
    type = LeftTop;
}

void WindowListerResizeWindow::handleEnterRightTopWindow(QWidget *win)
{
    win->setCursor(Qt::SizeBDiagCursor);
    type = RightTop;
}

void WindowListerResizeWindow::handleEnterLeftBottomWindow(QWidget *win)
{
    handleEnterRightTopWindow(win);
    type = LeftBottom;
}

void WindowListerResizeWindow::handleEnterRightBottomWindow(QWidget *win)
{
    handleEnterLeftTopWindow(win);
    type = RightBottom;
}

WindowListerResizeWindow::Type WindowListerResizeWindow::getType() const
{
    return type;
}

void WindowListerResizeWindow::titleMouseEnter(QWidget *watched)
{
    m_titleMouseEnter = true;
    mouseInWidget = false;

    watched->setCursor(Qt::ArrowCursor);
    type = None;
    qDebug() << "WindowListerResizeWindow::titleMouseEnter()" << endl;
}
void WindowListerResizeWindow::titleMouseLeave()
{
    m_titleMouseEnter = false;
}

