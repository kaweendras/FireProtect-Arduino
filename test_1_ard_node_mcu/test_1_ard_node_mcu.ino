#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

SoftwareSerial HC12(D5, D6); // HC-12 TX Pin, HC-12 RX Pin

#define WIFI_SSID "new"
#define WIFI_PASSWORD "123456789"
#define FIREBASE_HOST "fire-detect-74a07.firebaseio.com" //Without http:// or https:// schemes
#define FIREBASE_AUTH "XbOHoH43m8md6mHV7yZlqJjInBDRM0eEB9Swdlzj"
#define thresh_val 400
#define buzzer_pin D2

int buzzer = D2;
int  buttonPin1 = D1;

long time1 = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers

int previos1 = 1, current1;


//Define Firebase Data object
FirebaseData firebaseData;

void printResult(FirebaseData &data);
void senddata();

char ch ;
String ss  = "";

void setup() {

  Serial.begin(9600);
  HC12.begin(9600);               // Serial port to HC12
  Serial.println();
  Serial.println();
  pinMode(buzzer, OUTPUT);
  pinMode(buttonPin1, INPUT_PULLUP);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set the size of WiFi rx/tx buffers in the case where we want to work with large data.
  firebaseData.setBSSLBufferSize(1024, 1024);

  //Set the size of HTTP response buffers in the case where we want to work with large data.
  firebaseData.setResponseSize(1024);

}


int ii = 0;
String num = "";

void loop() {
  int sensorVal1 = digitalRead(buttonPin1);
  current1 = sensorVal1;

  ss = "";
  num = "";
  while (HC12.available()) {      // If HC-12 has data
    ch =  HC12.read();
    delay(10);
    if (ch == ':') {
      break;
    }
    num = num + ch;
  }

  while (HC12.available()) {      // If HC-12 has data
    ch =  HC12.read();
    delay(10);
    if (ch != '\n') {
      //    if (ch != 'z' ) {
      ss = ss + ch;
    }
  }
  if (ss != "") {
    Serial.println(ss);
    ii = ss.toInt();
    if (ii > 70) {
      senddata();
      while (1) {
        
        digitalWrite(buzzer,HIGH);
        delay(50);
        Serial.println("fire ");
        Serial.println(sensorVal1);
        if (sensorVal1 == 0 && previos1 == 1) {
          Serial.println("alarm off");
          
          break;
        }
      }
    }
    delay(10);
    
    
  }
  if (ii > 150) {
    
  }
  ss = "";
}
