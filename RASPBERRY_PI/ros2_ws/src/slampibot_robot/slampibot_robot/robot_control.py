import serial
import time
import sys
import tty
import termios

# ======================================================
# 시리얼 설정 (아두이노 연결 포트 확인 필수)
# 보통 '/dev/ttyACM0' 또는 '/dev/ttyUSB0'입니다.
# ======================================================
try:
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
except:
    try:
        ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
    except:
        print("아두이노를 찾을 수 없습니다. USB 연결을 확인하세요.")
        sys.exit()

def getch():
    """키보드 입력을 즉시 읽어오는 함수"""
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(sys.stdin.fileno())
        ch = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ch

print("---------------------------------------")
print(" 아두이노 로봇 시리얼 제어 프로그램")
print(" f: 전진, b: 후진, l: 좌회전, r: 우회전")
print(" s: 정지, q: 프로그램 종료")
print("---------------------------------------")

try:
    while True:
        # 키보드 입력 받기
        key = getch().lower()

        # 아두이노 코드가 인식하는 명령어로 변환하여 전송
        if key in ['f', 'b', 'l', 'r', 's']:
            ser.write(key.encode())
            print(f"\r명령 전송: {key}", end="")
        
        elif key == 'q':
            ser.write(b's')  # 종료 전 정지 명령 전송
            print("\n프로그램을 종료합니다.")
            break

        # 아두이노에서 보낸 센서 데이터(온습도, 거리) 읽기
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            print(f"\n[아두이노 데이터] {line}")

except KeyboardInterrupt:
    ser.write(b's')
    print("\n중단되었습니다.")

finally:
    ser.close()