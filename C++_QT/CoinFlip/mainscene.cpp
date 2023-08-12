#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPixmap>
#include <QPainter>
#include "mypushbutton.h"
#include "chooselevelscene.h"
#include <QTimer>
#include <QSound> //多媒体模块下的音效头文件

MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //设置固定大小
    this->setFixedSize(320,588);

    //设置应用图片
    this->setWindowIcon(QPixmap(":/icon/Coin0001.png"));

    //设置窗口标题
    this->setWindowTitle("翻金币");

    //点击退出，退出程序
    connect(ui->actionQuit,&QAction::triggered,[=](){
        this->close();
    });

    //准备开始按钮的音效
    QSound * startSound = new QSound(":/icon/TapButtonSound.wav",this);


    //创建开始按钮
    MyPushButton * startBtn = new MyPushButton(":/icon/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    //实例化选择关卡场景
    chooseScene = new ChooseLevelScene;

    //监听点击事件，执行特效
    connect(startBtn,&MyPushButton::clicked,[=](){
        startBtn->zoom1(); //向下跳跃
        startBtn->zoom2(); //向上跳跃

        startSound->play();

        //延时0.5秒后，进入选择场景
        QTimer::singleShot(500,this,[=](){
            this->hide(); //将自身隐藏
            chooseScene->setGeometry(this->geometry());
            chooseScene->show();
        });
    });

    //监听选择场景的返回按钮
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,[=](){
        chooseScene ->hide(); //将选择的关卡场景隐藏掉
        this->setGeometry(chooseScene->geometry());
        this->show(); //重新显示主场景
    });


}

void MainScene::paintEvent(QPaintEvent *)
{
    //创建画家，指定绘画的设备
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/icon/PlayLevelSceneBg.png");
    //绘制背景图  -- 指定拉伸成屏幕的宽度，屏幕的高度
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/icon/Title.png");
    //缩放图片 -- 缩放为原来的一半
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    //绘制标题
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);


}

MainScene::~MainScene()
{
    delete ui;
}
