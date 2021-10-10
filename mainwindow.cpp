#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginpassword.h"
#include <QFile>

#include <QPushButton>
#include <QMessageBox>

#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QDataStream>
#include <QSettings>
#include <pass.h>
#include "q_aes/qtinyaes.h"
#include <QCryptographicHash>


mainwindow::mainwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwindow)
{
    ui->setupUi(this);
    file = new QFile("file.bin");
    QString  name, login, password;


    layout = new QVBoxLayout();

    scrollWidget = new QWidget;
    scrollWidget->setLayout(layout);
    ui->scrollArea->setWidget(scrollWidget);




    secret_input = (QSettings("school_project", "password_manager").value("secret_key", "0")).toByteArray();
    XOR(secret_input);
    secret = (QString)(secret_input);

    aes = new QTinyAes();
    aes->setMode(QTinyAes::CTR);
    QByteArray key = "";
    for (int i = 0; i < QTinyAes::KeySize; ++i)
        key += secret_input[i];
    aes->setKey(key);
    aes->setIv("random_iv_128bit");

    count_of_widgets = 0;


    if(file->exists()) // если файл существует, то считываем данные
    {
        file->open(QFile::ReadOnly);
        QDataStream in(file);
        while (!in.atEnd()){
            QByteArray temp;
            in >> temp; // чтение данных

            QByteArray decoded_data = aes->decrypt(temp); // расшифровка

            QString decodedString(decoded_data);

            name = decodedString.split("|").at(0);
            login = decodedString.split("|").at(1);
            password = decodedString.split("|").at(2);


            mainwindow::add_line(name,login,password); // создание новой строки с данными
        }
    }
    else {
        file->open(QIODevice::WriteOnly | QIODevice::Truncate);
    }
    file->close();
    connect(ui->actionQuit, &QAction::triggered, qApp, &QApplication::quit);
    connect(ui->actionCreate_2, &QAction::triggered, this, &mainwindow::add_empty_line);
    connect(ui->actionSave, &QAction::triggered, this, &mainwindow::save_data);
}

mainwindow::~mainwindow()
{
    delete ui;
}

void mainwindow::save_data()
{
    file->open(QIODevice::WriteOnly | QIODevice::Truncate);
    file->close();
    file->open(QFile::WriteOnly);
    QDataStream out(file);


    for (int index = 0; index < layout->count(); ++index)
    //for (int index = 0; index < count_of_widgets; ++index)
    {
        //if (layout->takeAt(index) == nullptr)
        //    continue;

        //loginpassword* widget = (loginpassword *)(layout->itemAt(index)->widget()); // ПРОИСХОДИТ БАГ С ИНДЕКСАМИ
        //widget->refresh_data(); // проблема в рефреше - лайяут нач

        /*QByteArray out_data = ((QString)widget->name + "|" +
                               (QString)widget->login + "|" +
                               (QString)widget->password)
                .toUtf8();
                */

        QString out_data = (((QString)(((loginpassword *)layout->itemAt(index)->widget())->name))) + "|" +
                                       (((QString)(((loginpassword *)layout->itemAt(index)->widget())->login))) + "|" +
                                       (((QString)(((loginpassword *)layout->itemAt(index)->widget())->password)))
                        .toUtf8();


        QByteArray encoded_data = aes->encrypt(out_data.toUtf8());


        out << encoded_data;
    }
    file->close();
}

void mainwindow::add_line(QString name, QString login, QString password){

    loginpassword *widget = new loginpassword(ui->scrollArea, name, login, password);
    //layout->addWidget(widget, count_of_widgets+ 1, 0);
    //layout->addWidget(widget, layout->count(), 0);
   // QHBoxLayout *row = new QHBoxLayout();
    //row->addWidget(widget);
    //layout->addLayout(row);
    layout->addWidget(widget, 5);
    widget->setid(count_of_widgets);
    connect(widget->remove_button, &QPushButton::clicked, this, &mainwindow::delete_line);
    ++count_of_widgets;
}

void mainwindow::add_empty_line() {
    loginpassword *widget = new loginpassword(ui->scrollArea);
    //QHBoxLayout *row = new QHBoxLayout();
    //row->addWidget(widget);
    //layout->addLayout(row);
    layout->addWidget(widget, 5);
   // layout->addWidget(widget, layout->count(), 0);
    //layout->addWidget(widget, count_of_widgets + 1, 0);
    widget->setid(count_of_widgets);
    connect(widget->remove_button, &QPushButton::clicked, this, &mainwindow::delete_line);
    ++count_of_widgets;
}

void mainwindow::delete_line() {
    loginpassword* object = (loginpassword *)(sender()->parent());
    object->deleteLater();

    --count_of_widgets;
}

