#include "snakewidget.h"
#include<QKeyEvent>
#include<QLabel>
#include<QDebug>
#include<QTimer>
#include<QString>
#include<QFont>
#include<QMessageBox>
#include<QSound>
#include<QPainter>
snakewidget::snakewidget(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize((MAX_length+7)*oneLabelSize,MAX_width*oneLabelSize);//设置游戏窗口大小
    this->setWindowTitle("贪吃蛇小游戏");//设置游戏标题
    //startGame=new QPushButton(this);
    //startGame->setText("Let's start!");
    //startGame->resize(180,60);
    //startGame->move((MAX_length*oneLabelSize)/2-80,(MAX_width*oneLabelSize)/2-40);
    score=0;//初始化分数为0
    foodCount=0;//初始化食物数量
    timer=new QTimer(this);//初始化计时器
    //btnStopAndStart=new QPushButton("暂停",this);
    //btnGoBack=new QPushButton("返回",this);
    //btnStopAndStart->move(MAX_length*oneLabelSize,(MAX_width-9)*oneLabelSize);
    //btnGoBack->move(MAX_length*oneLabelSize,(MAX_width-7)*oneLabelSize);
    QPushButton *btnpause=new QPushButton("暂停",this);
    QPushButton *btncontinue=new QPushButton("继续",this);
//    QPalette palette1=btnpause->palette();
//    palette1.setColor(QPalette::ButtonText,Qt::yellow);
//    btnpause->setPalette(palette1);
//    QPalette palette2=btncontinue->palette();
//    palette2.setColor(QPalette::ButtonText,Qt::yellow);
//    btncontinue->setPalette(palette2);
    btnpause->move(650,480);
    btncontinue->move(650,510);
    btncontinue->setEnabled(false);
    scoreLabel=new QLabel(this);//初始化用于显示分数的标签
    scoreLabel->setGeometry(MAX_length*oneLabelSize,oneLabelSize,
                            6*oneLabelSize,(MAX_width-10)*oneLabelSize);//初始化标签大小和位置
    scoreLabel->setFont(QFont("微软雅黑",25));//设置分数标签字体
    scoreLabel->setStyleSheet("color:white");
    scoreLabel->setText("score:"+QString::number(score,10));//显示分数
    scoreLabel->setAlignment(Qt::AlignCenter);
    init();//初始化游戏和游戏地图
    initSnake();//初始化贪吃蛇的位置
    drawGameMapBorder();//绘制游戏边界
    drawScorePart();//绘制分数标签即游戏右边的边界
    timer=new QTimer(this);
    setFood();//设置地图中的食物
    //changeScore();
    //timer->start(moveSpeed);//添加三种模式后此语句可有可无
    /*connect(startGame,&QPushButton::clicked,[=](){
        slotOfStartSnakeGame();
    });*/
    connect(btnpause,&QPushButton::clicked,[=](){
            timer->stop();
            btnpause->setEnabled(false);
            btncontinue->setEnabled(true);
    });
    connect(btncontinue,&QPushButton::clicked,[=](){
            timer->start();
            btncontinue->setEnabled(false);
            btnpause->setEnabled(true);
    });
    connect(timer,&QTimer::timeout,[=](){
        slotOfMoveSnake();
    });//链接计时器与槽
    /*connect(btnStopAndStart,&QPushButton::clicked,[=](){
        if(timer->isActive()){
            timer->stop();
        }
        else{
            timer->start();
        }
        if(btnStopAndStart->text()=="暂停"){
            btnStopAndStart->setText("开始");
        }
        else{
            btnStopAndStart->setText("暂停");
        }
    });
    connect(btnGoBack,&QPushButton::clicked,[=](){
        this->close();
    });*/
}

snakewidget::~snakewidget()
{

}
void snakewidget::showQuestionMsg()
{
    switch(QMessageBox::question(this,"游戏结束","重新开始？",QMessageBox::Ok|
                                 QMessageBox::Cancel,QMessageBox::Ok)){
    case QMessageBox::Ok:
        slotOfStartSnakeGame();
        break;
    case QMessageBox::Cancel:
        this->close();
        break;
    default:
        break;
    }
}
void snakewidget::setTimer(int newMoveSpeed)
{
    moveSpeed=newMoveSpeed;
    timer->start(newMoveSpeed);//为计时器指定时间间隔
}
//游戏和游戏地图初始化
void snakewidget::init()
{
    background=new QSound("D:\\logo\\back2.wav",this);
    background->setLoops(-1);
    background->play();
    pixmap.load("D:\\logo\\shui.png");
    QPalette palette=this->palette();
    palette.setBrush(QPalette::Background,QBrush(pixmap.scaled(this->size())));
    this->setPalette(palette);
    foodCount=0;
    //moveSpeed=300;//此语句可有可无
    for(int x=0;x<MAX_length;x++){
        for(int y=0;y<MAX_width;y++){
            QLabel* label=new QLabel(this);
            label->setGeometry(x*oneLabelSize,y*oneLabelSize,
                               oneLabelSize,oneLabelSize);
            gameMap[x][y]=new SnakePartNode;//gameMap中储存的为snakePartNode的指针
            gameMap[x][y]->label=label;
            gameMap[x][y]->type=normal_label;
            gameMap[x][y]->x=x;
            gameMap[x][y]->y=y;
            label->hide();
        }
    }
}
//初始化贪吃蛇
void snakewidget::initSnake()
{
    int snakeFirstlen=3,snakeX=3,snakeY=5;
    dx=1;
    dy=0;//初始化贪吃蛇的方向为延x行进
    snakeList.clear();
    for(int x=snakeX;x<snakeX+snakeFirstlen;x++){
        snakeList.append(gameMap[x][snakeY]);
        snakeList[snakeList.length()-1]->type=snake_label;
        snakeList[snakeList.length()-1]->label->setStyleSheet("background:black");
        snakeList[snakeList.length()-1]->label->show();
    }
}
//设置食物的位置
void snakewidget::setFood()
{
    int foodx,foody;
    srand((unsigned int)time(0));
    while(foodNum<4){
        do{
            foodx=rand()%MAX_length;
            foody=rand()%MAX_width;
        }while(gameMap[foodx][foody]->type!=normal_label);
        gameMap[foodx][foody]->type=food_label;
        gameMap[foodx][foody]->label->setStyleSheet("background:red");
        gameMap[foodx][foody]->label->show();
        foodNum++;
    }
}
//绘制游戏地图的边界
void snakewidget::drawGameMapBorder()
{
    for(int x=0;x<MAX_length;x++){
        for(int y=0;y<MAX_width;y++){
            if(x==0||y==0||x==MAX_length-1||y==MAX_width-1){
                gameMap[x][y]->type=border_label;
                gameMap[x][y]->label->setStyleSheet("background:blue");
                gameMap[x][y]->label->show();
            }
        }
    }
}

