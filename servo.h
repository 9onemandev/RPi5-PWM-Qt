#ifndef SERVO_H
#define SERVO_H

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <stdexcept>
#include <iomanip>
#include <memory>
#include <udevpp.hpp>
#include <math.h>
#include <sysfspwm.hpp>

#include <QWidget>
#include <QKeyEvent>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Servo; }
QT_END_NAMESPACE

class Servo : public QWidget
{
    Q_OBJECT

public:
    Servo(QWidget *parent = nullptr);
    ~Servo();

public slots:
    void moveTop();
    void moveBottom();
    void moveLeft();
    void moveRight();

protected:
    virtual void keyPressEvent(QKeyEvent *e);

private:
    Ui::Servo *ui;
    sysfspwm::PWMChip mypwmchip;
    sysfspwm::PWM pwm0; //top-bot servo
    sysfspwm::PWM pwm1; //left-right servo
    int pwm0_pos;
    int pwm1_pos;
};
#endif // SERVO_H
