// Web server
ESP8266WebServer server ( 80 );

const char* WEB_PAGE = "<html>\
  <head>\
    <meta http-equiv='refresh' content='5'/>\
    <title>MiniRobotPilote home</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Hello from MiniRobot!</h1>\
    <p>Uptime: %02d:%02d:%02d</p>\
    <p><h3>Commands:</h3><ul><li><a href=\"/status\">See status</a></li>\
    <li><a href=\"/action?L=1\">Use actions</a></li>\
    <li><a href=\"/action?OP=2\">Set option</a></li></ul></p>\
  </body>\
</html>";


// Status action - specific response
void handleStatus() {

  String optRes = isOptionDetected() ? "true" : "false";
  
  server.send(200, "application/json", "{\"option\":" + optRes + ",\"leftSpeed\":" + leftSpeed + ",\"rightSpeed\":" + rightSpeed + "}");
}

// Standard actions - standard result
void handleAction() {

  String result = "ACK";
  
  if (server.hasArg("L")) {
    char action = server.arg("L").charAt(0);
    setBandAction(action);
  }
  
  if (server.hasArg("G")) {
    char action = server.arg("G").charAt(0);
    goStraight(true, 100 * (action -48));
  }
    
  if (server.hasArg("B")) {
    char action = server.arg("B").charAt(0);
    goStraight(false, 100 * (action -48));
  }
  
  if (server.hasArg("TL")) {
    char action = server.arg("TL").charAt(0);
    turnLeft( 10 * (action -48));
  }
    
  if (server.hasArg("TR")) {
    char action = server.arg("TR").charAt(0);
    turnRight(10 * (action -48));
  }
    
  if (server.hasArg("BR")) {
    char action = server.arg("BR").charAt(0);
    doABarrelRoll();
  }
    
  if (server.hasArg("OP")) {
    char action = server.arg("OP").charAt(0);
    doOptionAction(action);
  }
    
  if (server.hasArg("DI")) {
    doOptionAction('3');
    result = optionDistance;
  }
    
  server.send(200, "application/json", "{ \"result\":\"" + result + "\" }");
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

  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
  }

  localIp = WiFi.localIP() ;

  if ( MDNS.begin ( "esp8266" ) ) {
  }

  server.on ( "/", handleRoot );
  server.on ( "/action", handleAction );
  server.on ( "/status", handleStatus );
  server.onNotFound ( handleNotFound );
  server.begin();
}

void loopWifi () {
  server.handleClient();
}


