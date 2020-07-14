#include "mybutton.h"
#include<QSound>
mybutton::mybutton(QWidget *parent) : QPushButton(parent)
{

}
void mybutton::enterEvent(QEvent *)
{
    resize(210,75);
    QSound *background2=new QSound("D:\\logo\\beng.wav",this);
    background2->setLoops(1);
    background2->play();
}
void mybutton::leaveEvent(QEvent *)
{
    resize(200,70);
}
