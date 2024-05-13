#include "ball.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Border border(50,50,400,500);
    Ball ball(50,50,2,3,&border);

    ball.startMoving();    
    ball.show();



    return a.exec();
}

