# PC 서버

---

# 실행 방법

## 프로젝트 폴더 이동

```bash
cd SLAM_PROJECT/
```

---

## SERVER 폴더 이동

```bash
cd SERVER/
```

---

## ROS2 Workspace 이동

```bash
cd ros2_ws/
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

# Server 실행 순서

## 1. SLAM 서버 Launch 실행

Cartographer 기반 SLAM 서버를 실행합니다.

```bash
ros2 launch amr_server server.launch.py
```

---

## 2. RViz2 실행 (새 터미널 필요)

SLAM 지도, LiDAR Scan, TF 정보를 시각화하기 위해 새 터미널을 추가로 실행한 뒤 RViz2를 실행합니다.

### 새 터미널 실행 후:

```bash
cd SLAM_PROJECT/SERVER/ros2_ws/
```

```bash
source install/setup.bash
```

```bash
rviz2
```

---

# 실행 명령어 설명

| 명령어 | 역할 |
|---|---|
| `ros2 launch amr_server server.launch.py` | Cartographer 기반 SLAM 서버 실행 |
| `rviz2` | 지도 및 센서 데이터 시각화 |

---

# 폴더 구조

```text
SERVER
└── ros2_ws
    ├── README.md
    └── src
        └── amr_server
            ├── amr_server
            ├── launch
            │   └── server.launch.py
            ├── params
            │   └── slampibot_cartographer.lua
            ├── resource
            ├── test
            ├── package.xml
            ├── setup.py
            └── setup.cfg
```

---

# 폴더 설명

## launch/

ROS2 Launch 파일을 저장하는 폴더입니다.

| 파일명 | 설명 |
|---|---|
| `server.launch.py` | SLAM 서버 실행 Launch 파일 |

---

## params/

Cartographer SLAM 설정 파일을 저장하는 폴더입니다.

| 파일명 | 설명 |
|---|---|
| `slampibot_cartographer.lua` | Cartographer SLAM 설정 파일 |

---

## amr_server/

ROS2 Python 패키지 폴더입니다.

서버 측 SLAM 실행과 관련된 Python 패키지 구성을 포함합니다.

---

## resource/

ROS2 Python 패키지 인식을 위한 리소스 파일이 저장되는 폴더입니다.

---

## test/

ROS2 패키지 테스트 파일이 저장되는 폴더입니다.

---

# SLAM 데이터 흐름

```text
RPLidar C1
    ↓
/scan
    ↓
cartographer_node
    ↓
/map
    ↓
RViz2
```

---

# 주요 토픽

| Topic | 역할 |
|---|---|
| `/scan` | LiDAR 거리 데이터 |
| `/map` | SLAM Occupancy Grid Map |
| `/tf` | 동적 좌표 변환 |
| `/tf_static` | 고정 좌표 변환 |
| `/submap_list` | Cartographer Submap 정보 |

---

# RViz2 시각화 항목

RViz2에서 다음 항목을 추가하여 SLAM 상태를 확인할 수 있습니다.

| Display | Topic / Frame | 설명 |
|---|---|---|
| LaserScan | `/scan` | LiDAR 거리 데이터 확인 |
| Map | `/map` | 생성된 지도 확인 |
| TF | `/tf`, `/tf_static` | 좌표계 연결 확인 |
| RobotModel | `base_link` 기준 | 로봇 모델 확인 |

---

# 참고 사항

- ROS2 Humble 기반 개발
- Ubuntu 22.04 환경에서 실행
- `server.launch.py` 실행 후 RViz2는 반드시 별도 터미널에서 실행
- RViz2 실행 전 `source install/setup.bash` 수행 필요
- SLAM 지도 확인을 위해 `/map`, `/scan`, `/tf` 토픽 상태 확인 필요
