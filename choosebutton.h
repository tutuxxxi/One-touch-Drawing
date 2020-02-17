#ifndef CHOOSEBUTTON_H
#define CHOOSEBUTTON_H

#include <QPushButton>
#include <QString>
#include <QDebug>
#include "mybutton.h"
#include "status.h"

class ChooseButton : public QPushButton
{
    Q_OBJECT



    // 关卡三张图片封装
    QString lockedPath = ":/image/lock_level.png";
    QString activePath = ":/image/level.png";
    QString passPath = ":/image/pass_level.png";

    enum status statu; //保存状态

    int levelNum;  //按钮对于关卡数

    void printPicture();
public:
    ChooseButton(enum status, int levelNum);

signals:

public slots:
};

#endif // CHOOSEBUTTON_H
