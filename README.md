# ELEGOO Smart Robot Car V4.0 Baseline for ROS2

## 🚀 Not the official code (yet), just for personal use!  
By **Ki-Hwan Oh**

---

## 🔗 Official Resources
- [Official Website](https://www.elegoo.com/blogs/arduino-projects/elegoo-smart-robot-car-kit-v4-0-tutorial?srsltid=AfmBOorYwe8JgJe90HhXPzKqtYqGKDxzCjyLMzpd4t6CisLi9G8mrOoW)
- [Official GitHub Repository](https://github.com/elegooofficial/ELEGOO-Smart-Robot-Car-Kit-V4.0)

---

## 📋 Summary
The official code is designed mainly for their mobile app to control the robot.

This repository aims to make the robot usable with **ROS2** for advanced applications.

Additionally, the header files for each sensor are modular, allowing others to use them for various purposes.

The codes in this repo transmit the Arduino's serial outputs and the camera stream through the ESP32 Wi-Fi.

Feel free to start a discussion if you have innovative ideas to share! 😊

---
## ⚙️ Setup
[Arduino-CLI with VS Code Setup](./mySRC_v1/Readme.md)

---
## 📟 Available Sensors and Features
| Status | Component                | Comments                                                  |
|--------|--------------------------|-----------------------------------------------------------|
| ✅     | **White Square LED**     | Completed.                                                |
| ✅     | **Ultrasonic Sensor**    | Completed.                                                |
| 🟨     | **IR Sensor**            | Code ready, but there are issues with the sensor.         |
| ✅     | **Servo Motor**          | Completed (to move the ultrasonic sensor and camera).     |
| ✅     | **Voltage Measurement**  | Completed (A3 pin).                                       |
| ✅     | **Key Detection**        | Used to read the number of clicks.                        |
| ✅     | **ITR20001**             | Completed (Line Tracking).                                |
| ✅     | **Power Motors**         | Completed.                                                |
| ✅     | **MPU6050**              | Completed (Inertial Measurement Unit).                    |
| ✅     | **Camera + Wi-Fi**       | Completed.                                                |

---

## 📃 TODO List
- [ ] Complete a separate repository to read the signals through Wi-Fi and publish them as ROS topics.

---

## ⭐ & 🍴
If you find this repository helpful, click the ⭐ button to show your support!

If you'd like to modify the project, feel free to 🍴 this repo!

[![Star History Chart](https://api.star-history.com/svg?repos=koh43/ros2_smart_car_cpp&type=Date)](https://star-history.com/#koh43/ros2_smart_car_cpp&Date)
