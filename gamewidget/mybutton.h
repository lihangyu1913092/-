#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class mybutton : public QPushButton
{
    Q_OBJECT
public:
    explicit mybutton(QWidget *parent = nullptr);
    void enterEvent(QEvent *) ;
    void leaveEvent(QEvent*);
signals:

};

#endif // MYBUTTON_H
