#include "mypushbutton.h"
#include "widget.h"
#include "ui_widget.h"
#include"snakewidget.h"
#include<QDebug>
mypushbutton::mypushbutton(QWidget *parent) : QPushButton(parent)
{

}
void mypushbutton::enterEvent(QEvent *)
{
    qDebug()<<"鼠标进入了";
}
void mypushbutton:: leaveevent(QEvent*)
{
    qDebug()<<"鼠标出去了";
}
