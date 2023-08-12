#include "chooselevelscene.h"
#include "mypushbutton.h"
#include <QPainter>
#include <QMenuBar>
#include <QTimer>
#include <QDebug>
#include <QLabel>
#include <QSound>


ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //设置窗口固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/icon/Coin0001.png"));
    //设置标题
    this->setWindowTitle("选择关卡");

    //创建菜单栏
    QMenuBar * bar = this->menuBar();
    this->setMenuBar(bar);
    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");
    //创建按钮菜单项
    QAction * quitAction = startMenu->addAction("退出");

    //点击退出  退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/icon/BackButton.png",":/icon/BackButtonSelected.png");
    backBtn->setParent(this);

    backBtn->move(this->width() - backBtn->width(),this->height() - backBtn->height());

    //添加返回按钮音效
    QSound * backSound = new QSound(":/icon/BackButtonSound.wav",this);

    //返回按钮功能实现
    connect(backBtn,&MyPushButton::clicked,[=](){
        backSound->play();
        //告诉主场景  我返回了，主场景监听ChooseLevelScene返回按钮
        QTimer::singleShot(700,this,[=](){
           this->hide();
           //触发自定义信号，关闭自身，该信号写到signal下做声明
           emit this->chooseSceneBack();
        });
        //qDebug() << "返回按钮！";
    });

    //创建关卡按钮
    for(int i = 0; i < 20; i++)
    {
        MyPushButton * menuBtn = new MyPushButton(":/icon/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25 + (i%4)*70, 130+(i/4)*70);

        //监听每个按钮的点击事件
        connect(menuBtn,&MyPushButton::clicked,[=](){
           QString str = QString("您的选择是第 %1 关").arg(i+1);
           qDebug() << str;

           //进入到游戏场景
           this->hide(); //将选关场景隐藏掉
           this->setGeometry(this->geometry());
           play = new PlayScene(i+1); //创建游戏场景
           play->show(); //显示游戏场景

           //监听
           connect(play,&PlayScene::chooseSceneBack,[=](){
               this->setGeometry(play->geometry());
               this->show();
               delete play;
               play = NULL;
           });

        });

        //按钮上显示的文字
        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(), menuBtn->height());
        label->setText(QString::number(i+1));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter); //设置居中
        label->move(25 + (i%4)*70 , 130 + (i/4)*70);
        // 51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents,true); //鼠标事件穿透

    }

}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/icon/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/icon/Title.png");
    painter.drawPixmap((this->width() - pix.width())*0.5,30,pix.width(),pix.height(),pix);
}
