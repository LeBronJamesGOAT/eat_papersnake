#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QToolBar>
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include<QJsonObject>
#include<QJsonArray>
#include<QJsonDocument>
#include <QDir>
#include<QTextCodec>
#include<QInputDialog>
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include<windows.h>
#include <QPixmap>


static QTime ttime;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    setFocusPolicy(Qt::StrongFocus);
    QFont font ( "Microsoft YaHei", 20, 75);
    ui->label_2->setFont(font);ui->label_3->setFont(font);
    snake.append(QRectF(210,510,snakeNodeWidth,snakeNodeHeight));
    addTopRectF();
//    rewardNode.append(QRectF(110,110,snakeNodeWidth,snakeNodeWidth));
    //rewardTimer->start(time*30);


//    QToolBar *toolBar = addToolBar("ToolBar");
//    toolBar->addAction("pNew""");


    toolBar = new QToolBar(this);
    addToolBar(Qt::BottomToolBarArea,toolBar);
    beginAction = new QAction(tr("&BEGIN"),this);
    pauseAction = new QAction(tr("&PAUSE"),this);
    continueAction = new QAction(tr("&CONTINUE"),this);
    restartAction = new QAction(tr("&RESTART"),this);
    quitAction = new QAction(tr("&QUIT"),this);
    saveAction = new QAction(tr("&SAVE"),this);
    loadAction = new QAction(tr("&LAOD"),this);
    beginAction->setIcon(QIcon("./start.png"));
    pauseAction->setIcon(QIcon("./pause.png"));
    continueAction->setIcon(QIcon("./continue.png"));
    restartAction->setIcon(QIcon("./restart.png"));
    quitAction->setIcon(QIcon("./quit.png"));
    saveAction->setIcon(QIcon("./save.png"));
    loadAction->setIcon(QIcon("./load.png"));


    toolBar->addAction(beginAction);
    toolBar->addAction(pauseAction);
    toolBar->addAction(continueAction);
    toolBar->addAction(restartAction);
    toolBar->addAction(quitAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(loadAction);



    connect(beginAction,SIGNAL(triggered()),this,SLOT(on_actionBEGIN_triggered()));
    connect(pauseAction,SIGNAL(triggered()),this,SLOT(on_actionPAUSE_triggered()));
    connect(continueAction,SIGNAL(triggered()),this,SLOT(on_actionCONTINUE_triggered()));
    connect(restartAction,SIGNAL(triggered()),this,SLOT(on_actionRESTART_2_triggered()));
    connect(quitAction,SIGNAL(triggered()),this,SLOT(on_actionQUIT_2_triggered()));
    connect(saveAction,SIGNAL(triggered()),this,SLOT(on_actionSAVE_triggered()));
    connect(loadAction,SIGNAL(triggered()),this,SLOT(on_actionLOAD_triggered()));

set_state("not_begin");

    timer = new QTimer;

   connect(timer, SIGNAL(timeout()),this,SLOT(timeOut()));

}

