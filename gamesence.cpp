#include "gamesence.h"


gameSence::gameSence(int level){
    this->level = level;

    //窗口设置
    setFixedSize(500,800); //固定大小
    setWindowTitle("aaa");// 标题
    QIcon a(":/image/icon.png");
    setWindowIcon(a);// 图标



    // 动物前进后退音效
    front = new QSound(":/music/front.wav",this);
    back = new QSound(":/music/back.wav", this);




    //返回按钮实现
    MyButton* back_btn = new MyButton(":/image/exit.png");
    back_btn->setParent(this);//放置按钮
    back_btn->move( 0, this->height() * 0.9 );
    connect(back_btn,&MyButton::clicked,[=](){
        QSound::play(":/music/button.wav");
        emit comeBack();
    });




    //重新开始游戏按钮实现
    MyButton* regame_btn = new MyButton(":/image/restart.png");
    regame_btn->setParent(this);//放置按钮
    regame_btn->move( 391, this->height() * 0.9 );
    connect(regame_btn,&MyButton::clicked,[=](){
        emit flash();
    });



    //模式切换按钮
    MyButton *test = new MyButton(":/image/change_model.png");
    test->setParent(this);
    test->move( 0, this->height() * 0.05 );
    connect(test, &QPushButton::clicked, [=](){
        this->model++;
        if(model == 2)
            model = -1;

        switch(model){
        case -1:
            test->change(":/image/change_model.png");
            break;
        case 0:
            test->change(":/image/change_model1.png");
            break;
        case 1:
            test->change(":/image/change_model2.png");
            break;
        }
    });



    // 通过地图控制地图上36个盒子的创建
    for(int i= 0; i<6; i++){
        for(int j = 0; j<6; j++){

            //修改 -1为不可走 0为未走 1为猫位置（第一步）
            map[i][j] = this->gamemap[level][i][j] - 1;

            switch(map[i][j]){
            case -1:
                break;
            case 0:
                boxes[i][j] = new Box(i,j,this);
                connect(boxes[i][j], &Box::enter, this, &gameSence::gameFlash);
                passStep++;
                break;
            case 1:
                boxes[i][j] = new Box(i,j,this, Cat);
                connect(boxes[i][j], &Box::enter, this, &gameSence::gameFlash);
                cat_x = i;
                cat_y = j;
                break;
            }
        }
    }



    //提示按钮实现
    MyButton* prompt_btn = new MyButton(":/image/prompt.png");
    prompt_btn->setParent(this);//放置按钮
    prompt_btn->move( 391, this->height() * 0.05 );

    connect(prompt_btn,&MyButton::clicked,[=](){
        QSound::play(":/music/button.wav");

        switch(prompt()){
        case None:

            switch(dir){

            case Upward:
                boxes[cat_x][cat_y + 1]->prompt(Downward);
                break;
            case Right:
                boxes[cat_x - 1][cat_y]->prompt(Left);
                break;
            case Downward:
                boxes[cat_x][cat_y - 1]->prompt(Upward);
                break;
            case Left:
                boxes[cat_x + 1][cat_y]->prompt(Right);
                break;
            default:
                break;
            }

            break;
        case Upward:
            boxes[cat_x][cat_y - 1]->prompt(Upward);
            break;
        case Right:
            boxes[cat_x + 1][cat_y]->prompt(Right);
            break;
        case Downward:
            boxes[cat_x][cat_y + 1]->prompt(Downward);
            break;
        case Left:
            boxes[cat_x - 1][cat_y]->prompt(Left);
            break;
        }


    });



    //游戏胜利图案的创建
    win_lab = new QLabel();
    win_lab->setParent(this);
    QPixmap pix(":/image/win.png");
    win_lab->setFixedSize(pix.size());
    win_lab->setPixmap(pix);
    win_lab->move( 78,  -pix.height());



    //游戏胜利的三个按钮的创建
    end_back_btn = new MyButton(":/image/win_back.png");
    end_next_btn = new MyButton(":/image/win_next.png");
    end_regame_btn = new MyButton(":/image/win_regame.png");

    end_back_btn->setParent(this);
    end_next_btn->setParent(this);
    end_regame_btn->setParent(this);

    end_back_btn->move(this->width()*0.3, -100);
    end_next_btn->move(this->width()*0.5, -100);
    end_regame_btn->move(this->width()*0.7, -100);

    connect(end_back_btn, &MyButton::clicked,[=](){
        QSound::play(":/music/button.wav");
        emit win_back(this->level);
    });

    connect(end_next_btn, &MyButton::clicked,[=](){
        QSound::play(":/music/button.wav");
        emit win_next(this->level);
    });

    connect(end_regame_btn, &MyButton::clicked,[=](){
        QSound::play(":/music/button.wav");
        emit win_regame(this->level);
    });


    this->grabKeyboard();



}


