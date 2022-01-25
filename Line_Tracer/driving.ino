void drive(int pwmA, int pwmB) {
  pwmA = constrain(pwmA, -MOTOR_MAX_PWM, MOTOR_MAX_PWM); // 센서값을 -MAX ~ MAX 사이로 제한
  pwmB = constrain(pwmB, -MOTOR_MAX_PWM, MOTOR_MAX_PWM);

  // A모터 방향
  if (pwmA > 0) {
    digitalWrite(M_IN1, LOW);    // 정방향
    digitalWrite(M_IN2, HIGH);
  } else if (pwmA < 0) {
    digitalWrite(M_IN1, HIGH);   // 역방향
    digitalWrite(M_IN2, LOW);
  } else {
    digitalWrite(M_IN1, LOW);    // 멈춤
    digitalWrite(M_IN2, LOW);
  }

  // B모터 방향
   if (pwmB > 0) {
    digitalWrite(M_IN3, HIGH);   // 정방향
    digitalWrite(M_IN4, LOW);
  } else if (pwmB < 0) {
    digitalWrite(M_IN3, LOW);    // 역방향
    digitalWrite(M_IN4, HIGH);
  } else {
    digitalWrite(M_IN3, LOW);    // 멈춤
    digitalWrite(M_IN4, LOW);
  }

  if (abs(pwmA) < MOTOR_MIN_PWM) pwmA = 0;
  if (abs(pwmB) < MOTOR_MIN_PWM) pwmB = 0;

  analogWrite(EA, abs(pwmA));
  analogWrite(EB, abs(pwmB));
}
void go_forward(){
  drive(MOTOR_DRIVE_PWM, MOTOR_DRIVE_PWM);
  delay(100);
  pause();
}

void turn_right(){
  drive(-MOTOR_DRIVE_PWM, MOTOR_DRIVE_PWM);
  delay(900);
  pause();
}

void turn_left(){
  drive(MOTOR_DRIVE_PWM, -MOTOR_DRIVE_PWM);
  delay(900);
  pause();
}
void pause(){
  drive(0,0);
  delay(500);
}

void searchLeft(){
  while(digitalRead(R_Sensor) == LOW && digitalRead(L_Sensor) == LOW &&
        digitalRead(CR_Sensor) == LOW && digitalRead(CL_Sensor) == LOW){
          drive(130,-130);
  }
}
void searchRight(){
  while(digitalRead(R_Sensor) == LOW && digitalRead(L_Sensor) == LOW &&
        digitalRead(CR_Sensor) == LOW && digitalRead(CL_Sensor) == LOW){
          drive(-130,130);
  }
}
void allChecked(){
  while(true){
        linetracermode();
        if(digitalRead(CR_Sensor) == HIGH && digitalRead(CL_Sensor)== HIGH
          &&digitalRead(L_Sensor) == HIGH && digitalRead(R_Sensor)== HIGH){
            drive(130,130);
            delay(600);
            break;
    }
  }
}
void turn(){
  drive(130, -130);
  delay(2000);
}

void left3Checked(){
  while(true){
        linetracermode();
        if(digitalRead(CR_Sensor) == HIGH && digitalRead(CL_Sensor)== HIGH
          &&digitalRead(L_Sensor) == HIGH){
            break;
        }
      }
}
void right3Checked(){
  while(true){
        linetracermode();
        if(digitalRead(CR_Sensor) == HIGH && digitalRead(CL_Sensor)== HIGH
          &&digitalRead(R_Sensor) == HIGH){
            break;
        }
      }
}
void sideChecked(){
  while(true){
        linetracermode();
        if(digitalRead(R_Sensor) == HIGH &&digitalRead(L_Sensor) == HIGH){
            drive(0,0);
            delay(300);
            Serial.println("좌우2개감지");
            break;
        }
      }
}
void setPosition(){
  sideChecked();
  drive(-130,-130);
  delay(400);
}
void linetracermode(){

  if(digitalRead(CR_Sensor) == HIGH && digitalRead(CL_Sensor) == HIGH){    
      drive(MOTOR_DRIVE_PWM, MOTOR_DRIVE_PWM);
  }
  else if(digitalRead(CR_Sensor) == LOW && digitalRead(CL_Sensor) == HIGH){      
      drive(130, 0);
    }
  else if(digitalRead(CR_Sensor) == HIGH && digitalRead(CL_Sensor) == LOW){      
      drive(0, 130);
  }
  else if(digitalRead(R_Sensor) == HIGH){     
      drive(-MOTOR_DRIVE_PWM, MOTOR_DRIVE_PWM);
  }
  else if(digitalRead(L_Sensor) == HIGH){     
      drive(MOTOR_DRIVE_PWM, -MOTOR_DRIVE_PWM);
  }
}
