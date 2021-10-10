#ifndef LOGINPASSWORD_H
#define LOGINPASSWORD_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

namespace Ui {
class loginpassword;
}

class loginpassword : public QWidget
{
    Q_OBJECT

public:
    QPushButton* remove_button;
    explicit loginpassword(QWidget *parent = nullptr);
    loginpassword(QWidget *parent, QString& first_line, QString& second_line, QString& third_line);
    ~loginpassword();
    //QGridLayout* my_parent;
    void setid(int id);
    int getid();
    QString name, login, password;
    void refresh_data();
private slots:


signals:


private:
    Ui::loginpassword *ui;
    int id;


    void change_name();
    void change_password();
    void change_login();
};

#endif // LOGINPASSWORD_H
