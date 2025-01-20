#ifndef DRIVE_TIMER_H
#define DRIVE_TIMER_H

#include <Arduino.h>
#include <motor_control.h>

extern int direction;
extern const int mtr_power;
extern void drive_straight(int dir);

void create_timer(void);

#endif