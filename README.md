# Vector Bot Lite MicroROS

**Vector Bot Lite** is a robotics project designed to integrate a low-cost differential drive robot with the MicroROS framework. This repository showcases the power of MicroROS for real-time communication and control in robotic systems.

---

## About the Project

Vector Bot Lite is an ongoing project that focuses on integrating **MicroROS** into a low-cost differential drive robot. This is an extension of ROS 2 tailored for microcontrollers. This project demonstrates how to enable efficient robotic communication with limited hardware resources, suitable for lightweight and modular robotics applications.

---

## Features

- **MicroROS Integration**: Seamless communication between custom built differential drive robot and ROS 2 systems.
- **Real-time Control**: Execute precise movements and commands with minimal latency.
- **Scalable Architecture**: Supports easy upgrades and feature extensions.
- **Cross-platform Compatibility**: Compatible with Linux, Windows, and macOS.

---

## Requirements

- **[MicroROS Agent](https://micro.ros.org/docs/tutorials/core/first_application_linux/)**: Follow the steps on the page to create a MicroROS agent.
- **ROS 2 Humble**: The latest version of the Robot Operating System.
- **[PlatformIO](https://platformio.org/)**: Available as VSCode extension.
- **EPS32 WROOM-DA Microcontroller**: Check [this page](https://micro.ros.org/docs/overview/hardware/) for hardware compatability.

## Harware Requirements
- ESP32 WROOM-DA Module with expansion board
- TT Gearbox Motors with encoder disks x2
- Wheels with rubber tires x2
- L298N Motor Driver
- 7.4V Lipo battery
- Optical encoders x2
- LM2596 DC-DC Buck converter
- SSD1306 OLED I2C 128x64 Display

---

## Getting Started

### Prerequisites and Installation
Clone the repository and open the project on PlatformIO.

```bash
# Clone the repository
git clone git@github.com:nsaitarun-git/VectorBot_MicorROS_v3.git
```
### Update WiFi Credentials
Within the ```/lib/ros_publisher_subscriber/ros_publisher_subscriber.cpp``` file, edit the following lines with your WiFi credentials and PC IP address.

```c++
// Wifi credentials
IPAddress agent_ip(192, 168, 0, 0);
char ssid[] = "yourssid";
char psk[] = "yourpassword";
```

### Start the MicroROS Agent via WiFi
Navigate to the MicroROS agent workspace directory and enter the following commands.

```bash
# Source the workspace
source install/setup.bash 

# Start the agent
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888
```

### Start Controlling the Robot
The ```teleop_twist_keyboard``` package can be used to drive the robot. It can be installed with the following commands.

```bash
# Install teleop_twist_keyboard pkg
sudo apt-get update
sudo apt-get install ros-humble-teleop-twist-keyboard
```
Once the package has been installed, you can run the node using the following command.

```bash
ros2 run teleop_twist_keyboard teleop_twist_keyboard
```
You should be able to the drive the robot using your keyboard now. You can also see the encoder counts or "ticks" with the ```/encoder_counts``` topic. 
Use the following command to view the data being published to the topic.

```bash
ros2 topic echo /encoder_counts
```
# License
This project is licensed under the MIT License. See the [LICENSE](https://github.com/nsaitarun-git/VectorBot_MicorROS_v3/blob/main/LICENSE) file for details.
