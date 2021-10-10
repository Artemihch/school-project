#ifndef QR_CREATOR_H
#define QR_CREATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class QR_creator; }
QT_END_NAMESPACE

class QR_creator : public QMainWindow
{
    Q_OBJECT

public:
    QR_creator(QWidget *parent = nullptr, QString secret_key = "IfYouReadingThisErrorWasCaused");
    ~QR_creator();

private:
    Ui::QR_creator *ui;
};
#endif // QR_CREATOR_H
