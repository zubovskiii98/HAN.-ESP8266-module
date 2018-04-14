/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

 *************************************************************

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
/*--------------------------------------------------*/

//Define pins
#define TEMPERATURE_SENSOR_PIN 0
#define LED_PIN 5

//Include libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "e6a2456c6a95409e9c794d1064ba4c3b";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "........";
char pass[] = "........";

//Initialize variables
int temperature;
int brightness;
int led_status;

BLYNK_WRITE(V1)
{
  brightness = param.asInt();
}

BLYNK_WRITE(V2)
{
  led_status = param.asInt();
}

void setup()
{
  // Debug console. In Serial monitor of Arduino IDE you can
  // monitor the connection with the router and Blynk service
  Serial.begin(9600);

  //Initialize LED pin
  pinMode (LED_PIN, OUTPUT);
  //Initialize WiFi settings
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  //Run the Blynk sevice on the microcontroller
  Blynk.run();

  //------------LED Control-----------------//
   
   if (led_status == 1) {analogWrite (LED_PIN, brightness);}
    else {digitalWrite (LED_PIN, LOW);}
  //----------------------------------------//


  //--------Temperature sensor-------------//
  
  //Read the sensor
  temperature = analogRead(TEMPERATURE_SENSOR_PIN);

  //Convert the reading to degrees Celsius.
  temperature = round(temperature * 0.259);

  //Send the temperature to the app
  Blynk.virtualWrite (V0, temperature);
  //--------------------------------------//
}



