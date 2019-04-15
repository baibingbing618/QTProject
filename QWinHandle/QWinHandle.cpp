#include "QWinHandle.h"
#include "ui_QWinHandle.h"
#include <QDebug>
#include <QPainter>
#include <QLineEdit>
#include <QMdiSubWindow>
#include <QTextEdit>
#include <QLabel>

#include "mainwindow.h"

QWinHandle::QWinHandle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QWinHandle)
{
    ui->setupUi(this);
    initFixSize();

    WindowLister *lister = new WindowLister(this);

    QPixmap pixmap(":/png/resource/icon.png");

    // 关闭按钮
    QIcon btnCloseIcon;
    btnCloseIcon.addPixmap(pixmap.copy(608, 1024, 28, 24));
    ui->pushBtnClose->setIcon(btnCloseIcon);
    btnCloseIcon.detach();
    lister->registerCloseBtn(ui->pushBtnClose, this); //minwindow widget, not only button

    // 恢复,最大化按钮
    QIcon btnMaxIcon;
    btnMaxIcon.addPixmap(pixmap.copy(352, 1024, 28, 24));
    ui->pushBtnMax->setIcon(btnMaxIcon);
    btnMaxIcon.detach();
    lister->registerMaxBtn(ui->pushBtnMax, this);

    // 最小化按钮
    QIcon btnMinIcon;
    btnMinIcon.addPixmap(pixmap.copy(224, 1024, 28, 24));
    ui->pushBtnMin->setIcon(btnMinIcon);
    btnMinIcon.detach();
    lister->registerMinBtn(ui->pushBtnMin, this);

    lister->registerTabWidget(ui->tabWidget, this);

    lister->registerMdiArea(ui->mdiArea, this);

    lister->registerWindow(this);

    // 标题栏
    lister->registerWindowTitle(ui->pushBtnTitle, this);

    m_tabBtnToolFile = new QPushButton(this);
    m_tabBtnToolFile->setText(QString::fromLocal8Bit("File"));
    //m_tabClosebutton->setIcon(QApplication::style()->standardIcon(QStyle::SP_DockWidgetCloseButton));

    ui->tabWidget->setCornerWidget(m_tabBtnToolFile, Qt::TopLeftCorner);

    m_tabSearchEdit = new QLineEdit(this);
    m_tabSearchEdit->setPlaceholderText(QString("Search what you want."));
    ui->tabWidget->setCornerWidget(m_tabSearchEdit, Qt::TopRightCorner);
    qDebug() << "hasHeightForWidth" << ui->tabWidget->hasHeightForWidth() << endl;

    ui->mdiArea->setViewMode(QMdiArea::TabbedView); // Tab多页显示模式
    ui->mdiArea->setTabPosition(QTabWidget::North);
    ui->mdiArea->setTabsClosable(true); //页面可关闭
    ui->mdiArea->setTabsMovable(true);
    ui->mdiArea->setTabShape(QTabWidget::Rounded);
    ui->mdiArea->setOption(QMdiArea::DontMaximizeSubWindowOnActivation);

    /*
    //window1
    QTextEdit *window1 = new QTextEdit;
    window1->setHtml("C");
    ui->mdiArea->addSubWindow(window1);     //将window1放进mdiArea框架

    QMdiSubWindow* pMidWin = new QMdiSubWindow();
    pMidWin->setWindowTitle("first");
    pMidWin->setWidget(& QLabel("hey"));
    ui->mdiArea->addSubWindow(pMidWin);
    pMidWin->show();

    Q_FOREACH(QTabBar* tab,ui->mdiArea->findChildren<QTabBar *>())
    {
        //tab->setDrawBase(false);// 不绘制 底边（默认，QTabBar下面有条黑边）
        tab->setExpanding(false);
    }
    */

    connect(m_tabBtnToolFile, &QPushButton::clicked, this, &QWinHandle::clickToolFile);

    m_formFile = new FormFile(this);

    //m_formFile.move(this->pos());
    qDebug() << "Pos" << this->pos() << endl;
    //m_formFile.setAttribute(Qt::WA_ShowModal, true);
    m_formFile->resize(this->size());
    m_formFile->setWindowModality(Qt::NonModal);
    m_formFile->hide();

    ui->tabWidget->setTabBarAutoHide(true);

    m_toolbar = new QToolBar();

    QLineEdit* tabSearchEdit = new QLineEdit(m_toolbar);
    tabSearchEdit->setPlaceholderText(QString("Search what you want."));
    m_toolbar->addWidget(tabSearchEdit);

    m_tabBtnAuto = new QPushButton(m_toolbar);
    m_tabBtnAuto->setObjectName(QString("btnAuto"));
    m_tabBtnAuto->setText(QString("Hide/Show"));
    m_tabBtnAuto->setFixedWidth(120);
    m_toolbar->addWidget(m_tabBtnAuto);

    ui->tabWidget->setCornerWidget(m_toolbar, Qt::TopRightCorner);

    connect(m_tabBtnAuto, &QPushButton::clicked, this, &QWinHandle::clickToolHide);
}

QWinHandle::~QWinHandle()
{
    delete ui;
}

void QWinHandle::initFixSize()
{
}

void QWinHandle::setWindowTitle(const QString text)
{
}

void QWinHandle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QWidget::paintEvent(event);
}

void QWinHandle::clickToolFile()
{
    int nDlt = ui->pushBtnTitle->height() + ui->tabWidget->tabBar()->tabRect(0).height() + 4;
    m_formFile->move(this->pos().x(),
                    this->pos().y() + nDlt);
    m_formFile->resize(this->size().width(), this->size().height() - nDlt - 4);
    if(m_formFile->isHidden())
        m_formFile->show();
    else
        m_formFile->hide();
}

void QWinHandle::clickToolHide()
{
    if(!bHide)
    {
        m_nTabHeaderHeight = ui->tabWidget->tabBar()->tabRect(0).height();
        m_nTabHeight = ui->tabWidget->height();
        ui->tabWidget->setFixedHeight(m_nTabHeaderHeight);
    }
    else
    {
        ui->tabWidget->setFixedHeight(m_nTabHeight);
    }
    bHide = !bHide;
}
