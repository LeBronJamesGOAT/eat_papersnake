#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <QTimer>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    snake.append(QRectF(200,500,snakeNodeWidth,snakeNodeHeight));
    addTopRectF();
    addTopRectF();
    rewardNode.append(QRectF(100,100,snakeNodeWidth,snakeNodeWidth));
    //rewardTimer->start(time*30);
}

void MainWindow::mousePressEvent (QMouseEvent *event )//????????????
{

    int wi=(event->x()-30)/barrierNodeWidth;
    int wii=wi*barrierNodeWidth+30;
    int he=(event->y()-30)/barrierNodeHeight;
    int hee=he*barrierNodeHeight+30;
    bool paint=true;
    for(int i=0; i<barrier.length(); i++){
        if(barrier.at(i).left()==wii&&barrier.at(i).top()==hee){
            paint=false;
            barrier.removeAt(i);
            break;
        }
    }
    if(paint==true){    barrier.append(QRectF(wii,hee,barrierNodeWidth,barrierNodeHeight));}
    update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    QBrush brush;
    QFont font("方正舒体",12,QFont::ExtraLight,false);

    //反锯齿
    painter.setRenderHint(QPainter::Antialiasing);

    pen.setColor(Qt::black);
    brush.setColor(Qt::black);

    brush.setStyle(Qt::SolidPattern);
    painter.setPen(pen);
    painter.setBrush(brush);

    brush.setColor(Qt::gray);
    painter.setBrush(brush);
    painter.drawRect(QRectF(30,30,840,840));

    brush.setColor(Qt::black);
    painter.setBrush(brush);
    painter.drawRect(QRectF(50,50,800,800));

    brush.setColor(Qt::gray);
    painter.setBrush(brush);
//    painter.drawRect(QRectF(30,30,20,820));
//    painter.drawRect(QRectF(30,850,820,20));
//    painter.drawRect(QRectF(50,30,820,20));
//    painter.drawRect(QRectF(850,50,20,820));
    for(int i=0; i<barrier.length(); i++){
        painter.drawRect(barrier.at(i));
    }

    brush.setColor(Qt::green);
    painter.setBrush(brush);
    for(int i=0; i<snake.length(); i++){
        painter.drawRect(snake.at(i));
    }

    brush.setColor(Qt::red);
    painter.setBrush(brush);
    for(int i=0; i<rewardNode.length(); i++){
        painter.drawEllipse(rewardNode.at(i));
    }



    pen.setColor(Qt::white);
    painter.setPen(pen);
    painter.setFont(font);
    painter.drawText(20,20,QString("当前得分：")+QString("%1").arg(snake.length()));
//    }

    QWidget::paintEvent(event);
}
void MainWindow::addTopRectF()
{
    if(snake.at(0).y()-snakeNodeHeight < 0){
        snake.insert(0,QRectF(QPointF(snake.at(0).x(),this->height()-snakeNodeHeight),
                              QPointF(snake.at(0).x()+snakeNodeWidth,this->height())));
    }else{
        snake.insert(0,QRectF(snake.at(0).topLeft()+QPointF(0,-snakeNodeHeight),snake.at(0).topRight()));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

