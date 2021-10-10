#ifndef PASS_H
#define PASS_H

#include <QMainWindow>
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class pass; }
QT_END_NAMESPACE

class pass : public QMainWindow
{
    Q_OBJECT

public:
    pass(QWidget *parent = nullptr);
    ~pass();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_returnPressed();

private:
    Ui::pass *ui;
    mainwindow *second;
    QByteArray secret;
};

void XOR(QByteArray& input);

#endif // PASS_H
