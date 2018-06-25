// Web server
ESP8266WebServer server ( 80 );

const char* WEB_PAGE = "<html>\
  <head>\
    <meta http-equiv='refresh' content='5'/>\
    <title>ESP8266 Demo</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Hello from ESP8266!</h1>\
    <p>Uptime: %02d:%02d:%02d</p>\
    <img src=\"/capture.jpg\" />\
  </body>\
</html>";



// actions
void handleAction() {

  if (server.hasArg("L")) {
    char action = server.arg("L").charAt(0);
    Serial.print("Light change : ");
    Serial.println(action);
    setBandAction(action);
  }

  if (server.hasArg("G")) {
    char action = server.arg("G").charAt(0);
    Serial.print("Go ");
    Serial.println(action);
    goStraight(true, 100 * (action -48));
  }
  
  if (server.hasArg("B")) {
    char action = server.arg("B").charAt(0);
    Serial.print("Backward ");
    Serial.println(action);
    goStraight(false, 100 * (action -48));
  }

  if (server.hasArg("TL")) {
    char action = server.arg("TL").charAt(0);
    Serial.print("Turn left ");
    Serial.println(action);
    turnLeft( 10 * (action -48));
  }
  
  if (server.hasArg("TR")) {
    char action = server.arg("TR").charAt(0);
    Serial.print("Turn right ");
    Serial.println(action);
    turnRight(10 * (action -48));
  }
  
  server.send(200, "application/json", "{ result:'ACK' }");
}

void handleRoot() {
  char temp[400];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  // Write Web page
  snprintf ( temp, 400, WEB_PAGE, hr, min % 60, sec % 60 );
  
  server.send ( 200, "text/html", temp );
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  server.send ( 404, "text/plain", message );
}

void setupWifi () {
  WiFi.mode ( WIFI_STA );
  WiFi.begin ( ssid, password );
//  Serial.println ( "" );

  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  localIp = WiFi.localIP() ;

  Serial.println ( "" );
  Serial.print ( "Connected to " );
  Serial.println ( ssid );
  Serial.print ( "IP address: " );
  Serial.println ( localIp );

  if ( MDNS.begin ( "esp8266" ) ) {
 //   Serial.println ( "MDNS responder started" );
  }

  server.on ( "/", handleRoot );
  server.on ( "/inline", []() {
    server.send ( 200, "text/plain", "this works as well" );
  } );
  server.on ( "/action", handleAction );
  server.onNotFound ( handleNotFound );
  server.begin();
//  Serial.println ( "HTTP server started" );
}

void loopWifi () {
  server.handleClient();
}

//void drawCapture() {
//  server.send ( 200, "image/jpg", loadPreview());
//}
