# ARDUINO

병원 자율주행 AMR(Autonomous Mobile Robot)의 Arduino 제어 코드입니다.

Arduino Uno를 기반으로 모터 제어, 초음파 센서 측정, LCD 출력 기능을 수행합니다.

Raspberry Pi와 Serial UART 통신을 통해 ROS2 명령을 수신하여 로봇을 제어합니다.

---

# 주요 기능

- DC 모터 제어
- 초음파 장애물 감지
- LCD 상태 출력
- Raspberry Pi Serial 통신
- 자율주행 보조 제어

---

# 하드웨어 구성

| 장치 | 모델 |
|---|---|
| MCU | Arduino Uno |
| Motor Driver | L293D |
| Motor | DC Motor ×4 |
| Ultrasonic Sensor | HC-SR04 |
| LCD | I2C LCD 16x2 |
| Temperature Sensor | DHT11 |

---

# 폴더 구조

```text
ARDUINO
│
└── robot_control
    └── robot_control.py.ino
