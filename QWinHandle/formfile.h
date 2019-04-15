#ifndef FORMFILE_H
#define FORMFILE_H

#include <QWidget>

namespace Ui {
class FormFile;
}

class FormFile : public QWidget
{
    Q_OBJECT

public:
    explicit FormFile(QWidget *parent = 0);
    ~FormFile();

private slots:
    void on_btnClose_clicked();

private:
    Ui::FormFile *ui;
};

#endif // FORMFILE_H