void MainWindow::set_state(QString str){
    if(str=="not_begin"){
        state=not_begin;
        dir=Up;
        steps=-1;
        points=0;
        t_last=0;
        t_now=0;
        to_grow=0;
        speed=500;
        need_move=0;
        gameOver = true;
        gameStart = false;
        ui->actionPAUSE->setEnabled(false);
        ui->actionCONTINUE->setEnabled(false);
        ui->actionRESTART_2->setEnabled(false);
        ui->actionSAVE->setEnabled(false);
        ui->actionBEGIN->setEnabled(true);
        ui->actionQUIT_2->setEnabled(true);
        ui->actionLOAD->setEnabled(true);

        pauseAction->setEnabled(false);
        continueAction->setEnabled(false);
        restartAction->setEnabled(false);
        saveAction->setEnabled(false);
        beginAction->setEnabled(true);
        quitAction->setEnabled(true);
        loadAction->setEnabled(true);

        //1 begin
        //2 continue
        //3 quit
        //4 restart
        //5 pause
        //6 load
        //7 save
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
        ui->pushButton_7->setEnabled(false);
        ui->pushButton->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_6->setEnabled(true);


    }

    if(str=="running"){

        ui->actionCONTINUE->setEnabled(false);
        ui->actionRESTART_2->setEnabled(false);
        ui->actionSAVE->setEnabled(false);
        ui->actionBEGIN->setEnabled(false);
        ui->actionLOAD->setEnabled(false);
        ui->actionQUIT_2->setEnabled(true);
        ui->actionPAUSE->setEnabled(true);


        continueAction->setEnabled(false);
        restartAction->setEnabled(false);
        saveAction->setEnabled(false);
        beginAction->setEnabled(false);
        loadAction->setEnabled(false);
        pauseAction->setEnabled(true);
        quitAction->setEnabled(true);

        //1 begin
        //2 continue
        //3 quit
        //4 restart
        //5 pause
        //6 load
        //7 save
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_7->setEnabled(false);
        ui->pushButton->setEnabled(false);
        ui->pushButton_6->setEnabled(false);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
    }
    if(str=="pause"){



        ui->actionPAUSE->setEnabled(false);
        ui->actionBEGIN->setEnabled(false);
        ui->actionLOAD->setEnabled(false);
        ui->actionSAVE->setEnabled(true);
        ui->actionRESTART_2->setEnabled(true);
        ui->actionQUIT_2->setEnabled(true);
        ui->actionCONTINUE->setEnabled(true);


        pauseAction->setEnabled(false);
        beginAction->setEnabled(false);
        loadAction->setEnabled(false);
        continueAction->setEnabled(true);
        restartAction->setEnabled(true);
        saveAction->setEnabled(true);
        quitAction->setEnabled(true);

        //1 begin
        //2 continue
        //3 quit
        //4 restart
        //5 pause
        //6 load
        //7 save
        ui->pushButton_5->setEnabled(false);
        ui->pushButton_7->setEnabled(true);
        ui->pushButton_6->setEnabled(false);
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
        ui->pushButton->setEnabled(false);
        ui->pushButton_3->setEnabled(true);

    }
    if(str=="end"){



        ui->actionPAUSE->setEnabled(false);
        ui->actionBEGIN->setEnabled(false);
        ui->actionLOAD->setEnabled(false);
        ui->actionSAVE->setEnabled(false);
        ui->actionRESTART_2->setEnabled(true);
        ui->actionQUIT_2->setEnabled(true);
        ui->actionCONTINUE->setEnabled(false);


        pauseAction->setEnabled(false);
        beginAction->setEnabled(false);
        loadAction->setEnabled(false);
        continueAction->setEnabled(false);
        restartAction->setEnabled(true);
        saveAction->setEnabled(false);
        quitAction->setEnabled(true);

        //1 begin
        //2 continue
        //3 quit
        //4 restart
        //5 pause
        //6 load
        //7 save
        ui->pushButton_5->setEnabled(false);
        ui->pushButton_7->setEnabled(false);
        ui->pushButton_6->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_4->setEnabled(true);
        ui->pushButton->setEnabled(false);
        ui->pushButton_3->setEnabled(true);
        QMessageBox::information(this, QString::fromLocal8Bit("GG"),QString::fromLocal8Bit("STRIKE!!!"));


    }
}

void MainWindow::setreward()
{
    int a=getRandom(),b=getRandom();
    while(1){
        //检测是否实在蛇身上
        bool if_on=false;
        for(int i=0;i<snake.length();++i){
            if(b==snake.at(i).top()&&a==snake.at(i).left()){
                if_on=true;
                break;
            }
        }
        for(int i=0;i<barrier.length();++i){
            if(b==barrier.at(i).top()&&a==barrier.at(i).left()){
                if_on=true;
                break;
            }
        }
        if(!if_on)break;
    }


    reward=QRectF(a,b,snakeNodeWidth,snakeNodeWidth);
}



void MainWindow::timeOut()
{
//    for(int i=0; i<rewardNode.length(); i++){
//        if(rewardNode.at(i).contains(snake.at(0).topLeft()+QPointF(snakeNodeWidth/2,snakeNodeHeight/2))){
//            flage++;//正常奖励
//            rewardNode.removeAt(i);
//            break;
//        }
//    }
    if((gameStart==true&&state==runing)){
        Sleep(1000/speed);
        if(snake.at(0)==reward){points++;to_grow+=3;setreward();}
        if(to_grow==0){
            switch (dir) {
            case Up:
                addTopRectF();
                break;
            case Down:
                addDownRectF();
                break;
            case Right:
                addRightRectF();
                break;
            case Left:
                addLeftRectF();
                break;
            default:
                break;
            }
             if(gameStart==true&&state==runing){
        deleteLastRectF();}


        update();

        }
        else{
            to_grow--;
            switch (dir) {
            case Up:
                addTopRectF();
                break;
            case Down:
                addDownRectF();
                break;
            case Right:
                addRightRectF();
                break;
            case Left:
                addLeftRectF();
                break;
            default:
                break;
            }

        update();
        }
    }



}

