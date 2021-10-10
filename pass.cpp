#include "pass.h"
#include "ui_pass.h"
#include <QFile>
#include <QMessageBox>
#include "qgoogleauth/qgoogleauth.h"
#include <QSettings>
#include <ctime>
#include "process.h"
#include "qr/qr_creator.h"

QByteArray generate_random_string(const int len){
    QByteArray tmp_s;
    static const char alph[] = {
        "234567" "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    };
    srand( (unsigned) time(NULL) * _getpid());
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i)
        tmp_s += alph[rand() % (sizeof(alph) - 1)];

    return tmp_s;
}

void XOR(QByteArray &input)
{
    for (int i = 0; i < 32; ++i)
    {
        input[i] = input[i]^i;
    }
}



pass::pass(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::pass)
{
    ui->setupUi(this);
    QSettings *settings = new QSettings("school_project", "password_manager");
    secret = settings->value("secret_key", "0").toByteArray();

    if (secret == "0")
    {
        secret = generate_random_string(32);

        QR_creator* qr = new QR_creator(nullptr, secret);
        qr->showNormal();

        QFile* file = new QFile("file.bin");
        file->remove();

        XOR(secret);
        settings->setValue("secret_key", secret);
        XOR(secret);
    }
    else {
        XOR(secret);
    }
}

pass::~pass()
{
    delete ui;
}


void pass::on_pushButton_clicked()
{
    // DEBUG:
    /*second = new mainwindow();
    second->show();
    this->hide();*/
    // DEBUG END
    if (ui->lineEdit->text() == QGoogleAuth::generatePin(secret)){
        second = new mainwindow();
        second->show();
        this->hide();
    }
    else
    {
        QMessageBox::information(this, "Менеджер паролей", "Неверный пароль!");
        ui->lineEdit->setText("");
    }
}

void pass::on_lineEdit_returnPressed()
{
    if (ui->lineEdit->text() == QGoogleAuth::generatePin(secret)){  
        second = new mainwindow();
        second->show();
        this->hide();
    }
    else
    {
        QMessageBox::information(this, "Менеджер паролей", "Неверный пароль!");
        ui->lineEdit->setText("");
    }
}
