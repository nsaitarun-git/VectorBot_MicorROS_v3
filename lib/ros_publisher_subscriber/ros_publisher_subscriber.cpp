#include <ros_publisher_subscriber.h>
#include <motor_control.h>
#include <oled_display.h>

// Message types
geometry_msgs__msg__Twist cmd_vel_msg;
std_msgs__msg__UInt16MultiArray msg_multiarray;

// Come variables
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_timer_t timer;

// Subscriber
rcl_subscription_t cmd_vel_sub;
rclc_executor_t executor_sub;

// Publisher
rcl_publisher_t publisher;
rclc_executor_t executor_pub;

RosPubSub::RosPubSub()
{
}

// Initialisation (Wifi and node)
void RosPubSub::initialize()
{
    // Add Wifi (PC IP Address)
    IPAddress agent_ip(192, 168, 1, 184);
    size_t agent_port = 8888;

    // Wifi credentials
    char ssid[] = "CommunityFibre10Gb_57E28";
    char psk[] = "srinivas";

    // Set transport
    set_microros_wifi_transports(ssid, psk, agent_ip, agent_port);
    delay(2000);

    allocator = rcl_get_default_allocator();

    // create init_options
    rclc_support_init(&support, 0, NULL, &allocator);

    // create node
    rclc_node_init_default(&node, "micro_ros_platformio_node", "", &support);
}

// Start executors for publisher and subscriber
void RosPubSub::executors_start()
{
    // create executor subscriber
    rclc_executor_init(&executor_sub, &support.context, 1, &allocator);
    rclc_executor_add_subscription(&executor_sub, &cmd_vel_sub, &cmd_vel_msg, &RosPubSub::cmd_vel_callback, ON_NEW_DATA);

    // create executor publisher
    rclc_executor_init(&executor_pub, &support.context, 1, &allocator);
    rclc_executor_add_timer(&executor_pub, &timer);
}

// Publisher timer callback
void timer_callback(rcl_timer_t *timer, int64_t last_call_time)
{
    u_int16_t msg_array[2] = {enc_left, enc_right};
    msg_multiarray.data.size = 2;
    msg_multiarray.data.data = msg_array;
    rcl_publish(&publisher, &msg_multiarray, NULL);
}

// Define publisher and subscriber
void RosPubSub::pub_sub_define()
{
    // create subscriber
    // subscribe to 'cmd_vel' topic
    rclc_subscription_init_default(
        &cmd_vel_sub,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
        "cmd_vel");

    // create publisher
    rclc_publisher_init_default(
        &publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, UInt16MultiArray),
        "encoder_counts");

    // create timer (publish period milli seconds)
    const unsigned int timer_timeout = 500;
    rclc_timer_init_default(
        &timer,
        &support,
        RCL_MS_TO_NS(timer_timeout),
        timer_callback);
}

// Subscriber callback
void RosPubSub::cmd_vel_callback(const void *msg_recv)
{
    const geometry_msgs__msg__Twist *recieved_data = (const geometry_msgs__msg__Twist *)msg_recv;

    // Save recieved data into fields
    float linear_vel = recieved_data->linear.x;
    float angular_vel = recieved_data->angular.z;

    // Debug
    Serial.print(linear_vel);
    Serial.print(" , ");
    Serial.println(angular_vel);

    // Move robot according to commands
    // Display direction arrows
    if (linear_vel > 0)
    {
        // Serial.println("forward");J
        direction = 1;
        displayArrow("forward");
    }
    else if (linear_vel < 0)
    {
        // Serial.println("backward");
        direction = 2;
        displayArrow("backward");
    }
    else if (angular_vel > 0)
    {
        // Serial.println("left");
        direction = 3;
        displayArrow("left");
    }
    else if (angular_vel < 0)
    {
        // Serial.println("right");
        direction = 4;
        displayArrow("right");
    }
    else
    {
        // Serial.println("stop");
        direction = 0;
        displayArrow("stop");
    }
}

// Start publishing and subscribing to topics
void RosPubSub::start_msgs()
{
    rclc_executor_spin_some(&executor_pub, RCL_MS_TO_NS(100));
    rclc_executor_spin_some(&executor_sub, RCL_MS_TO_NS(100));
}
