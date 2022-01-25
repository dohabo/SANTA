void conveyor(){
  unsigned int vr = map(analogRead(A0),0,1023,0,511);
  if(vr<256){
    analogWrite(MOTOR_A1,255-vr);
    analogWrite(MOTOR_A2,0);
    Serial.print("front - ");
    Serial.println(255-vr);
  }
  else{
    analogWrite(MOTOR_A1,0);
    analogWrite(MOTOR_A2,vr-256);
    Serial.print("back - ");
    Serial.println(vr-256);
  }
}
