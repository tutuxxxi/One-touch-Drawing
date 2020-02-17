#include "box.h"
#include <QDebug>

Box::Box(int x, int y, QWidget *parent, enum Pic picType){
    this->parent = parent;
    this->x = x;
    this->y = y;
    this->picType = picType;
    label = new MyLabel();
    label->setParent(parent);
    show();

    prompt_lab = new MyLabel();
    prompt_lab->setParent(parent);

    // 移出标签向gameSence传递移出当前格子信息
    connect(label, &MyLabel::enter, [=](){
       prompt_lab->clear();
       emit enter(this->x, this->y);
    });

    connect(prompt_lab, &MyLabel::enter, [=](){
       emit enter(this->x, this->y);
    });
}

// 图片的设置（伴随着提示图片的清除）
void Box::set(enum Pic a){
    picType = a;
    clear();
    prompt_lab->clear();
}

void Box::show(){
   switch (picType) {
    case Box_:
        str = ":/image/box.png"; //盒子
        break;
    case Cat:
        str = ":/image/cat.png"; //猫
        break;
    case Pass_cat_up:
        str = ":/image/pass_cat_up.png"; //猫向上
        break;
    case Pass_cat_right:
        str = ":/image/pass_cat_right.png"; //猫向右
        break;
    case Pass_cat_down:
        str = ":/image/pass_cat_down.png"; //猫向下
        break;
    case Pass_cat_left:
        str = ":/image/pass_cat_left.png"; //猫向左
        break;
    case Pass_box_up:
        str = ":/image/pass_box_up.png"; //向上
        break;
    case Pass_box_right:
        str = ":/image/pass_box_right.png"; //向右
        break;
    case Pass_box_down:
        str = ":/image/pass_box_down.png"; //向下
        break;
    case Pass_box_left:
        str = ":/image/pass_box_left.png"; //向左
        break;
    case Pass_box_up_left:
        str = ":/image/pass_box_up&left.png"; //上左
        break;
    case Pass_box_up_right:
        str = ":/image/pass_box_up&right.png"; //上右
        break;
    case Pass_box_down_left:
        str = ":/image/pass_box_down&left.png"; //下左
        break;
    case Pass_box_down_right:
        str = ":/image/pass_box_down&right.png"; //下右
        break;
    case Pass_box_up_down:
        str = ":/image/pass_box_up&down.png"; //上下
        break;
    case Pass_box_left_right:
        str = ":/image/pass_box_left&right.png";  //左右
        break;

    }



    QPixmap pix;
    pix.load(str);
    label->setFixedSize(pix.size());
    label->setPixmap(pix);

    if (picType == Cat || picType ==  Pass_cat_up || picType ==  Pass_cat_down ){
        label->move( x * 69 + 43, y * 69 + 167 );
    }else{
        label->move( x * 69 + 43, y * 69 + 170 );
    }
}

void Box::clear(){
    label->clear();
}

enum Pic Box::whichPic(){
    return picType;
}

// 提示图片的添加
void Box::prompt(enum direction dir){
    QPixmap prompt_pix;

    // 加载图片
    switch(dir){
    case Upward:
        prompt_pix.load(":/image/prompt_up.png");
        break;
    case Downward:
        prompt_pix.load(":/image/prompt_down.png");
        break;
    case Left:
        prompt_pix.load(":/image/prompt_left.png");
        break;
    case Right:
        prompt_pix.load(":/image/prompt_right.png");
        break;
    default:
        break;
    }

    prompt_lab->setFixedSize(prompt_pix.size());
    prompt_lab->setPixmap(prompt_pix);
    prompt_lab->move( x * 69 + 43, y * 69 + 170 );
}
