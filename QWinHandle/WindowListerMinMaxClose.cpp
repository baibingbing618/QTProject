#include "WindowListerMinMaxClose.h"
#include <QDebug>

WindowListerMinMaxClose::WindowListerMinMaxClose(QObject *parent) : QObject(parent)
{
    pressedWidget = NULL;
}

WindowListerMinMaxClose::~WindowListerMinMaxClose()
{
}

void WindowListerMinMaxClose::registerMinBtn(QWidget *btn, QWidget *window)
{
    btn->setProperty("_btnType_", MinButton);
    btn->setProperty("_btnCtrlWindow_", (int)(window));
    btn->installEventFilter(this);
}

void WindowListerMinMaxClose::registerMaxBtn(QWidget *btn, QWidget *window)
{
    btn->setProperty("_btnType_", NormalMaxButton);
    btn->setProperty("_btnCtrlWindow_", (int)(window));
    btn->installEventFilter(this);
}

void WindowListerMinMaxClose::registerCloseBtn(QWidget *btn, QWidget *window, QWidget *)
{
    btn->setProperty("_btnType_", CloseButton);
    btn->setProperty("_btnCtrlWindow_", (int)(window));
    btn->installEventFilter(this);
}

bool WindowListerMinMaxClose::eventFilter(QObject *watched, QEvent *event)
{
    //qDebug() << event << endl;
    if(QEvent::MouseButtonPress == event->type()){  // 按钮按下
        pressedWidget = watched;
    }
    else if(QEvent::MouseButtonRelease == event->type()){   // 按钮释放
        if(watched == pressedWidget){
            QWidget * win = NULL;
            bool hasWin = false;
            win = (QWidget *)(watched->property("_btnCtrlWindow_").toInt(&hasWin));
            if(hasWin){
                switch(watched->property("_btnType_").toInt()){
                case NormalMaxButton:
                    if(win->property("_winIsMax_").toBool()){
                        // 当前窗口已经是最大,需要执行恢复大小
                        win->move(win->property("_winNormalPos_").toPoint());
                        win->resize(win->property("_winNormalSize_").toSize());
                        win->setProperty("_winIsMax_", false);
                    }
                    else{
                        // 当前窗口需要执行最大化
                        win->setProperty("_winNormalPos_", win->pos()); // 保存正常时位置
                        win->setProperty("_winNormalSize_", QSize(win->width(), win->height())); // 保存正常大小
                        win->setProperty("_winIsMax_", true);
                        win->setGeometry(qApp->desktop()->availableGeometry(qApp->desktop()->screenNumber(win->pos())));
                    }
                    break;
                case CloseButton:
                    win->close();
                    break;
                case MinButton:
                    win->showMinimized();
                    break;
                }
            }
            pressedWidget = NULL;
        }
    }
    else if(QEvent::MouseMove == event->type()){
        if(((QWidget*)(watched))->rect().contains(((QMouseEvent *)(event))->pos())){
            pressedWidget = watched;
        }else{
            pressedWidget = NULL;
        }
    }
    else if(event->type() == QEvent::Enter){
        handleEnter(static_cast<QWidget *>(watched), static_cast<QMouseEvent*>(event));
    }
    else if(event->type() == QEvent::Leave){
        handleLeave(static_cast<QWidget *>(watched), static_cast<QMouseEvent*>(event));
    }
    return false;
}

// 鼠标进入标题栏
void WindowListerMinMaxClose::handleEnter(QWidget *watched, QMouseEvent *event)
{
    emit mouseEnter(watched);
    event->accept();
}

// 鼠标离开标题栏
void WindowListerMinMaxClose::handleLeave(QWidget *watched, QMouseEvent *event)
{
    emit mouseLeave(watched);
    event->accept();
}
