#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString butImg);   //代表图片路径

    int posX; //x坐标
    int posY; //y坐标
    bool flag; //正反标志

    void changeFlag();  //改变标志，执行反转效果
    QTimer * timer1; //正面翻反面  定时器
    QTimer * timer2; //反面翻正面  定时器
    int min = 1; //最小图片
    int max = 8; //最大图片

    bool isAnimation = false;  //做翻转动画的标志

    //重写 按下
    void mousePressEvent(QMouseEvent *);

    bool isWin = false; //是否胜利的标志


signals:

public slots:
};

#endif // MYCOIN_H
