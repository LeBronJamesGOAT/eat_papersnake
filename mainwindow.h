#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
//    void keyPressEvent(QKeyEvent *);

private:
    void addTopRectF();
    void addDownRectF();
    void addLeftRectF();
    void addRightRectF();
    void deleteLastRectF();
    bool snakeStrike();
    enum Move{Left,Right,Up,Down};
    enum status{not_begin,runing,pause};
protected slots:
//    void timeOut();
//    void rewardTimeOut();
private:
    Ui::MainWindow *ui;
    QList<QRectF> snake;//贪吃蛇本体
    QList<QRectF> barrier;
    int snakeNodeWidth = 20;
    int snakeNodeHeight = 20;
    int barrierNodeWidth = 20;
    int barrierNodeHeight = 20;
    int steps=0;
//    QTimer *timer;
//    QTimer *rewardTimer;
//    int time = 100;
    int moveFlage = Up;
    bool gameOver = false;
    bool gameStart = false;
    QList<QRectF> rewardNode;//奖励节点
};
#endif // MAINWINDOW_H
