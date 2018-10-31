void startBuzzer(){
   pinMode(BUZZER_PIN, OUTPUT);
}

void doEndBeep(){
   digitalWrite(BUZZER_PIN,LOW);
}

void doStartBeep(){
  
   analogWrite(BUZZER_PIN, 50);
}

void doBeep(){
  
   analogWrite(BUZZER_PIN, 50);
   delay(200);
   analogWrite(BUZZER_PIN, 200);
   delay(200);
   digitalWrite(BUZZER_PIN,LOW);
}
