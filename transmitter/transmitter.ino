#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <DHT.h>

/* -------- LoRa -------- */
#define SS   10
#define RST  9
#define DIO0 2

/* -------- MPU6050 -------- */
const int MPU = 0x68;
int16_t AcX,AcY,AcZ;

/* -------- DHT11 -------- */
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);

/* -------- Sensors -------- */
#define VIB_PIN 6
#define GAS_PIN A0

/* -------- Active Buzzer -------- */
#define BUZZER 7

float temp = 0;
unsigned long lastDHT=0;

void setup(){

  Serial.begin(9600);

  // LoRa
  LoRa.setPins(SS,RST,DIO0);

  if(!LoRa.begin(433E6)){
    Serial.println("LoRa FAIL");
    while(1);
  }

  LoRa.setSyncWord(0xF3);

  // IMPORTANT: disabled on BOTH sides
  // LoRa.enableCrc();

  // MPU wake
  Wire.begin();

  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  // DHT
  dht.begin();
  delay(2000);

  pinMode(VIB_PIN,INPUT);

  pinMode(BUZZER,OUTPUT);
  digitalWrite(BUZZER,LOW);

  Serial.println("TX READY");
}

void loop(){

  /* Read DHT every 2 sec */
  if(millis()-lastDHT >= 2000){

    float t=dht.readTemperature();

    if(!isnan(t)){
      temp=t;
    }

    lastDHT=millis();
  }

  /* Read MPU */
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);

  Wire.requestFrom(MPU,6);

  if(Wire.available()>=6){

    AcX = Wire.read()<<8 | Wire.read();
    AcY = Wire.read()<<8 | Wire.read();
    AcZ = Wire.read()<<8 | Wire.read();

    /* Read Sensors */
    int gasValue = analogRead(GAS_PIN);

    // LM393 active LOW
  // ----- improved vibration detection -----
// -------- Vibration + Buzzer Fix --------

static unsigned long vibHoldUntil = 0;

// LM393 active LOW
if(digitalRead(VIB_PIN)==LOW){
    delay(20); // debounce
    if(digitalRead(VIB_PIN)==LOW){
        vibHoldUntil = millis() + 3000; // hold buzzer ON for 3 sec
    }
}

// true while hold active
bool vibAlert = (millis() < vibHoldUntil);

// gas can still exist internally if you want,
// but it should NOT affect vibration indication or buzzer
bool gasAlert = (gasValue > 40);

// display ONLY vibration state
String status;

if(vibAlert){
   status = "NOT_DETECTED";
}
else{
   status = "DETECTED";
}

// buzzer ONLY for vibration
if(vibAlert){
   digitalWrite(BUZZER,HIGH);
}
else{
   digitalWrite(BUZZER,LOW);
}


    /* Debug output */
    Serial.print("TX -> ");
    Serial.print(temp,1);
    Serial.print(",");

    Serial.print(AcX);
    Serial.print(",");

    Serial.print(AcY);
    Serial.print(",");

    Serial.print(AcZ);
    Serial.print(",");

    Serial.print(status);
    Serial.print(",");

    Serial.println(gasValue);

    /* Send framed packet */
    LoRa.beginPacket();

    LoRa.print("<");

    LoRa.print(temp,1);
    LoRa.print(",");

    LoRa.print(AcX);
    LoRa.print(",");

    LoRa.print(AcY);
    LoRa.print(",");

    LoRa.print(AcZ);
    LoRa.print(",");

    LoRa.print(status);
    LoRa.print(",");

    LoRa.print(gasValue);

    LoRa.print(">");

    LoRa.endPacket();
  }

  delay(2000);
}
