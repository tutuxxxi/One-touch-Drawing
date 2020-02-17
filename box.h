#ifndef BOX_H
#define BOX_H

#include <QString>
#include <QWidget>
#include <QPixmap>
#include "mylabel.h"
#include "direction.h"
#include "pic.h"

class Box : public QObject
{
    Q_OBJECT

    QWidget *parent;


    int x, y;   //盒子坐标 用于打印图片（决定图片位置）

    enum Pic picType;


    QString str; //指向需要打印的图片地址

    MyLabel* label, *prompt_lab ;

public:
    Box(int x, int y, QWidget *parent = 0, enum Pic picType = Box_);

    void set(enum Pic); //设置图片
    void show();  //显示图片
    void clear();  //清除图片
    void prompt(enum direction);
    enum Pic whichPic();
signals:
    void enter(int x, int y);
public slots:
};



#endif // BOX_H
