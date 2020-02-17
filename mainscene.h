#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "mybutton.h"
#include "choosescene.h"
#include <QMovie>

namespace Ui {
class MainScene;
}

class MainScene : public QWidget
{
    Q_OBJECT
    chooseScene* nextScene;
    QSound * btn_sound;
public:
    explicit MainScene(QWidget *parent = 0);
    ~MainScene();

    void paintEvent(QPaintEvent *event);
private:
    Ui::MainScene *ui;
};

#endif // MAINSCENE_H
