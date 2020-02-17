#include "mybutton.h"


MyButton::MyButton(QString imagePath) : imagePath(imagePath)
{
    // 为按钮添加图片
    QPixmap pix;
    if(!pix.load(imagePath)){
        qDebug() << "图片加载失败:" << this->imagePath;
        return;
    }
    this->setFixedSize(pix.width(), pix.height()); //将大小设置为传入的图片大小

    this->setStyleSheet( "QPushButton{border: 0px;}" );//设置图片边框为0px（去除边框）

    this->setIcon( pix );// 加入图片
    this->setIconSize( QSize(pix.width(), pix.height()) );
}

void MyButton::change(QString str){
    this->imagePath = str;

    QPixmap p(imagePath);

    this->setIcon(p);
}
