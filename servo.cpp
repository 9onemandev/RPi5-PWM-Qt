#include "servo.h"
#include "ui_servo.h"

#include <unistd.h>

#define PNS 20000000       // period in ns
#define LRS 1450000        // left-right servo mid position
#define TBS 2300000        // top-bot servo mid position
#define LRMIN 450000       // left-right min position
#define LRMAX 2500000      // left-right max pos
#define TBMIN 1360000      // top-bot servo min position
#define TBMAX 2660000      // top-bot servo max position

Servo::Servo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Servo),
      mypwmchip("/sys/class/pwm/pwmchip6"),
      pwm0(mypwmchip.export_pwm(0)),
      pwm1(mypwmchip.export_pwm(1)),
      pwm0_pos(TBS),
      pwm1_pos(LRS)
{
    ui->setupUi(this);

    //wait for initialization of export
    usleep(500000);

    //init servos
    pwm0.set_period(std::chrono::nanoseconds(PNS));
    pwm0.set_duty_cycle(std::chrono::nanoseconds(TBS));
    pwm0.set_enabled(true);

    pwm1.set_period(std::chrono::nanoseconds(PNS));
    pwm1.set_duty_cycle(std::chrono::nanoseconds(LRS));
    pwm1.set_enabled(true);

    //controls
    connect(ui->mt, &QPushButton::clicked, this, &Servo::moveTop);
    connect(ui->mb, &QPushButton::clicked, this, &Servo::moveBottom);
    connect(ui->ml, &QPushButton::clicked, this, &Servo::moveLeft);
    connect(ui->mr, &QPushButton::clicked, this, &Servo::moveRight);
}

Servo::~Servo()
{
    delete ui;

    //release servos
    pwm0.set_enabled(false);
    pwm1.set_enabled(false);
}

void Servo::moveTop()
{
    pwm0_pos += 10000 * ui->speed->value();
    if(pwm0_pos <= TBMAX)
    {
        pwm0.set_duty_cycle(std::chrono::nanoseconds(pwm0_pos));
        qDebug() << "move top:" << "value" << pwm0_pos;
    }
    else
    {
        pwm0_pos = TBMAX;
        qDebug() << "move top: maximum reached, move rejected";
    }
}

void Servo::moveBottom()
{
    pwm0_pos -= 10000 * ui->speed->value();
    if(pwm0_pos >= TBMIN)
    {
        pwm0.set_duty_cycle(std::chrono::nanoseconds(pwm0_pos));
        qDebug() << "move bottom:" << "value" << pwm0_pos;
    }
    else
    {
        pwm0_pos = TBMIN;
        qDebug() << "move bottom: minimum reached, move rejected";
    }
}

void Servo::moveLeft()
{
    pwm1_pos -= 10000 * ui->speed->value();
    if(pwm1_pos >= LRMIN)
    {
        pwm1.set_duty_cycle(std::chrono::nanoseconds(pwm1_pos));
        qDebug() << "move left:" << "value" << pwm1_pos;
    }
    else
    {
        pwm1_pos = LRMIN;
        qDebug() << "move left: minimum reached, move rejected";
    }
}

void Servo::moveRight()
{
    pwm1_pos += 10000 * ui->speed->value();
    if(pwm1_pos <= LRMAX)
    {
        pwm1.set_duty_cycle(std::chrono::nanoseconds(pwm1_pos));
        qDebug() << "move right:" << "value" << pwm1_pos;
    }
    else
    {
        pwm1_pos = LRMAX;
        qDebug() << "move right: maximum reached, move rejected";
    }
}

void Servo::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    // move top
    case 87:
    {
        moveTop();
        break;
    }
    // move bottom
    case 83:
    {
        moveBottom();
        break;
    }
    // move left
    case 65:
    {
        moveLeft();
        break;
    }
    // move right
    case 68:
    {
        moveRight();
        break;
    }
    default: break;
    }

    QWidget::keyPressEvent(e);
}