void MainWindow::mousePressEvent (QMouseEvent *event )//????????????
{
    if(state==not_begin){
        int wi=(event->x()-30)/barrierNodeWidth;
        int wii=wi*barrierNodeWidth+30;
        int he=(event->y()-30)/barrierNodeHeight;
        int hee=he*barrierNodeHeight+30;
        bool paint=true;
        if(wii>=50&&wii<850&&hee>=50&&hee< 850){
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
    }

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    ui->label_2->setText("steps:"+QString::number(steps));
    ui->label_3->setText("points:"+QString::number(points));


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
//    for(int i=0;i<40;++i){
//        for(int j=0;j<40;++j){
//            painter.drawRect(QRectF(50+i*20,50+j*20,20,20));
//        }
//    }
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
    brush.setColor(Qt::red);
    painter.setBrush(brush);
    painter.drawEllipse(reward);

    brush.setColor(Qt::green);
    painter.setBrush(brush);

    for(int i=0; i<snake.length(); i++){
        painter.drawRect(snake.at(i));
    }
    QPixmap image1;
    image1.load("face.png");
    painter.drawPixmap(snake.at(0).x(),snake.at(0).y(),snake.at(0).width(),snake.at(0).height(),image1);
//    brush.setColor(Qt::blue);
//    painter.setBrush(brush);
//    painter.drawEllipse(snake.at(0));



    QWidget::paintEvent(event);

}
void MainWindow::addTopRectF()
{   steps++;

    if(snake.at(0).y()-snakeNodeHeight < 50){
        gameStart=false;state=pause;;
        set_state("end");

    }else{
        snake.insert(0,QRectF(snake.at(0).topLeft()+QPointF(0,-snakeNodeHeight),snake.at(0).topRight()));
    }

    if(snakeStrike()){
        gameStart=false;state=pause;;
        set_state("end");
    }
}

void MainWindow::addDownRectF()
{
    steps++;
    if(snake.at(0).y()+snakeNodeHeight*2 > 850){
        gameStart=false;state=pause;
        set_state("end");
    }else{
        snake.insert(0,QRectF(snake.at(0).bottomLeft(),snake.at(0).bottomRight()+QPointF(0,snakeNodeHeight)));
    }
    if(snakeStrike()){
        gameStart=false;state=pause;;
         set_state("end");
    }
}
//向左移动
void MainWindow::addLeftRectF()
{
    steps++;
    if(snake.at(0).x()-snakeNodeWidth < 50){
        gameStart=false;state=pause;
        set_state("end");
    }else{
        snake.insert(0,QRectF(snake.at(0).topLeft()+QPointF(-snakeNodeWidth,0),snake.at(0).bottomLeft()));
    }
    if(snakeStrike()){
        gameStart=false;state=pause;;
        set_state("end");
    }
}
//向右移动
void MainWindow::addRightRectF()
{
    steps++;
    if(snake.at(0).x()+snakeNodeWidth*2 > 850){
        gameStart=false;state=pause;
        set_state("end");
    }else{
        snake.insert(0,QRectF(snake.at(0).topRight(),snake.at(0).bottomRight()+QPointF(snakeNodeWidth,0)));
    }
    if(snakeStrike()){
        gameStart=false;state=pause;;
        set_state("end");
    }
}
//删除结尾数据
void MainWindow::deleteLastRectF()
{
    snake.removeLast();
}

int MainWindow::getRandom()
{
    QTime time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);

    int num = qrand()%780;
    int w=num/barrierNodeWidth;
    return w*barrierNodeWidth+50;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_Up:
        if(dir != Down){
            dir = Up;
        }
        break;
    case Qt::Key_Down:
        if(dir != Up){
            dir = Down;
        }
        break;
    case Qt::Key_Right:
        if(dir != Left){
            dir = Right;
        }
        break;
    case Qt::Key_Left:
        if(dir != Right){
            dir = Left;
        }
        break;
//    case Qt::Key_Enter:
//    case Qt::Key_Return:
//        if(gameOver){
//            snake.clear();
//            rewardNode.clear();
//            moveFlage = Up;
//            snake.append(QRectF(200,500,snakeNodeWidth,snakeNodeHeight));
//            addTopRectF();
//            addTopRectF();
//            //首先生成一个奖励节点
//            rewardNode.append(QRectF(100,100,snakeNodeWidth,snakeNodeWidth));
//            timer->start(time);
//            rewardTimer->start(time*30);
//            gameOver = false;
//        }
//        break;
    case Qt::Key_Space:
        if(!gameStart){
          set_state("running");
            if(state==not_begin){

                //生成奖励
                setreward();

            }
            ttime.restart();
            state=runing;
            timer->start(100);
            gameStart = true;
        }else if(gameStart ){
            set_state("pause");
            t_last=t_now;
            t_now=0;
            state=pause;
            timer->stop();
            state=pause;
            gameStart = false;
        }
        break;
    default:
        break;
    }
}

