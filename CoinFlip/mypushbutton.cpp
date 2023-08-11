#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QPushButton>

//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{

//}

MyPushButton::MyPushButton(QString normalImg,QString pressImg)
{
    //成员变量normalImgPath保存正常显示图片路径
    normalImgPath = normalImg;
    //成员变量pressedImgPath保存按下后显示的图片
    pressedImgPath = pressImg;
    //创建QPixmap对象
    QPixmap pixmap;
    //判断是否能够加载正常显示的图片，若不能提示加载失败
    bool ret = pixmap.load(normalImgPath);
    if(!ret)
    {
      qDebug() << normalImg << "加载图片失败!";
    }
    //设置图片的固定尺寸
    this->setFixedSize( pixmap.width(), pixmap.height() );
    //设置不规则图片的样式表
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pixmap);
    //设置图标大小
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
}

//向下跳跃
void MyPushButton::zoom1()
{
    //创建动画对象
    QPropertyAnimation * animation1 = new QPropertyAnimation(this,"geometry");
    //设置时间间隔，单位毫秒
    animation1->setDuration(200);
    //创建起始位置
    animation1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //创建结束位置
    animation1->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置缓和曲线，QEasingCurve::OutBounce为弹跳效果
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    animation1->start();
}
//向上跳跃
void MyPushButton::zoom2()
{
    //创建动画对象
    QPropertyAnimation * animation1 = new QPropertyAnimation(this,"geometry");
    //设置时间间隔，单位毫秒
    animation1->setDuration(200);
    //创建起始位置
    animation1->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //创建结束位置
    animation1->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置缓和曲线，QEasingCurve::OutBounce为弹跳效果
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    animation1->start();
}

//鼠标事件
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(pressedImgPath != "")
    {
        QPixmap pixmap;
        bool ret = pixmap.load(pressedImgPath);
        if(!ret)
        {
            qDebug() << pressedImgPath << "加载图片失败！";
        }

        this->setFixedSize(pixmap.width(),pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    }

    //交给父类执行按下事件
    return QPushButton::mousePressEvent(e);
}
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(normalImgPath != "") //选中路径不为空，显示选中图片
    {
      QPixmap pixmap;
      bool ret = pixmap.load(normalImgPath);
      if(!ret)
      {
        qDebug() << normalImgPath << "加载图片失败!";
      }
      this->setFixedSize( pixmap.width(), pixmap.height() );
      this->setStyleSheet("QPushButton{border:0px;}");
      this->setIcon(pixmap);
      this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    }
    //交给父类执行 释放事件
    return QPushButton::mouseReleaseEvent(e);
}
