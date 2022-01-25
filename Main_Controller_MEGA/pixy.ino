void pixy_(){
    pixy.ccc.getBlocks();
    if(pixy.ccc.numBlocks){
      Serial.print("Detected ");
      client.print("OPR4_END");
      Serial.println("OPR4종료 송신");
    }
  else{
    Serial.print("불량");
    client.print("OPR4_ERROR");
    Serial.println("OPR4에러 송신");
    }
}