gameSence::~gameSence(){

}


//鼠标控制游戏
void gameSence::gameFlash(int x, int y){

    if(this->model == 0)
        return;

    //移入玩家下一个格子
    if(x == cat_x && y == cat_y + 1){
        if(this->dir == Upward){
            // 上一步正好是向上

            // 修改当前位置图片
            boxes[cat_x][cat_y]->clear();
            boxes[cat_x][cat_y]->set(Box_);
            boxes[cat_x][cat_y]->show();

            map[cat_x][cat_y++] = 0; //当前位置变为可走位置并移动猫位置

            step--; //步数修改

            //修改上一步格子的图片， 并记录上上次的移动方向
            dir = backJudge(Downward, boxes[cat_x][cat_y]);

            back->play();

        }else if(map[x][y] == 0){
            //移入的格子为可移动格子

            //修改当前格子的图片
            printJudge(dir, Downward, boxes[cat_x][cat_y]);

            //修改位置
            map[cat_x][++cat_y] = ++step;

            //记录方向
            dir = Downward;

            //修改移入的方块的图片
            boxes[cat_x][cat_y]->clear();
            boxes[cat_x][cat_y]->set(Pass_cat_down);
            boxes[cat_x][cat_y]->show();

            //播放音效
            front->play();

            //胜利判断
            this->passJudge();
        }

    }
    // 移入玩家上一个格子
    else if(x == cat_x && y == cat_y - 1){
        if(this->dir == Downward){
            // 上一步正好是向下

            // 修改当前位置图片
            boxes[cat_x][cat_y]->clear();
            boxes[cat_x][cat_y]->set(Box_);
            boxes[cat_x][cat_y]->show();

            map[cat_x][cat_y--] = 0; //当前位置变为可走位置并移动猫位置

            //修改上一步格子的图片， 并记录上上次的移动方向
            dir = backJudge(Upward, boxes[cat_x][cat_y]);

            step--;

            back->play();
        }else if(map[x][y] == 0){
            //移入的格子为可移动格子

            //修改当前格子的图片
            printJudge(dir, Upward, boxes[cat_x][cat_y]);

            //修改位置
            map[cat_x][--cat_y] = ++step;

            //记录方向
            dir = Upward;

            //修改移入的方块的图片
            boxes[cat_x][cat_y]->clear();
            boxes[cat_x][cat_y]->set(Pass_cat_up);
            boxes[cat_x][cat_y]->show();

            //播放音效
            front->play();

            //胜利判断
            this->passJudge();
        }

    }
    // 移入玩家右一个格子
    else if(x == cat_x + 1 && y == cat_y){
        if(this->dir == Left){
            // 上一步正好是向左

            // 修改当前位置图片
            boxes[cat_x][cat_y]->clear();
            boxes[cat_x][cat_y]->set(Box_);
            boxes[cat_x][cat_y]->show();

            map[cat_x++][cat_y] = 0; //当前位置变为可走位置并移动猫位置

            //修改上一步格子的图片， 并记录上上次的移动方向
            dir = backJudge(Right, boxes[cat_x][cat_y]);

            step--;

            back->play();
        }else if(map[x][y] == 0){
            //移入的格子为可移动格子

            //修改当前格子的图片
            printJudge(dir, Right, boxes[cat_x][cat_y]);

            //修改位置
            map[++cat_x][cat_y] = ++step;

            //记录方向
            dir = Right;

            //修改移入的方块的图片
            boxes[cat_x][cat_y]->clear();
            boxes[cat_x][cat_y]->set(Pass_cat_right);
            boxes[cat_x][cat_y]->show();

            //播放音效
            front->play();

            //胜利判断
            this->passJudge();
        }

    }
    // 移入玩家左一个格子
    else if(x == cat_x - 1 && y == cat_y){
        if(this->dir == Right){
            // 上一步正好是向右

            // 修改当前位置图片
            boxes[cat_x][cat_y]->clear();
            boxes[cat_x][cat_y]->set(Box_);
            boxes[cat_x][cat_y]->show();

            map[cat_x--][cat_y] = 0; //当前位置变为可走位置并移动猫位置

            //修改上一步格子的图片， 并记录上上次的移动方向
            dir = backJudge(Left, boxes[cat_x][cat_y]);

            step--;

            back->play();
        }else if(map[x][y] == 0){
            //移入的格子为可移动格子

            //修改当前格子的图片
            printJudge(dir, Left, boxes[cat_x][cat_y]);

            //修改位置
            map[--cat_x][cat_y] = ++step;

            //记录方向
            dir = Left;

            //修改移入的方块的图片
            boxes[cat_x][cat_y]->clear();
            boxes[cat_x][cat_y]->set(Pass_cat_left);
            boxes[cat_x][cat_y]->show();

            //播放音效
            front->play();

            //胜利判断
            this->passJudge();
        }

    }
}

