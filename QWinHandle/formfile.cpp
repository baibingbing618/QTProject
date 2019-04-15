#include "formfile.h"
#include "ui_formfile.h"
#include "customtabstyle.h"

FormFile::FormFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormFile)
{
    ui->setupUi(this);
    //no titleBar
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    //setWindowModality(Qt::WindowModal);
    ui->tabWidget->tabBar()->setStyle(new CustomTabStyle);
}

FormFile::~FormFile()
{
    delete ui;
}

void FormFile::on_btnClose_clicked()
{
    close();
}
