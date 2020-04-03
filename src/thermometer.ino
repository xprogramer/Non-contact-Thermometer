/**
  Author: x-programer (Abainia Kheireddine)
  Email: k.abainia@gmail.com
  Non-contact Thermometer v1.0

  This is a low cost non-contact (infrared) thermometer
  based on Arduino. The overall program uses 23k of memory,
  which requires Mega328 microcontroller at least to support
  the program. This project uses Adafruit library for the
  VL53L0X sensor, and this library is expensively consuming 
  (17k of memory). This thermometer also measures the distance
  of the targeted object, and to this end, a time of flight distance
  sensor (VL53L0X) is used and could be replaced with its improved
  version (e.g. VL6180X).
**/

#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include "Adafruit_VL53L0X.h"
#include "printing_functions.h"

// comment if you don't want to use Serial Monitor
//#define __DEBUG_

#define BUZZER_PIN 2
#define BUTTON_PIN 8
#define LASER_PIN 9

#define DIST_OFFSET 1.7 // to be adjusted depending on your design
                        // because the minimal working distance of
                        // VL53L0X is 20 mm
#define TEMPERATURE_THRESHOLD 38 // the human normal temperature
                                 // does not exceed 38 °C

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void highTemperatureAlarm();
void failAlarm();
void successAlarm();

// global variables
bool init_failed = false; // init status
bool active = false; // control button
float dist; //object distance

void setup() {
  #ifdef __DEBUG_
    Serial.begin(9600);
    Serial.println("Starting the system");
  #endif
  // configure the buzzer pin as output
  pinMode(BUZZER_PIN, OUTPUT);
  // configure the measure button as input
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  // configure the laser pin as output
  pinMode(LASER_PIN, OUTPUT);
  // configure the screen
  LCD_setup();
  // initialize the MLX90614 sensor
  if (!mlx.begin()) {
    init_failed = true;
    #ifdef __DEBUG_
      Serial.println("Failed to initialize MLX90614");
    #endif
  }
  // initialize the VL53L0X sensor
  if (!lox.begin()) {
    init_failed = true;
    #ifdef __DEBUG_
      Serial.println("Failed to initialize VL53L0X");
    #endif
  }
  if(init_failed) {
    #ifdef __DEBUG_
      Serial.println("Initialization is failed !");
    #endif
    // alarm an error
    failAlarm();
  }
  else {
    #ifdef __DEBUG_
      Serial.println("[ Successfully initialized ]");
    #endif
    // alarm a success
    successAlarm();
  }
  clear();
}

void loop() {
  if(digitalRead(BUTTON_PIN) == LOW) {
      active = true;
      digitalWrite(LASER_PIN, HIGH);
      clear();
  }
  else {
      active = false;
      digitalWrite(LASER_PIN, LOW);
      clear();
  }
  // if the initialization failed    
  if(init_failed) {
    setCursor(25,2);
    printChar(0x7f, 0x49, 0x49, 0x49, 0x41); // print E
    printChar(0x7c, 0x08, 0x04, 0x04, 0x08); // print r
    printChar(0x7c, 0x08, 0x04, 0x04, 0x08); // print r
    printChar(0x38, 0x44, 0x44, 0x44, 0x38); // print o
    printChar(0x7c, 0x08, 0x04, 0x04, 0x08); // print r
    printChar(0x00, 0x00, 0x00, 0x00, 0x00); // print sapce
    printChar(0x00, 0x00, 0x5f, 0x00, 0x00); // print !
    failAlarm();
  }
  // if the initialization is done and the measure button is pressed
  else if(active) {
    setCursor(1,5);
    VL53L0X_RangingMeasurementData_t measure;
    printDistance(); // print "Distance"
    setCursor(54,5);
    lox.rangingTest(&measure, false);
    
    if (measure.RangeStatus != 4) {  
      dist = (float)measure.RangeMilliMeter / 10;
      dist -= DIST_OFFSET;
      #ifdef __DEBUG_
        Serial.print("Distance (cm): ");
        Serial.println(dist);
      #endif
    }
    else {
      #ifdef __DEBUG_
        Serial.println(" out of range ");
      #endif
      dist = 99999;
    }
    // print the distance value
    printFloatNumber(dist);
  
    setCursor(2,0);
    printAmbient(); // print "Ambient"
    setCursor(40,0);
    // read the ambient temperature
    float deg;
    deg = mlx.readAmbientTempC();
    // print the ambient temperature
    printFloatNumber(deg, true);
    #ifdef __DEBUG_
      Serial.print("Ambient temperature (°C) :  ");
      Serial.println(deg);
    #endif
    // read the object temperature
    deg = mlx.readObjectTempC();
    // print the object temperature
    printObjectDeg(deg);
    #ifdef __DEBUG_
      Serial.print("Object temperature (°C) :  ");
      Serial.println(deg);
    #endif
    if(deg > TEMPERATURE_THRESHOLD) {
      highTemperatureAlarm();
    }
    delay(1000);
  }
  // if the measure button is not pressed
  else {
    #ifdef __DEBUG_
      Serial.println("Ready to measure..Press the button !");
    #endif
    setCursor(25,2);
    printChar(0x7f, 0x09, 0x19, 0x29, 0x46); // print R
    printChar(0x7f, 0x49, 0x49, 0x49, 0x41); // print e
    printChar(0x20, 0x54, 0x54, 0x54, 0x78); // print a
    printChar(0x38, 0x44, 0x44, 0x48, 0x7f); // print d
    printChar(0x0c, 0x50, 0x50, 0x50, 0x3c); // print y
    printChar(0x00, 0x00, 0x00, 0x00, 0x00); // print space
    printChar(0x00, 0x00, 0x5f, 0x00, 0x00); // print !
    delay(500);
  }
}


void highTemperatureAlarm() {
  tone(BUZZER_PIN,1000);
  delay(2000);
  noTone(BUZZER_PIN);
}

void successAlarm() {
  tone(BUZZER_PIN,1000);
  delay(500);
  tone(BUZZER_PIN,500);
  delay(500);
  noTone(BUZZER_PIN);
  delay(1000);
}

void failAlarm() {
  tone(BUZZER_PIN,1000);
  delay(300);
  noTone(BUZZER_PIN);
  delay(500);
  tone(BUZZER_PIN,700);
  delay(300);
  noTone(BUZZER_PIN);
  delay(500);
  tone(BUZZER_PIN,1000);
  delay(300);
  noTone(BUZZER_PIN);
  delay(1000);
}
