#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H
#include "widget.h"
#include "ui_widget.h"
#include"snakewidget.h"
#include <QPushButton>

class mypushbutton : public QPushButton
{
    Q_OBJECT
public:
    explicit mypushbutton(QWidget *parent = nullptr);
    void enterEvent(QEvent *event) ;
    void leaveevent(QEvent*);
signals:

};

#endif // MYPUSHBUTTON_H
