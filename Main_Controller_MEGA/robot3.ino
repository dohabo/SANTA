//비전 검사 시 양품일 경우
void robot3_1(){
  int movedelay = 20;//(로봇 작동 속도)
  int waitdelay = 100;//(서보 모터간 딜레이)
  // Servo1 구동
  for(int i = 120; i>=1; i--){
    Servo3_1.write(i);
    delay(movedelay);
  }
  delay(waitdelay);

  // Servo2 구동
  for(int i = 30;i<=80;i++){
    Servo3_2.write(i);
    delay(movedelay);
  }
delay(waitdelay);

  // Servo3 구동
  for(int i = 50; i>=20;i--){
    Servo3_3.write(i);
    delay(movedelay);
  }
  for(int i = 90; i<=160;i++){
    Servo3_4.write(i);
    delay(movedelay);
  }
  for(int i = 80; i>=20;i--){
    Servo3_2.write(i);
    delay(movedelay);
  }
  delay(waitdelay);
  for(int i = 1; i<=120; i++){
    Servo3_1.write(i);
    delay(movedelay);
  }
  delay(waitdelay);
  // Servo2 구동
  for(int i = 20;i<=70;i++){
    Servo3_2.write(i);
    delay(movedelay);
  }
  delay(waitdelay);

    for(int i = 150; i>=90;i--){
    Servo3_4.write(i);
    delay(movedelay);
  }
  delay(waitdelay);
  for(int i = 70; i>=30;i--){
    Servo3_2.write(i);
    delay(movedelay);
  }
}

// 비전 검사 시 불량일 경우
void robot3_2(){
  int movedelay = 20;//(로봇 작동 속도)
  int waitdelay = 100;//(서보 모터간 딜레이)
  // Servo1 구동
  for(int i = 120; i>=1; i--){
    Servo3_1.write(i);
    delay(movedelay);
  }
  delay(waitdelay);

  // Servo2 구동
  for(int i = 30;i<=90;i++){
    Servo3_2.write(i);
    delay(movedelay);
  }
delay(waitdelay);

  // Servo3 구동
  for(int i = 50; i>=20;i--){
    Servo3_3.write(i);
    delay(movedelay);
  }
  for(int i = 90; i<=150;i++){
    Servo3_4.write(i);
    delay(movedelay);
  }
  for(int i = 90; i>=30;i--){
    Servo3_2.write(i);
    delay(movedelay);
  }
  delay(waitdelay);
  for(int i = 1; i<=30; i++){
    Servo3_1.write(i);
    delay(movedelay);
  }
  delay(waitdelay);
  // Servo2 구동
  for(int i = 30;i<=75;i++){
    Servo3_2.write(i);
    delay(movedelay);
  }
  delay(waitdelay);

    for(int i = 150; i>=90;i--){
    Servo3_4.write(i);
    delay(movedelay);
  }
  delay(waitdelay);
  for(int i = 75; i>=30;i--){
    Servo3_2.write(i);
    delay(movedelay);
  }
}
