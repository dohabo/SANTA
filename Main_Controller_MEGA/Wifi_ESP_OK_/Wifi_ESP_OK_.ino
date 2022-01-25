#include <SoftwareSerial.h>
#include <WiFiEsp.h>
#include <Servo.h>
#include <Pixy2.h>

//Wifi 설정 및 Wifi pin 설정
char ssid[] = "iptime";
char pass[] = "asdf1234";
int status = WL_IDLE_STATUS;
//SoftwareSerial myserial(42,43);
IPAddress serverIP(192,168,0,58);
WiFiEspClient client;
char strBuf[255];

// 적외선 센서
int sensor = 35; // 적외선 센서 핀

//로봇1 세팅값
Servo Servo1_1;
Servo Servo1_2;
Servo Servo1_3;
Servo Servo1_4;

// 로봇2 세팅값
Servo Servo2_1;
Servo Servo2_2;
Servo Servo2_3;
Servo Servo2_4;


// 로봇3 세팅값
Servo Servo3_1;
Servo Servo3_2;
Servo Servo3_3;
Servo Servo3_4;

//컨베이어 핀
#define MOTOR_A1 22
#define MOTOR_A2 23

//이미지센서
Pixy2 pixy;

void setup() {
  Serial.begin(115200);
  
  //WiFi 세팅
  Serial3.begin(9600);
  Serial.setTimeout(20);
  WiFi.init(&Serial3);
  Serial3.setTimeout(20);
  while(status != WL_CONNECTED){
    Serial.print("Attempting to connect to WPA SSID:");
    Serial.print(ssid);
    status = WiFi.begin(ssid,pass);
  }
  Serial.println("You're connected to the network");
  client.connect(serverIP,7788);
  Servo1_1.attach(2);
  Servo1_2.attach(3);
  Servo1_3.attach(4);
  Servo1_4.attach(5);
  Servo2_1.attach(6);
  Servo2_2.attach(7);
  Servo2_3.attach(8);
  Servo2_4.attach(9);
  Servo3_1.attach(10);
  Servo3_2.attach(11);
  Servo3_3.attach(12);
  Servo3_4.attach(13);
  
  //**로봇1 초기위치 세팅
  Servo1_1.write(40);
  Servo1_2.write(130);
  Servo1_3.write(150);
  Servo1_4.write(90);
  
  //**로봇2 초기위치 세팅
  Servo2_1.write(90);
  Servo2_2.write(30);
  Servo2_3.write(60);
  Servo2_4.write(90);

  //**로봇3 초기위치 세팅
  Servo3_1.write(120);
  Servo3_2.write(30);
  Servo3_3.write(50);
  Servo3_4.write(90);
  
  //*적외선 센서 세팅
  pinMode(sensor,INPUT);
  
  //**컨베이어 세팅
  pinMode(A0,INPUT);
  pinMode(MOTOR_A1,OUTPUT);
  pinMode(MOTOR_A2,OUTPUT);
  pixy.init();
}

void loop() {
  int IR = digitalRead(sensor);
  if(IR == LOW){                // 적외선 센서로 상자 재고 확인
    client.print("OPR1_END");
    Serial.println("OPR1전송 완료");
    delay(3000);
  }
  if(client.available()){
    String msg = client.readString();
    Serial.println(msg);
    if(msg == "OPR2_START"){    // 컨베이어로 이동 로봇 작동 및 컨베이어 작동 , 정지
      Serial.println("이동로봇작동");
      robot1();
      delay(1000);
      Serial.println("이동로봇작동 완료");
      Serial.println("컨베이어 작동 시작");
      int conv_timer = 0;
      while(true){
        conveyor();
        conv_timer++;
        if(conv_timer > 2000){ // 컨베이어 작동 시간
          pinMode(MOTOR_A1,0);
          pinMode(MOTOR_A2,0);
          break;
        }
      }
      conv_timer = 0;
      Serial.println("컨베이어 정지");
      client.print("OPR2_END");
      Serial.println("OPR2종료 송신");
    }
    if(msg == "OPR3_START"){    // 상자에 리본 부착 로봇 작동 및 컨베이어 작동, 정지
      Serial.println("생산로봇작동");
      robot2(); // 리본 부착 로봇 동작 소스 필요
      delay(1000);
      Serial.println("생산로봇 작동 완료");
      Serial.println("컨베이어 작동 시작");
      pinMode(MOTOR_A1,OUTPUT);
      pinMode(MOTOR_A2,OUTPUT);
      int conv_timer = 0;
      while(true){
        conveyor();
        conv_timer++;
        if(conv_timer > 700){ // 컨베이어 작동 시간
          pinMode(MOTOR_A1,0);
          pinMode(MOTOR_A2,0);
          break;
        }
      }
      conv_timer = 0;
      Serial.println("컨베이어 정지");
      client.print("OPR3_END");
      Serial.println("OPR3종료 송신");
    }
    if(msg == "OPR4_START"){    // 비전 검사 작동, 양품 불량품에 따라 송신 신호 달라야 함
      Serial.println("검사로봇작동");
      delay(3000);
      pixy_();
      Serial.println("검사로봇 작동 완료");
      pinMode(MOTOR_A1,OUTPUT);
      pinMode(MOTOR_A2,OUTPUT);
      int conv_timer = 0;
      while(true){
        conveyor();
        conv_timer++;
        if(conv_timer > 1500){ // 컨베이어 작동 시간
          pinMode(MOTOR_A1,0);
          pinMode(MOTOR_A2,0);
          break;
        }
      }
      conv_timer = 0;
      delay(1000);
    }
    if(msg == "OPR5_START"){    // 썰매에 적재하는 로봇 작동(양품일 경우)
      Serial.println("썰매적재 로봇작동");
      robot3_1();
      delay(1000);
      Serial.println("썰매적재 로봇작동");
      client.print("OPR5_END");
      Serial.println("OPR5종료 송신");
    }
    if(msg == "OPR6_START"){    // 불량품 이동하는 로봇 작동(불량품일 경우)
      Serial.println("불량품 이동 로봇작동");
      robot3_2();
      delay(1000);
      Serial.println("불량품 이동 로봇작동");
      client.print("OPR6_END");
      Serial.println("OPR6종료 송신");
    }
  }
}
