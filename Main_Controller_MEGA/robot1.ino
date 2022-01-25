void robot1(){
  int movedelay = 20;
  int waitdelay = 100;

  for(int i = 40; i <= 90; i++)
  {
    Servo1_1.write(i);
    delay(movedelay);
  }
  delay(waitdelay);
  for(int i = 130; i >= 85; i--)
  {
    Servo1_2.write(i);
    delay(movedelay);
  }
  delay(waitdelay);
  for(int i = 150; i <= 180; i++)
  {
    Servo1_3.write(i);
    delay(movedelay);
  }
  delay(waitdelay);
  for(int i = 30; i <= 100; i++){
    Servo1_4.write(i);
    delay(movedelay);
  }
  delay(waitdelay);
  for(int i = 170; i >= 140; i--)
  {
    Servo1_3.write(i);
    delay(movedelay);
  }
  delay(waitdelay);
  for(int i = 85; i <= 140; i++)
  {
    Servo1_2.write(i);
    delay(movedelay);
  }
  delay(waitdelay);
  for(int i = 90; i <= 150; i++)
  {
    Servo1_1.write(i);
    delay(movedelay);
  }
  delay(waitdelay);
  for(int i = 140; i >= 95; i--)
  {
    Servo1_2.write(i);
    delay(movedelay);
  }
  delay(waitdelay);
  for(int i = 100; i >= 30; i--){
    Servo1_4.write(i);
    delay(movedelay);
  }
  for(int i = 95; i <= 130; i++)
  {
    Servo1_2.write(i);
    delay(movedelay);
  }
}
