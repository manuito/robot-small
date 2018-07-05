int leftSpeed, rightSpeed ;

/*
 * Provided commands for motor
 */

void setupMotors(){
  // Motors
  pinMode(LEFT_DIR_PIN, OUTPUT);
  pinMode(LEFT_DRV_PIN, OUTPUT);
  pinMode(RIGHT_DIR_PIN, OUTPUT);
  pinMode(RIGHT_DRV_PIN, OUTPUT);
}

void goStraight(bool direction, uint8_t speed){
  driveLeft(direction, speed);
  driveRight(direction, speed);
}

void turnLeft(uint8_t speed){
  driveLeft(true, speed);
  driveRight(false, speed);
}

void turnRight(uint8_t speed){
  driveLeft(false, speed);
  driveRight(true, speed);
}

void doABarrelRoll(){
  driveLeft(false, 2);
  driveRight(false, 1);
  delay(actionDelay);
  driveLeft(true, 1);
  driveRight(false, 3);
  delay(actionDelay);
  goStraight(true, 1);
  delay(actionDelay);
  goStraight(false, 1);
  delay(actionDelay);
  driveLeft(true, 2);
  driveRight(true, 1);
  delay(actionDelay);
  goStraight(true, 0);
}

/**
 * Internal commands
 */

void driveLeft(bool direction, uint8_t speed){ 

  if(speed == 0){
    digitalWrite(LEFT_DIR_PIN, false);
    digitalWrite(LEFT_DRV_PIN, false);
  } else {
    // Apply command
    if(direction){
      digitalWrite(LEFT_DIR_PIN, true);
      analogWrite(LEFT_DRV_PIN, speed);
    } else {
      digitalWrite(LEFT_DRV_PIN, true);
      analogWrite(LEFT_DIR_PIN, speed);
    }
  }

  // Update state
  if(direction){
    leftSpeed = speed;
  } else {
    leftSpeed = 0-speed;    
  }
}

void driveRight(bool direction, uint8_t speed){ 

  if(speed == 0){
    digitalWrite(RIGHT_DIR_PIN, false);
    digitalWrite(RIGHT_DRV_PIN, false);
  } else {
    // Apply command
    if(direction){
      digitalWrite(RIGHT_DIR_PIN, true);
      analogWrite(RIGHT_DRV_PIN, speed);
    } else {
      digitalWrite(RIGHT_DRV_PIN, true);
      analogWrite(RIGHT_DIR_PIN, speed);
    }
  }
  
  // Update state
  if(direction){
    rightSpeed = speed;
  } else {
    rightSpeed = -speed;    
  }  
}

// For monitoring
int getLeftState(){
  return leftSpeed;
}

// For monitoring
int getRightState(){
  return rightSpeed;
}

