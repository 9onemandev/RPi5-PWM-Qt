#include "servo.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Servo w;
    w.show();

    return a.exec();
}
