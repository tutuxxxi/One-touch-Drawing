#include "mylabel.h"
#include <QDebug>
MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{  
}

void MyLabel::enterEvent(QEvent *){
    emit enter();
}
