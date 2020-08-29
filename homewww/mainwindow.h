#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent (QMouseEvent * );
    void keyPressEvent(QKeyEvent *);


private:
    void set_state(QString str);
    void addTopRectF();
    void addDownRectF();
    void addLeftRectF();
    void addRightRectF();
    void deleteLastRectF();
    bool snakeStrike();
    int getRandom();
    void setreward();
    enum Move{Left,Right,Up,Down};
    enum status{not_begin,runing,pause,end};
protected slots:
    void timeOut();
    void gg();
//    void forward();
//    void rewardTimeOut();
private slots:
    void on_actionBEGIN_triggered();

    void on_actionPAUSE_triggered();

    void on_actionCONTINUE_triggered();

    void on_actionRESTART_2_triggered();

    void on_actionQUIT_2_triggered();

    void on_actionSAVE_triggered();

    void on_actionLOAD_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

//    void on_beginButton_clicked();

private:
    Ui::MainWindow *ui;
    QList<QRectF> snake;//贪吃蛇本体
    QList<QRectF> barrier;
    const int snakeNodeWidth = 20;
    const int snakeNodeHeight = 20;
    const int barrierNodeWidth = 20;
    const int barrierNodeHeight = 20;
    int steps=-0;
    int points=0;
//    double t_last=0;
//    double t_now=0;
    int to_grow=0;
    int speed=500;
    QTimer *timer;

//    QTimer *rewardTimer;
//    int time = 100;
//    int need_move=0;
    int state=not_begin;
    int dir = Up;
//    bool gameOver = true;
    bool gameStart = false;
    QRectF reward;//奖励节点

    QToolBar *toolBar;
    QAction *beginAction ;
    QAction *pauseAction ;
    QAction *continueAction ;
    QAction *restartAction ;
    QAction *quitAction ;
    QAction *saveAction ;
    QAction *loadAction;

};
#endif // MAINWINDOW_H
