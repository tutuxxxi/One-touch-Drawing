#include "choosescene.h"

chooseScene::chooseScene(QWidget *parent) : QWidget(parent)
{
    setFixedSize(500,800); //固定大小
    setWindowTitle("aaa");// 标题
    QIcon a(":/image/icon.png");
    setWindowIcon(a);// 图标

    // 返回按钮的设置
    MyButton* choose_btn = new MyButton(":/image/exit.png");
    choose_btn->setParent(this);//放置按钮
    choose_btn->move( 0, this->height() * 0.9 );

    // 实现返回按钮功能
    connect(choose_btn, &MyButton::clicked, [=](){
        emit this->comeBack();
        QSound::play(":/music/button.wav");
    });


    //加载游戏关卡选择界面
    loadChoose();
}
chooseScene::~chooseScene(){

}


// 绘图事件
void chooseScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix(":/image/choose_background.png");

    painter.drawPixmap(0,0,pix);
}

//读通关记录
void chooseScene::read_passNum(){
    QFile file("passData.bat");
    file.open(QIODevice::ReadOnly);
    QString str = file.readAll();
    file.close();
    passNum = str.toInt();
}
//写通关记录
void chooseScene::write_passNum(){
    QFile file("passData.bat");
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out << passNum + 1;
    file.close();
}

// 加载游戏（通过记录打印当前的选关按钮）
void chooseScene::loadChoose(){
    this->read_passNum();

    // 打印通过的关卡
    for(int i = 0; i<passNum; i++){
        btn[i] = new MyButton(":/image/pass_level.png");
        btn[i]->setParent(this);
        btn[i]->move( (i % 5) * 80 + 50, (i / 5) * 80 + 80 );
        connect(btn[i], &MyButton::clicked, [=](){
           gs = new gameSence(i);  //创建下一个游戏窗口
           gs->show();
           this->hide();
           QSound::play(":/music/button.wav");

           connect(gs, &gameSence::comeBack, [=](){
               this->show();
               //gs->~QObject();
               gs->~gameSence();
               gs = NULL;
           });

           connect(gs, &gameSence::flash, [=](){
               //gs->~QObject();
               gs->~gameSence();
               btn[i]->click();
           });

           //通关检测
           connect(gs,&gameSence::pass, this, [=](int num){
               if(num == passNum){
                   // 写入目前通过关卡数
                   write_passNum();
               }
           });

           connect(gs,&gameSence::win_back,[=](int num){
               if(num == passNum){
                   //从新通过的关卡返回
                   //gs->~QObject();
                   gs->~gameSence();
                   emit flash(); //刷新当前界面
               }else{
                   this->show();
                   //gs->~QObject();
                   gs->~gameSence();
                   gs = NULL;
               }
           });

           connect(gs, &gameSence::win_next, [=](int num){
               //gs->~QObject();
               gs->~gameSence();
               emit win(num+1);
           });

           connect(gs,&gameSence::win_regame, [=](int num){
               //gs->~QObject();
               gs->~gameSence();
               emit win(num);
           });

        });
    }

    //打印激活关
    btn[passNum] = new MyButton(":/image/level.png");
    btn[passNum]->setParent(this);
    btn[passNum]->move( (passNum % 5) * 80 + 50, (passNum / 5) * 80 + 80 );
    connect(btn[passNum], &MyButton::clicked, [=](){
       gs = new gameSence(passNum);  //创建下一个游戏窗口
       gs->show();
       this->hide();
       QSound::play(":/music/button.wav");

       connect(gs, &gameSence::comeBack, [=](){
           this->show();
           //gs->~QObject();
           gs->~gameSence();
           gs = NULL;
       });

       connect(gs, &gameSence::flash, [=](){
           //gs->~QObject();
           gs->~gameSence();
           btn[passNum]->click();
       });

       //通关检测
       connect(gs,&gameSence::pass, this, [=](int num){
           if(num == passNum){
               // 写入目前通过关卡数
               write_passNum();
           }
       });

       connect(gs,&gameSence::win_back,[=](int num){
           if(num == passNum){
               //从新通过的关卡返回
               //gs->~QObject();
               gs->~gameSence();
               emit flash(); //刷新当前界面
           }else{
               this->show();
               //gs->~QObject();
               gs->~gameSence();
               gs = NULL;
           }
       });

       connect(gs, &gameSence::win_next, [=](int num){
           //gs->~QObject();
           gs->~gameSence();
           emit win(num+1);
       });

       connect(gs,&gameSence::win_regame, [=](int num){
           //gs->~QObject();
           gs->~gameSence();
           emit win(num);
       });

    });

    // 打印锁关
    for(int i = passNum + 1; i<35; i++){
        btn[i] = new MyButton(":/image/lock_level.png");
        btn[i]->setParent(this);
        btn[i]->move( (i % 5) * 80 + 50, (i / 5) * 80 + 80 );

    };

}

//为外部实现关卡进入按钮按下
void chooseScene::clickBtn(int num){
    this->btn[num]->click();
}
