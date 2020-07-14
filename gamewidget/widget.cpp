#include "widget.h"
#include "ui_widget.h"
#include"snakewidget.h"
#include<QSound>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    snakewidget* w=new snakewidget;
    w->hide();
    ui->btnSlow->setEnabled(false);
    ui->btnSlow->setVisible(false);
    ui->btnQuick->setEnabled(false);
    ui->btnQuick->setVisible(false);
    ui->btnFast->setEnabled(false);
    ui->btnFast->setVisible(false);
    connect(ui->btnStart,&QPushButton::clicked,[=](){
        ui->btnSlow->setEnabled(true);
        ui->btnSlow->setVisible(true);
        ui->btnQuick->setEnabled(true);
        ui->btnQuick->setVisible(true);
        ui->btnFast->setEnabled(true);
        ui->btnFast->setVisible(true);
        ui->btnStart->setEnabled(false);
        ui->btnStart->setVisible(false);
        ui->btnOut->setEnabled(false);
        ui->btnOut->setVisible(false);
    });
    if(ui->btnOut->underMouse())
    {
        ui->btnOut->resize(230,80);
        update();
    }
    if(ui->btnFast->underMouse())
    {
        ui->btnFast->resize(230,80);
        update();
    }
    if(ui->btnSlow->underMouse())
    {
        ui->btnSlow->resize(230,80);
        update();
    }
    if(ui->btnQuick->underMouse())
    {
        ui->btnQuick->resize(230,80);
        update();
    }
    if(ui->btnStart->underMouse())
    {
        ui->btnStart->resize(230,80);
        update();
    }
        QPixmap pixmap("D:\\logo\\main.jpg.png");
        QPalette palette=this->palette();
        palette.setBrush(QPalette::Background,QBrush(pixmap.scaled(this->size())));
        this->setPalette(palette);
        QSound *background2=new QSound("D:\\logo\\niao2.wav",this);
        background2->setLoops(-1);
        background2->play();
    connect(ui->btnOut,&QPushButton::clicked,[=](){
        background2->stop();
        this->close();
    });
    connect(ui->btnSlow,&QPushButton::clicked,[=](){
        background2->stop();
        this->hide();
        w->setTimer(500);
        w->show();
    });
    connect(ui->btnQuick,&QPushButton::clicked,[=](){
        background2->stop();
        this->hide();
        w->setTimer(300);
        w->show();
    });
    connect(ui->btnFast,&QPushButton::clicked,[=](){
        background2->stop();
        this->hide();
        w->setTimer(100);
        w->show();
    });
}

Widget::~Widget()
{
    delete ui;
}

