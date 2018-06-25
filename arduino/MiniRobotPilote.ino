// For RGB Band
#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>

// For Wifi control
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// Motor driver 
#define LEFT_DIR_PIN   D2
#define LEFT_DRV_PIN   D1
#define RIGHT_DIR_PIN  D6
#define RIGHT_DRV_PIN  D3

// RGB band
#define RGB_PIN D4
#define RGB_BAND_PIXEL_COUNT 8

// Status LED
#define LED_STARTED D7

// Camera params
#define PIC_PKT_LEN    512   //data length of each read, dont set this too big because ram is limited
#define CAM_ADDR       0
#define CAM_SERIAL     Serial
#define PIC_RES        7 // 7 = 640*480, 3 = 160*128 
#define PRE_RES        3 // 3 = 160*128
const byte cameraAddr = (CAM_ADDR << 5);  // addr
unsigned long picTotalLen = 0;            // picture length

// Wifi params
const char *ssid = XXXXX;
const char *password = xxxxxx;

// Active Wifi IP
IPAddress localIp;

// Various delay
int actionDelay = 500;
int shortestDelay = 100;

// And loop control
int actionStep = 0;

void setup() {  

  Serial.begin(9600);

  startBand();
  setupMotors();
  
  // Startup led
  pinMode(LED_STARTED, OUTPUT);
  digitalWrite(LED_STARTED, HIGH);   // turn the LED on (HIGH is the voltage level)

  setBandAction('2');

  goStraight(true, 1);

  delay(1000);
  
  goStraight(true, 0);
 
  setupWifi();
  Serial.println("started");
}

void loop() {
  
  if(actionStep >= actionDelay){
    doBandAction();
    actionStep = 0;
  } else {
    actionStep += shortestDelay;
  }

  doBandShortAction();

  delay(shortestDelay);

  loopWifi();
}
