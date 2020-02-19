#include <SoftwareSerial.h>

const byte HC12TxdPin = 10;                  // Transmit Pin on HC12
const byte HC12RxdPin = 11;                  // Recieve Pin on HC12

SoftwareSerial HC12(HC12TxdPin, HC12RxdPin); // Create Software Serial Port

void senddata();

void setup() {
  Serial.begin(9600);                       // Open serial port to computer
  HC12.begin(9600);                         // Open serial port to HC12
}

int i = 12;
void loop() {
  senddata();
}
