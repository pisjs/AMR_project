import os # 운영체제의 파일 경로 기능을 사용하기 위해 불러옴
from glob import glob # 폴더 내의 여러 파일들을 패턴(*.py 등)으로 찾기 위해 불러옴
from setuptools import find_packages, setup # ROS2 패키지 빌드 및 설치를 위한 도구

package_name = 'slampibot_robot' # 패키지 이름을 변수로 정의 (오타 방지)

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']), # 테스트 폴더를 제외한 파이썬 패키지 자동 검색
    data_files=[
        # [기본] ROS2 시스템이 이 패키지를 인식하게 만드는 인덱스 파일 등록
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        
        # [기본] 패키지의 정보(의존성 등)가 담긴 XML 파일 등록
        ('share/' + package_name, ['package.xml']),
        
        # [실행] launch 폴더 안의 모든 .launch.py 파일들을 설치 경로로 복사
        # (이게 있어야 ros2 launch 명령어가 작동합니다)
        (os.path.join('share', package_name, 'launch'), glob('launch/*.launch.py')),
        
        # [설정] params 폴더 안의 모든 파일(주로 .lua)들을 설치 경로로 복사
        # (Cartographer SLAM이 이 경로에서 설정값을 읽어옵니다)
        (os.path.join('share', package_name, 'params'), glob('params/*')),
        
        # [참고] urdf나 rviz 폴더는 현재 비어있으므로 등록하지 않습니다.
        # 나중에 파일이 생기면 위와 같은 형식으로 추가하면 됩니다.
    ],
    install_requires=['setuptools'], # 설치 시 필요한 파이썬 라이브러리
    zip_safe=True, # 파일을 압축해서 설치할지 여부 (ROS2는 보통 True)
    maintainer='pisjs', # 패키지 관리자 이름
    maintainer_email='pisjs@todo.todo', # 관리자 이메일
    description='4WD Robot SLAM Package without Encoder/IMU', # 패키지 설명
    license='TODO: License declaration', # 라이선스 정보
    tests_require=['pytest'], # 테스트 도구
    entry_points={
        'console_scripts': [
            # 직접 만든 파이썬 노드 실행 파일 등록
            'robot_control = slampibot_robot.robot_control:main',
        ],
    },
)