//绘制分数区域的边界
void snakewidget::drawScorePart()
{
    for(int x=MAX_length;x<MAX_length+7;x++){
        for(int y=0;y<MAX_width;y+=MAX_width-1){
            QLabel* label=new QLabel(this);
            label->setStyleSheet("background:blue");
            label->setGeometry(x*oneLabelSize,y*oneLabelSize,
                               oneLabelSize,oneLabelSize);
            label->show();
        }
    }
    for(int y=1;y<MAX_width-1;y++){
        QLabel * label=new QLabel(this);
        label->setStyleSheet("background:blue");
        label->setGeometry((MAX_length+6)*oneLabelSize,y*oneLabelSize,
                           oneLabelSize,oneLabelSize);
        label->show();
    }
}
//改变分数
void snakewidget::changeScore()
{
    foodCount++;
    score=foodCount;
    scoreLabel->setText("score:"+QString::number(score));
}
//游戏结束
void snakewidget::gameOver()
{
    score=0;
    foodCount=0;
    //moveSpeed=300;
    timer->stop();
    delete background;
    for(int x=1;x<MAX_length-1;x++){
        for(int y=1;y<MAX_width-1;y++){
            gameMap[x][y]->type=normal_label;
            gameMap[x][y]->label->hide();
        }
    }
    pixmap.load("D:\\logo\\defeat2.png");
    QPalette palette=this->palette();
    palette.setBrush(QPalette::Background,QBrush(pixmap.scaled(this->size())));
    this->setPalette(palette);
    QSound *background2=new QSound("D:\\logo\\gameover.wav",this);
    background2->setLoops(1);
    background2->play();
    QTimer::singleShot(3000,this,[=](){
        drawGameMapBorder();
        showQuestionMsg();
    });

    //startGame->setEnabled(true);
    //startGame->show();

}
//移动蛇的位置
void snakewidget::moveSnake()
{
    getHeadAndTail();
    SnakePartNode* tmp=gameMap[head->x+dx][head->y+dy];
    if(tmp->type==snake_label||tmp->type==border_label){
        gameOver();
    }
    else{
        if(tmp->type==food_label){
            changeScore();
            snakeList.append(tmp);
            tmp->type=snake_label;
            foodNum--;
            setFood();
        }
        else{
            tmp->type=snake_label;
            snakeList.append(tmp);
            tail->type=normal_label;
            tail->label->hide();
            snakeList.removeFirst();
        }
        tmp->label->setStyleSheet("background:blank");
        tmp->label->show();
    }
    //tmp->label->setStyleSheet("background:blank");
    //tmp->label->show();

}
//获取贪吃蛇链表的头与尾
void snakewidget::getHeadAndTail()
{
    head=snakeList.at(snakeList.length()-1);
    tail=snakeList.at(0);
}
//移动贪吃蛇的槽
void snakewidget::slotOfMoveSnake(){
    moveSnake();
}
//重新开始游戏的槽
void snakewidget::slotOfStartSnakeGame(){
    init();
    initSnake();
    drawGameMapBorder();
    drawScorePart();
    foodNum=0;
    setFood();
    score=0;
    foodCount=0;
    timer->start(moveSpeed);
    scoreLabel->setText("score:"+QString::number(score));
    //moveSnake();
    //timer->start(moveSpeed);
    //startGame->setEnabled(false);
    //startGame->hide();
}
//键盘设计
void snakewidget::keyPressEvent(QKeyEvent *event){
    switch(event->key())
    {
    case Qt::Key_Up:
        if(dx!=0){
            dx=0;
            dy=-1;
            //moveSnake();
        }
        break;
    case Qt::Key_Down:
        if(dx!=0){
            dx=0;
            dy=1;
            //moveSnake();
        }
        break;
    case Qt::Key_Left:
        if(dy!=0){
            dx=-1;
            dy=0;
            //moveSnake();
        }
        break;
    case Qt::Key_Right:
        if(dy!=0){
            dx=1;
            dy=0;
            //moveSnake();
        }
        break;
    case Qt::Key_Space:
        if(timer->isActive()){
            timer->stop();
        }
        else{
            timer->start();
        }
        break;
    default:
        break;
    }
    //return QWidget::keyPressEvent(event);
}

