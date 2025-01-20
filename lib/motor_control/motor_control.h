#include <Arduino.h>

void configMotorPins(void);
void forward(int leftSpeed, int rightSpeed);
void back(int leftSpeed, int rightSpeed);
void left(int leftSpeed, int rightSpeed);
void right(int leftSpeed, int rightSpeed);
void stop(void);
void moveAllDirDemo(int leftSpeed, int rightSpeed);