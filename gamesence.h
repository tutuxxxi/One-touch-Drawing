#ifndef GAMESENCE_H
#define GAMESENCE_H


#include "mybutton.h"
#include "box.h"
#include <QPainter>
#include <QIcon>
#include <QKeyEvent>
#include <QSound>
#include <QMessageBox>

class gameSence : public QWidget
{
    Q_OBJECT

    int level;  //关卡数

    //模式
    int model = -1;

    int gamemap[35][6][6] = {

        {   //1
            {0,0,0,0,0,0},
            {0,0,2,1,1,0},
            {0,0,0,0,1,0},
            {0,0,0,0,1,0},
            {0,0,1,1,1,0},
            {0,0,0,0,0,0}
        },


        {   //2
            {0,0,0,0,0,0},
            {0,1,1,2,1,1},
            {0,1,0,0,0,1},
            {0,1,0,0,0,1},
            {0,1,1,1,1,1},
            {0,0,0,0,0,0}
        },


        {   //3
            {0,0,0,0,0,0},
            {0,2,1,1,1,1},
            {0,1,1,1,0,1},
            {0,1,0,1,0,1},
            {0,1,1,1,0,1},
            {0,0,0,0,0,0}
        },


        {   //4
            {0,0,0,0,0,0},
            {0,1,1,0,0,1},
            {2,1,1,1,1,1},
            {0,1,1,1,1,0},
            {0,1,1,1,1,0},
            {0,0,0,0,0,0}
        },


        {   //5
            {0,0,0,0,0,0},
            {1,1,1,1,1,2},
            {1,1,1,0,0,0},
            {1,1,1,0,1,0},
            {0,0,1,1,1,0},
            {0,0,0,0,0,0}
        },


        {   //6
            {0,0,0,0,0,0},
            {2,0,0,1,1,1},
            {1,1,1,1,1,1},
            {1,1,1,0,1,0},
            {1,1,1,1,1,0},
            {0,0,0,0,0,0}
        },


        {   //7
            {1,1,1,1,1,1},
            {1,0,1,1,0,1},
            {1,2,1,1,1,1},
            {1,1,1,1,1,1},
            {1,0,1,1,0,1},
            {1,1,1,1,1,1}
        },


        {   //8  15
            {0,1,1,1,0,0},
            {0,1,1,1,1,1},
            {1,2,1,1,1,1},
            {1,0,1,0,0,1},
            {1,1,1,1,1,1},
            {1,1,0,1,1,1}
        },


        {   //9  17
            {0,0,0,1,1,0},
            {1,1,1,1,1,1},
            {1,0,0,0,1,1},
            {1,2,1,0,1,1},
            {1,1,1,0,0,1},
            {0,0,1,1,1,1}
        },


        {   //10  23
            {1,1,1,0,0,0},
            {1,2,1,1,0,0},
            {0,1,1,1,1,1},
            {0,1,1,1,1,1},
            {1,1,1,1,0,0},
            {1,1,1,0,0,0}
        },


        {   //11  24
            {0,0,1,1,0,0},
            {0,0,1,1,0,0},
            {1,2,1,1,1,1},
            {1,1,1,1,1,1},
            {0,0,1,1,0,0},
            {0,0,1,1,0,0}
        },


        {   //12  29
            {1,1,1,1,1,1},
            {1,0,1,1,0,1},
            {2,1,0,0,1,1},
            {1,1,0,0,1,1},
            {1,0,1,1,0,1},
            {1,1,1,1,1,1}
        },


        {   //13  31
            {1,1,1,1,0,0},
            {1,0,0,1,1,1},
            {1,1,1,1,1,1},
            {1,1,2,0,1,1},
            {1,0,1,0,1,1},
            {1,1,1,0,0,0}
        },


        {   //14  32
            {1,1,0,1,1,1},
            {1,1,1,1,1,1},
            {2,1,1,1,1,0},
            {0,0,1,1,1,1},
            {1,1,1,0,0,1},
            {1,1,1,1,1,1}
        },


        {   //15  33
            {0,0,0,1,1,1},
            {2,1,1,1,0,1},
            {0,0,1,1,1,1},
            {1,1,1,0,1,1},
            {1,0,1,0,0,1},
            {1,1,1,1,1,1}
        },


        {   //16  36
            {0,1,1,1,0,0},
            {1,1,0,1,1,1},
            {1,2,1,1,1,1},
            {1,1,1,0,0,1},
            {0,1,1,1,1,1},
            {0,0,0,1,1,0}
        },


        {   //17  38
            {0,1,1,1,0,0},
            {1,1,0,1,1,1},
            {1,1,1,1,0,1},
            {1,1,2,1,0,1},
            {1,1,0,1,1,1},
            {0,0,0,1,1,1}
        },


        {   //18  43
            {0,1,1,0,0,0},
            {0,1,1,1,1,2},
            {0,1,0,1,1,0},
            {0,1,1,1,0,0},
            {0,1,1,1,1,1},
            {0,0,0,1,1,0}
        },


        {   //19  44
            {1,1,1,1,1,0},
            {1,0,1,1,1,0},
            {1,1,1,2,0,0},
            {0,1,1,1,1,0},
            {1,1,1,0,1,1},
            {0,0,1,1,1,1}
        },


        {   //20  47
            {0,1,1,1,1,1},
            {0,1,1,0,0,1},
            {0,0,1,1,0,1},
            {2,1,1,1,1,1},
            {0,0,1,1,0,1},
            {0,0,0,1,1,1}
        },


        {   //21  48
            {0,1,1,1,1,1},
            {1,1,1,1,0,1},
            {1,0,1,1,2,1},
            {1,1,1,1,0,1},
            {0,1,1,1,1,1},
            {0,1,1,0,1,1}
        },


        {   //22  50
            {2,1,0,0,1,1},
            {1,1,0,1,1,1},
            {1,1,1,1,1,1},
            {1,1,1,0,1,1},
            {1,0,0,0,1,1},
            {1,1,1,1,1,1}
        },


        {   //23  53
            {0,1,1,1,1,0},
            {0,1,2,0,1,1},
            {1,1,0,1,1,1},
            {1,1,1,1,1,0},
            {1,0,1,1,1,0},
            {1,1,1,1,0,0}
        },


        {   //24  55
            {0,0,1,1,1,1},
            {0,0,1,0,0,1},
            {1,2,1,1,1,1},
            {1,0,1,1,1,1},
            {1,1,1,0,1,1},
            {0,0,1,1,1,1}
        },


        {   //25  56
            {0,0,1,1,1,0},
            {1,2,1,0,1,0},
            {1,0,1,1,1,1},
            {1,0,1,1,1,1},
            {1,1,1,0,1,0},
            {0,0,1,1,1,0}
        },


        {   //26  57
            {0,1,1,1,1,0},
            {1,1,1,1,1,1},
            {1,1,1,2,1,1},
            {1,0,1,0,1,1},
            {1,1,1,0,1,1},
            {0,1,1,0,0,0}
        },


        {   //27  58
            {0,0,1,1,1,1},
            {0,0,1,1,0,1},
            {1,1,2,1,1,1},
            {1,0,1,1,1,0},
            {1,1,1,1,1,0},
            {0,0,0,1,0,0}
        },


        {   //28  60
            {0,0,0,0,1,1},
            {0,1,1,1,1,1},
            {0,1,0,1,1,0},
            {1,1,2,1,1,0},
            {1,1,1,0,1,1},
            {0,0,1,1,1,1}
        },


        {   //29  61
            {1,1,1,1,1,2},
            {1,1,1,1,1,0},
            {1,1,0,0,1,1},
            {0,1,1,1,1,1},
            {1,1,1,1,0,0},
            {0,0,1,1,0,0}
        },


        {   //30  62
            {0,0,1,1,1,1},
            {0,1,1,0,0,1},
            {0,1,1,1,1,1},
            {0,0,1,0,1,1},
            {0,1,1,2,1,1},
            {0,1,1,1,1,1}
        },


        {   //31  63
            {0,1,1,1,1,1},
            {0,1,1,1,0,1},
            {0,1,1,2,1,1},
            {0,0,1,1,1,1},
            {0,1,0,1,1,1},
            {0,1,1,1,1,1}
        },


        {   //32  64
            {0,1,1,1,1,1},
            {0,1,0,1,0,1},
            {0,1,2,1,1,1},
            {0,1,1,0,1,1},
            {0,1,1,1,1,1},
            {0,1,1,1,1,1}
        },


        {   //33  65
            {0,1,1,1,1,1},
            {0,1,1,0,1,1},
            {0,1,1,1,1,1},
            {0,1,2,1,1,1},
            {0,0,1,1,1,1},
            {0,0,1,1,1,1}
        },


        {   //34  66
            {0,0,1,1,1,0},
            {0,0,1,0,1,1},
            {0,1,1,2,1,1},
            {0,1,0,1,1,1},
            {0,1,1,1,1,1},
            {0,1,1,1,1,0}
        },


        {   //35  67
            {1,1,1,1,1,0},
            {0,1,1,1,1,0},
            {1,1,0,1,1,1},
            {1,1,2,1,1,1},
            {1,1,1,0,1,1},
            {1,1,1,0,1,1}
        }
    };

    // 记录玩家位置
    int cat_x, cat_y;

    // 记录玩家上一步走的方向
    enum direction dir = None;


    int step = 1; //步数记录
    int passStep = 1; //通关需要的步数


    Box* boxes[6][6];  //盒子数组
    int map[6][6]; //后台地图

    //胜利图案与按钮的创建
    QLabel *win_lab;
    MyButton *end_back_btn, *end_next_btn, *end_regame_btn;

    QSound *front, *back;

    void printJudge(enum direction,enum direction, Box*);
    enum direction backJudge(enum direction, Box*);
    void passJudge();
    enum direction prompt();
public:
    gameSence(int level);
    ~gameSence();

    // 绘图事件
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
signals:

    void pass(int); //通关信号
    void comeBack(); //返回信号
    void flash(); //刷新信号

    void win_back(int);
    void win_next(int);
    void win_regame(int);
public slots:
    // 游戏刷新
    void gameFlash(int x, int y);
};

#endif // GAMESENCE_H
