#include "WindowListerTabWidget.h"
#include <QDebug>

WindowListerTabWidget::WindowListerTabWidget(QObject *parent) : QObject(parent)
{
}

WindowListerTabWidget::~WindowListerTabWidget()
{
}

void WindowListerTabWidget::registerTabWidget(QWidget *btn, QWidget *window)
{
    //btn->setProperty("_btnCtrlWindow_", (int)(window));
    btn->installEventFilter(this);
}

bool WindowListerTabWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonDblClick){
        handleDoubleClicked(static_cast<QWidget *>(watched), static_cast<QMouseEvent*>(event));
    }
    else if(event->type() == QEvent::MouseButtonPress){
        handleMousePressed(static_cast<QWidget *>(watched), static_cast<QMouseEvent*>(event));
    }
    else if(event->type() == QEvent::MouseMove){
        handleMouseMove(static_cast<QWidget *>(watched), static_cast<QMouseEvent*>(event));
    }
    else if(event->type() == QEvent::MouseButtonRelease){
        handleMouseRelease(static_cast<QWidget *>(watched), static_cast<QMouseEvent*>(event));
    }
    else if(event->type() == QEvent::Enter){
        handleEnter(static_cast<QWidget *>(watched), static_cast<QMouseEvent*>(event));
    }
    else if(event->type() == QEvent::Leave){
        handleLeave(static_cast<QWidget *>(watched), static_cast<QMouseEvent*>(event));
    }
    else{
        event->accept();
    }

    return false;
}

// 鼠标按下
void WindowListerTabWidget::handleMousePressed(QWidget *, QMouseEvent *event)
{
    event->accept();
}

// 鼠标移动
void WindowListerTabWidget::handleMouseMove(QWidget *watched, QMouseEvent *e)
{
    e->accept();
}

// 鼠标释放
void WindowListerTabWidget::handleMouseRelease(QWidget *watched, QMouseEvent *e)
{
    e->accept();
}

// 鼠标双击
void WindowListerTabWidget::handleDoubleClicked(QWidget *watched, QMouseEvent *event)
{
    event->accept();
}

// 鼠标进入标题栏
void WindowListerTabWidget::handleEnter(QWidget *watched, QMouseEvent *event)
{
    emit mouseEnter(watched);
    event->accept();
}

// 鼠标离开标题栏
void WindowListerTabWidget::handleLeave(QWidget *watched, QMouseEvent *event)
{
    emit mouseLeave(watched);
    event->accept();
}