bool MainWindow::snakeStrike()
{
    bool tmp=false;
    for(int i=1; i<snake.length(); i++){
            if(snake.at(i) == snake.at(0)){
                gameStart=false;state=pause;
                tmp=true;
        }
    }

    for(int i=0; i<barrier.length(); i++){
            if(barrier.at(i) == snake.at(0)){
                gameStart=false;state=pause;
                tmp=true;
        }
    }
    return tmp;

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionBEGIN_triggered()
{
set_state("running");
if(state!=not_begin){return;}
setreward();
ttime.restart();
state=runing;
timer->start(100);
gameStart = true;
}

void MainWindow::on_actionPAUSE_triggered()
{
    set_state("pause");
    if(state!=runing)return;
    t_last=t_now;
    t_now=0;
    state=pause;
    timer->stop();
    state=pause;
    gameStart = false;
}

void MainWindow::on_actionCONTINUE_triggered()
{
    if(state!=pause)return;
    ttime.restart();
    state=runing;

    timer->start(100);
    gameStart = true;
}

void MainWindow::on_actionRESTART_2_triggered()
{
    state=not_begin;
    gameStart = false;
    dir=Up;
    foreach(auto item,snake)
    {
        snake.removeOne(item);
    }
//    foreach(auto item,barrier)
//    {
//        barrier.removeOne(item);
//        qDebug()<<"qlist.size()="<<barrier.size();
//    }
    snake.append(QRectF(210,510,snakeNodeWidth,snakeNodeHeight));
    addTopRectF();
    this->on_actionBEGIN_triggered();
}

void MainWindow::on_actionQUIT_2_triggered()
{
    close();
}

void MainWindow::on_actionSAVE_triggered()
{
//    QDir *d=new QDir(QDir::currentPath());
//        QStringList filter;
//        filter<<"*.json";
//        d->setNameFilters(filter); //过滤文件类型
//        QList<QFileInfo> *fileInfo=new QList<QFileInfo>(d->entryInfoList(filter));
//        int count=fileInfo->count();  //文件个数
//        QString ttt="/"+QString::number(count)+".json";
//    QFile file(QDir::currentPath() + ttt);
     QString text = QFileDialog::getOpenFileName(NULL,"save",".","*.json");
     QFile file(text);
        if(!file.open(QIODevice::ReadWrite)) {

            QMessageBox::information(this, QString::fromLocal8Bit("Warning"),QString::fromLocal8Bit("File open error"));
        return;
        } else {
            qDebug() <<"File open!";
        }
    // 使用QJsonObject对象插入键值对。
        QJsonObject jsonObject;
        jsonObject.insert("steps", steps);
        jsonObject.insert("points", points);
        jsonObject.insert("t_last", t_last);
        jsonObject.insert("t_now", t_now);
        jsonObject.insert("to_grow", to_grow);
        jsonObject.insert("need_move", need_move);
        jsonObject.insert("dir", dir);
        jsonObject.insert("gameStart", gameStart);
        jsonObject.insert("gameOver", gameOver);
        jsonObject.insert("barrier_length", barrier.length());
        jsonObject.insert("snake_length", snake.length());
        jsonObject.insert("speed", speed);

        QJsonArray json;
        json.append(jsonObject);
        for(int i=0;i<barrier.length();++i){
            QJsonObject jo;
            jo.insert("left", barrier.at(i).left());
            jo.insert("top", barrier.at(i).top());
            json.append(jo);
        }


        for(int i=0;i<snake.length();++i){
            QJsonObject jo;
            jo.insert("left", snake.at(i).left());
            jo.insert("top", snake.at(i).top());
            json.append(jo);
        }
        QJsonObject jo;
        jo.insert("left", reward.left());
        jo.insert("top", reward.top());
        json.append(jo);
    // 使用QJsonDocument设置该json对象
        QJsonDocument jsonDoc;
        jsonDoc.setArray(json);

    // 将json以文本形式写入文件并关闭文件。

        file.write(jsonDoc.toJson());
        file.close();
        QMessageBox::information(this, QString::fromLocal8Bit("Information"),QString::fromLocal8Bit("File saved"));
}

void MainWindow::on_actionLOAD_triggered()

{
    QString text = QFileDialog::getOpenFileName(NULL,"load",".","*.json");
//    bool ok;
//    QString text = QInputDialog::getText(this, tr("file"),tr("enter your file here"), QLineEdit::Normal,0, &ok);
    /*QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
    QFile file(QDir::currentPath()+"0.json");
        if (file.open(QIODevice::ReadOnly))
        {
            QByteArray Data = file.readAll();
            QJsonDocument jsonDoc(QJsonDocument::fromJson(Data));
            if (jsonDoc.isObject()){
                QJsonArray arr = obj["contents"].toArray();
                if (!arr.isEmpty() && arr[0].isObject())
                {
                    for (int j = 0; j < arr.size(); j++)
                    {
                        QJsonObject itemObj = arr[j].toObject();
                        QString value1 = codec->toUnicode(itemObj["Key1"].toString().toLocal8Bit());
                        QString value2 = codec->toUnicode(itemObj["Key2"].toString().toLocal8Bit());
                        if (!value1.isEmpty() && !value2.isEmpty())
                        {
                            //对数据value1和value2进行操作
                        }
                    }
                }
            }
        }
        file.close();
    qDebug()<<"save";
    */
//    QFile loadFile(QDir::currentPath()+"/2.json");
    QFile loadFile(text);
        if(!loadFile.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, QString::fromLocal8Bit("Warning"),QString::fromLocal8Bit("File open error"));
            return;
        }

        QByteArray allData = loadFile.readAll();
        loadFile.close();
        QJsonParseError json_error;
        QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));
        if(json_error.error != QJsonParseError::NoError)
        {
            qDebug() << "json error!";
            return;
        }
        QJsonArray arr=jsonDoc.array();

       QJsonObject rootObj = arr[0].toObject();

