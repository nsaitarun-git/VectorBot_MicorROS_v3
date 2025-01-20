#ifndef ROS_PUB_SUB_H
#define ROS_PUB_SUB_H

#include <Arduino.h>
#include <micro_ros_platformio.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <motor_control.h>

#include <geometry_msgs/msg/twist.h>
#include <std_msgs/msg/u_int16_multi_array.h>

#if !defined(MICRO_ROS_TRANSPORT_ARDUINO_WIFI)
#endif

extern volatile unsigned long enc_left;
extern volatile unsigned long enc_right;
extern int direction;

class RosPubSub
{
public:
    RosPubSub();

    void initialize();
    void pub_sub_define();
    static void cmd_vel_callback(const void *msg_recv);
    void start_msgs();
    void executors_start();

private:
    static float linear_vel;
    static float angular_vel;
};

#endif