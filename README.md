# AMR Project
병원 환경을 대상으로 한 자율주행 혈액 운반 AMR(Autonomous Mobile Robot) 프로젝트입니다.

ROS2 Humble 기반으로 LiDAR SLAM, 원격 제어, 센서 모니터링 기능을 구현하였습니다.

---

# 프로젝트 개요

본 프로젝트는 병원 내 혈액 및 의료 물품 운반을 목표로 제작된 자율주행 로봇입니다.

주요 기능:

- LiDAR 기반 SLAM 지도 생성
- ROS2 기반 노드 통신
- Raspberry Pi ↔ Arduino Serial 제어
- 초음파 장애물 감지
- LCD 상태 출력
- 원격 주행 제어
- 병원 실내 자율주행 환경 테스트

---

# 시스템 구성

## Hardware

- Raspberry Pi 4
- Arduino Uno
- RPLidar C1
- HC-SR04 Ultrasonic Sensor
- L293D Motor Driver
- DC Motor ×4
- I2C LCD
- DHT11 Sensor

---

# Software

- Ubuntu 22.04
- ROS2 Humble
- Cartographer ROS
- RViz2
- Python
- Arduino IDE

---

# 프로젝트 구조

```text
AMR_project
│
├── ARDUINO
│   └── robot_control
│       └── robot_control.py.ino
│
├── RASPBERRY_PI
│   └── ros2_ws
│       └── src
│           └── slampibot_robot
│
├── SERVER
│   └── ros2_ws
│       └── src
│           └── amr_server
│
└── README.md