//键盘控制游戏
void gameSence::keyPressEvent(QKeyEvent *event){
    if(this->model == 1)
        return;

    if(event->key() == Qt::Key_Up){
        if(cat_y != 0){
            switch(map[cat_x][cat_y - 1]){
            case -1:  //上一个不能走
                break;
            case 0:  //上一个可以走
                //移入的格子为可移动格子

                //修改当前格子的图片
                printJudge(dir, Upward, boxes[cat_x][cat_y]);

                //修改位置
                map[cat_x][--cat_y] = ++step;

                //记录方向
                dir = Upward;

                //修改移入的方块的图片
                boxes[cat_x][cat_y]->clear();
                boxes[cat_x][cat_y]->set(Pass_cat_up);
                boxes[cat_x][cat_y]->show();

                //播放音效
                front->play();

                //胜利判断
                this->passJudge();

                break;
            default: //上一个已经走过
                if(dir == Downward){

                    // 修改当前位置图片
                    boxes[cat_x][cat_y]->clear();
                    boxes[cat_x][cat_y]->set(Box_);
                    boxes[cat_x][cat_y]->show();

                    map[cat_x][cat_y--] = 0; //当前位置变为可走位置并移动猫位置

                    //修改上一步格子的图片， 并记录上上次的移动方向
                    dir = backJudge(Upward, boxes[cat_x][cat_y]);

                    step--;

                    back->play();

                }
                break;
            }

        }

    }else if(event->key() == Qt::Key_Right){
        if(cat_x != 5){
            switch(map[cat_x + 1][cat_y]){
            case -1:
                break;
            case 0:
                //移入的格子为可移动格子

                //修改当前格子的图片
                printJudge(dir, Right, boxes[cat_x][cat_y]);

                //修改位置
                map[++cat_x][cat_y] = ++step;

                //记录方向
                dir = Right;

                //修改移入的方块的图片
                boxes[cat_x][cat_y]->clear();
                boxes[cat_x][cat_y]->set(Pass_cat_right);
                boxes[cat_x][cat_y]->show();

                //播放音效
                front->play();

                //胜利判断
                this->passJudge();
            default:
                if(dir == Left){
                    // 上一步正好是向左

                    // 修改当前位置图片
                    boxes[cat_x][cat_y]->clear();
                    boxes[cat_x][cat_y]->set(Box_);
                    boxes[cat_x][cat_y]->show();

                    map[cat_x++][cat_y] = 0; //当前位置变为可走位置并移动猫位置

                    //修改上一步格子的图片， 并记录上上次的移动方向
                    dir = backJudge(Right, boxes[cat_x][cat_y]);

                    step--;

                    back->play();
                }

                break;
            }
        }
    }else if(event->key() == Qt::Key_Down){
        if(cat_y != 5){
            switch(map[cat_x][cat_y + 1]){
            case -1:
                break;
            case 0:
                //移入的格子为可移动格子

                //修改当前格子的图片
                printJudge(dir, Downward, boxes[cat_x][cat_y]);

                //修改位置
                map[cat_x][++cat_y] = ++step;

                //记录方向
                dir = Downward;

                //修改移入的方块的图片
                boxes[cat_x][cat_y]->clear();
                boxes[cat_x][cat_y]->set(Pass_cat_down);
                boxes[cat_x][cat_y]->show();

                //播放音效
                front->play();

                //胜利判断
                this->passJudge();

                break;
            default:
                if(dir == Upward){
                    // 上一步正好是向上

                    // 修改当前位置图片
                    boxes[cat_x][cat_y]->clear();
                    boxes[cat_x][cat_y]->set(Box_);
                    boxes[cat_x][cat_y]->show();

                    map[cat_x][cat_y++] = 0; //当前位置变为可走位置并移动猫位置

                    step--; //步数修改

                    //修改上一步格子的图片， 并记录上上次的移动方向
                    dir = backJudge(Downward, boxes[cat_x][cat_y]);

                    back->play();
                }

                break;
            }
        }

    }else if(event->key() == Qt::Key_Left){
        if(cat_x != 0){
            switch(map[cat_x - 1][cat_y]){
            case -1:
                break;
            case 0:
                //移入的格子为可移动格子

                //修改当前格子的图片
                printJudge(dir, Left, boxes[cat_x][cat_y]);

                //修改位置
                map[--cat_x][cat_y] = ++step;

                //记录方向
                dir = Left;

                //修改移入的方块的图片
                boxes[cat_x][cat_y]->clear();
                boxes[cat_x][cat_y]->set(Pass_cat_left);
                boxes[cat_x][cat_y]->show();

                //播放音效
                front->play();

                //胜利判断
                this->passJudge();

                break;
            default:
                if(dir == Right){
                    // 上一步正好是向右

                    // 修改当前位置图片
                    boxes[cat_x][cat_y]->clear();
                    boxes[cat_x][cat_y]->set(Box_);
                    boxes[cat_x][cat_y]->show();

                    map[cat_x--][cat_y] = 0; //当前位置变为可走位置并移动猫位置

                    //修改上一步格子的图片， 并记录上上次的移动方向
                    dir = backJudge(Left, boxes[cat_x][cat_y]);

                    step--;

                    back->play();
                }


                break;
            }
        }
    }
}


