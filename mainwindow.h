#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFormLayout>
#include <QMainWindow>
#include "q_aes/qtinyaes.h"
#include <QFile>
#include <QCryptographicHash>


namespace Ui {
class mainwindow;
}

class mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = nullptr);
    ~mainwindow();
    void add_empty_line();
    void add_line(QString name, QString login, QString password);
    void save_data();

private slots:
    void delete_line();

private:
    Ui::mainwindow *ui;
    QWidget *scrollWidget;
//    QGridLayout *layout;
    QVBoxLayout *layout;
    QString secret;
    QString iv;
    QTinyAes* aes;
    QFile* file;
    QByteArray secret_input;

    int count_of_widgets;
};


#endif // MAINWINDOW_H
