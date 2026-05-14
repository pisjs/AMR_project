#include <AFMotor.h>          // Adafruit Motor Shield 라이브러리 (모터 제어용)
#include <DHT.h>             // DHT 센서 라이브러리 (온습도 측정용)
#include <Wire.h>            // I2C 통신 라이브러리
#include <LiquidCrystal_I2C.h> // I2C LCD 제어 라이브러리

// 1. 모터 및 센서 설정 (수정됨)
AF_DCMotor m1(1); // 오른쪽 뒷바퀴 (Rear Right)
AF_DCMotor m2(2); // 오른쪽 앞바퀴 (Front Right)
AF_DCMotor m3(3); // 왼쪽 앞바퀴 (Front Left)
AF_DCMotor m4(4); // 왼쪽 뒷바퀴 (Rear Left)

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD 주소(0x27), 16열 2행 설정

const int trigPin = A0; // 초음파 센서 Trig 핀을 아날로그 A0에 연결
const int echoPin = A1; // 초음파 센서 Echo 핀을 아날로그 A1에 연결

#define DHTPIN A2       // DHT11 데이터 핀을 아날로그 A2에 연결
#define DHTTYPE DHT11   // 센서 타입을 DHT11로 정의
DHT dht(DHTPIN, DHTTYPE); // DHT 객체 초기화

// --- 속도 설정 (전진 속도만 독립적으로 수정) ---
int forwardSpeed = 200; // 전진 시 모터 속도 (0~255 사이)
int moveSpeed = 135;    // 후진 등 평상시 기본 이동 속도
int turnSpeed = 230;    // 회전 시 마찰을 이기기 위한 높은 속도
// ----------------------

unsigned long lastUpdate = 0; // LCD/센서 데이터 업데이트 주기 계산용 변수
char currentCmd = 's';        // 현재 로봇의 상태(명령어) 저장 (기본값 's' = 정지)

void setup() {
  Serial.begin(9600);        // PC와의 시리얼 통신 속도 설정
  pinMode(trigPin, OUTPUT);  // 초음파 발사 핀을 출력으로 설정
  pinMode(echoPin, INPUT);   // 초음파 수신 핀을 입력으로 설정
  dht.begin();               // 온습도 센서 작동 시작
  
  lcd.init();                // LCD 초기화
  lcd.backlight();           // LCD 백라이트 켜기
  lcd.clear();               // LCD 화면 지우기
}

// 초음파를 이용해 거리를 계산하는 함수
long getDistance() {
  digitalWrite(trigPin, LOW); delayMicroseconds(2); // 핀 초기화
  digitalWrite(trigPin, HIGH); delayMicroseconds(10); // 10마이크로초 동안 초음파 발사
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 20000); // 반사되어 돌아온 시간 측정 (타임아웃 20ms)
  long dist = duration * 17 / 1000; // 시간을 cm 단위 거리로 변환 (음속 기반 계산)
  return (dist <= 0) ? 999 : dist;  // 측정이 안 되면 999 반환, 아니면 거리값 반환
}

// 모든 모터의 속도를 한 번에 설정하는 함수
void setAllSpeed(int s) {
  m1.setSpeed(s); m2.setSpeed(s); m3.setSpeed(s); m4.setSpeed(s);
}

// 전진 함수 (요청사항 반영 수정)
void moveForward()  { 
  setAllSpeed(forwardSpeed); // 전진용 속도 적용
  // 배선 상태에 맞춘 전진 방향 설정
  m1.run(FORWARD);  // 오른쪽 뒷바퀴
  m2.run(BACKWARD); // 오른쪽 앞바퀴 (반대로 수정됨)
  m3.run(BACKWARD); // 왼쪽 앞바퀴
  m4.run(BACKWARD); // 왼쪽 뒷바퀴
}

// 후진 함수
void moveBackward() { 
  setAllSpeed(moveSpeed); // 일반 이동 속도 적용
  // 전진과 반대 방향으로 설정 (전진 설정을 기준으로 반전)
  m1.run(BACKWARD); m2.run(FORWARD); m3.run(FORWARD);  m4.run(FORWARD);  
}

// 좌회전 함수 (제자리 회전)
void turnLeft() { 
  setAllSpeed(turnSpeed); // 회전용 속도 적용
  // 우측은 전진 방향, 좌측은 후진 방향으로 회전
  m1.run(FORWARD);  m2.run(BACKWARD); 
  m3.run(FORWARD);  m4.run(FORWARD); 
} 

// 우회전 함수 (제자리 회전)
void turnRight() { 
  setAllSpeed(turnSpeed); 
  // 좌측은 전진 방향, 우측은 후진 방향으로 회전
  m1.run(BACKWARD); m2.run(FORWARD);  
  m3.run(BACKWARD); m4.run(BACKWARD); 
} 

// 모든 모터 정지 함수
void stopRobot() { m1.run(RELEASE);  m2.run(RELEASE);  m3.run(RELEASE);  m4.run(RELEASE);  }

void loop() {
  long distance = getDistance(); // 매 루프마다 현재 전방 거리 측정

  // 블루투스나 시리얼 모니터로부터 새로운 명령이 들어왔는지 확인
  if (Serial.available() > 0) {
    currentCmd = Serial.read(); // 들어온 문자를 currentCmd에 저장
  }

  // 장애물 감지 및 주행 로직
  if (currentCmd == 'f' && distance <= 25) { 
    // 전진 중인데 앞에 장애물이 25cm 이내에 있으면
    stopRobot(); // 강제로 정지 (충돌 방지)
  } else {
    // 입력된 명령어에 따라 동작 수행
    if (currentCmd == 'f') moveForward();       // 'f' 입력 시 전진
    else if (currentCmd == 'b') moveBackward();  // 'b' 입력 시 후진
    else if (currentCmd == 'l') turnLeft();      // 'l' 입력 시 좌회전
    else if (currentCmd == 'r') turnRight();     // 'r' 입력 시 우회전
    else stopRobot();                            // 그 외의 경우(또는 's') 정지
  }

  // 2초(2000ms)마다 센서 값 업데이트 및 LCD 출력
  if (millis() - lastUpdate >= 2000) {
    lastUpdate = millis(); // 마지막 업데이트 시간 갱신
    float h = dht.readHumidity();    // 습도 읽기
    float t = dht.readTemperature(); // 온도 읽기

    // LCD 첫 번째 줄 표시 (온도, 습도)
    lcd.setCursor(0, 0);
    lcd.print("T:"); lcd.print((int)t); lcd.print("C  H:"); lcd.print((int)h); lcd.print("%   ");
    // LCD 두 번째 줄 표시 (거리)
    lcd.setCursor(0, 1);
    lcd.print("Dist: "); lcd.print(distance); lcd.print("cm      "); 

    // 시리얼 모니터로 데이터 전송 (앱이나 PC에서 모니터링용)
    Serial.print("T:"); Serial.print(t);
    Serial.print(",H:"); Serial.print(h);
    Serial.print(",D:"); Serial.println(distance);
  }
}