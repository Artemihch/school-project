#include "qremovebutton.h"

void qRemoveButton::setID(int _id)
{
    ID = _id;
}

int qRemoveButton::getID(){
    return ID;
}

qRemoveButton::qRemoveButton(QObject *parent) : QObject(parent)
{}

qRemoveButton::~qRemoveButton()
{
}
