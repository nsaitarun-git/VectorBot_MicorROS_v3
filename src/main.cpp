#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <oled_display.h>
#include <motor_control.h>
#include <ros_publisher_subscriber.h>

// OLED display settings
#define i2c_Address 0x3c

// Encoder pins
const int enc_left_pin = 13;  // Motor A
const int enc_right_pin = 15; // Motor B

// Encoder ticks ISR
volatile unsigned long enc_left = 0;
volatile unsigned long enc_right = 0;

// Encoder variables
unsigned long num_ticks_left = 0;
unsigned long num_ticks_right = 0;
int power_left = 0;
int power_right = 0;

// Used to determine which way to turn to adjust
unsigned long diff_left;
unsigned long diff_right;

// Previous encoder values
unsigned long enc_left_prev = 0;
unsigned long enc_right_prev = 0;

// Motor speed
const int mtr_power = 100;
const int mtr_offset = 5;

// Control mo
int direction = 0;

// ROS communication object
RosPubSub ros_pub_sub;

// Function definitions
void count_left();
void count_right();
void encoder_init(void);
void driveStraight(int dir);

void setup()
{
  Serial.begin(115200);

  // Configure motor pins
  configMotorPins();

  // Configure encoder pins
  pinMode(enc_left_pin, INPUT_PULLUP);
  pinMode(enc_right_pin, INPUT_PULLUP);

  // Set up interrupts
  attachInterrupt(digitalPinToInterrupt(enc_left_pin), count_left, CHANGE);
  attachInterrupt(digitalPinToInterrupt(enc_right_pin), count_right, CHANGE);

  // Initialise ROS subscriber node
  ros_pub_sub.initialize();
  ros_pub_sub.pub_sub_define();
  ros_pub_sub.executors_start();

  // Configure OLED display
  display.begin(i2c_Address, true);

  // Initialise encoders
  encoder_init();
}

void loop()
{

  // Use flag to control motor direction
  if (direction == 1)
  {
    driveStraight(1);
  }
  else if (direction == 2)
  {
    driveStraight(-1);
  }
  else if (direction == 3)
  {
    left(mtr_power, mtr_power);
  }
  else if (direction == 4)
  {
    right(mtr_power, mtr_power);
  }
  else
  {
    stop();
  }

  // Start publishing and subscribing to topics
  ros_pub_sub.start_msgs();
}

// ISR for left motor
void count_left()
{
  enc_left++;
}

// ISR for right motor
void count_right()
{
  enc_right++;
}

// Initialise encoders
void encoder_init(void)
{

  // Set initial motor power
  power_left = mtr_power;
  power_right = mtr_power;

  // Reset encoder counts
  enc_left = 0;
  enc_right = 0;

  // Remember previous encoder counts
  enc_left_prev = enc_left;
  enc_right_prev = enc_right;
}

// Drive robot straight with motor feedback
void driveStraight(int dir)
{
  // Sample number of encoder ticks
  num_ticks_left = enc_left;
  num_ticks_right = enc_right;

  // Set direction
  if (dir == 1)
  {
    forward(power_left - 10, power_right);
  }
  else
  {
    back(power_left - 10, power_right);
  }

  // Number of ticks counted since last time
  diff_left = num_ticks_left - enc_left_prev;
  diff_right = num_ticks_right - enc_right_prev;

  // Store current tick counter for next time
  enc_left_prev = num_ticks_left;
  enc_right_prev = num_ticks_right;

  // If left is faster, slow it down and speed up right
  if (diff_left > diff_right)
  {
    power_left -= mtr_offset;
    power_right += mtr_offset;
  }

  // If right is faster, slow it down and speed up left
  if (diff_left < diff_right)
  {
    power_left += mtr_offset;
    power_right -= mtr_offset;
  }

  vTaskDelay(pdMS_TO_TICKS(20));
}