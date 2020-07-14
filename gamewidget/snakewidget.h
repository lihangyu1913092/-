/////////小组成员////////
/*李航宇、吕尤、褚羿升、张杰*/
#ifndef SNAKEWIDGET_H
#define SNAKEWIDGET_H
#include <QWidget>
#include<QTimer>
#include<QDebug>
#include<QLabel>
#include<QList>
#include<QEvent>
#include<QKeyEvent>
#include<QPushButton>
#include<QMessageBox>
#include<QSound>
const int MAX_width=20;
const int MAX_length=20;
const int oneLabelSize=30;

enum labelAttribute{
    snake_label,
    normal_label,
    border_label,
    food_label
};

struct SnakePartNode{
    int x,y,type;
    QLabel* label;
};

class snakewidget : public QWidget
{
    Q_OBJECT

public:
    void init();
    void initSnake();
    void setFood();
    void drawGameMapBorder();
    void drawScorePart();
    void changeScore();
    void gameOver();
    void moveSnake();
    void getHeadAndTail();
    void setTimer(int);
    //int moveSpeed;
    void showQuestionMsg();

    snakewidget(QWidget *parent = nullptr);
    ~snakewidget();
private slots:
    void slotOfMoveSnake();
    void slotOfStartSnakeGame();
protected:
    void keyPressEvent(QKeyEvent*event);
private:
    SnakePartNode* gameMap[MAX_length][MAX_width];
    QList<SnakePartNode*>snakeList;
    int score;
    int foodNum=0;
    int foodCount;
    int moveSpeed=100;
    int dx;
    int dy;
    SnakePartNode* head;
    SnakePartNode* tail;
    QLabel *scoreLabel;
    //QPushButton* startGame;
    QTimer* timer;
    //QPushButton* btnStopAndStart;
    //QPushButton* btnGoBack;
    QSound *background;
    QPixmap pixmap;
};
#endif // SNAKEWIDGET_H

