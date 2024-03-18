# RPi5-PWM-Qt
Rpi5 PWM servo control using Qt

Thanks a lot https://github.com/danjperron for your help in starting doing tricks with RPi.

Sources were used:
https://github.com/danjperron/sysfspwm (original source https://github.com/zeroping/sysfspwm | danjperron fixed bug for it)

libudev is needed. Rest details descreibed on official Rpi forum: https://forums.raspberrypi.com/viewtopic.php?t=367452

Program could be build with Qt qmake.

I just added some control using WASD and ui buttons (details in servo.cpp file).

Here is used hardware:
- RPi 5
- Rpi camer module v3
- 2-DOF Pan-Tilt HAT


![msg-4123678493-350298](https://github.com/9onemandev/RPi5-PWM-Qt/assets/163633812/70886b13-eb85-4d9b-a325-b36296650ac0)

Pay attention to parameters:

#define PNS 20000000       // period in ns
#define LRS 1450000        // left-right servo mid position
#define TBS 2300000        // top-bot servo mid position
#define LRMIN 450000       // left-right min position
#define LRMAX 2500000      // left-right max pos
#define TBMIN 1360000      // top-bot servo min position
#define TBMAX 2660000      // top-bot servo max position

and rotation directions in keypress event method. They may vary for your case. Code written for camera mounted on ceiling (not staying on the table).


