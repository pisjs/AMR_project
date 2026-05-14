include "map_builder.lua"      -- 기본 맵 생성 라이브러리 포함
include "trajectory_builder.lua" -- 로봇 경로 생성 라이브러리 포함

options = {
  map_builder = MAP_BUILDER,        -- 사용할 맵 빌더 객체 지정
  trajectory_builder = TRAJECTORY_BUILDER, -- 사용할 경로 빌더 객체 지정
  map_frame = "map",                -- 지도의 기준 좌표계 이름
  tracking_frame = "base_link",     -- SLAM이 추적할 로봇의 중심 좌표계 (바퀴 중심)
  published_frame = "base_link",    -- 위치 정보를 발행할 기준 좌표계
  odom_frame = "odom",              -- 주행 기록(Odometry) 좌표계 이름
  provide_odom_frame = true,        -- 엔코더가 없으므로 SLAM이 가상 odom 좌표를 직접 생성함
  publish_frame_projected_to_2d = true, -- 모든 위치 정보를 2D 평면(지면)에 투사하여 발행
  use_odometry = false,             -- 하드웨어 엔코더 데이터를 사용하지 않음 (우리 로봇 상황)
  use_nav_sat = false,              -- GPS 데이터를 사용하지 않음
  use_landmarks = false,            -- 특정 랜드마크 인식 기능을 사용하지 않음
  num_laser_scans = 1,              -- 사용하는 라이다 센서의 개수 (RPLidar 1개)
  num_multi_echo_laser_scans = 0,   -- 멀티 에코 라이다 기능 미사용 (일반 라이다는 0)
  num_subdivisions_per_laser_scan = 1, -- 한 번의 라이다 스캔을 쪼개서 처리할 단위
  num_point_clouds = 0,             -- 3D 포인트클라우드 데이터 미사용
  lookup_transform_timeout_sec = 0.2, -- 좌표 변환(TF)을 기다려주는 최대 시간
  submap_publish_period_sec = 0.3,  -- 부분 지도(Submap)를 업데이트하는 주기
  pose_publish_period_sec = 5e-3,   -- 로봇의 현재 위치(Pose)를 발행하는 주기 (0.005초)
  trajectory_publish_period_sec = 30e-3, -- 이동 경로를 발행하는 주기
  rangefinder_sampling_ratio = 1.,  -- 라이다 데이터 샘플링 비율 (1.0 = 100% 사용)
  odometry_sampling_ratio = 1.,     -- 오도메트리 데이터 샘플링 비율
  fixed_frame_pose_sampling_ratio = 1., -- 고정 프레임 데이터 샘플링 비율
  imu_sampling_ratio = 1.,          -- IMU 데이터 샘플링 비율
  landmarks_sampling_ratio = 1.,    -- 랜드마크 데이터 샘플링 비율
}

MAP_BUILDER.use_trajectory_builder_2d = true -- 2D SLAM 기능을 활성화

-- [2D 경로 빌더 세부 설정]
TRAJECTORY_BUILDER_2D.min_range = 0.12         -- 라이다 측정 최소 거리 (이보다 가까우면 무시)
TRAJECTORY_BUILDER_2D.max_range = 12.0         -- 라이다 측정 최대 거리 (C1 사양에 맞춰 12m)
TRAJECTORY_BUILDER_2D.missing_data_ray_length = 12.0 -- 데이터가 없는 방향을 벽이 없다고 판단할 거리
TRAJECTORY_BUILDER_2D.use_imu_data = false     -- IMU 데이터를 사용하지 않음 (우리 로봇 상황)
TRAJECTORY_BUILDER_2D.use_online_correlative_scan_matching = true -- 스캔 데이터를 비교해 위치를 찾는 기능 (엔코더 없을 때 필수)
TRAJECTORY_BUILDER_2D.motion_filter.max_angle_radians = math.rad(0.1) -- 로봇이 0.1도 이상 회전했을 때만 지도를 업데이트함

-- [포즈 그래프(지도 최적화) 설정]
POSE_GRAPH.constraint_builder.min_score = 0.65 -- 지도 생성 시 두 데이터가 65% 이상 일치해야 연결함
POSE_GRAPH.constraint_builder.global_localization_min_score = 0.7 -- 위치를 완전히 잃었을 때 다시 찾기 위한 최소 일치 점수

return options -- 설정값 반환
