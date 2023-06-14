


#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "2xrKwgCnmTCR4m5aAx7kviRHT7WqVSyV";
char ssid[] = "Bluetooth";
char pass[] = "midorafk69";


#include <DHT.h>


#include "DHT.h"
#define DHTTYPE DHT11

#define dht_dpin D4
DHT dht(dht_dpin, DHTTYPE);

BlynkTimer timer;

int relayM = D1;
int relayF1 = D2;


#define trigPin D5
#define echoPin D6

long duration;
long distance;

void setup()
{
  pinMode(relayM, OUTPUT);
  pinMode(relayF1, OUTPUT);


  pinMode ( trigPin, OUTPUT);
  pinMode (echoPin, INPUT);

  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  dht.begin();
  Serial.begin(9600);
  Serial.println("Humidity and temperature\n\n");
  delay(100);

  //  digitalWrite(relayM, LOW);
  //  digitalWrite(relayF1, LOW);
  //  digitalWrite(relayF2, LOW);


}

void loop()
{
  //  digitalWrite(relayM, LOW);
  //  digitalWrite(relayF1, LOW);
  //  digitalWrite(relayF2, LOW);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("Current humidity = ");
  Serial.print(h);
  Serial.print("%       ");
  Serial.print("temperature = ");
  Serial.print(t);
  Serial.println("C  ");
  delay(800);

  Serial.println ("=======================================================================");

  if (h <= 80)

  {
    digitalWrite(relayM, HIGH);
    Serial.println(" Motorpump is On. ");
    Blynk.email("niveshncwanninayaka@gmail.com", " Motorpump is On. Current Water level is Low.");
    Blynk.notify(" Motorpump is On. Current Water level is Low.  ");

    delay(1000);
  }
  else
  {
    digitalWrite(relayM, LOW);
    Serial.println(" Motor pump is Off. ");

    delay(1000);

  }
  Serial.println("");
  Serial.println("");
  delay(1000);

  Serial.println ("=======================================================================");

  if ( t >= 32)
  {
    digitalWrite (relayF1, HIGH);



    Serial.println(" Fans are On. Current Tempereture is high ");

    Blynk.email("niveshncwanninayaka@gmail.com", "  Fans are On. Current Tempereture is high ");
    Blynk.notify(" Fans are On. Current Tempereture is high  \n \n \n");


    delay(1000);
  }
  else
  {
    digitalWrite(relayF1, LOW);


    Serial.println(" Fans are Off. Current Tempereture is general.  ");


    delay(1000);
  }
  digitalWrite ( trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite ( trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite ( trigPin, LOW);

  duration = pulseIn ( echoPin, HIGH);

  distance = duration * 0.034 / 2 ;
  Serial.println("************************************************");

  Serial.print("distance   ")  ;
  Serial.println(distance)  ;
  delay (1000);

  delay(5000);
  int botH = 12;
  int area = 3.124 * 3 * 3; // area of water bottele
  int volfb = area * botH; // volume of full water bottle
  int bocw = (botH - distance); // Remain water level after 5 seconds

  int volume = bocw * area;  // Remain water
  int uvolume = volfb - volume;


  Serial.println("");
  Serial.println("after 5 seconds");

  Serial.print(" Remain water level : ");
  Serial.print( bocw);
  Serial.println(" cm");
  delay (500);

  Serial.print(" Current Usage water volume : ");
  Serial.print( uvolume);
  Serial.println(" cm3");
  delay (500);

  Serial.println("");
  Serial.println("");





  Blynk.virtualWrite(V3, t);
  Blynk.virtualWrite(V4, h);
  Blynk.virtualWrite(V5, bocw);
  
  Blynk.run();
  timer.run();
}
