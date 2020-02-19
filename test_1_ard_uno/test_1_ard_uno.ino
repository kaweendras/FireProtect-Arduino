#include <SoftwareSerial.h>

const byte HC12TxdPin = 10;                  // Transmit Pin on HC12
const byte HC12RxdPin = 11;                  // Recieve Pin on HC12

int smokeA0 = A5;
int sensorThreshold = 140;

String place = "home";

SoftwareSerial HC12(HC12TxdPin, HC12RxdPin); // Create Software Serial Port

void senddata();

void setup() {
  pinMode(smokeA0, INPUT);

  Serial.begin(9600);                       // Open serial port to computer
  HC12.begin(9600);                         // Open serial port to HC12
}
String stringToSend = "hello world";
int i = 0;

void loop() {
  int analogSensor = analogRead(smokeA0);
  // Define
  //  if (analogSensor > 70) {
  String str = place + ":" + (String)analogSensor;

  // Length (with one extra character for the null terminator)
  int str_len = str.length() + 1;

  // Prepare the character array (the buffer)
  char char_array[str_len];

  // Copy it over
  str.toCharArray(char_array, str_len);
  for (i = 0; i < str_len; i++) {
    HC12.write(char_array[i]);
    //  senddata();
  }

  HC12.write('\n');
  //  }
  Serial.println(analogSensor);
  delay(1000);
}
