/**************************************************************************
 *                                                                       *
     NeoPixel / WS2812b Adventskalender
     created by Tim! / 54696d21

	 rev 1 10.12.2017
 *                                                                      *
 **************************************************************************/


// benötigte Bibilotheken
#include <ESP8266WiFi.h>	//standard library
#include <TimeLib.h>		//TimeLib.h by Paul Stoffregen
#include <Wire.h>       //I2C
#include <NTPClient.h>  //NTP Zeit
#include <WiFiUdp.h>    //Netzwerkprotokoll für NTP
#include <Adafruit_NeoPixel.h> //LED-Treiber


#define LED_INPUT_DATA D1	//Datenpin leds
#define BRIGHTNESS 10 // Helligkeit
#define PIXELS 24		//Anzahl der Leds

WiFiUDP ntpUDP;               //Protokoll für NTP auf UDP festlegen
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 20000); //festlegen der NTP-Einstellungen

const char *ssid     = "**********************";					//WLAN daten zum stellen der Uhr via NTP
const char *password = "**********************";

Adafruit_NeoPixel leds = Adafruit_NeoPixel(PIXELS, LED_INPUT_DATA, NEO_GRB + NEO_KHZ800); // led treiber definitionen



void setup () {
  WiFi.begin(ssid, password); //aufbauen der WLAN-Verbindung
  Serial.begin(115200); //Serielle Schnittstelle initialisieren zur Textausgabe
  Wire.begin();   // I2C  initialisieren


  pinMode(LED_INPUT_DATA, OUTPUT); //festlegen des Datenpins der NeoPixel
  leds.begin();						//leds initialisieren
  leds.setBrightness(BRIGHTNESS); // leds auf oben definierten Hellgikeitswert setzen



}

void loop () {
  timeClient.update();  //Zeitverwaltung via NTP
  setTime(timeClient.getEpochTime()); //NTP-Zeit übergeben, zur verwaltung in einem human-readable-format
  Serial.print("Tag im Monat: ");
  Serial.println(day());

  for(int i=0;i<=(day()-1);i++){	//leds pixelweise einschalten bis jeweiliger Tag erreicht ist
    Serial.print("loop hochzählen: ");
    Serial.println(i); //ausgabe der nummer der aktuellen led
    leds.setPixelColor(i, leds.Color(150,0,0)); // reines rot.
    leds.show(); //der zuletzt auf leds geschriebene zustand wird angezeigt
    delay(300);	//Wartezeit der Animation


  }
  leds.show(); //anzeigen bei austritt aus der schleife (sollte nicht notwendig sein)


  Serial.print("Zeige aktuellen Tag im Monat: ");
  Serial.println(day()); //ausgabe des tages im monat
  Serial.println("Warte...");
  delay(5000); //zeitdauer in der alle leds des jeweiligen tages an sind


  for(int l=(day()-1); l>=0 ;l--){	//day-1, denn die NeoPixelbeginnen bei 0; leds gehen nacheinander aus, ausgehend von tagesmaxium bis zur 0
    Serial.print("loop runterzählen: ");
    Serial.println(l); //ausgabe des tages im monat

    leds.setPixelColor(l, leds.Color(0,0,0)); //Schwarzwert
    leds.show(); //der zuletzt auf leds geschriebene zustand wird angezeigt
    delay(300);	//Dauer der Animation
  }
  leds.show();	//anzeigen bei austritt aus der schleife (sollte nicht notwendig sein)

  Serial.println("Warte...");
  delay(1000); //zeitdauer in der alle leds aus sind

}
