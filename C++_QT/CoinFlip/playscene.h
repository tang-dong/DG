#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);

    PlayScene(int levelNum);

    int levelIndex; //内部成员属性，记录所选关卡

    void paintEvent(QPaintEvent *);

    int gameArray[4][4];  //二维数组，维护每个关卡的具体数据

    MyCoin * coinBtn[4][4]; //金币按钮数组

    bool isWin = true; //是否胜利

signals:
    void chooseSceneBack();
public slots:
};

#endif // PLAYSCENE_H
