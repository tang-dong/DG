#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QAction>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QPropertyAnimation>
#include "mypushbutton.h"
#include "chooselevelscene.h"
#include "mycoin.h"
#include "dataconfig.h"
#include <QSound>

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int levelNum)
{
    QString str = QString("进入了第 %1 关").arg(levelNum);
    qDebug() << str;
    this->levelIndex = levelNum;

    //初始化游戏场景
    //设置固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/icon/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币");

    //创建菜单栏
    QMenuBar * bar = this->menuBar();
    this->setMenuBar(bar);
    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");
    //创建按钮菜单项
    QAction * quitAction = startMenu->addAction("退出");
    //点击退出，退出游戏
    connect(quitAction,&QAction::triggered,[=](){this->close();});

    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/icon/BackButton.png",":/icon/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(),this->height() - backBtn->height());

    //返回按钮功能实现
    connect(backBtn,&MyPushButton::clicked,[=](){
        QTimer::singleShot(500, this,[=](){
            this->hide();
            //触发自定义信号，关闭自身，该信号写到 signals下做声明
            emit this->chooseSceneBack();
        });
    });

    //显示当前关卡
    QLabel * label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    QString str1 = QString("Leavel: %1").arg(this->levelIndex);
    label->setText(str1);
    label->setGeometry(QRect(30,this->height() - 50,120,50)); //设置位置和大小


    //初始化每个关卡的二维数组
    dataConfig config;
    for (int i = 0;i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    //翻金币音效
    QSound *flipSound = new QSound(":/icon/ConFlipSound.wav",this);
    //胜利按钮音效
    QSound *winSound = new QSound(":/icon/LevelWinSound.wav",this);

    //创建金币背景图片
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            //绘制背景图片
            QLabel * label = new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/icon/BoardNode.png"));
            label->setParent(this);
            label->move(57 + i*50, 200 + j*50);

            //金币对象
//            MyCoin * coin = new MyCoin(":/icon/Coin0001.png");
//            coin->setParent(this);
//            coin->move(59 + i*50, 204 + j*50);
            QString img;
            if(gameArray[i][j] == 1)
            {
                img = ":/icon/Coin0001.png";
            }
            else
            {
                img = ":/icon/Coin0008.png";
            }
            MyCoin * coin = new MyCoin(img);
            coin->setParent(this);
            coin->move(59 + i*50, 204 + j*50);
            coin->posX = i; //记录x坐标
            coin->posY = j; //记录y坐标

            coin->flag = gameArray[i][j];  //记录正反标志

            coinBtn[i][j] = coin;


            //胜利图片显示
            QLabel * winLabel = new QLabel;
            QPixmap tmpPix;
            tmpPix.load(":/icon/LevelCompletedDialogBg.png");
            winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
            winLabel->setPixmap(tmpPix);
            winLabel->setParent(this);
            winLabel->move((this->width() - tmpPix.width())*0.5,-tmpPix.height());


            connect(coin,&MyCoin::clicked,[=](){

                flipSound->play();
                //点击按钮，将所有的按钮都先禁用
                for(int i = 0; i < 4; i++)
                {
                    for(int j = 0; j < 4; j++)
                    {
                        this->coinBtn[i][j]->isWin = true;
                    }
                }

                coin->changeFlag();
                gameArray[i][j] = gameArray[i][j] == 0 ? 1 : 0; //数组内部记录的标志同步修改

                //点击上下左右
                QTimer::singleShot(300,this,[=](){
                    if(coin->posX+1 <= 3)
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        gameArray[coin->posX+1][coin->posY] = gameArray[coin->posX+1][coin->posY] == 0 ? 1 : 0;
                    }

                    if(coin->posX-1 >= 0)
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        gameArray[coin->posX-1][coin->posY] = gameArray[coin->posX-1][coin->posY] == 0 ? 1 : 0;
                    }
                    if(coin->posY+1 <= 3)
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        gameArray[coin->posX][coin->posY+1] = gameArray[coin->posX+1][coin->posY] == 0 ? 1 : 0;
                    }
                    //周围下侧硬币翻转条件
                    if(coin->posY-1 >= 0)
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        gameArray[coin->posX][coin->posY-1] = gameArray[coin->posX+1][coin->posY] == 0 ? 1 : 0;
                    }

                    //翻完周围金币后，将所有金币解开禁用
                    for(int i = 0; i < 4; i++)
                    {
                        for(int j = 0; j < 4; j++)
                        {
                            this->coinBtn[i][j]->isWin = false;
                        }
                    }

                    //判断是否胜利
                    this->isWin = true;
                    for(int i = 0; i < 4; i++)
                    {
                        for(int j = 0; j < 4; j++)
                        {
                            if(coinBtn[i][j]->flag == false)
                            {
                                this->isWin = false;
                                break;
                            }
                        }
                    }

                    if(this->isWin == true)
                    {
                        //胜利了
                        qDebug() << "游戏胜利";
                        //将所有按钮的胜利标志改为true;如果再次点击按钮，直接return，不做响应
                        for(int i = 0; i < 4; i++)
                        {
                            for(int j = 0; j < 4; j++)
                            {
                                coinBtn[i][j]->isWin = true;
                            }
                        }

                        //播放游戏胜利音效
                        winSound->play();

                        QPropertyAnimation * animation1 = new QPropertyAnimation(winLabel,"geometry");
                        animation1->setDuration(1000);
                        animation1->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));

                        animation1->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));

                        animation1->setEasingCurve(QEasingCurve::OutBounce);
                        animation1->start();
                        QTimer::singleShot(800,this,[=](){
                            emit chooseSceneBack(); //需要先提前创建一个选择关卡的界面
                            int nextLeveNum = levelNum + 1;
                            if(nextLeveNum <= 20)
                            {
                                PlayScene * nextLevelScene = new PlayScene(nextLeveNum);
                                nextLevelScene->show();
                                //this->hide();
                            }

                        });
                    }
                });
            });
        }
    }



}

void PlayScene::paintEvent(QPaintEvent *)
{
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/icon/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/icon/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap( 10,30,pix.width(),pix.height(),pix);
}
