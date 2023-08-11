#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <QPaintEvent>
#include "chooselevelscene.h"

namespace Ui {
class MainScene;
}

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScene(QWidget *parent = nullptr);
    ~MainScene();

    //重写paintEvent事件，画背景图
    void paintEvent(QPaintEvent *);

    ChooseLevelScene * chooseScene = NULL;

private:
    Ui::MainScene *ui;
};

#endif // MAINSCENE_H
