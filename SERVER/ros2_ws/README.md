# PC 서버
ros2 버전은 humble 우분투 22.04


slam  모니터링

cd ros2_ws
colcon build
source install/setup.bash

ros2 launch amr_server server.launch.py

위 명령어로 slam 구동 시각화 rvizi2는 따로 실행할 것