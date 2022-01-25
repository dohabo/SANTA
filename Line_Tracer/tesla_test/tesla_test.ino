// 정의 
#define EA 3      //***적용
#define EB 8      //***적용
#define M_IN1 4   //***적용
#define M_IN2 5   //***적용
#define M_IN3 9   //***적용
#define M_IN4 10  //***적용

#define MOTOR_MIN_PWM 110
#define MOTOR_MAX_PWM 255
#define MOTOR_DRIVE_PWM 120

#define R_Sensor 39    //***적용
#define CR_Sensor 40   //***적용
#define CL_Sensor 41   //***적용
#define L_Sensor 38    //***적용

void setup() {
  pinMode(EA, OUTPUT);
  pinMode(M_IN1, OUTPUT);
  pinMode(M_IN2, OUTPUT); 
  // 오른쪽 바퀴 초기화   
  pinMode(EB, OUTPUT);
  pinMode(M_IN3, OUTPUT);  
  pinMode(M_IN4, OUTPUT);
  // 센서 초기화
  pinMode(R_Sensor, INPUT); 
  pinMode(CR_Sensor, INPUT);
  pinMode(CL_Sensor, INPUT);
  pinMode(L_Sensor, INPUT);
  // 시리얼 초기화 
  Serial.begin(9600);
  Serial2.begin(9600);
}

void loop() {
  if(Serial2.available())
  {
    String msg = Serial2.readString();
    Serial.println(msg);
    // A주소로 출발_우측
    if(msg == "A_GO"){
      delay(3000); // 대기
      sideChecked();
      delay(300);
      drive(130, 130);
      delay(600);
      turn_left();
      searchLeft();
      sideChecked();
      pause();
      delay(3000);
      turn();
      
      left3Checked();
      
      drive(-130,130);
      delay(300);
      searchLeft();
      sideChecked();
      delay(300);
      //출발 위치에서 회전
      delay(300);
      turn();
      drive(0,0);
      delay(100);
      searchLeft();
      setPosition();
      drive(0,0);
      return;
    }
    // B주소로 출발_중간
    else if(msg == "B_GO"){
      delay(3000); // 대기
      sideChecked();
      delay(300);
      drive(130, 130);
      delay(700);
      sideChecked();
      pause();
      delay(3000);
      turn();
      searchLeft();
      allChecked();
      sideChecked();
      delay(300);
      //출발 위치에서 회전
      sideChecked();
      delay(300);
      turn();
      
      drive(0,0);
      delay(100);
      setPosition();
      drive(0,0);
      delay(100);
      return;
      Serial.println("B주소로 출발");
    }
    //C주소로 출발_왼쪽
    else if(msg == "C_GO"){
      delay(3000); // 대기
      sideChecked();
      delay(300);
      drive(130, 130);
      delay(600);
      turn_right();
      searchRight();
      sideChecked();
      pause();
      delay(3000);
      turn();
      
      right3Checked();
      
      drive(130,-130);
      delay(300);
      searchRight();
      sideChecked();
      delay(300);
      //출발 위치에서 회전
      delay(300);
      turn();
      drive(0,0);
      delay(100);
      searchLeft();
      setPosition();
      drive(0,0);
      return;
    }
  }
}
