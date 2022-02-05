#include <SoftwareSerial.h>
#define rxPin 10
#define txPin 11

SoftwareSerial jsnSerial(rxPin, txPin);
unsigned int distance;

void setup() {
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  jsnSerial.begin(9600);
  //Serial.begin(9600);
}

void loop() {
  delay(1000);
  getDistance();
  if (distance <= 1000) {
    delay(600);
    getDistance();
    if (distance <= 1000) {
      digitalWrite(12, LOW);
    }
  } else {
    delay(600);
    getDistance();
    if (distance > 1000) {
      digitalWrite(12, HIGH);
    }
  }
}

void getDistance() {
  byte startByte, h_data, l_data, sum = 0;
  byte buf[3];
  unsigned int req;

  jsnSerial.write(0x01);
  delay(50);
  if (jsnSerial.available()) {
    startByte = (byte)jsnSerial.read();
    if (startByte == 255) {
      jsnSerial.readBytes(buf, 3);
      h_data = buf[0];
      l_data = buf[1];
      sum = buf[2];
      req = (h_data << 8) + l_data;
      if ((( h_data + l_data) & 0xFF) != sum) {
        //Serial.println("Invalid result");
        return;
      } else {
        //Serial.println(distance);
        distance = req;
      }
    }
  }
}
