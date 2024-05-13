#include "ball.h"
#include "ui_ball.h"

Ball::Ball(float ballX, float ballY, float dx, float dy, Border *mborder, QWidget *parent):QWidget(parent){

    ui->setupUi(this);
    this->ballX = ballX;
    this->ballY = ballY;
    this->dx = dx;
    this->dy = dy;
    this->mborder = mborder;
    g = 9.8; // 重力加速度
    q = 0.9; // 碰撞系数
    t = 16; // 假设定时器更新时间为16ms ，使程序以60帧运行
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&Ball::updateBallPosition);
}

Border::Border(int rectX , int rectY , int rectWidth , int rectHeight){
    this->rectX = rectX;
    this->rectY = rectY;
    this->rectWidth = rectWidth;
    this->rectHeight = rectHeight;
}

bool Border::checkCollision(float x, float y,int r, Direction direction) {
        switch (direction) {
        case LEFT:
            return x - r <= rectX;
        case RIGHT:
            return x + r >= rectX + rectWidth;
        case TOP:
            return y - r <= rectY;
        case BOTTOM:
            return y + r >= rectY + rectHeight;
        default:
            return false;
            }
        }

void Ball::startMoving(){
    timer->start(t);
}

void Ball::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event); // 调用基类的paintEvent函数

    QPainter painter(this);
    draw(painter); // 调用draw函数进行绘制
}

void Ball::draw(QPainter& painter) const {
    // 绘制小球
    painter.setBrush(Qt::red);//设置画刷为红色
    painter.drawEllipse(QPointF(ballX, ballY), r, r);
}

void Border::draw(QPainter& painter) const {
    // 绘制矩形框
    painter.drawRect(rectX, rectY, rectWidth, rectHeight);

}

void Ball::updateBallPosition(){

    // 小球的运动
      ballX += dx;
      ballY += dy;

    // 检查小球是否碰撞到矩形框的左边或右边
        if ((dx < 0 && mborder->checkCollision(ballX, ballY, r, LEFT)) ||
            (dx > 0 && mborder->checkCollision(ballX, ballY, r, RIGHT))) {
            // 如果是，改变X方向上的速度
            dx = -dx * q;// 改变水平方向速度方向和大小

        }
        // 检查小球是否碰撞到矩形框的上边或下边（地面）
        if ((dy < 0 && mborder->checkCollision(ballX, ballY, r, TOP)) ||
             (dy > 0 && mborder->checkCollision(ballX, ballY, r, BOTTOM))) {
                // 如果是，改变Y方向上的速度
               dy = -dy * q;//改变竖直方向速度方向和大小
            }
      dy += (g / 1000 * t);//每次更新小球位置时，垂直速度加上重力加速度,单位换算成秒
      update();//重绘窗口
}

Ball::~Ball()//Ball类的析构函数
{}
