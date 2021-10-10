#ifndef QREMOVEBUTTON_H
#define QREMOVEBUTTON_H

#include <QObject>

class qRemoveButton : public QObject
{
    Q_OBJECT
public:
    explicit qRemoveButton(QObject *parent = nullptr);
    ~qRemoveButton();
    int getID();
    void setID(int _id);
signals:

private:
    int ID;
};

#endif // QREMOVEBUTTON_H
