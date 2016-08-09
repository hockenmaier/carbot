/*
  LiquidCrystal Library - Hello World
 
 Tests CarBot with a simpe go-forward and stop before hitting a wall program
 
 LCD Documentation:
 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 
 Pin Config (Arduino Uno R3)
 0 LCD Data
 1 LCD Data
 2 LCD Data
 3 Piezo Speaker
 4 LCD Data
 5 Ultrasonic Mount Servo Motor
 6 LCD
 7 Ultrasonic Trigger
 8 Ultrasonic Echo
 9 Drive Motor Power
 10 Turn Motor Power
 11 LCD
 12 Drive Motor Direction
 13 Turn Motor Direction
 */

//Included Libraries:
#include <NewPing.h>
#include <LiquidCrystal.h>
#include <Servo.h> 

//Screen setup
LiquidCrystal lcd(11, 6, 4, 2, 1, 0);

//Eyes Motor

Servo myservo;

//Turning motor:
int dirpinA = 13; // Direction pin for motor A is Digital 13
int speedpinA = 10; // Speed pin for motor A is Digital 10 (PWM)

//Drive Motor:
int dirpinB = 12; // Direction pin for motor B is Digital 12
int speedpinB = 9; // Speed pin for motor B is Digital 9 (PWM)

//Eyes
NewPing sonar(7, 8, 200); // NewPing setup of pins and maximum distance.
unsigned int uS = 0;
int pingDist = 0;

//Mouth
int speakerPin = 3;

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void setup() {
  //Eyes Motor
  //myservo.attach(5);
  //myservo.write(90);
  //delay(500);
  //myservo.detach();
  
  //Turning Motor
  pinMode(dirpinA, OUTPUT);
  //Drive Motor
  pinMode(dirpinB, OUTPUT);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  //Mouth:
  pinMode(speakerPin, OUTPUT);
  
  lcd.setCursor(0, 0);
  lcd.print("Program Start   ");
  
  digitalWrite(dirpinB, 0); // set drive direction
  analogWrite(speedpinB, 0); // set drive speed pretty fast (PWM)
  digitalWrite(dirpinA, 0); // set turn direction
  analogWrite(speedpinA, 0); // set turn speed (PWM)
  
  playNote('c', 100);
  delay(15);
  playNote('c', 100);
  delay(15);
  playNote('g', 200);
  delay(500);
}

void loop() {
    lcd.setCursor(0, 0);
    uS = sonar.ping();
    pingDist = uS / US_ROUNDTRIP_CM;
    
    if (pingDist >= 30) {
      digitalWrite(dirpinB, 0);
      analogWrite(speedpinB, 250); // set drive speed pretty fast (PWM)
      digitalWrite(dirpinA, 1);
      analogWrite(speedpinA, 150);
      lcd.setCursor(0, 0);
      lcd.print("Going...        ");
      lcd.setCursor(0, 1);
      lcd.print("          ");
      lcd.setCursor(0, 1);
      lcd.print(pingDist);
    }else if (pingDist == 0){
      digitalWrite(dirpinB, 0);
      analogWrite(speedpinB, 250); // set drive speed pretty fast (PWM)
      digitalWrite(dirpinA, 1);
      analogWrite(speedpinA, 200);
      lcd.setCursor(0, 0);
      lcd.print("Going...        ");
      lcd.setCursor(0, 1);
      lcd.print("          ");
      lcd.setCursor(0, 1);
      lcd.print(pingDist);
    }else{
      digitalWrite(dirpinA, 0);
      analogWrite(speedpinA, 150);
      digitalWrite(dirpinB, 1);
      analogWrite(speedpinB, 200);
      lcd.setCursor(0, 0);
      lcd.print("Stopping!       ");
      lcd.setCursor(0, 1);
      lcd.print("          ");
      lcd.setCursor(0, 1);
      lcd.print(pingDist);
    }
    delay(50);
}
