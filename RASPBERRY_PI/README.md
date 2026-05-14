# RASPBERRY_PI

병원 자율주행 AMR(Autonomous Mobile Robot)의 Raspberry Pi 기반 ROS2 제어 패키지입니다.

Raspberry Pi는 ROS2 Humble 환경에서 LiDAR SLAM, Raspberry Pi Camera 스트리밍, Serial 기반 Arduino 제어 기능을 수행합니다.

---

# 주요 기능

- ROS2 기반 로봇 제어
- `/cmd_vel` 속도 명령 처리
- Arduino Serial UART 통신
- LiDAR 기반 SLAM
- Raspberry Pi Camera 영상 스트리밍
- ROS2 Launch 시스템 구성

---

# 개발 환경

| 항목 | 내용 |
|---|---|
| SBC | Raspberry Pi 4 |
| OS | Ubuntu 22.04 |
| ROS Version | ROS2 Humble |
| Language | Python |
| Build Tool | colcon |

---

# 실행 방법

## Workspace 이동

```bash
cd ~/ros2_ws
```

---

## 빌드

```bash
colcon build
```

---

## 환경 설정

```bash
source install/setup.bash
```

---

# Raspberry Pi 실행 순서

## 1. 로봇 제어 노드 실행

`/cmd_vel` 토픽을 구독하여 Arduino로 Serial 명령을 전달하는 노드입니다.

```bash
ros2 run slampibot_robot robot_control
```

---

## 2. SLAM Launch 실행

LiDAR 및 SLAM 시스템을 실행합니다.

```bash
ros2 launch slampibot_robot slam.launch.py
```

---

## 3. Raspberry Pi Camera 노드 실행

Raspberry Pi Camera 영상을 ROS2 토픽으로 발행합니다.

```bash
ros2 run camera_ros camera_node --ros-args -p width:=640 -p height:=480 -p format:=YUYV
```

---

# 실행 노드 설명

| 명령어 | 역할 |
|---|---|
| `ros2 run slampibot_robot robot_control` | Arduino Serial 제어 |
| `ros2 launch slampibot_robot slam.launch.py` | LiDAR 및 SLAM 실행 |
| `ros2 run camera_ros camera_node` | Raspberry Pi Camera 영상 발행 |

---

# 카메라 설정

| 항목 | 값 |
|---|---|
| Width | 640 |
| Height | 480 |
| Format | YUYV |

---

# 카메라 토픽 예시

| Topic | 역할 |
|---|---|
| `/image_raw` | 카메라 원본 영상 |
| `/camera_info` | 카메라 정보 |

---

# ROS2 토픽 구조

| Topic | 역할 |
|---|---|
| `/cmd_vel` | 로봇 속도 명령 |
| `/scan` | LiDAR 거리 데이터 |
| `/map` | Occupancy Grid Map |
| `/tf` | 동적 좌표 변환 |
| `/tf_static` | 고정 좌표 변환 |
| `/image_raw` | 카메라 영상 데이터 |

---

# 전체 시스템 실행 구조

```text
Raspberry Pi Camera
        ↓
    camera_node
        ↓
    /image_raw

RPLidar C1
        ↓
      /scan
        ↓
cartographer_node
        ↓
      /map

teleop_twist_keyboard
        ↓
     /cmd_vel
        ↓
   robot_control
        ↓
    Serial UART
        ↓
    Arduino Uno
```

---

# 폴더 구조

```text
RASPBERRY_PI
└── ros2_ws
    └── src
        └── slampibot_robot
            ├── launch
            ├── resource
            ├── slampibot_robot
            ├── test
            ├── package.xml
            ├── setup.py
            └── setup.cfg
```

---

# 사용 패키지

| 패키지 | 역할 |
|---|---|
| `rclpy` | ROS2 Python 클라이언트 |
| `geometry_msgs` | 속도 명령 메시지 |
| `sensor_msgs` | 센서 데이터 메시지 |
| `cartographer_ros` | SLAM |
| `rviz2` | 시각화 |
| `camera_ros` | 카메라 영상 발행 |

---

# SLAM 구성

| 항목 | 내용 |
|---|---|
| Sensor | RPLidar C1 |
| SLAM | Cartographer ROS |
| Map Resolution | 0.05 |
| Frame Structure | map → odom → base_link |

---

# 프로젝트 목적

본 프로젝트는 병원 환경에서 혈액 및 의료 물품을 안전하게 운반하기 위한 자율주행 AMR 플랫폼 개발을 목표로 합니다.

Raspberry Pi는 ROS2 기반 메인 제어 시스템 역할을 수행합니다.

---

# 향후 개선 사항

- Navigation2 적용
- Encoder 기반 주행 제어
- IMU 센서 추가
- 자율 경로 계획
- Multi-floor Navigation
- 병원 환경 실증 테스트 확대

---

# 참고 사항

- ROS2 Humble 기반 개발
- Ubuntu PC와 네트워크 기반 연동
- RViz2를 통한 실시간 지도 시각화 지원
- Raspberry Pi ↔ Arduino Serial UART 통신 사용
- Raspberry Pi Camera Module 기반 영상 스트리밍 사용
