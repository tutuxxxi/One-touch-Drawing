#ifndef CHOOSESCENE_H
#define CHOOSESCENE_H


#include "mybutton.h"
#include "gamesence.h"
#include <QFile>
#include <QTextStream>

class chooseScene : public QWidget
{
    Q_OBJECT

    int passNum; //记录过关记录
    MyButton *btn[36];
    gameSence* gs = NULL;
public:
    explicit chooseScene(QWidget *parent = nullptr);
    ~chooseScene();

    void paintEvent(QPaintEvent *event);

    void read_passNum();
    void write_passNum();

    void loadChoose();

    void clickBtn(int num);
signals:
    void comeBack(); //用于标明返回mainsence的信号
    void chooseLevel(int i); //用于关卡选择的信号
    void flash();  //通关后需要重新打印窗口
    void win(int);
public slots:
};

#endif // CHOOSESCENE_H
