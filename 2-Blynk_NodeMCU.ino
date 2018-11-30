/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  This example shows how to monitor a button state
  using polling mechanism.

  App project setup:
    LED widget on V1
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "21d4cf05a381402a98dfe7a0bd000056";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Projetosiot";
char pass[] = "pelicano2018";

int prevState = -1;
int currState = -1;
long lastChangeTime = 0;

WidgetLED led1(V2);
void checkPin()
{
  // Invert state, since button is "Active LOW"
  int state = !digitalRead(D3);

  // Debounce mechanism
  long t = millis();
  if (state != prevState) {
    lastChangeTime = t;
  }
  if (t - lastChangeTime > 50) {
    if (state != currState) {
      currState = state;
      Blynk.virtualWrite(V1, state);
    }
  }
  prevState = state;
  
  if (state) {
    led1.on();
  }

  if (!state) {
    led1.off();
  }
   
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Make pin 2 default HIGH, and attach INT to our handler
  pinMode(D3, INPUT_PULLUP);
}

void loop()
{
  Blynk.run();
  checkPin();
  
}
