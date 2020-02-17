#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include <QDebug>

class MyButton : public QPushButton
{
    Q_OBJECT
    QString imagePath;//保存图片地址

public:
    MyButton(QString);
    void change(QString str);
signals:

public slots:
};

#endif // MYBUTTON_H
