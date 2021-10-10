#include "loginpassword.h"
#include "ui_loginpassword.h"

loginpassword::loginpassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginpassword)
{
    ui->setupUi(this);
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    remove_button = ui->pushButton;

    name = "";
    login = "";
    password = "";

    connect(ui->lineEdit, &QLineEdit::editingFinished, this, &loginpassword::change_name);
    connect(ui->lineEdit_2, &QLineEdit::editingFinished, this, &loginpassword::change_login);
    connect(ui->lineEdit_3, &QLineEdit::editingFinished, this, &loginpassword::change_password);
}

loginpassword::loginpassword(QWidget *parent, QString& first_line, QString& second_line, QString& third_line) :
    QWidget(parent),
    ui(new Ui::loginpassword)
{
    ui->setupUi(this);
    ui->lineEdit->setText(first_line);
    ui->lineEdit_2->setText(second_line);
    ui->lineEdit_3->setText(third_line);
    remove_button = ui->pushButton;

    name = first_line;
    login = second_line;
    password = third_line;


    connect(ui->lineEdit, &QLineEdit::editingFinished, this, &loginpassword::change_name);
    connect(ui->lineEdit_2, &QLineEdit::editingFinished, this, &loginpassword::change_login);
    connect(ui->lineEdit_3, &QLineEdit::editingFinished, this, &loginpassword::change_password);
}


void loginpassword::change_name()
{
    name = ui->lineEdit->text();
}

void loginpassword::change_password()
{
    password = ui->lineEdit_3->text();
}

void loginpassword::change_login()
{
    login = ui->lineEdit_2->text();
}


void loginpassword::refresh_data()
{
    name = ui->lineEdit->text();
    login = ui->lineEdit_2->text();
    password = ui->lineEdit_3->text();
}

void loginpassword::setid(int id_)
{
    id = id_;
}


int loginpassword::getid()
{
    return id;
}


loginpassword::~loginpassword()
{
    delete ui;
}



