void robot2() {
  int movedelay = 30;//(로봇 작동 속도)
  int waitdelay = 200;//(서보 모터간 딜레이)
  //Action_1_Start(정면->리본 잡는 액션)
  // Servo1 구동
  for(int i = 90; i>=1; i--){
    Servo2_1.write(i);
    delay(movedelay);
  }
  delay(waitdelay);
  // Servo2 구동
  for(int i = 30;i<=85;i++){
    Servo2_2.write(i);
    Serial.print("Servo2:");
    Serial.println(i);
    delay(movedelay);
  }
  delay(waitdelay);
  // Servo3 구동
  for(int i = 60; i>=40;i--){
    Servo2_3.write(i);
    Serial.print("Servo3:");
    Serial.println(i);
    delay(movedelay);
  }
  delay(waitdelay);
  // Servo4 구동
  for(int i = 100; i>=45;i--){
    Servo2_4.write(i);
    Serial.print("Servo4:");
    Serial.println(i);
    delay(movedelay);
  }
  delay(waitdelay);
  //Action_1_End
  //Acttion_2_Start(리본 잡은 후 정면으로 이동)
  // Servo2 구동
  for(int i = 55;i>=10;i--){
    Servo2_2.write(i);
    Serial.print("Servo2:");
    Serial.println(i);
    delay(movedelay);
  }
  delay(waitdelay);
  // Servo1 구동
  for(int i = 1; i<=100; i++){
    Servo2_1.write(i);
    Serial.print("Servo1:");
    Serial.println(i);
    delay(movedelay);
  }
  //Action_2_End
   
  //Action_3_Start(리본 부착 액션)
  // Servo3 구동
  for(int i = 60; i>=5;i--){
    Servo2_3.write(i);
    Serial.print("Servo3:");
    Serial.println(i);
    delay(movedelay);
  }
  delay(waitdelay);
  for(int i = 10;i<=30;i++){
    Servo2_2.write(i);
    Serial.print("Servo2:");
    Serial.println(i);
    delay(movedelay);
  }
  // Servo4 구동
  for(int i = 45; i<=90;i++){
    Servo2_4.write(i);
    Serial.print("Servo4:");
    Serial.println(i);
    delay(movedelay);
  }
  delay(waitdelay);
  // Servo3 구동
  for(int i = 20; i<=60;i++){
    Servo2_3.write(i);
    Serial.print("Servo3:");
    Serial.println(i);
    delay(movedelay);
  }
}
