#include "mainscene.h"
#include "ui_mainscene.h"


MainScene::MainScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);

    btn_sound = new QSound(":/music/button.wav", this);

    setFixedSize(500,800); //固定大小
    setWindowTitle("aaa");// 标题
    QIcon a(":/image/icon.png");
    setWindowIcon(a);// 图标

    QLabel *l = new QLabel();
    l->setParent(this);
    QMovie *movie = new QMovie(":/image/main.GIF");
    l->setMovie(movie);
    l->move(177, 600);
    movie->start();
    l->show();


    MyButton* main_btn = new MyButton( ":/image/btn.png"); //创建主界面按钮
    main_btn->setParent(this);//放置按钮
    main_btn->move( (this->width() - main_btn->width())/2, this->height() * 0.58 );

    // 实现开始游戏按钮的功能
    connect(main_btn, &MyButton::clicked, [=](){
        this->nextScene = new chooseScene();
        this->nextScene->show();// 显示下一窗口
        this->hide(); //隐藏本窗口
        btn_sound->play();

        // 监听使chooseSence返回按钮功能实现
        connect(nextScene, &chooseScene::comeBack, [=](){
            this->show(); //显示本窗口
            this->nextScene->hide(); //隐藏chooseSence
        });

        connect(nextScene, &chooseScene::flash, [=](){
            //nextScene->~QObject();
            nextScene->~chooseScene();
            nextScene = NULL;
            main_btn->clicked();
        });

        connect(nextScene, &chooseScene::win, [=](int num){
            //nextScene->~QObject();
            nextScene->~chooseScene();
            nextScene = NULL;
            main_btn->clicked();
            nextScene->clickBtn(num);
        });

    });


}

// 绘图事件
void MainScene::paintEvent(QPaintEvent *){
    QPainter painter(this);

    QPixmap pix(":/image/mainMenu.png");
    painter.drawPixmap(0,0,pix);
}

MainScene::~MainScene()
{
    delete ui;
}