//        //输出所有key，这一步是非必须的，放最后的话，你可能读不到任何key
//        QStringList keys = rootObj.keys();
//        for(int i = 0; i < keys.size(); i++)
//        {
//            qDebug() << "key" << i << " is:" << keys.at(i);
//        }

//        //因为是预先定义好的JSON数据格式，所以这里可以这样读取

         dir=rootObj["dir"].toInt();
         gameOver=rootObj["gameOver"].toInt();
         gameStart=rootObj["gameStart"].toInt();
         need_move=rootObj["need_move"].toInt();
         points=rootObj["points"].toInt();
         steps=rootObj["steps"].toInt();
         t_last=rootObj["t_last"].toInt();
         t_now=rootObj["t_now"].toInt();
         to_grow=rootObj["to_grow"].toInt();
         speed=rootObj["speed"].toInt();
         int barrier_length=rootObj["barrier_length"].toInt();
         int snake_length=rootObj["snake_length"].toInt();

         foreach(auto item,snake)
         {
             snake.removeOne(item);
         }
         foreach(auto item,barrier)
         {
             barrier.removeOne(item);

         }

           for(int i = 1; i<=barrier_length; i++)
           {
               barrier.append(QRectF(arr.at(i)["left"].toInt(),arr.at(i)["top"].toInt(),barrierNodeWidth,barrierNodeHeight));

           }
           for(int i=barrier_length+1;i<=barrier_length+snake_length;++i){
               snake.append(QRectF(arr.at(i)["left"].toInt(),arr.at(i)["top"].toInt(),barrierNodeWidth,barrierNodeHeight));

           }
           int tttt=barrier_length+snake_length+1;
           reward=QRectF(arr.at(tttt)["left"].toInt(),arr.at(tttt)["top"].toInt(),barrierNodeWidth,barrierNodeHeight);
           update();
        loadFile.close();

}

void MainWindow::on_pushButton_clicked()
{
    on_actionBEGIN_triggered();
}

void MainWindow::on_pushButton_2_clicked()
{
    on_actionCONTINUE_triggered();
}

void MainWindow::on_pushButton_4_clicked()
{
    on_actionRESTART_2_triggered();
}

void MainWindow::on_pushButton_3_clicked()
{
    on_actionQUIT_2_triggered();
}

void MainWindow::on_pushButton_5_clicked()
{
    on_actionPAUSE_triggered();
}



void MainWindow::on_pushButton_6_clicked()
{
    on_actionLOAD_triggered();
}

void MainWindow::on_pushButton_7_clicked()
{
    on_actionSAVE_triggered();
}

void MainWindow::on_pushButton_8_clicked()
{
    bool ok;
   QString text = QInputDialog::getText(this, tr("SPEED"),tr("enter your speed here"), QLineEdit::Normal,0, &ok);
   speed=text.toInt();


}

