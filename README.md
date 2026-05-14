
Ubuntu PC 서버에서 실행되는 ROS2 SLAM 모니터링 패키지입니다.

서버 PC는 Raspberry Pi에서 전달되는 LiDAR 데이터를 기반으로 SLAM을 실행하고, RViz2를 통해 지도와 센서 데이터를 시각화합니다.

---

# 주요 기능

- ROS2 Humble 기반 SLAM 실행
- Cartographer 설정 관리
- Occupancy Grid Map 생성
- RViz2를 통한 지도 시각화
- Raspberry Pi 로봇 시스템과 연동

---

# 개발 환경

| 항목 | 내용 |
|---|---|
| PC | Ubuntu Server PC |
| OS | Ubuntu 22.04 |
| ROS Version | ROS2 Humble |
| SLAM | Cartographer ROS |
| Visualization | RViz2 |
| Build Tool | colcon |

---

# 프로젝트 목적

본 서버 패키지는 병원 자율주행 AMR 프로젝트에서 SLAM 지도 생성과 모니터링을 담당합니다.

Raspberry Pi가 로봇 하드웨어 제어를 담당하고, Server PC는 SLAM 실행 및 RViz2 시각화를 담당합니다.

---