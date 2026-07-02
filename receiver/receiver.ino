#include <SPI.h>
#include <LoRa.h>

#define SS   10
#define RST  9
#define DIO0 2

void setup(){

  Serial.begin(9600);

  LoRa.setPins(SS,RST,DIO0);

  if(!LoRa.begin(433E6)){
    Serial.println("RX FAIL");
    while(1);
  }

  LoRa.setSyncWord(0xF3);

  // IMPORTANT disabled on BOTH
  // LoRa.enableCrc();

  Serial.println("RX READY");
}

void loop(){

  int packetSize = LoRa.parsePacket();

  if(packetSize > 0){

    String msg="";

    while(LoRa.available()){
      msg += (char)LoRa.read();
    }

    msg.trim();

    // Find framed packet
    int startPos = msg.indexOf('<');
    int endPos   = msg.lastIndexOf('>');

    if(startPos<0 || endPos<0 || endPos<=startPos){
      // bad packet, discard and continue
      while(LoRa.available()) LoRa.read();
      return;
    }

    msg = msg.substring(startPos+1,endPos);

    int c1=msg.indexOf(',');
    int c2=msg.indexOf(',',c1+1);
    int c3=msg.indexOf(',',c2+1);
    int c4=msg.indexOf(',',c3+1);
    int c5=msg.indexOf(',',c4+1);

    if(c1<0||c2<0||c3<0||c4<0||c5<0){
      return;
    }

    String temp=msg.substring(0,c1);
    String xVal=msg.substring(c1+1,c2);
    String yVal=msg.substring(c2+1,c3);
    String zVal=msg.substring(c3+1,c4);
    String status=msg.substring(c4+1,c5);
    String gasVal=msg.substring(c5+1);

    Serial.print("TEMP:");
    Serial.print(temp);

    Serial.print(" X:");
    Serial.print(xVal);

    Serial.print(" Y:");
    Serial.print(yVal);

    Serial.print(" Z:");
    Serial.print(zVal);

    Serial.print(" VIBRATION:");
    Serial.print(status);

    Serial.print(" GAS:");
    Serial.println(gasVal);

    Serial.println("------------------");
  }

  delay(20); // small receiver pacing
}
