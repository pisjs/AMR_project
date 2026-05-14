#!/usr/bin/env python3

import os
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import Command
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    # 1. 패키지 이름 설정: 우리가 만든 패키지 이름을 변수로 지정
    package_name = 'slampibot_robot'
    # 패키지가 설치된 실제 경로(공유 디렉토리)를 가져옵니다.
    pkg_share = get_package_share_directory(package_name)

    # 3. RPLidar C1 드라이버 노드: 하드웨어 라이다로부터 데이터를 받아오는 역할
    rplidar_cmd = Node(
        package='rplidar_ros',
        executable='rplidar_node',
        name='rplidar_node',
        parameters=[{
            'channel_type': 'serial',
            'serial_port': '/dev/ttyUSB0', # 라이다가 연결된 USB 포트 (확인 결과 ttyUSB0)
            'serial_baudrate': 460800,     # C1 모델의 통신 속도
            'frame_id': 'laser',           # 라이다 데이터의 기준점 이름 정의
            'inverted': False,             # 라이다 설치 방향 반전 여부
            'angle_compensate': True,      # 회전 속도에 따른 각도 보정 활성화
        }],
        output='screen'
    )

    # 4. 고정 좌표 변환 (Static TF): 로봇 본체와 센서 사이의 물리적 거리를 계산기(SLAM)에 알려줌
    # [x y z roll pitch yaw] 순서: 본체 중심에서 라이다가 위로 10cm(0.1m) 위에 있다고 선언
    static_tf_cmd = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        arguments=['0', '0', '0.1', '0', '0', '0', 'base_link', 'laser']
    )


    # 실행할 명령 목록(LaunchDescription) 생성 및 노드 추가
    ld = LaunchDescription()

    ld.add_action(rplidar_cmd)      # 라이다 켜기
    ld.add_action(static_tf_cmd)   # 좌표 중심 잡기

    return ld
