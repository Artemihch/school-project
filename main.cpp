#include "pass.h"
#include <QFile>
#include <QTextStream>
#include <QApplication>

// СДЕЛАТЬ КНОПКУ ОБНОВЛЕНИЯ ПАРОЛЯ

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    pass w;
    QFile f(":qdarkstyle/style.qss");

    if (!f.exists())   {
        printf("Unable to set stylesheet, file not found\n");
    }
    else   {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }
    w.show();
    return a.exec();
}
