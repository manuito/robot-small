// Serial option

int optionCurrentAction;
String optionDistance = "";
String optionResult = "";

void checkOptionDetected(){
  delay(250);
  Serial.print("OPT");
  delay(1000);
  if (Serial.available()>0) {
    digitalWrite(LED_STARTED, LOW); 
    optionResult = Serial.readString();
  }
}

boolean isOptionDetected(){
  return optionResult == "OPTION-READY";
}

void startOption(){
  callOptionCommand("START");
}

void doOptionAction(byte action){
  optionCurrentAction = action - 48;
   switch (optionCurrentAction) {
    case 1:
      callOptionCommand("FAD");
      break;
    case 2:
      callOptionCommand("BEE");
      break;
    case 3:
      optionDistance = callOptionCommandResult("DIS");
      break;
  }
}

void callOptionCommand(String command){
  Serial.print(command);
  delay(200);
  if (Serial.available()>0) {
    optionResult = Serial.readString();
  }
}


String callOptionCommandResult(String command){
  Serial.print(command);
  delay(250);
  if (Serial.available()>0) {
    optionResult = Serial.readString();
    String value = getValue(optionResult, '|', 0);
    optionResult == "OPTION-READY";
    return value;
  }
  return "timeout";
}

String getValue(String data, char separator, int index){
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