//绘图事件
void gameSence::paintEvent(QPaintEvent *){
    QPainter painter(this);

    QPixmap pix(":/iamge/background.png");

    painter.drawPixmap(0,0,pix);

}

//通关判断
void gameSence::passJudge(){
    if(step == passStep){//通关判断
        this->releaseKeyboard();
        // 传递通关信息
        emit pass(level);
        QSound::play(":/music/win.wav");

        win_lab->move( 78,  200);

        end_back_btn->move(105, 460);
        end_next_btn->move(215, 460);
        end_regame_btn->move(325, 460);

    }
}


// 通过传入前后方向为Box判断应该使用的图片
void gameSence::printJudge(enum direction before,enum direction after, Box* box){
    box->clear();
    switch(before){
    case None:
        switch(after){
        case Upward:
            box->set(Pass_box_up);
            break;
        case Downward:
            box->set(Pass_box_down);
            break;
        case Left:
            box->set(Pass_box_left);
            break;
        case Right:
            box->set(Pass_box_right);
            break;
        default:
            break;
        }
        break;
    case Upward:
        switch(after){
        case Upward:
            box->set(Pass_box_up_down);
            break;
        case Left:
            box->set(Pass_box_down_left);
            break;
        case Right:
            box->set(Pass_box_down_right);
            break;
        default:
            break;
        }
        break;
    case Downward:
        switch(after){
        case Downward:
            box->set(Pass_box_up_down);
            break;
        case Left:
            box->set(Pass_box_up_left);
            break;
        case Right:
            box->set(Pass_box_up_right);
            break;
        default:
            break;
        }
        break;
    case Left:
        switch(after){
        case Upward:
            box->set(Pass_box_up_right);
            break;
        case Downward:
            box->set(Pass_box_down_right);
            break;
        case Left:
            box->set(Pass_box_left_right);
            break;
        default:
            break;
        }
        break;
    case Right:
        switch(after){
        case Upward:
            box->set(Pass_box_up_left);
            break;
        case Downward:
            box->set(Pass_box_down_left);
            break;
        case Right:
            box->set(Pass_box_left_right);
            break;
        default:
            break;
        }
        break;
    }
    box->show();
}

// 判断并执行返回情况 并返回上上步走到上一步的方向
enum direction gameSence::backJudge(enum direction back, Box* box){
    box->clear();
    enum direction d;

