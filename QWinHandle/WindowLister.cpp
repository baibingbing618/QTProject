#include "WindowLister.h"

WindowLister::WindowLister(QObject *parent) : QObject(parent)
{
     minMaxClose  = new WindowListerMinMaxClose(this);
     iconTitle    = new WindowListerIconTitle(this);
     resizeWindow = new WindowListerResizeWindow(this);

     tabWidget    = new WindowListerTabWidget(this);
     mdiArea      = new WindowListerMdiArea(this);

     connect(minMaxClose, &WindowListerMinMaxClose::mouseEnter, resizeWindow, &WindowListerResizeWindow::titleMouseEnter);
     connect(minMaxClose, &WindowListerMinMaxClose::mouseLeave, resizeWindow, &WindowListerResizeWindow::titleMouseLeave);

     connect(iconTitle, &WindowListerIconTitle::mouseEnter, resizeWindow, &WindowListerResizeWindow::titleMouseEnter);
     connect(iconTitle, &WindowListerIconTitle::mouseLeave, resizeWindow, &WindowListerResizeWindow::titleMouseLeave);

     connect(tabWidget, &WindowListerTabWidget::mouseEnter, resizeWindow, &WindowListerResizeWindow::titleMouseEnter);
     connect(tabWidget, &WindowListerTabWidget::mouseLeave, resizeWindow, &WindowListerResizeWindow::titleMouseLeave);

     connect(mdiArea, &WindowListerMdiArea::mouseEnter, resizeWindow, &WindowListerResizeWindow::titleMouseEnter);
     connect(mdiArea, &WindowListerMdiArea::mouseLeave, resizeWindow, &WindowListerResizeWindow::titleMouseLeave);

}

void WindowLister::registerWindow(QWidget * win)
{
     resizeWindow->registerWindow(win);
}

void WindowLister::registerMinBtn(QWidget *btn, QWidget *window)
{
    minMaxClose->registerMinBtn(btn, window);
}

void WindowLister::registerMaxBtn(QWidget *btn, QWidget *window)
{
    minMaxClose->registerMaxBtn(btn, window);
}

void WindowLister::registerCloseBtn(QWidget *btn, QWidget *window, QWidget *alert)
{
    minMaxClose->registerCloseBtn(btn, window, alert);
}

void WindowLister::registerWindowTitle(QWidget *btn, QWidget *window)
{
    iconTitle->registerWindowTitle(btn, window);
}

void WindowLister::registerTabWidget(QWidget* btn, QWidget * window)
{
    tabWidget->registerTabWidget(btn, window);
}

void WindowLister::registerMdiArea(QWidget* btn, QWidget * window)
{
    mdiArea->registerMdiArea(btn, window);
}




