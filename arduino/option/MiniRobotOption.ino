#include <SR04.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Servo.h>

// Serial In -> Com input from robot
#define SER_IN_TX_PIN 8
#define SER_IN_RX_PIN 7

// HS Sensor
#define HC_ECHO_PIN   3
#define HC_TRIG_PIN   2

// Status LED
#define LED_PIN       6

// Buzzer
#define BUZZER_PIN    5

// Servo
#define SERVO_PIN     10

// Create software serial input
SoftwareSerial serialIn(SER_IN_TX_PIN, SER_IN_RX_PIN);

Servo servo; 

boolean startCom = false;

void setup() {
  
  Serial.begin(9600);

  serialIn.begin(9600);
  delay(200);

  startBuzzer();
  startLed();
  startServo();
 
  if(Serial){
    if(serialIn){
      Serial.println("SerialIn ready");
    }
    Serial.println("Setup Complete!");
  }

  digitalWrite(LED_PIN, HIGH);
  delay(200);

  rotateServo();
}

void loop() {

  if (serialIn.available() > 0){
    digitalWrite(LED_PIN, HIGH);
    delay(30); // Let complete command
    String com = serialIn.readString();
    Serial.print("Received command : ");
    Serial.println(com);
    if(com == "START"){
      digitalWrite(LED_PIN, HIGH);
      doStartBeep();
      startCom = true;
    }
    if(com == "FAD"){
      fading();
    }
    if(com == "BEE"){
      doBeep();
    }
    if(com == "DIS"){
      serialIn.print(getDistance());
      serialIn.print("|");
    }
    serialIn.print("OPTION-READY");
  }
  delay(200);
  digitalWrite(LED_PIN, LOW);
  doEndBeep();
}