    switch(back){
    case Upward:
        switch(box->whichPic()){
        case Pass_box_down_left:
            box->set(Pass_cat_right);
            d = Right;
            break;
        case Pass_box_down_right:
            box->set(Pass_cat_left);
            d = Left;
            break;
        case Pass_box_up_down:
            box->set(Pass_cat_down);
            d = Downward;
            break;
        case Pass_box_down:
            box->set(Cat);
            d = None;
            break;
        default:
            break;
        }

        break;
    case Downward:
        switch(box->whichPic()){
        case Pass_box_up_left:
            box->set(Pass_cat_right);
            d = Right;
            break;
        case Pass_box_up_right:
            box->set(Pass_cat_left);
            d = Left;
            break;
        case Pass_box_up_down:
            box->set(Pass_cat_up);
            d = Upward;
            break;
        case Pass_box_up:
            box->set(Cat);
            d = None;
            break;
        default:
            break;
        }

        break;
    case Left:
        switch(box->whichPic()){
        case Pass_box_down_right:
            box->set(Pass_cat_up);
            d = Upward;
            break;
        case Pass_box_up_right:
            box->set(Pass_cat_down);
            d = Downward;
            break;
        case Pass_box_left_right:
            box->set(Pass_cat_right);
            d = Right;
            break;
        case Pass_box_right:
            box->set(Cat);
            d = None;
            break;
        default:
            break;
        }

        break;
    case Right:
        switch(box->whichPic()){
        case Pass_box_down_left:
            box->set(Pass_cat_up);
            d = Upward;
            break;
        case Pass_box_up_left:
            box->set(Pass_cat_down);
            d = Downward;
            break;
        case Pass_box_left_right:
            box->set(Pass_cat_left);
            d = Left;
            break;
        case Pass_box_left:
            box->set(Cat);
            d = None;
            break;
        default:
            break;
        }

        break;
    default:
        break;
    }
    box->show();
    return d;
}


bool DFS(int map[6][6], int ways[2][36], int& top ,int& step){
    //方向数组
    int dirc[4][2] = {
        {0 , -1},
        {1 , 0},
        {0 , 1},
        {-1, 0}
    };


    for(int i = 0; i < 4; i++){
        if(  (ways[0][top-1] + dirc[i][0] < 6)
             && (ways[0][top-1] + dirc[i][0] >= 0)
             && (ways[1][top-1] + dirc[i][1] < 6)
             && (ways[1][top-1] + dirc[i][1] >= 0)
             && (map[ ways[0][top-1] + dirc[i][0] ][ ways[1][top-1] + dirc[i][1] ] == 0) ){
            // 此方位可以移动
            step--;// 步数改变

            //路径入队列
            ways[0][top] = ways[0][top-1] + dirc[i][0];
            ways[1][top] = ways[1][top-1] + dirc[i][1];

            map[ ways[0][top] ][ ways[1][top] ] = 1; //修改地图

            top++;

            // 移动到最后一步
            if(step == 0){
                return true;
            }else{
                if(DFS(map, ways, top, step)){
                    return true; //如果继续进行搜索出结果，则输出
                }//继续搜索不出结果，则返回
            }
        }
    }

    // 四个方向都是行走过的，且没有找到出口
    // 算法返回
    step++;
    top--;
    map[ ways[0][top] ][ ways[1][top] ] = 0;
    return false;
}

// 利用深度优先搜索进行游戏提示的实现
enum direction gameSence::prompt(){
    //获得还需要移动的步数
    int pstep = passStep-step;
    //复制当前地图
    int pmap[6][6];
    for(int i = 0; i < 6; i++){
        for(int j = 0; j< 6; j++)
            pmap[i][j] = map[i][j];
    }

    //路径栈 用于储存路径的x值y值
    int ways[2][36];
    //队列底索引
    int base = 0;
    int top = base + 1;

    //初始化第一个位置
    ways[0][base] = cat_x;
    ways[1][base] = cat_y;



    if(DFS(pmap, ways, top, pstep)){
        if(ways[0][base] == ways[0][base+1]){
            if(ways[1][base + 1] == ways[1][base] + 1){
                // 向下
                return Downward;
            }else{
                // 向上
                return Upward;
            }

        }else{
            if(ways[0][base + 1] == ways[0][base] + 1){
                // 向右
                return Right;
            }else{
                // 向左
                return Left;
            }

        }
    }else{
        return None;
    }

}


