//------------------------
//-------LIBRARIES--------
//-------------------------
#include <AFMotor.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//------------------------
//--MOTORS-CONFIGURATION--
//------------------------
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

//------------------------
//---------PINS-----------
//------------------------
#define servoPin 10

//------------------------
//-------Variables--------
//------------------------
long distance;
long motorSpeed=175;
int leftDistance;
int rightDistance;

//------------------------
//------DECLARATION-------
//------------------------
Servo myServo;
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Starting Robot");

  for (int i = 0; i < 3; i++) {
    lcd.setCursor(0, 1);
    lcd.print("Loading   ");
    delay(300);

    lcd.setCursor(0, 1);
    lcd.print("Loading.  ");
    delay(300);

    lcd.setCursor(0, 1);
    lcd.print("Loading.. ");
    delay(300);

    lcd.setCursor(0, 1);
    lcd.print("Loading...");
    delay(300);
}
  lcd.clear();
  lcd.print("Robot Initiated!");
  Wire.begin(8);
  motor1.setSpeed(motorSpeed);
  motor2.setSpeed(motorSpeed);
  motor3.setSpeed(motorSpeed);
  motor4.setSpeed(motorSpeed);
  pinMode(servoPin,OUTPUT);
  myServo.attach(servoPin);
  myServo.write(90);
  Serial.begin(500000);
}
void servoLeft(){
  myServo.write(0);
}
void servoRight(){
  myServo.write(180);
}
void forward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
void left() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
void right() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}


void loop() {
  forward();
  Wire.requestFrom(8, 1);

  if (Wire.available()) {
    distance = Wire.read();
  }
  if (distance<=30){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Obstacledetected");
    servoLeft();
    delay(100);
    Wire.requestFrom(8,1);
    if (Wire.available()){
      leftDistance=Wire.read();
    }
    servoRight();
    delay(100);
    Wire.requestFrom(8,1);
    if (Wire.available()){
      rightDistance=Wire.read();
    }
    if (leftDistance<rightDistance){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Obstacledetected");
      lcd.setCursor(0,1);
      lcd.print("At left!");
      right();
      delay(100);
      forward();
    }
    else{
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Obstacledetected");
      lcd.setCursor(0,1);
      lcd.print("At right!");
      left();
      delay(100);
      forward();
    }

  }
    
  
}  
