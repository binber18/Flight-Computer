#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;

int sample = 0;

String datastring = "";

float ax, ay, az;

Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");

  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
  
}

void loop() {

  sensors_event_t event;
  accel.getEvent(&event);

  ax = event.acceleration.x;
  ay = event.acceleration.y;
  az = event.acceleration.z;
  
  
  datastring = (String)sample + ";" + (String)micros() + ";" + (String)ax + ";" + (String)ay + ";" + (String)az;
  File dataFile = SD.open("RED2.csv", FILE_WRITE);
  dataFile.println(datastring);
  dataFile.close();
  sample ++;
}









