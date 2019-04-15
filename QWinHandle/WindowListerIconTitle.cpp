#include "WindowListerIconTitle.h"
#include <QDebug>

WindowListerIconTitle::WindowListerIconTitle(QObject *parent) : QObject(parent)
{
     point = new QPoint(-1, -1);
     m_move = false;
}

WindowListerIconTitle::~WindowListerIconTitle()
{
    if(point){
        delete point;
        point = NULL;
    }
}

void WindowListerIconTitle::registerWindowTitle(QWidget *btn, QWidget *window)
{
    btn->setProperty("_btnCtrlWindow_", (int)(window));
    btn->installEventFilter(this);
}

bool WindowListerIconTitle::eventFilter(QObject *watched, QEvent *event)
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
void WindowListerIconTitle::handleMousePressed(QWidget *, QMouseEvent *event)
{
    qDebug() << "WindowListerIconTitle:: Mouse Pressed" << endl;

    *point = event->globalPos();
    m_pressed = true;
    event->accept();
}

// 鼠标移动
void WindowListerIconTitle::handleMouseMove(QWidget *watched, QMouseEvent *e)
{
    // 鼠标按下,而且父窗口不处理消息
    if(m_pressed)
    {   // 鼠标按下后才允许移动
        m_move = true;

        qDebug() << "WindowListerIconTitle::handleMouseMove" << endl;

        QWidget * win = (QWidget *)watched->property("_btnCtrlWindow_").toInt();

        //qDebug() << e->globalPos() << point << endl;
        int dx = e->globalX() - point->x();
        int dy = e->globalY() - point->y();
        *point = e->globalPos();
        if(win->property("_winIsMax_").toBool()){
            win->resize(win->property("_winNormalSize_").toSize());
            win->setProperty("_winIsMax_", false);
        }
        win->move(win->x() + dx, win->y() + dy);
    }

    e->accept();
}

// 鼠标释放
void WindowListerIconTitle::handleMouseRelease(QWidget *watched, QMouseEvent *e)
{
    qDebug() << "WindowListerIconTitle:: Mouse Release" << endl;
    m_pressed = false;
    if(!m_move){
        return;
    }
    QWidget * win = (QWidget *)watched->property("_btnCtrlWindow_").toInt();

    int dx = e->globalX() - point->x();
    int dy = e->globalY() - point->y();
    win->move(win->x() + dx, win->y() + dy);
    *point = QPoint(-1, -1);
    m_move = false;
    e->accept();
}

// 鼠标双击
void WindowListerIconTitle::handleDoubleClicked(QWidget *watched, QMouseEvent *event)
{
    QWidget * win = (QWidget *)watched->property("_btnCtrlWindow_").toInt();
    if(win->property("_winIsMax_").toBool()){
        win->move(win->property("_winNormalPos_").toPoint());
        win->resize(win->property("_winNormalSize_").toSize());
        win->setProperty("_winIsMax_", false);
    }
    else{
        win->setProperty("_winNormalPos_", win->pos());
        win->setProperty("_winNormalSize_", QSize(win->width(), win->height()));
        win->setProperty("_winIsMax_", true);
        win->setGeometry(qApp->desktop()->availableGeometry(qApp->desktop()->screenNumber(win->pos())));
    }
    event->accept();
}

// 鼠标进入标题栏
void WindowListerIconTitle::handleEnter(QWidget *watched, QMouseEvent *event)
{
    qDebug() << "WindowListerIconTitle::handleEnter" << endl;
    emit mouseEnter(watched);
    event->accept();
}

// 鼠标离开标题栏
void WindowListerIconTitle::handleLeave(QWidget *watched, QMouseEvent *event)
{
    qDebug() << "WindowListerIconTitle::handleLeave" << endl;
    m_move = false;
    m_pressed = false;
    emit mouseLeave(watched);
    event->accept();
}
//
void WindowListerIconTitle::enterResize(bool bParent)
{
    qDebug() << "WindowListerIconTitle::enterResize" << endl;
    //m_move = false;
}
