#ifndef BALL_H
#define BALL_H

#include <QApplication>
#include <QWidget>
#include <QTimer>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class Ball; }
QT_END_NAMESPACE

class Border;//前置声明
enum Direction {
    LEFT, RIGHT, TOP, BOTTOM
};//枚举类型


class Ball : public QWidget
{
    Q_OBJECT
public:
    Ball(float ballX, float ballY, float dx, float dy, Border *mborder, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void updateBallPosition() ;//改变小球位置的函数
    void draw(QPainter& painter) const;
    ~Ball();
    void startMoving();//开始运动的函数

private:
    float ballX; // 小球 x 坐标
    float ballY; // 小球 y 坐标
    float dx; // 小球水平方向速度
    float dy; // 小球垂直方向速度
    int r;  //小球半径
    Border *mborder;
    float g; //重力加速度
    float q;//碰撞系数
    int t;//定时器更新时间

    Ui::Ball *ui;    
    QTimer *timer;
};


class Border {
public:
    Border(int rectX , int rectY , int rectWidth , int rectHeight);
    bool checkCollision(float x, float y,int r,Direction direction);
    void draw(QPainter& painter) const;

private:
    int rectX;//矩形框左上角x坐标
    int rectY;//矩形框左上角y坐标
    int rectWidth;//矩形框宽度
    int rectHeight;//矩形框高度

};

#endif // BALL_H
