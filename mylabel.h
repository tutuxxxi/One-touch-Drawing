#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class MyLabel : public QLabel
{
    Q_OBJECT

public:
    explicit MyLabel(QWidget *parent = nullptr);

    void enterEvent(QEvent *event);

signals:

    void enter(); //离开信号
public slots:
};

#endif // MYLABEL_H
