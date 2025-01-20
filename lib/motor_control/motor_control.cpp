#include <motor_control.h>

// Pin definitions
const int in1 = 5;
const int in2 = 17;
const int in3 = 18;
const int in4 = 19;

// PWM Pins
const int enA = 32;
const int enB = 33;

// Configure motor pins
void configMotorPins(void)
{
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);
}

// Define direction of motors
void forward(int leftSpeed, int rightSpeed)
{
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    analogWrite(enA, leftSpeed);
    analogWrite(enB, rightSpeed);
}

void back(int leftSpeed, int rightSpeed)
{
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    analogWrite(enA, leftSpeed);
    analogWrite(enB, rightSpeed);
}

void left(int leftSpeed, int rightSpeed)
{
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    analogWrite(enA, leftSpeed);
    analogWrite(enB, rightSpeed);
}

void right(int leftSpeed, int rightSpeed)
{
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    analogWrite(enA, leftSpeed);
    analogWrite(enB, rightSpeed);
}

void stop(void)
{
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    analogWrite(enA, 0);
    analogWrite(enB, 0);
}

void moveAllDirDemo(int leftSpeed, int rightSpeed)
{
    // Set PWM value to control speed
    analogWrite(enA, leftSpeed);
    analogWrite(enB, rightSpeed);

    // Switch direction
    forward(leftSpeed, rightSpeed);
    vTaskDelay(pdMS_TO_TICKS(3000));
    back(leftSpeed, rightSpeed);
    vTaskDelay(pdMS_TO_TICKS(3000));
    left(leftSpeed, rightSpeed);
    vTaskDelay(pdMS_TO_TICKS(3000));
    right(leftSpeed, rightSpeed);
    vTaskDelay(pdMS_TO_TICKS(3000));
}