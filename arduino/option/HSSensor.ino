// HS Sensor
SR04 sr04Sensor = SR04(HC_ECHO_PIN,HC_TRIG_PIN);

// On demand only
long getDistance(){
  return sr04Sensor.Distance();
}
